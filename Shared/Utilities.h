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
float rr_frand();
float rr_fclamp(float, float, float);

#define RR_CONCAT(a, b) a ## b
#define RR_REPEAT(count, macro) RR_CONCAT(RR_REPEAT, count)(macro)

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
