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

#include <Server/Client.h>
#include <Server/Simulation.h>
#include <Server/Squad.h>

#ifndef NDEBUG
#define MESSAGE_BUFFER_SIZE (32 * 1024 * 1024)
#else
#define MESSAGE_BUFFER_SIZE (1024 * 1024)
#endif

extern uint8_t lws_message_data[MESSAGE_BUFFER_SIZE];
extern uint8_t *outgoing_message;

struct lws_context;
struct lws;
struct rr_server;
struct rr_squad_member;

struct rr_server
{
    struct rr_simulation simulation;
    uint8_t clients_in_use[RR_BITSET_ROUND(RR_MAX_CLIENT_COUNT)];
    struct rr_server_client clients[RR_MAX_CLIENT_COUNT];
    struct lws_context *server;
    struct lws_context *api_client_context;
    struct lws *api_client;
    struct rr_squad squads[RR_MAX_CLIENT_COUNT];
    uint8_t api_ws_ready;
    char server_alias[16];
};

void rr_server_init(struct rr_server *);
void rr_server_free(struct rr_server *);

uint8_t rr_client_create_squad(struct rr_server *, struct rr_server_client *);
uint8_t rr_client_find_squad(struct rr_server *, struct rr_server_client *);
uint8_t rr_client_join_squad_with_code(struct rr_server *,
                                       struct rr_server_client *, char *);
uint8_t rr_client_join_squad(struct rr_server *, struct rr_server_client *,
                             uint8_t);
void rr_client_leave_squad(struct rr_server *, struct rr_server_client *);
struct rr_squad_member *rr_squad_get_client_slot(struct rr_server *,
                                                 struct rr_server_client *);
struct rr_squad *rr_client_get_squad(struct rr_server *,
                                     struct rr_server_client *);

// Blocking function. The only time this function will never end unless the
// server crashes
void rr_server_run(struct rr_server *);
