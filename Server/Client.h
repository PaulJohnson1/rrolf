#pragma once

#include <stdint.h>

#include <Shared/Rivet.h>
#include <Shared/Bitset.h>
#include <Shared/StaticData.h>

struct rr_binary_encoder;

struct rr_server_client_message
{
    struct rr_server_client_message *next;
    uint64_t len;
    uint8_t *packet;
};

struct rr_server_client
{
    struct rr_rivet_account rivet_account;
    uint64_t clientbound_encryption_key;
    uint64_t serverbound_encryption_key;
    uint64_t requested_verification;
    struct rr_server *server;
    struct lws *socket_handle;
    struct rr_server_client_message *message_root;
    struct rr_server_client_message *message_at;
    struct rr_component_player_info *player_info;
    double experience;
    float player_accel_x;
    float player_accel_y;
    char ip_address[100];
    uint32_t inventory[rr_petal_id_max][rr_rarity_id_max];
    uint32_t craft_fails[rr_petal_id_max][rr_rarity_id_max];
    uint8_t joined_squad_before[RR_BITSET_ROUND(RR_SQUAD_COUNT)];
    uint8_t squad_pos;
    uint8_t squad;
    uint8_t received_first_packet : 1;
    uint8_t verified : 1;
    uint8_t dev : 1;
    uint8_t in_squad : 1;
    uint8_t pending_kick : 1;
    uint8_t in_use : 1;
};

void rr_server_client_init(struct rr_server_client *);
void rr_server_client_create_flower(struct rr_server_client *);

void rr_server_client_write_message(struct rr_server_client *, uint8_t *, uint64_t);
void rr_server_client_write_account(struct rr_server_client *);
void rr_server_client_craft_petal(struct rr_server_client *, uint8_t, uint8_t, uint32_t);
int rr_server_client_read_from_api(struct rr_server_client *, struct rr_binary_encoder *);
void rr_server_client_write_to_api(struct rr_server_client *);