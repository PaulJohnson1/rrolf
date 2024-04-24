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

#include <Server/Client.h>

#include <libwebsockets.h>
#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <Server/EntityAllocation.h>
#include <Server/Server.h>
#include <Server/Simulation.h>
#include <Shared/Binary.h>
#include <Shared/Component/PlayerInfo.h>
#include <Shared/Crypto.h>
#include <Shared/Entity.h>
#include <Shared/pb.h>

double CRAFT_XP_GAINS[rr_rarity_id_max - 1] = {1, 8, 60, 750, 25000, 1000000, 100000000};

void rr_server_client_init(struct rr_server_client *this)
{
    memset(this, 0, sizeof *this);
    this->clientbound_encryption_key = rr_get_rand();
    this->serverbound_encryption_key = rr_get_rand();
    this->requested_verification = rr_get_rand();
    this->speed_percent = 1;
}

void rr_server_client_create_flower(struct rr_server_client *this)
{
    if (this->player_info == NULL)
        return;
    if (this->player_info->flower_id != RR_NULL_ENTITY)
        return;
    struct rr_simulation *simulation = &this->server->simulation;
    EntityIdx p =
        rr_simulation_alloc_player(simulation, 1, this->player_info->parent_id);
    uint32_t spawn_zone =
        this->player_info->level / 25 > 3 ? 3 : this->player_info->level / 25;
    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, p);
    struct rr_maze_declaration *decl = &RR_MAZES[RR_GLOBAL_BIOME];
    rr_component_physical_set_x(
        physical,
        2 * decl->grid_size * (decl->spawn_zones[spawn_zone].x + rr_frand()));
    rr_component_physical_set_y(
        physical,
        2 * decl->grid_size * (decl->spawn_zones[spawn_zone].y + rr_frand()));
    struct rr_binary_encoder encoder;
    rr_binary_encoder_init(&encoder, outgoing_message);
    rr_binary_encoder_write_uint8(&encoder, 3);
    for (uint64_t i = 0; i < 10; i++)
    {
        struct rr_component_player_info_petal_slot *slot =
            this->player_info->slots + i;
        rr_binary_encoder_write_uint8(&encoder, slot->id);
        rr_binary_encoder_write_uint8(&encoder, slot->rarity);
    }
    for (uint64_t i = 0; i < 10; i++)
    {
        struct rr_component_player_info_petal_slot *slot =
            this->player_info->secondary_slots + i;
        rr_binary_encoder_write_uint8(&encoder, slot->id);
        rr_binary_encoder_write_uint8(&encoder, slot->rarity);
    }
    rr_binary_encoder_write_uint8(&encoder, 0);
    lws_write(this->server->api_client, encoder.start,
              encoder.at - encoder.start, LWS_WRITE_BINARY);
}

void rr_server_client_write_message(struct rr_server_client *this,
                                    uint8_t *data, uint64_t size)
{
    if (this->message_length++ >= 512)
    {
        this->pending_kick = 1;
        lws_callback_on_writable(this->socket_handle);
        return;
    }
    if (this->received_first_packet)
    {
        this->clientbound_encryption_key =
            rr_get_hash(this->clientbound_encryption_key);
        rr_encrypt(data, size, this->clientbound_encryption_key);
    }
    struct rr_server_client_message *message = malloc(sizeof *message);
    uint8_t *packet = malloc(LWS_PRE + size);
    memcpy(packet + LWS_PRE, data, size);
    message->next = NULL;
    message->len = size;
    message->packet = packet;
    if (this->message_root == NULL)
        this->message_root = message;
    else
        this->message_at->next = message;
    this->message_at = message;
    lws_callback_on_writable(this->socket_handle);
    // lws_write(this->socket_handle, data, size, LWS_WRITE_BINARY);
}

void rr_server_client_write_account(struct rr_server_client *client)
{
    struct proto_bug encoder;
    proto_bug_init(&encoder, outgoing_message);
    proto_bug_write_uint8(&encoder, rr_clientbound_account_result, "header");
    proto_bug_write_string(&encoder, client->rivet_account.uuid,
                           sizeof client->rivet_account.uuid, "uuid");
    proto_bug_write_float64(&encoder, client->experience, "xp");
    for (uint8_t id = 1; id < rr_petal_id_max; ++id)
        for (uint8_t rarity = 0; rarity < rr_rarity_id_max; ++rarity)
        {
            if (client->inventory[id][rarity] == 0)
                continue;
            proto_bug_write_uint8(&encoder, id, "id");
            proto_bug_write_uint8(&encoder, rarity, "rarity");
            proto_bug_write_varuint(&encoder, client->inventory[id][rarity],
                                    "count");
        }
    proto_bug_write_uint8(&encoder, 0, "id");
    for (uint8_t id = 1; id < rr_petal_id_max; ++id)
        for (uint8_t rarity = 0; rarity < rr_rarity_id_max; ++rarity)
        {
            if (client->craft_fails[id][rarity] == 0)
                continue;
            proto_bug_write_uint8(&encoder, id, "id");
            proto_bug_write_uint8(&encoder, rarity, "rarity");
            proto_bug_write_varuint(&encoder, client->craft_fails[id][rarity],
                                    "count");
        }
    proto_bug_write_uint8(&encoder, 0, "id");
    rr_server_client_write_message(client, encoder.start,
                                   encoder.current - encoder.start);
}

