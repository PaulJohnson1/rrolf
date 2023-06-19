#pragma once

#include <stdint.h>

struct rr_server_client_loadout_petal
{
    uint8_t id;
    uint8_t rarity;
};

struct rr_server_client
{
    uint64_t clientbound_encryption_key;
    uint64_t serverbound_encryption_key;
    uint64_t requested_verification;
    struct lws *socket_handle;
    struct rr_component_player_info *player_info;
    struct rr_server *server;
    int file_descriptor;
    uint8_t received_first_packet;
    uint8_t verified;
    uint8_t ready;

    struct rr_server_client_loadout_petal loadout[20];
    char client_nickname[16];
};

void rr_server_client_init(struct rr_server_client *);
void rr_server_client_create_flower(struct rr_server_client *);