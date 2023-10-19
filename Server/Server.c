#include <Server/Server.h>

#include <assert.h>
#include <math.h>
#include <pthread.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

#include <libwebsockets.h>

#include <Server/Client.h>
#include <Server/EntityAllocation.h>
#include <Server/Logs.h>
#include <Server/Simulation.h>
#include <Server/UpdateProtocol.h>
#include <Server/Waves.h>
#include <Shared/Api.h>
#include <Shared/Binary.h>
#include <Shared/Bitset.h>
#include <Shared/Component/Physical.h>
#include <Shared/Crypto.h>
#include <Shared/Rivet.h>
#include <Shared/Utilities.h>
#include <Shared/Vector.h>
#include <Shared/cJSON.h>
#include <Shared/pb.h>

uint8_t lws_message_data[MESSAGE_BUFFER_SIZE];
uint8_t *outgoing_message = lws_message_data + LWS_PRE;

struct connected_captures
{
    char *token;
    struct rr_server_client *client;
};

static void *rivet_connected_endpoint(void *_captures)
{
    struct connected_captures *captures = _captures;
    struct rr_server_client *this = captures->client;
    char *token = captures->token;
    if (!rr_rivet_players_connected(getenv("RIVET_TOKEN"), token))
    {
        if (strcmp(token, this->rivet_account.token) == 0 && this->in_use)
            this->pending_kick = 1;
    }
    free(token);
    free(captures);
    return NULL;
}

static void *rivet_disconnected_endpoint(void *_captures)
{
    char *token = _captures;
    rr_rivet_players_disconnected(getenv("RIVET_TOKEN"), token);
    free(_captures);
    return NULL;
}

static void rr_server_client_create_player_info(struct rr_server *server, struct rr_server_client *client)
{
    puts("creating player info");
    struct rr_component_player_info *player_info = client->player_info =
        rr_simulation_add_player_info(&server->simulation, rr_simulation_alloc_entity(&server->simulation));
    player_info->squad = client->squad;
    struct rr_squad_member *member = player_info->squad_member = rr_squad_get_client_slot(server, client);
    rr_component_player_info_set_squad_pos(player_info, client->squad_pos);
    rr_component_player_info_set_slot_count(player_info, 10);
    player_info->level = level_from_xp(client->experience);
    rr_component_player_info_set_slot_count(client->player_info, RR_SLOT_COUNT_FROM_LEVEL(player_info->level));
    struct rr_component_arena *arena = rr_simulation_get_arena(&server->simulation, 1);
    for (uint64_t i = 0; i < player_info->slot_count; ++i)
    {
        uint8_t id = member->loadout[i].id;
        uint8_t rarity = member->loadout[i].rarity;
        player_info->slots[i].id = id;
        player_info->slots[i].rarity = rarity;
        player_info->slots[i].count = RR_PETAL_DATA[id].count[rarity];

        id = member->loadout[i + 10].id;
        rarity = member->loadout[i + 10].rarity;
        player_info->secondary_slots[i].id = id;
        player_info->secondary_slots[i].rarity = rarity;
    }
}

void rr_server_client_free(struct rr_server_client *this)
{
    // WARNING: ONLY TO BE USED WHEN CLIENT DISCONNECTS
    if (this->player_info != NULL)
        rr_simulation_request_entity_deletion(&this->server->simulation, this->player_info->parent_id);
    rr_client_leave_squad(this->server, this);
    puts("<rr_server::client_disconnect>");
}

static void write_animation_function(struct rr_simulation *simulation, struct proto_bug *encoder, struct rr_server_client *client, uint32_t pos)
{
    struct rr_simulation_animation *animation = &simulation->animations[pos];
    if (animation->type == rr_animation_type_damagenumber && animation->squad != client->squad)
        return;
    proto_bug_write_uint8(encoder, 1, "continue");
    proto_bug_write_uint8(encoder, animation->type, "ani type");
    switch (animation->type)
    {
    case rr_animation_type_lightningbolt:
        proto_bug_write_uint8(encoder, animation->length, "ani length");
        for (uint32_t i = 0; i < animation->length; ++i)
        {
            proto_bug_write_float32(encoder, animation->points[i].x, "ani x");
            proto_bug_write_float32(encoder, animation->points[i].y, "ani y");
        }
        break;
    case rr_animation_type_damagenumber:
        proto_bug_write_float32(encoder, animation->x, "ani x");
        proto_bug_write_float32(encoder, animation->y, "ani y");
        proto_bug_write_varuint(encoder, animation->damage, "damage");
        break;
    case rr_animation_type_chat:
        proto_bug_write_string(encoder, animation->name, 64, "name");
        proto_bug_write_string(encoder, animation->message, 64, "chat");
        break;
    }
}

