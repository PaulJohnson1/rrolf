#pragma once

#ifndef NDEBUG
#define RR_UNREACHABLE() assert(0)
#else
#define RR_UNREACHABLE() __builtin_unreachable()
#endif
