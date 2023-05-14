#include <Server/Server.h>

#include <assert.h>
#include <time.h>
#include <unistd.h>

#include <Shared/Bitset.h>

#include <libwebsockets.h>

void rr_server_client_init(struct rr_server_client *self)
{
    memset(self, 0, sizeof *self);
}

void rr_server_client_tick(struct rr_server_client *self)
{
    puts("client tick or sometihng lol");
}

int rr_server_lws_callback_function(struct lws *socket, enum lws_callback_reasons reason, void *_self, void *idk, size_t size)
{
    struct rr_server *self = _self;
    switch (reason)
    {
    case LWS_CALLBACK_ESTABLISHED:
    {
        puts("client connected");
        // mke more readable later
        for (uint64_t i = 0; i < RR_MAX_CLIENT_COUNT; i++)
            if (rr_bitset_get(self->clients_in_use, i))
            {
                rr_bitset_set(self->clients_in_use, i);
                rr_server_client_init(self->clients + i);
                self->clients[i].file_descriptor = lws_get_socket_fd(socket);
                return 0;
            }
        RR_UNREACHABLE();
    }

    case LWS_CALLBACK_CLOSED:
    {
        puts("client disconnected");
        for (uint64_t i = 0; i < RR_MAX_CLIENT_COUNT; i++)
            if (!rr_bitset_get(self->clients_in_use, i))
            {
                if (self->clients[i].file_descriptor == lws_get_socket_fd(socket))
                {
                    rr_bitset_unset(self->clients_in_use, i);
                    return 0;
                }
            }
        RR_UNREACHABLE();
    }

    default:
        break;
    }
    return 0;
}

void rr_server_init(struct rr_server *self)
{
    memset(self, 0, sizeof *self);
    rr_simulation_init(&self->simulation);
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
    info.user = self;

    self->server = lws_create_context(&info);
    assert(self->server);
}

void rr_server_tick(struct rr_server *self)
{
    rr_simulation_tick(&self->simulation);
    for (uint64_t i = 0; i < RR_MAX_CLIENT_COUNT; i++)
        if (rr_bitset_get(self->clients_in_use, i))
            rr_server_client_tick(self->clients + i);
}

void rr_server_run(struct rr_server *self)
{
    while (1)
    {
        struct timeval start;
        gettimeofday(&start, NULL); // gettimeofday actually starts from unix timestamp 0 (goofy)
        lws_service(self->server, -1);
        rr_server_tick(self);
        struct timeval end;
        gettimeofday(&end, NULL);

        long elapsed_time = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
        printf("tick took %ld microseconds\n", elapsed_time);
        long to_sleep = 40000 - elapsed_time;
        usleep(to_sleep > 0 ? to_sleep : 0);
    }
}