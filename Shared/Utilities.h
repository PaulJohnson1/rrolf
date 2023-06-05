#pragma once

#include <stdint.h>
#include <stdio.h>

#ifndef NDEBUG
#define RR_UNREACHABLE(MESSAGE) \
    fputs(#MESSAGE, stderr);    \
    assert(0)
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
