#include <Server/Server.h>
#include <Server/Client.h>

#include <assert.h>
#include <sys/time.h>
#include <unistd.h>

#include <Server/Simulation.h>
#include <Shared/Bitset.h>
#include <Shared/Utilities.h>
#include <Shared/Vector.h>
#include <Shared/Component/Physical.h>

#include <libwebsockets.h>
#ifdef RR_WINDOWS
#include <plugins/protocol_lws_status.c>
#endif

void rr_server_client_create_player_info(struct rr_server_client *this)
{
    puts("creating player info");
    this->player_info = rr_simulation_add_player_info(&this->server->simulation, rr_simulation_alloc_entity(&this->server->simulation));
    rr_server_client_create_flower(this);
}

void rr_server_client_free(struct rr_server_client *this)
{
    puts("client disconnected");
    // rr_simulation_free_entity(&this->server->simulation, this->player_info->flower_id);
    // rr_simulation_free_entity(&this->server->simulation, this->player_info->parent_id);
}

void rr_server_client_write_message(struct rr_server_client *this, uint8_t *message_start, uint8_t *message_end)
{
    lws_write(this->socket_handle, message_start, message_end - message_start, LWS_WRITE_BINARY);
}

void rr_server_client_broadcast_update(struct rr_server_client *this)
{
    struct rr_server *server = this->server;

    // 128 KB (not needed but just in case)
    static uint8_t outgoing_message[128 * 1024];
    struct rr_encoder encoder;
    rr_encoder_init(&encoder, outgoing_message);
    rr_encoder_write_uint8(&encoder, 0);
    rr_simulation_write_binary(&server->simulation, &encoder, this->player_info);
    rr_server_client_write_message(this, encoder.start, encoder.current);
}

void rr_server_client_tick(struct rr_server_client *this)
{
    if (this->player_info != NULL)
    {
        if (this->player_info->flower_id != 0)
        {
            struct rr_component_physical *flowerp = rr_simulation_get_physical(&this->server->simulation, this->player_info->flower_id);
            rr_component_player_info_set_camera_x(this->player_info, flowerp->x);
            rr_component_player_info_set_camera_y(this->player_info, flowerp->y);
        }
    }
    rr_server_client_broadcast_update(this);
}

int rr_server_lws_callback_function(struct lws *socket, enum lws_callback_reasons reason, void *context, void *packet, size_t size)
{
    struct rr_server *this = (struct rr_server *)lws_context_user(lws_get_context(socket));
    switch (reason)
    {
    case LWS_CALLBACK_ESTABLISHED:
    {
        for (uint64_t i = 0; i < RR_MAX_CLIENT_COUNT; i++)
            if (!rr_bitset_get_bit(this->clients_in_use, i))
            {
                rr_bitset_set(this->clients_in_use, i);
                rr_server_client_init(this->clients + i);
                this->clients[i].server = this;
                this->clients[i].file_descriptor = lws_get_socket_fd(socket);
                this->clients[i].socket_handle = socket;
                rr_server_client_create_player_info(this->clients + i);
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
                    // free playerinfo and player
                    if (this->clients[i].player_info != NULL)
                    {
                        if (this->clients[i].player_info->flower_id != 0)
                            rr_simulation_free_entity(&this->simulation, this->clients[i].player_info->flower_id);
                        rr_simulation_free_entity(&this->simulation, this->clients[i].player_info->parent_id);
                    }
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
        for (uint64_t i = 0; i < RR_MAX_CLIENT_COUNT; i++)
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
        struct rr_encoder encoder;
        rr_encoder_init(&encoder, packet);
        // rr_log_hex(packet, packet + size);
        switch (rr_encoder_read_uint8(&encoder))
        {
        case 0:
        {
            if (size != 3)
            {
                puts("unsafe input packet with length != 3");
                return 0;
            }
            rr_encoder_read_uint8(&encoder);
            uint64_t movementFlags = rr_encoder_read_uint8(&encoder);
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
            break;
        }
        case 1:
        {
            if (size != 1)
            {
                puts("someone sent a spawn packet with size != 1");
                return 0;
            }
            rr_server_client_create_flower(client);
            // ctor player
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

void rr_server_tick(struct rr_server *this)
{
    rr_simulation_tick(&this->simulation);
    for (uint64_t i = 0; i < RR_MAX_CLIENT_COUNT; i++)
        if (rr_bitset_get(this->clients_in_use, i))
            rr_server_client_tick(this->clients + i);
}

void rr_server_run(struct rr_server *this)
{
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

    this->server = lws_create_context(&info);
    assert(this->server);

    while (1)
    {
        struct timeval start;
        struct timeval end;

        gettimeofday(&start, NULL); // gettimeofday actually starts from unix timestamp 0 (goofy)
        rr_server_tick(this);
        lws_service(this->server, -1);
        gettimeofday(&end, NULL);

        long elapsed_time = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
        if (elapsed_time > 100)
            printf("tick took %ld microseconds\n", elapsed_time);
        long to_sleep = 40000 - elapsed_time;
        usleep(to_sleep > 0 ? to_sleep : 0);
    }
}
