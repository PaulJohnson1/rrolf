#include <Server/Server.h>

#include <assert.h>
#include <time.h>
#include <unistd.h>

#include <Server/Simulation.h>
#include <Shared/Bitset.h>

#include <libwebsockets.h>

void rr_server_client_init(struct rr_server_client *this)
{
    memset(this, 0, sizeof *this);
    puts("client connected");
}

void rr_server_client_create_player_info(struct rr_server_client *this)
{
    puts("creating player info");
    this->player_info = rr_simulation_alloc_entity(&this->server->simulation);
}

void rr_server_client_free(struct rr_server_client *this)
{
    puts("client disconnected");
    rr_simulation_free_entity(&this->server->simulation, this->player_info);
}

void rr_server_client_tick(struct rr_server_client *this)
{
    puts("client tick or sometihng lol");
}

int rr_server_lws_callback_function(struct lws *socket, enum lws_callback_reasons reason, void *context, void *other, size_t size)
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
                    rr_bitset_unset(this->clients_in_use, i);
                    rr_server_client_free(this->clients + i);
                    return 0;
                }
            }
        RR_UNREACHABLE("cloudn't remove client");
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
    struct lws_protocols protocol;
    memset(&info, 0, sizeof(info));
    memset(&protocol, 0, sizeof(protocol));

    protocol.name = "g";
    protocol.callback = rr_server_lws_callback_function;

    info.port = 8000;
    info.protocols = &protocol;
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
        printf("tick took %ld microseconds\n", elapsed_time);
        long to_sleep = 40000 - elapsed_time;
        usleep(to_sleep > 0 ? to_sleep : 0);
    }
}
