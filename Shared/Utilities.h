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
#include <stdio.h>

#ifndef NDEBUG
#include <assert.h>
#define RR_UNREACHABLE(MESSAGE) assert(!MESSAGE)
#else
#define RR_UNREACHABLE(MESSAGE) __builtin_unreachable()
#endif

#ifdef RR_CLIENT
#define RR_CLIENT_ONLY(...) __VA_ARGS__
#else
#define RR_CLIENT_ONLY(...)
#endif

#ifdef RR_SERVER
#define RR_SERVER_ONLY(...) __VA_ARGS__
#else
#define RR_SERVER_ONLY(...)
#endif

void rr_log_hex(uint8_t *, uint8_t *);
float rr_lerp(float, float, float);
float rr_angle_lerp(float, float, float);
int rr_angle_within(float, float, float);
float rr_frand();
float rr_fclamp(float, float, float);
char *rr_sprintf(char *, double);

int rr_base_64_decode(char *, const char *);
int rr_base_64_encode(char *, const char *, int);

#define RR_CONCAT(a, b) a ## b
#define RR_REPEAT(count, macro) RR_CONCAT(RR_REPEAT, count)(macro)

#define RR_SET_IF_GREATER(var, num) { if ((var) < (num)) (var) = (num); }
#define RR_SET_IF_LESS(var, num) { if ((num) < (var)) (var) = (num); }
#define RR_REPEAT0(macro)
#define RR_REPEAT1(macro) macro(0)
#define RR_REPEAT2(macro) RR_REPEAT1(macro) macro(1)
#define RR_REPEAT3(macro) RR_REPEAT2(macro) macro(2)
#define RR_REPEAT4(macro) RR_REPEAT3(macro) macro(3)
#define RR_REPEAT5(macro) RR_REPEAT4(macro) macro(4)
#define RR_REPEAT6(macro) RR_REPEAT5(macro) macro(5)
#define RR_REPEAT7(macro) RR_REPEAT6(macro) macro(6)
#define RR_REPEAT8(macro) RR_REPEAT7(macro) macro(7)
#define RR_REPEAT9(macro) RR_REPEAT8(macro) macro(8)
#define RR_REPEAT10(macro) RR_REPEAT9(macro) macro(9)
