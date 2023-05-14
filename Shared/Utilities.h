#pragma once

#include <stdint.h>

#ifndef NDEBUG
#include <stdio.h>
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
