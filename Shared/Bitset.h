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

#define RR_BITSET_ROUND(x) ((x + 7) >> 3)
// #define RR_BITSET_ROUND(x) (x)

// May return any number that is 1, 2, 4, 8, 16, 32, 64, 128.
uint8_t rr_bitset_get_bit(uint8_t *, uint64_t);

// Will only ever return 1 or 0. (takes one more instuction than
// rr_bitset_get_bit)
uint8_t rr_bitset_get(uint8_t *, uint64_t);
void rr_bitset_unset(uint8_t *, uint64_t);
void rr_bitset_set(uint8_t *, uint64_t);
void rr_bitset_maybe_set(uint8_t *, uint64_t, uint8_t);
void rr_bitset_for_each_bit(uint8_t *start, uint8_t *end, void *,
                            void (*cb)(uint64_t, void *));
void rr_bitset_for_each_bit_until(uint8_t *start, uint8_t *end, void *,
                                  uint8_t (*cb)(uint64_t, void *));
