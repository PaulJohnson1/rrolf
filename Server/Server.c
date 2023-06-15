#include <Server/Server.h>

#include <assert.h>
#include <sys/time.h>
#include <unistd.h>

#include <libwebsockets.h>

#include <Shared/Component/Physical.h>
#include <Shared/Bitset.h>
#include <Shared/Crypto.h>
#include <Shared/pb.h>
#include <Shared/Utilities.h>
#include <Shared/Vector.h>
#include <Server/Client.h>
#include <Server/Simulation.h>

#include <libwebsockets.h>

#ifndef NDEBUG
#define MESSAGE_BUFFER_SIZE (32 * 1024 * 1024)
#else
#define MESSAGE_BUFFER_SIZE (1024 * 1024)
#endif
static uint8_t lws_message_data[MESSAGE_BUFFER_SIZE];
static uint8_t *outgoing_message = lws_message_data + LWS_PRE;

void rr_server_client_create_player_info(struct rr_server_client *this)
{
    puts("creating player info");
    this->player_info = rr_simulation_add_player_info(&this->server->simulation, rr_simulation_alloc_entity(&this->server->simulation));
    rr_component_player_info_set_slot_count(this->player_info, 10);
    // rr_server_client_create_flower(this);
}

void rr_server_client_free(struct rr_server_client *this)
{
    puts("client disconnected");
    if (this->player_info->flower_id != RR_NULL_ENTITY)
        rr_simulation_request_entity_deletion(&this->server->simulation, this->player_info->flower_id);
    rr_simulation_request_entity_deletion(&this->server->simulation, this->player_info->parent_id);
}

void rr_server_client_encrypt_message(struct rr_server_client *this, uint8_t *start, uint64_t size)
{
    this->clientbound_encryption_key = rr_get_hash(this->clientbound_encryption_key);
    rr_encrypt(start, size, this->clientbound_encryption_key);
}

void rr_server_client_write_message(struct rr_server_client *this, uint8_t *message_start, uint64_t size)
{
    lws_write(this->socket_handle, message_start, size, LWS_WRITE_BINARY);
}

void rr_server_client_broadcast_update(struct rr_server_client *this)
{
    struct rr_server *server = this->server;
    // 128 KB (not needed but just in case)
    struct proto_bug encoder;
    proto_bug_init(&encoder, outgoing_message);
    proto_bug_write_uint8(&encoder, 0, "header");
    rr_simulation_write_binary(&server->simulation, &encoder, this->player_info);
    rr_server_client_encrypt_message(this, encoder.start, encoder.current - encoder.start);
    rr_server_client_write_message(this, encoder.start, encoder.current - encoder.start);
}

void rr_server_client_tick(struct rr_server_client *this)
{
    if (this->server->simulation_active)
    {
        if (rr_simulation_has_entity(&this->server->simulation, this->player_info->flower_id))
        {
            struct rr_component_physical *physical = rr_simulation_get_physical(&this->server->simulation, this->player_info->flower_id);
            rr_component_player_info_set_camera_x(this->player_info, physical->x);
            rr_component_player_info_set_camera_y(this->player_info, physical->y);
        }
        rr_server_client_broadcast_update(this);
    }
    else
    {
        // 128 KB (not needed but just in case)
        struct proto_bug encoder;
        proto_bug_init(&encoder, outgoing_message);
        proto_bug_write_uint8(&encoder, 69, "header");
        for (uint32_t i = 0; i < 4; ++i)
            proto_bug_write_uint8(&encoder, rr_bitset_get(&this->server->clients_in_use[0], i), "bitbit");
        rr_server_client_encrypt_message(this, encoder.start, encoder.current - encoder.start);
        rr_server_client_write_message(this, encoder.start, encoder.current - encoder.start);
        //send squad info
    }
}

