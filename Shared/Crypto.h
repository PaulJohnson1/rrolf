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


#if defined(RR_CLIENT) && defined(EMSCRIPTEN) && defined(NDEBUG)
inline void rr_encrypt(uint8_t *start, uint64_t size, uint64_t key)
    __attribute__((always_inline));
inline void rr_decrypt(uint8_t *start, uint64_t size, uint64_t key)
    __attribute__((always_inline));
#else
void rr_encrypt(uint8_t *start, uint64_t size, uint64_t key);
void rr_decrypt(uint8_t *start, uint64_t size, uint64_t key);
#endif
uint64_t rr_get_rand();
uint64_t rr_get_hash(uint64_t);
