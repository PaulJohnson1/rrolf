// Copyright (C) 2024  Paul Johnson

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.

// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#pragma once

#include <stdint.h>

#include <Shared/Bitset.h>
#include <Shared/Rivet.h>
#include <Shared/StaticData.h>

#define dev_cheat_enabled(simulation, entity, cheat_name)                      \
    (rr_simulation_has_player_info(simulation,                                 \
        rr_simulation_get_relations(simulation, entity)->root_owner) &&        \
        rr_simulation_get_player_info(simulation,                              \
            rr_simulation_get_relations(simulation, entity)->root_owner)->     \
                client->dev_cheats.cheat_name)

struct rr_binary_encoder;

struct rr_server_client_message
{
    struct rr_server_client_message *next;
    uint64_t len;
    uint8_t *packet;
};

struct rr_server_client_dev_cheats
{
    uint8_t invisible : 1;
    uint8_t invulnerable : 1;
    uint8_t no_aggro : 1;
    uint8_t no_wall_collision : 1;
    uint8_t no_collision : 1;
    uint8_t no_grid_influence : 1;
    float speed_percent;
    float fov_percent;
};

struct rr_server_client
{
    struct rr_rivet_account rivet_account;
    uint64_t clientbound_encryption_key;
    uint64_t serverbound_encryption_key;
    uint64_t requested_verification;
    uint8_t quick_verification;
    uint64_t message_length;
    struct rr_server *server;
    struct lws *socket_handle;
    struct rr_server_client_message *message_root;
    struct rr_server_client_message *message_at;
    struct rr_component_player_info *player_info;
    struct rr_server_client_dev_cheats dev_cheats;
    double experience;
    float player_accel_x;
    float player_accel_y;
    char ip_address[100];

    uint32_t inventory[rr_petal_id_max][rr_rarity_id_max];
    uint32_t craft_fails[rr_petal_id_max][rr_rarity_id_max];
    uint32_t ticks_to_next_squad_action;
    uint8_t joined_squad_before[RR_BITSET_ROUND(RR_SQUAD_COUNT)];
    uint8_t squad_pos;
    uint8_t squad;
    uint8_t received_first_packet : 1;
    uint8_t verified : 1;
    uint8_t dev : 1;
    uint8_t in_squad : 1;
    uint8_t pending_kick : 1;
    uint8_t in_use : 1;
    uint8_t pending_quick_join : 1;
};

void rr_server_client_init(struct rr_server_client *);
void rr_server_client_create_flower(struct rr_server_client *);

void rr_server_client_write_message(struct rr_server_client *, uint8_t *,
                                    uint64_t);
void rr_server_client_write_account(struct rr_server_client *);
void rr_server_client_craft_petal(struct rr_server_client *, uint8_t, uint8_t,
                                  uint32_t);
int rr_server_client_read_from_api(struct rr_server_client *,
                                   struct rr_binary_encoder *);
void rr_server_client_write_to_api(struct rr_server_client *);