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

#include <Server/Simulation.h>

#include <Shared/Squad.h>

#define RR_ERROR_CODE_INVALID_SQUAD 255
#define RR_ERROR_CODE_FULL_SQUAD 254
#define RR_ERROR_CODE_KICKED_FROM_SQUAD 253

struct rr_server_client;
struct rr_server;

struct rr_squad
{
    struct rr_squad_member members[RR_SQUAD_MEMBER_COUNT];
    uint8_t member_count;
    uint8_t private;
    char squad_code[7];
};

void rr_squad_init(struct rr_squad *, struct rr_server *, uint8_t);

uint8_t rr_squad_has_space(struct rr_squad *);

void rr_squad_add_client(struct rr_squad *, struct rr_server_client *);
void rr_squad_remove_client(struct rr_squad *, struct rr_server_client *);
