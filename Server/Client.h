#pragma once

#include <stdint.h>

struct rr_server_client
{
    uint64_t clientbound_encryption_key;
    uint64_t serverbound_encryption_key;
    uint64_t requested_verification;
    struct lws *socket_handle;
    struct rr_component_player_info *player_info;
    struct rr_server *server;
    int file_descriptor;
    uint8_t received_first_packet:1;
    uint8_t verified:1;
};

void rr_server_client_init(struct rr_server_client *);
void rr_server_client_create_flower(struct rr_server_client *);