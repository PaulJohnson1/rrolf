#pragma once

#include <stdint.h>

#ifndef NDEBUG
#define RR_UNREACHABLE() assert(0)
#else
#define RR_UNREACHABLE() __builtin_unreachable()
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