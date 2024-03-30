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

#include <Shared/Binary.h>

#include <stdio.h>
#include <string.h>

void rr_binary_encoder_init(struct rr_binary_encoder *this, uint8_t *ptr)
{
    this->at = this->start = ptr;
}

uint8_t rr_binary_encoder_read_uint8(struct rr_binary_encoder *this)
{
    return *this->at++;
}

uint64_t rr_binary_encoder_read_varuint(struct rr_binary_encoder *this)
{
    uint8_t byte;
    uint64_t data = 0ull;
    uint64_t shift = 0ull;

    do
    {
        byte = rr_binary_encoder_read_uint8(this);
        data |= ((byte & 254ull) << shift) >> 1;
        shift += 7ull;
    } while (byte & 1ull);

    return data;
}

uint32_t rr_binary_encoder_read_utf8(struct rr_binary_encoder *this)
{
    uint8_t byte;
    uint64_t data = 0ull;
    uint64_t shift = 0ull;

    do
    {
        byte = rr_binary_encoder_read_uint8(this);
        data |= ((byte & 127ull) << shift);
        shift += 7ull;
    } while (byte & 128);

    return data;
}

float rr_binary_encoder_read_float32(struct rr_binary_encoder *this)
{
    float data;
    memcpy(&data, this->at, sizeof data);
    this->at += sizeof data;
    return data;
}

double rr_binary_encoder_read_float64(struct rr_binary_encoder *this)
{
    double data;
    memcpy(&data, this->at, sizeof data);
    this->at += sizeof data;
    return data;
}

void rr_binary_encoder_read_nt_string(struct rr_binary_encoder *this, char *buf)
{
    while (*this->at)
    {
        *buf++ = *this->at++;
    }
    *buf = 0;
    this->at++;
}

void rr_binary_encoder_write_uint8(struct rr_binary_encoder *this, uint8_t v)
{
    *this->at++ = v;
}

void rr_binary_encoder_write_varuint(struct rr_binary_encoder *this, uint64_t v)
{
    while (v > 127)
    {
        rr_binary_encoder_write_uint8(this, (v << 1) | 1);
        v >>= 7;
    }
    rr_binary_encoder_write_uint8(this, v << 1);
}

void rr_binary_encoder_write_utf8(struct rr_binary_encoder *this, uint32_t v)
{
    while (v > 127)
    {
        rr_binary_encoder_write_uint8(this, v | 128);
        v >>= 7;
    }
    rr_binary_encoder_write_uint8(this, v);
}

void rr_binary_encoder_write_nt_string(struct rr_binary_encoder *this,
                                       char *buf)
{
    while (*buf)
    {
        rr_binary_encoder_write_uint8(this, *buf++);
    }
    rr_binary_encoder_write_uint8(this, 0);
}

void rr_binary_encoder_write_float32(struct rr_binary_encoder *this, float data)
{
    memcpy(this->at, &data, sizeof data);
    this->at += sizeof data;
}

void rr_binary_encoder_write_float64(struct rr_binary_encoder *this,
                                     double data)
{
    memcpy(this->at, &data, sizeof data);
    this->at += sizeof data;
}