void rr_server_client_craft_petal(struct rr_server_client *this, uint8_t id,
                                  uint8_t rarity, uint32_t count)
{
    if (id >= rr_petal_id_max || rarity >= rr_rarity_id_max - 1)
        return;
    if (count < 5)
        return;
    if (this->inventory[id][rarity] < count)
        return;
    uint32_t now = count;
    uint32_t success = 0;
    double base = RR_CRAFT_CHANCES[rarity];
    double xp_gain = 0;
    while (now >= 5)
    {
        if (rr_frand() < base * (++this->craft_fails[id][rarity]))
        {
            ++success;
            this->craft_fails[id][rarity] = 0;
            now -= 5;
        }
        else
            now -= 1 + rand() % 4;
        xp_gain += CRAFT_XP_GAINS[rarity];
    }
    this->inventory[id][rarity] -= (count - now);
    this->inventory[id][rarity + 1] += success;
    this->experience += xp_gain;
    rr_server_client_write_to_api(this);

    struct proto_bug encoder;
    proto_bug_init(&encoder, outgoing_message);
    proto_bug_write_uint8(&encoder, rr_clientbound_craft_result, "header");
    proto_bug_write_uint8(&encoder, id, "craft id");
    proto_bug_write_uint8(&encoder, rarity, "craft rarity");
    proto_bug_write_varuint(&encoder, success, "success count");
    proto_bug_write_varuint(&encoder, count - now, "fail count");
    proto_bug_write_varuint(&encoder, this->craft_fails[id][rarity],
                            "attempts");
    proto_bug_write_float64(&encoder, xp_gain, "craft xp");
    rr_server_client_write_message(this, encoder.start,
                                   encoder.current - encoder.start);
}

int rr_server_client_read_from_api(struct rr_server_client *this,
                                   struct rr_binary_encoder *encoder)
{
    memset(this->craft_fails, 0, sizeof this->craft_fails);
    memset(this->inventory, 0, sizeof this->inventory);
    char uuid[sizeof this->rivet_account.uuid];
    rr_binary_encoder_read_nt_string(encoder, uuid);
    if (strcmp(uuid, this->rivet_account.uuid))
        return 0;
    this->experience = rr_binary_encoder_read_float64(encoder);
    uint8_t id = rr_binary_encoder_read_uint8(encoder);
    while (id)
    {
        uint8_t rarity = rr_binary_encoder_read_uint8(encoder);
        uint32_t count = rr_binary_encoder_read_varuint(encoder);
        if (rarity < rr_rarity_id_max)
            this->inventory[id][rarity] = count;
        id = rr_binary_encoder_read_uint8(encoder);
    }
    if (this->dev)
    {
        this->experience = 10000000000; // lvl 120
        for (uint8_t id = 1; id < rr_petal_id_max; ++id)
            for (uint8_t rarity = 0; rarity < rr_rarity_id_max; ++rarity)
                this->inventory[id][rarity] = 20;
    }
    id = rr_binary_encoder_read_uint8(encoder);
    while (id)
    {
        uint8_t rarity = rr_binary_encoder_read_uint8(encoder);
        uint32_t count = rr_binary_encoder_read_varuint(encoder);
        if (rarity < rr_rarity_id_max)
            this->craft_fails[id][rarity] = count;
        id = rr_binary_encoder_read_uint8(encoder);
    }
    return 1;
}

void rr_server_client_write_to_api(struct rr_server_client *this)
{
    if (this->dev)
        return;
    struct rr_binary_encoder encoder;
    rr_binary_encoder_init(&encoder, outgoing_message);
    rr_binary_encoder_write_uint8(&encoder, 2);
    rr_binary_encoder_write_nt_string(&encoder, this->rivet_account.uuid);
    rr_binary_encoder_write_float64(&encoder, this->experience);
    for (uint8_t id = 1; id < rr_petal_id_max; ++id)
        for (uint8_t rarity = 0; rarity < rr_rarity_id_max; ++rarity)
        {
            if (this->inventory[id][rarity] == 0)
                continue;
            rr_binary_encoder_write_uint8(&encoder, id);
            rr_binary_encoder_write_uint8(&encoder, rarity);
            rr_binary_encoder_write_varuint(&encoder,
                                            this->inventory[id][rarity]);
        }
    rr_binary_encoder_write_uint8(&encoder, 0);
    for (uint8_t id = 1; id < rr_petal_id_max; ++id)
        for (uint8_t rarity = 0; rarity < rr_rarity_id_max; ++rarity)
        {
            if (this->craft_fails[id][rarity] == 0)
                continue;
            rr_binary_encoder_write_uint8(&encoder, id);
            rr_binary_encoder_write_uint8(&encoder, rarity);
            rr_binary_encoder_write_varuint(&encoder,
                                            this->craft_fails[id][rarity]);
        }
    rr_binary_encoder_write_uint8(&encoder, 0);
    lws_write(this->server->api_client, encoder.start,
              encoder.at - encoder.start, LWS_WRITE_BINARY);
}