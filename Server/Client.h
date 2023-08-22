#pragma once

#include <stdint.h>

#include <Shared/Rivet.h>

struct rr_server_client_loadout_petal
{
    uint8_t id;
    uint8_t rarity;
};

struct __rr_client_message
{
    uint64_t size;
    uint8_t *data;
    struct __rr_client_message *next;
};

struct rr_server_client
{
    struct rr_rivet_account rivet_account;
    struct rr_server_client_loadout_petal loadout[20];
    uint64_t clientbound_encryption_key;
    uint64_t serverbound_encryption_key;
    uint64_t requested_verification;
    struct rr_server *server;
    struct __rr_client_message *messages;
    struct lws *socket_handle;
    struct rr_component_player_info *player_info;
    float player_accel_x;
    float player_accel_y;
    float requested_start_wave_percent;
    uint32_t max_wave;
    int file_descriptor;
    char ip_address[100];
    char client_nickname[18 * 4];
    uint32_t level;
    uint32_t response_time;
    uint8_t received_first_packet : 1;
    uint8_t verified : 1;
    uint8_t ready : 4;
    uint8_t loadout_validated : 1;
    uint8_t loadout_pending_validation : 1;
};

void rr_server_client_init(struct rr_server_client *);
void rr_server_client_create_flower(struct rr_server_client *);