#pragma once

#include <stdint.h>

struct rr_server_client
{
    int file_descriptor;
    uint64_t encryption_key;
    struct lws *socket_handle;
    struct rr_component_player_info *player_info;
    struct rr_server *server;
};

void rr_server_client_init(struct rr_server_client *);

void rr_server_client_create_flower(struct rr_server_client *);