int rr_server_lws_callback_function(struct lws *socket, enum lws_callback_reasons reason, void *context, void *packet, size_t size)
{
    struct rr_server *this = (struct rr_server *)lws_context_user(lws_get_context(socket));
    switch (reason)
    {
    case LWS_CALLBACK_ESTABLISHED:
    {
        if (this->simulation_active)
            return 0;
        for (uint64_t i = 0; i < RR_MAX_CLIENT_COUNT; i++)
            if (!rr_bitset_get_bit(this->clients_in_use, i))
            {
                rr_bitset_set(this->clients_in_use, i);
                rr_server_client_init(this->clients + i);
                this->clients[i].server = this;
                this->clients[i].file_descriptor = lws_get_socket_fd(socket);
                this->clients[i].socket_handle = socket;

                // send encryption key
                struct proto_bug encryption_key_encoder;
                proto_bug_init(&encryption_key_encoder, outgoing_message);
                proto_bug_write_uint64(&encryption_key_encoder, this->clients[i].requested_verification, "verification");
                proto_bug_write_uint32(&encryption_key_encoder, rr_get_rand(), "useless bytes");
                proto_bug_write_uint64(&encryption_key_encoder, this->clients[i].clientbound_encryption_key, "c encryption key");
                proto_bug_write_uint64(&encryption_key_encoder, this->clients[i].serverbound_encryption_key, "s encryption key");
                rr_encrypt(outgoing_message, 1024, 21094093777837637ull);
                rr_encrypt(outgoing_message, 8, 1);
                rr_encrypt(outgoing_message, 1024, 59731158950470853ull);
                rr_encrypt(outgoing_message, 1024, 64709235936361169ull);
                rr_encrypt(outgoing_message, 1024, 59013169977270713ull);
                rr_server_client_write_message(this->clients + i, outgoing_message, 1024);
                return 0;
            }
        RR_UNREACHABLE("max clients reached");
    }
    case LWS_CALLBACK_CLOSED:
    {
        int file_descriptor = lws_get_socket_fd(socket);
        for (uint64_t i = 0; i < RR_MAX_CLIENT_COUNT; i++)
            if (rr_bitset_get(this->clients_in_use, i))
            {
                if (this->clients[i].file_descriptor == file_descriptor)
                {
                    rr_bitset_unset(this->clients_in_use, i);
                    rr_server_client_free(this->clients + i);
                    return 0;
                }
            }
        RR_UNREACHABLE("cloudn't remove client");
    }

    case LWS_CALLBACK_RECEIVE:
    {
        if (size == 0)
            break;
        struct rr_server_client *client = NULL;
        uint64_t i = 0;
        for (; i < RR_MAX_CLIENT_COUNT; i++)
        {
            if (!rr_bitset_get(this->clients_in_use, i))
                continue;
            if (this->clients[i].file_descriptor == lws_get_socket_fd(socket))
            {
                client = &this->clients[i];
                break;
            }
        }
        if (client == NULL)
        {
            puts("null client????");
            return 0;
        }

        rr_decrypt(packet, size, client->serverbound_encryption_key);
        client->serverbound_encryption_key = rr_get_hash(rr_get_hash(client->serverbound_encryption_key));

        struct proto_bug encoder;
        proto_bug_init(&encoder, packet);
        
        if (!client->received_first_packet)
        {
            client->received_first_packet = 1;
            if (size < 16)
            {
                puts("skid gaming1");
                lws_close_reason(socket, LWS_CLOSE_STATUS_MESSAGE_TOO_LARGE /* troll */, (uint8_t *)"script kiddie1", sizeof "script kiddie");
                return 1;
            }

            proto_bug_read_uint64(&encoder, "useless bytes");
            uint64_t received_verification = proto_bug_read_uint64(&encoder, "verification");
            if (received_verification != client->requested_verification)
            {
                puts("skid gaming1");
                lws_close_reason(socket, LWS_CLOSE_STATUS_MESSAGE_TOO_LARGE, (uint8_t *)"script kiddie2", sizeof "script kiddie");
                return 1;
            }

            puts("socket verified");
            client->verified = 1;

            return 0;
        }
        switch (proto_bug_read_uint8(&encoder, "header"))
        {
        case 0:
        {
            if (size < 3)
            {
                puts("unsafe input packet with length < 3");
                return 0;
            }
            proto_bug_read_uint8(&encoder, "movement type");
            uint64_t movementFlags = proto_bug_read_uint8(&encoder, "movement kb flags");
            float x = 0;
            float y = 0;

            if (movementFlags & 1)
                y--;
            if (movementFlags & 2)
                x--;
            if (movementFlags & 4)
                y++;
            if (movementFlags & 8)
                x++;
            if (client->player_info == NULL)
                break;
            if (client->player_info->flower_id == 0)
                break;
            if (x != 0 && y != 0)
            {
                // 1 / sqrt(2)
                x *= 0.70710678118;
                y *= 0.70710678118;
            }
            struct rr_component_physical *physical = rr_simulation_get_physical(&this->simulation, client->player_info->flower_id);
            rr_vector_set(&physical->acceleration, x, y);

            client->player_info->input = movementFlags >> 4;
            break;
        }
        case 1:
        {
            if (size < 1)
            {
                puts("someone sent a spawn packet with size < 1");
                return 0;
            }
            rr_server_client_create_flower(client);
            // ctor player
            break;
        }
        case 2:
        {
            if (size < 2)
            {
                puts("someone sent a petal switch packet with size < 2");
                return 0;
            }
            if (client->player_info->flower_id == RR_NULL_ENTITY)
                return 0;
            uint8_t pos = proto_bug_read_uint8(&encoder, "petal switch");
            struct rr_component_player_info_petal_slot *slot = &client->player_info->slots[pos];
            struct rr_component_player_info_petal_slot *s_slot = &client->player_info->secondary_slots[pos];
            for (uint32_t i = 0; i < slot->count; ++i)
            {
                EntityIdx id = slot->petals[i].simulation_id;
                if (id != RR_NULL_ENTITY && rr_simulation_has_entity(&this->simulation, id))
                {
                    struct rr_component_physical *physical = rr_simulation_get_physical(&this->simulation, id);
                    struct rr_component_health *health = rr_simulation_get_health(&this->simulation, id);

                    rr_component_health_set_health(health, 0);
                    rr_component_physical_set_server_animation_tick(physical, 6);
                }

            }
            uint8_t temp = slot->id;
            slot->id = s_slot->id;
            s_slot->id = temp;
            temp = slot->rarity;
            slot->rarity = s_slot->rarity;
            s_slot->rarity = temp;

            slot->count = RR_PETAL_DATA[slot->id].count[slot->rarity];
            for (uint32_t i = 0; i < slot->count; ++i)
                slot->petals[i].cooldown_ticks = RR_PETAL_DATA[slot->id].cooldown;
        }
        }
    }
    default:
        break;
    }
    return 0;
}

