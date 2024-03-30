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
// a normal binary encoder

#define RR_API_SUCCESS 45

struct rr_binary_encoder
{
    uint8_t *at;
    uint8_t *start;
};

void rr_binary_encoder_init(struct rr_binary_encoder *, uint8_t *);
uint8_t rr_binary_encoder_read_uint8(struct rr_binary_encoder *);
uint64_t rr_binary_encoder_read_varuint(struct rr_binary_encoder *);
uint32_t rr_binary_encoder_read_utf8(struct rr_binary_encoder *);
float rr_binary_encoder_read_float32(struct rr_binary_encoder *);
double rr_binary_encoder_read_float64(struct rr_binary_encoder *);
void rr_binary_encoder_read_nt_string(struct rr_binary_encoder *, char *);

void rr_binary_encoder_write_uint8(struct rr_binary_encoder *, uint8_t);
void rr_binary_encoder_write_varuint(struct rr_binary_encoder *, uint64_t);
void rr_binary_encoder_write_float32(struct rr_binary_encoder *, float);
void rr_binary_encoder_write_float64(struct rr_binary_encoder *, double);
void rr_binary_encoder_write_utf8(struct rr_binary_encoder *, uint32_t);
void rr_binary_encoder_write_nt_string(struct rr_binary_encoder *, char *);