void rr_server_client_broadcast_update(struct rr_server_client *this)
{
    struct rr_server *server = this->server;
    struct rr_simulation *simulation = &server->simulation;
    struct proto_bug encoder;
    proto_bug_init(&encoder, outgoing_message);
    proto_bug_write_uint8(&encoder, rr_clientbound_update, "header");

    struct rr_squad *squad = rr_client_get_squad(server, this);
    for (uint32_t i = 0; i < RR_SQUAD_MEMBER_COUNT; ++i)
    {
        if (squad->members[i].in_use == 0)
        {
            proto_bug_write_uint8(&encoder, 0, "bitbit");
            continue;
        }
        struct rr_squad_member *member = &squad->members[i];
        proto_bug_write_uint8(&encoder, 1, "bitbit");
        proto_bug_write_uint8(&encoder, member->playing, "ready");
        proto_bug_write_uint8(&encoder, member->is_dev, "is_dev");
        proto_bug_write_string(&encoder, member->nickname, 16, "nickname");
        for (uint8_t j = 0; j < 20; ++j)
        {
            proto_bug_write_uint8(&encoder, member->loadout[j].id, "id");
            proto_bug_write_uint8(&encoder, member->loadout[j].rarity, "rar");
        }
    }
    proto_bug_write_uint8(&encoder, this->squad_pos, "sqpos");
    proto_bug_write_uint8(&encoder, squad->private, "private");
    proto_bug_write_uint8(&encoder, RR_GLOBAL_BIOME, "biome");
    char joined_code[16];
    sprintf(joined_code, "%s-%s", server->server_alias, squad->squad_code);
    proto_bug_write_string(&encoder, joined_code, 16, "squad code");
    proto_bug_write_uint8(&encoder, this->player_info != NULL, "in game");
    if (this->player_info != NULL)
        rr_simulation_write_binary(&server->simulation, &encoder, this->player_info);
    rr_server_client_write_message(this, encoder.start, encoder.current - encoder.start);
    proto_bug_init(&encoder, outgoing_message);
    proto_bug_write_uint8(&encoder, rr_clientbound_animation_update, "header");
    for (uint32_t i = 0; i < simulation->animation_length; ++i)
        write_animation_function(simulation, &encoder, this, i);
    proto_bug_write_uint8(&encoder, 0, "continue");
    rr_server_client_write_message(this, encoder.start, encoder.current - encoder.start);
}

static void delete_entity_function(EntityIdx entity, void *_captures)
{
    if (rr_simulation_has_entity(_captures, entity))
        rr_simulation_request_entity_deletion(_captures, entity);
}

void rr_server_init(struct rr_server *this)
{
    // printf("server size: %lu\n", sizeof *this);
    memset(this, 0, sizeof *this);
#ifndef RIVET_BUILD
    // RR_GLOBAL_BIOME = rr_biome_id_garden;
#endif
    rr_static_data_init();
    rr_simulation_init(&this->simulation);
    for (uint32_t i = 0; i < RR_SQUAD_COUNT; ++i)
        rr_squad_init(&this->squads[i], this, i);
}

void rr_server_free(struct rr_server *this) { lws_context_destroy(this->server); }