void rr_server_init(struct rr_server *this)
{
    printf("server size: %lu\n", sizeof *this);
    memset(this, 0, sizeof *this);
    rr_simulation_init(&this->simulation);
}

void rr_server_free(struct rr_server *this)
{
    lws_context_destroy(this->server);
}

static void rr_simulation_tick_entity_resetter_function(EntityIdx entity, void *captures)
{
    struct rr_simulation *this = captures;
#define XX(COMPONENT, ID)                            \
    if (rr_simulation_has_##COMPONENT(this, entity)) \
        rr_simulation_get_##COMPONENT(this, entity)->protocol_state = 0;
    RR_FOR_EACH_COMPONENT
#undef XX
    if (rr_simulation_has_physical(this, entity))
        rr_simulation_get_physical(this, entity)->ticked_animation = 0;
    if (rr_simulation_has_drop(this, entity))
        memset(&rr_simulation_get_drop(this, entity)->picked_up_this_tick, 0, sizeof rr_simulation_get_drop(this, entity)->picked_up_this_tick);
}

void rr_server_tick(struct rr_server *this)
{
    if (this->simulation_active)
        rr_simulation_tick(&this->simulation);
    uint32_t client_count = 0;
    for (uint64_t i = 0; i < RR_MAX_CLIENT_COUNT; i++)
        if (rr_bitset_get(this->clients_in_use, i))
        {
            rr_server_client_tick(this->clients + i);
            ++client_count;
        }
    if (this->simulation_active)
        rr_simulation_for_each_entity(&this->simulation, &this->simulation, rr_simulation_tick_entity_resetter_function);
    else if (client_count == 2)
    {
        this->simulation_active = 1;
        for (uint64_t i = 0; i < RR_MAX_CLIENT_COUNT; i++)
        if (rr_bitset_get(this->clients_in_use, i))
        {
            rr_server_client_create_player_info(this->clients + i);
            rr_server_client_create_flower(this->clients + i);
        }
    }
}

void rr_server_run(struct rr_server *this)
{
    //this->simulation_active = 1;
    struct lws_context_creation_info info;
    memset(&info, 0, sizeof(info));

    struct lws_protocols protocols[2] = {
        {"g", rr_server_lws_callback_function, 0, 0},
        {NULL, NULL, 0, 0}};
    info.port = 8000;
    info.protocols = &protocols[0];
    info.gid = -1;
    info.uid = -1;
    info.user = this;
    info.pt_serv_buf_size = MESSAGE_BUFFER_SIZE;

    this->server = lws_create_context(&info);
    assert(this->server);

    while (1)
    {
        struct timeval start;
        struct timeval end;

        gettimeofday(&start, NULL); // gettimeofday actually starts from unix timestamp 0 (goofy)
        lws_service(this->server, -1);
        rr_server_tick(this);
        gettimeofday(&end, NULL);

        long elapsed_time = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
        //if (elapsed_time > 100)
            //printf("tick took %ld microseconds\n", elapsed_time);
        long to_sleep = 40000 - elapsed_time;
        usleep(to_sleep > 0 ? to_sleep : 0);
    }
}