static void rr_simulation_tick_entity_resetter_function(EntityIdx entity, void *captures)
{
    struct rr_simulation *this = captures;
#define XX(COMPONENT, ID)                                                                                                                                      \
    if (rr_simulation_has_##COMPONENT(this, entity))                                                                                                           \
        rr_simulation_get_##COMPONENT(this, entity)->protocol_state = 0;
    RR_FOR_EACH_COMPONENT
#undef XX
}

static int handle_lws_event(struct rr_server *this, struct lws *ws, enum lws_callback_reasons reason, uint8_t *packet, size_t size)
{
    switch (reason)
    {
    case LWS_CALLBACK_ESTABLISHED:
    {
        if (!this->api_ws_ready)
        {
            lws_close_reason(ws, LWS_CLOSE_STATUS_GOINGAWAY, (uint8_t *)"api ws not ready", sizeof "api ws not ready" - 1);
            return -1;
        }
        for (uint64_t i = 0; i < RR_MAX_CLIENT_COUNT; i++)
            if (!rr_bitset_get_bit(this->clients_in_use, i))
            {
                rr_bitset_set(this->clients_in_use, i);
                rr_server_client_init(this->clients + i);
                this->clients[i].server = this;
                this->clients[i].socket_handle = ws;
                this->clients[i].in_use = 1;
                lws_set_opaque_user_data(ws, this->clients + i);
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

        lws_close_reason(ws, LWS_CLOSE_STATUS_GOINGAWAY, (uint8_t *)"too many active clients", sizeof "to many active clients" - 1);
        return -1;
    }
    case LWS_CALLBACK_CLOSED:
    {
        struct rr_server_client *client = lws_get_opaque_user_data(ws);
        if (client != NULL)
        {
            uint64_t i = (client - this->clients);
            rr_bitset_unset(this->clients_in_use, i);
            client->in_use = 0;
            client->socket_handle = NULL;
            if (client->received_first_packet == 0)
                return 0;
#ifdef RIVET_BUILD
            /*
                        rr_rivet_players_disconnected(
                            getenv("RIVET_TOKEN"),
                            this->clients[i].rivet_account.token);
                            */
            char *token = malloc(500);
            strncpy(token, client->rivet_account.token, 500);
            pthread_t thread;
            pthread_create(&thread, NULL, rivet_disconnected_endpoint, token);
            pthread_detach(thread);
#endif
            struct rr_binary_encoder encoder;
            rr_binary_encoder_init(&encoder, outgoing_message);
            rr_binary_encoder_write_uint8(&encoder, 1);
            rr_binary_encoder_write_nt_string(&encoder, this->clients[i].rivet_account.uuid);
            rr_binary_encoder_write_uint8(&encoder, i);
            lws_write(this->api_client, encoder.start, encoder.at - encoder.start, LWS_WRITE_BINARY);
            rr_server_client_free(this->clients + i);
            char log[100] = {"ip: `"};
            strcat(log, this->clients[i].ip_address);
            strcat(log, "`");
            return 0;
        }
        puts("client joined but instakicked");
        break;
    }
    case LWS_CALLBACK_SERVER_WRITEABLE:
    {
        struct rr_server_client *client = lws_get_opaque_user_data(ws);
        if (client == NULL)
            return -1;
        if (client->pending_kick)
        {
            struct rr_server_client_message *message = client->message_root;
            while (message != NULL)
            {
                struct rr_server_client_message *tmp = message->next;
                free(message->packet);
                free(message);
                message = tmp;
            }
            lws_close_reason(ws, LWS_CLOSE_STATUS_GOINGAWAY, (uint8_t *)"kicked for unspecified reason", sizeof "kicked for unspecified reason" - 1);
            return -1;
        }
        struct rr_server_client_message *message = client->message_root;
        while (message != NULL)
        {
            lws_write(ws, message->packet + LWS_PRE, message->len, LWS_WRITE_BINARY);
            struct rr_server_client_message *tmp = message->next;
            free(message->packet);
            free(message);
            message = tmp;
        }
        client->message_at = client->message_root = NULL;
        break;
    }
    case LWS_CALLBACK_RECEIVE:
    {
        struct rr_server_client *client = lws_get_opaque_user_data(ws);
        uint64_t i = (client - this->clients);
        rr_decrypt(packet, size, client->serverbound_encryption_key);
        client->serverbound_encryption_key = rr_get_hash(rr_get_hash(client->serverbound_encryption_key));
        struct proto_bug encoder;
        proto_bug_init(&encoder, packet);
        proto_bug_set_bound(&encoder, packet + size);
        client->ticks_to_afk_kick = 0;
        if (!client->received_first_packet)
        {
            client->received_first_packet = 1;

            proto_bug_read_uint64(&encoder, "useless bytes");
            uint64_t received_verification = proto_bug_read_uint64(&encoder, "verification");
            if (received_verification != client->requested_verification)
            {
                printf("%lu %lu\n", client->requested_verification, received_verification);
                fputs("invalid verification\n", stderr);
                lws_close_reason(ws, LWS_CLOSE_STATUS_GOINGAWAY, (uint8_t *)"invalid v", sizeof "invalid v" - 1);
                return -1;
            }

            memset(&client->rivet_account, 0, sizeof(struct rr_rivet_account));
            // Read rivet token
            proto_bug_read_string(&encoder, client->rivet_account.token, 300, "rivet token");
            // Read uuid
            proto_bug_read_string(&encoder, client->rivet_account.uuid, 100, "rivet uuid");

#ifdef RIVET_BUILD
            for (uint32_t j = 0; j < RR_MAX_CLIENT_COUNT; ++j)
            {
                if (!rr_bitset_get(this->clients_in_use, j))
                    continue;
                if (i == j)
                    continue;
                if (strcmp(client->rivet_account.uuid, this->clients[j].rivet_account.uuid) == 0)
                {
                    fputs("skid multibox\n", stderr);
                    lws_close_reason(ws, LWS_CLOSE_STATUS_GOINGAWAY, (uint8_t *)"skid multibox", sizeof "skid multibox");
                    return -1;
                }
            }
#endif
            if (proto_bug_read_varuint(&encoder, "dev_flag") == 49453864343)
                client->dev = 1;

#ifdef RIVET_BUILD
            /*
            if (!rr_rivet_players_connected(
                    getenv("RIVET_TOKEN"),
                    client->rivet_account.token))
            {
                fputs("rivet error\n", stderr);
                lws_close_reason(ws, LWS_CLOSE_STATUS_GOINGAWAY,
                                (uint8_t *)"rivet error",
                                sizeof "rivet error");
                return -1;
            }
            */
            struct connected_captures *captures = malloc(sizeof *captures);
            captures->client = client;
            captures->token = malloc(500);
            strncpy(captures->token, client->rivet_account.token, 500);
            pthread_t thread;
            pthread_create(&thread, NULL, rivet_connected_endpoint, captures);
            pthread_detach(thread);

#endif
            printf("<rr_server::socket_verified::%s>\n", client->rivet_account.uuid);
            struct rr_binary_encoder encoder;
            rr_binary_encoder_init(&encoder, outgoing_message);
            rr_binary_encoder_write_uint8(&encoder, 0);
            rr_binary_encoder_write_nt_string(&encoder, client->rivet_account.uuid);
            rr_binary_encoder_write_uint8(&encoder, i);
            lws_write(this->api_client, encoder.start, encoder.at - encoder.start, LWS_WRITE_BINARY);
            // rr_client_join_squad(this, client, 0);
            return 0;
        }
        if (!client->verified)
            break;
        switch (proto_bug_read_uint8(&encoder, "header"))
        {
        case rr_serverbound_input:
        {
            if (client->player_info == NULL)
                break;
            if (client->player_info->flower_id == RR_NULL_ENTITY)
                break;
            uint8_t movementFlags = proto_bug_read_uint8(&encoder, "movement kb flags");
            float x = 0;
            float y = 0;

            if ((movementFlags & 64) == 0)
            {
                y -= (movementFlags & 1) >> 0;
                x -= (movementFlags & 2) >> 1;
                y += (movementFlags & 4) >> 2;
                x += (movementFlags & 8) >> 3;
                if (x || y)
                {
                    float mag_1 = RR_PLAYER_SPEED / sqrtf(x * x + y * y);
                    x *= mag_1;
                    y *= mag_1;
                }
            }
            else
            {
                x = proto_bug_read_float32(&encoder, "mouse x");
                y = proto_bug_read_float32(&encoder, "mouse y");
                if ((x != 0 || y != 0) && fabsf(x) < 10000 && fabsf(y) < 10000)
                {
                    float mag_1 = sqrtf(x * x + y * y);
                    float scale = (client->dev ? 30 : RR_PLAYER_SPEED) * rr_fclamp((mag_1 - 25) / 50, 0, 1);
                    x *= scale / mag_1;
                    y *= scale / mag_1;
                }
            }
            if ((x != 0 || y != 0) && fabsf(x) < 10000 && fabsf(y) < 10000)
            {
                client->player_accel_x = x;
                client->player_accel_y = y;
            }
            else
            {
                client->player_accel_x = 0;
                client->player_accel_y = 0;
            }

            client->player_info->input = (movementFlags >> 4) & 3;
            break;
        }
        case rr_serverbound_petal_switch:
        {
            if (client->player_info->flower_id == RR_NULL_ENTITY)
                return 0;
            uint8_t pos = proto_bug_read_uint8(&encoder, "petal switch");
            while (pos != 0 && pos <= 10 && encoder.current - encoder.start <= size)
            {
                rr_component_player_info_petal_swap(client->player_info, &this->simulation, pos - 1);
                pos = proto_bug_read_uint8(&encoder, "petal switch");
            }
            break;
        }
        case rr_serverbound_squad_join:
        {
            if (client->ticks_to_next_squad_action > 0)
                break;
            client->ticks_to_next_squad_action = 10;
            uint8_t type = proto_bug_read_uint8(&encoder, "join type");
            if (type > 3)
                break;
            if (type == 3)
            {
                if (client->in_squad)
                {
                    rr_client_leave_squad(this, client);
                    struct proto_bug encoder;
                    proto_bug_init(&encoder, outgoing_message);
                    proto_bug_write_uint8(&encoder, rr_clientbound_squad_leave, "header");
                    rr_server_client_write_message(client, encoder.start, encoder.current - encoder.start);
                }
                break;
            }
            rr_client_leave_squad(this, client);
            uint8_t squad = RR_ERROR_CODE_INVALID_SQUAD;
            if (type == 2)
                squad = rr_client_create_squad(this, client);
            else if (type == 1)
            {
                char link[16] = {0};
                proto_bug_read_string(&encoder, link, 7, "connect link");
                squad = rr_client_join_squad_with_code(this, link);
            }
            else if (type == 0)
                squad = rr_client_find_squad(this, client);
            if (squad == RR_ERROR_CODE_INVALID_SQUAD)
            {
                struct proto_bug failure;
                proto_bug_init(&failure, outgoing_message);
                proto_bug_write_uint8(&failure, rr_clientbound_squad_fail, "header");
                proto_bug_write_uint8(&failure, 0, "fail type");
                rr_server_client_write_message(client, failure.start, failure.current - failure.start);
                client->in_squad = 0;
                break;
            }
            if (squad == RR_ERROR_CODE_FULL_SQUAD)
            {
                struct proto_bug failure;
                proto_bug_init(&failure, outgoing_message);
                proto_bug_write_uint8(&failure, rr_clientbound_squad_fail, "header");
                proto_bug_write_uint8(&failure, 1, "fail type");
                rr_server_client_write_message(client, failure.start, failure.current - failure.start);
                client->in_squad = 0;
                break;
            }
            rr_client_join_squad(this, client, squad);
            break;
        }
        case rr_serverbound_squad_ready:
        {
            if (client->ticks_to_next_squad_action > 0)
                break;
            client->ticks_to_next_squad_action = 10;
            if (!client->in_squad)
            {
                uint8_t squad = rr_client_find_squad(this, client);
                if (squad != RR_ERROR_CODE_FULL_SQUAD && squad != RR_ERROR_CODE_INVALID_SQUAD)
                    rr_client_join_squad(this, client, squad);
            }
            if (client->in_squad)
            {
                if (rr_squad_get_client_slot(this, client)->playing == 0)
                {
                    if (client->player_info != NULL)
                    {
                        rr_simulation_request_entity_deletion(&this->simulation, client->player_info->parent_id);
                        client->player_info = NULL;
                    }
                    rr_squad_get_client_slot(this, client)->playing = 1;
                    rr_server_client_create_player_info(this, client);
                    rr_server_client_create_flower(client);
                }
                else
                {
                    if (client->player_info != NULL)
                    {
                        rr_simulation_request_entity_deletion(&this->simulation, client->player_info->parent_id);
                        client->player_info = NULL;
                        rr_squad_get_client_slot(this, client)->playing = 0;
                    }
                }
            }
            break;
        }
        case rr_serverbound_squad_update:
        {
            if (!client->in_squad)
                return 0;
            proto_bug_read_string(&encoder, rr_squad_get_client_slot(this, client)->nickname, 16, "nickname");
            uint8_t loadout_count = proto_bug_read_uint8(&encoder, "loadout count");

            if (loadout_count > 10)
                break;
            struct rr_squad_member *member = rr_squad_get_client_slot(this, client);
            if (member == NULL)
                break;
            uint32_t temp_inv[rr_petal_id_max][rr_rarity_id_max];

            memcpy(temp_inv, client->inventory, sizeof client->inventory);
            for (uint8_t i = 0; i < loadout_count; i++)
            {
                uint8_t id = proto_bug_read_uint8(&encoder, "id");
                uint8_t rarity = proto_bug_read_uint8(&encoder, "rarity");
                if (id >= rr_petal_id_max)
                    break;
                if (rarity >= rr_rarity_id_max)
                    break;
                member->loadout[i].rarity = rarity;
                member->loadout[i].id = id;
                if (id && temp_inv[id][rarity]-- == 0)
                {
                    memset(member->loadout, 0, sizeof member->loadout);
                    break;
                }
                id = proto_bug_read_uint8(&encoder, "id");
                rarity = proto_bug_read_uint8(&encoder, "rarity");
                if (id >= rr_petal_id_max)
                    break;
                if (rarity >= rr_rarity_id_max)
                    break;
                member->loadout[i + 10].rarity = rarity;
                member->loadout[i + 10].id = id;
                if (id && temp_inv[id][rarity]-- == 0)
                {
                    memset(member->loadout, 0, sizeof member->loadout);
                    break;
                }
            }

            break;
        }
        case rr_serverbound_private_update:
        {
            if (client->in_squad)
                rr_client_get_squad(this, client)->private = 0;
            break;
        }
        case rr_serverbound_squad_kick:
        {
            if (!client->in_squad)
                break;
            if (client->squad_pos != 0 && !client->dev)
                break;
            uint8_t pos = proto_bug_read_uint8(&encoder, "kick pos");
            if (pos >= RR_SQUAD_MEMBER_COUNT)
                break;
            if (pos == client->squad_pos)
                break;
            struct rr_squad *squad = rr_client_get_squad(this, client);
            if (!squad->members[pos].in_use)
                break;
            struct rr_server_client *to_kick = squad->members[pos].client;
            if (to_kick == NULL)
                break;
            if (to_kick->dev)
                break;
            if (to_kick->player_info != NULL)
            {
                rr_simulation_request_entity_deletion(&this->simulation, to_kick->player_info->parent_id);
                to_kick->player_info = NULL;
            }
            rr_client_leave_squad(this, to_kick);
            struct proto_bug failure;
            proto_bug_init(&failure, outgoing_message);
            proto_bug_write_uint8(&failure, rr_clientbound_squad_fail, "header");
            proto_bug_write_uint8(&failure, 2, "fail type");
            rr_server_client_write_message(to_kick, failure.start, failure.current - failure.start);
            break;
        }
        case rr_serverbound_petals_craft:
        {
            uint8_t id = proto_bug_read_uint8(&encoder, "craft id");
            uint8_t rarity = proto_bug_read_uint8(&encoder, "craft rarity");
            uint32_t count = proto_bug_read_varuint(&encoder, "craft count");
            rr_server_client_craft_petal(client, id, rarity, count);
            break;
        }
        case rr_serverbound_chat:
        {
            if (!client->in_squad)
                break;
            if (!client->player_info)
                break;
            struct rr_simulation_animation *animation = &this->simulation.animations[this->simulation.animation_length++];
            proto_bug_read_string(&encoder, animation->message, 64, "chat");
            animation->type = rr_animation_type_chat;
            animation->squad = client->squad;
            strncpy(animation->name, rr_squad_get_client_slot(this, client)->nickname, 64);
            break;
        }
        default:
            break;
        }
        return 0;
    }
    default:
        return 0;
    }

    return 0;
}

static int api_lws_callback(struct lws *ws, enum lws_callback_reasons reason, void *user, void *packet, size_t size)
{
    struct rr_server *this = (struct rr_server *)lws_context_user(lws_get_context(ws));
    switch (reason)
    {
    case LWS_CALLBACK_CLIENT_ESTABLISHED:
    {
        puts("connected to api server");
        this->api_ws_ready = 1;
        char *lobby_id =
#ifdef RIVET_BUILD
            getenv("RIVET_LOBBY_ID");
#else
            "localhost";
#endif
        struct rr_binary_encoder encoder;
        rr_binary_encoder_init(&encoder, outgoing_message);
        rr_binary_encoder_write_uint8(&encoder, 101);
        rr_binary_encoder_write_nt_string(&encoder, lobby_id);
        lws_write(this->api_client, encoder.start, encoder.at - encoder.start, LWS_WRITE_BINARY);
    }
    break;
    case LWS_CALLBACK_CLIENT_RECEIVE:
    {
        // parse incoming client data
        struct rr_binary_encoder decoder;
        rr_binary_encoder_init(&decoder, packet);
        if (rr_binary_encoder_read_uint8(&decoder) != RR_API_SUCCESS)
            break;
        switch (rr_binary_encoder_read_uint8(&decoder))
        {
        case 0:
        {
            rr_binary_encoder_read_nt_string(&decoder, this->server_alias);
            break;
        }
        case 1:
        {
            printf("%lu\n", size);
            uint8_t pos = rr_binary_encoder_read_uint8(&decoder);
            if (pos >= 64)
            {
                printf("<rr_api::malformed_req::%d>\n", pos);
                break;
            }
            struct rr_server_client *client = &this->clients[pos];
            if (!client->in_use)
            {
                printf("<rr_api::client_nonexistent::%d>\n", pos);
                break;
            }
            if (!rr_server_client_read_from_api(client, &decoder))
            {
                printf("<rr_server::account_failed_read::%s>\n", client->rivet_account.uuid);
                client->pending_kick = 1;
                break;
            }
            client->verified = 1;
            struct proto_bug encoder;
            proto_bug_init(&encoder, outgoing_message);
            proto_bug_write_uint8(&encoder, rr_clientbound_squad_leave, "header");
            rr_server_client_write_message(client, encoder.start, encoder.current - encoder.start);
            rr_server_client_write_account(client);
            printf("<rr_server::account_read::%s>\n", client->rivet_account.uuid);
            break;
        }
        case 2:
        {
            uint8_t pos = rr_binary_encoder_read_uint8(&decoder);
            if (pos >= 64)
            {
                printf("<rr_api::malformed_req::%d>\n", pos);
                break;
            }
            struct rr_server_client *client = &this->clients[pos];
            if (!client->in_use)
            {
                printf("<rr_api::client_nonexistent::%d>\n", pos);
                break;
            }
            char uuid[sizeof client->rivet_account.uuid];
            rr_binary_encoder_read_nt_string(&decoder, uuid);
            if (strcmp(uuid, client->rivet_account.uuid) == 0)
            {
                printf("<rr_server::client_kick::%s>\n", uuid);
                client->pending_kick = 1;
            }
            break;
        }
        default:
            break;
        }
        break;
    }
    case LWS_CALLBACK_CLIENT_CLOSED:
        // uh oh
        fprintf(stderr, "api ws disconnected\n");
        abort();
        break;
    case LWS_CALLBACK_CLIENT_CONNECTION_ERROR:
        fprintf(stderr, "api ws refused to connect\n");
        abort();
        break;
    default:
        return 0;
    }
    return 0;
}

static int lws_callback(struct lws *ws, enum lws_callback_reasons reason, void *user, void *packet, size_t size)
{
    switch (reason)
    {
    case LWS_CALLBACK_ESTABLISHED:
    case LWS_CALLBACK_SERVER_WRITEABLE:
    case LWS_CALLBACK_RECEIVE:
    case LWS_CALLBACK_CLOSED:
        break;
    default:
        return 0;
    }
    // assert(pthread_mutex_lock(&mutex) == 0);

    struct rr_server *this = (struct rr_server *)lws_context_user(lws_get_context(ws));
    int close = handle_lws_event(this, ws, reason, packet, size);
    if (close)
        return close;
    // assert(pthread_mutex_unlock(&mutex) == 0);
    return 0;
}

void *thread_func(void *arg)
{
    struct rr_server *this = (struct rr_server *)arg;
    while (1)
    {
        lws_service(this->server, 0);
    }
    return 0;
}

static void lws_log(int level, char const *log) { printf("%d %s", level, log); }

static void server_tick(struct rr_server *this)
{
    if (!this->api_ws_ready)
        return;
    rr_simulation_tick(&this->simulation);
    for (uint64_t i = 0; i < RR_MAX_CLIENT_COUNT; ++i)
    {
        if (rr_bitset_get(this->clients_in_use, i))
        {
            struct rr_server_client *client = &this->clients[i];
            if (++client->ticks_to_afk_kick >= 180 * 25)
            {
                //printf("rr_server::afk_kick::%s>\n", client->rivet_account.uuid);
                //client->pending_kick = 1;
            }
            if (client->pending_kick)
                lws_callback_on_writable(client->socket_handle);
            if (client->ticks_to_next_squad_action > 0)
                --client->ticks_to_next_squad_action;
            if (!client->verified || !client->in_squad)
                continue;
            if (client->player_info != NULL)
            {
                if (rr_simulation_entity_alive(&this->simulation, client->player_info->flower_id))
                    rr_vector_set(&rr_simulation_get_physical(&this->simulation, client->player_info->flower_id)->acceleration, client->player_accel_x,
                                  client->player_accel_y);
                if (client->player_info->drops_this_tick_size > 0)
                {
                    for (uint32_t i = 0; i < client->player_info->drops_this_tick_size; ++i)
                    {
                        uint8_t id = client->player_info->drops_this_tick[i].id;
                        uint8_t rarity = client->player_info->drops_this_tick[i].rarity;
                        ++client->inventory[id][rarity];
                    }
                    rr_server_client_write_to_api(client);
                    rr_server_client_write_account(client);
                    client->player_info->drops_this_tick_size = 0;
                }
            }
            rr_server_client_broadcast_update(client); 
            
            if (!client->dev)
                continue;
            struct proto_bug encoder;
            proto_bug_init(&encoder, outgoing_message);
            proto_bug_write_uint8(&encoder, rr_clientbound_squad_dump, "header");
            for (uint32_t s = 0; s < RR_SQUAD_COUNT; ++s)
            {
                struct rr_squad *squad = &this->squads[s];
                for (uint32_t i = 0; i < RR_SQUAD_MEMBER_COUNT; ++i)
                {
                    if (squad->members[i].in_use == 0)
                    {
                        proto_bug_write_uint8(&encoder, 0, "bitbit");
                        continue;
                    }
                    struct rr_squad_member *member = &squad->members[i];
                    proto_bug_write_uint8(&encoder, 1, "bitbit");
                    proto_bug_write_uint8(&encoder, member->playing, "ready");
                    proto_bug_write_uint8(&encoder, member->is_dev, "is_dev");
                    proto_bug_write_string(&encoder, member->nickname, 16, "nickname");
                    for (uint8_t j = 0; j < 20; ++j)
                    {
                        proto_bug_write_uint8(&encoder, member->loadout[j].id, "id");
                        proto_bug_write_uint8(&encoder, member->loadout[j].rarity, "rar");
                    }
                }
                proto_bug_write_uint8(&encoder, squad->private, "private");
                proto_bug_write_uint8(&encoder, RR_GLOBAL_BIOME, "biome");
                char joined_code[16];
                sprintf(joined_code, "%s-%s", this->server_alias, squad->squad_code);
                proto_bug_write_string(&encoder, joined_code, 16, "squad code");
            }
            rr_server_client_write_message(client, encoder.start, encoder.current - encoder.start);
        }
    }
}

void rr_server_run(struct rr_server *this)
{
    {
        struct lws_context_creation_info info = {0};

        info.protocols = (struct lws_protocols[]){{"g", lws_callback, sizeof(uint8_t), MESSAGE_BUFFER_SIZE, 0, NULL, 0}, {0}};

        info.port = 1234;
        info.user = this;
        info.pt_serv_buf_size = MESSAGE_BUFFER_SIZE;

        this->server = lws_create_context(&info);
        assert(this->server);
    }
    {
        struct lws_context_creation_info info = {0};
        struct lws_client_connect_info client_info = {0};

        struct lws_protocols protocols[] = {
            {
                "g",
                api_lws_callback,
                0,
                128 * 1024,
            },
            {NULL, NULL, 0, 0} // terminator
        };
        info.port = CONTEXT_PORT_NO_LISTEN;
        info.protocols = protocols;
        info.gid = -1;
        info.uid = -1;
        info.user = this;

        this->api_client_context = lws_create_context(&info);
        if (!this->api_client_context)
        {
            puts("couldn't create api server context");
            exit(1);
        }
        client_info.context = this->api_client_context;
        client_info.address =
#ifndef RIVET_BUILD
            "localhost";
#else
            "45.79.197.197";
#endif
        client_info.port = 55554;
        client_info.path = "/api/" RR_API_SECRET;
        client_info.host = client_info.address;
        client_info.origin = client_info.address;
        client_info.protocol = protocols[0].name;
        this->api_client = lws_client_connect_via_info(&client_info);
        if (!this->api_client)
        {
            puts("couldn't create api client");
            exit(1);
        }
    }

    while (1)
    {
        struct timeval start;
        struct timeval end;

        gettimeofday(&start, NULL);
        lws_service(this->server, -1);
        lws_service(this->api_client_context, -1);
        server_tick(this);
        rr_simulation_for_each_entity(&this->simulation, &this->simulation, rr_simulation_tick_entity_resetter_function);
        this->simulation.animation_length = 0;
        gettimeofday(&end, NULL);

        uint64_t elapsed_time = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
        if (elapsed_time > 25000)
            fprintf(stderr, "tick took %lu microseconds\n", elapsed_time);
        int64_t to_sleep = 40000 - elapsed_time;
        if (to_sleep > 0)
            usleep(to_sleep);
    }
}
