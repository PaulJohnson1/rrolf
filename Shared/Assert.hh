#pragma once

#include <assert.h>

#ifdef RROLF_ENABLE_ASSERTIONS
#define RROLF_ASSERT(CONDITION) assert(CONDITION);
#else
#define RROLF_ASSERT(CONDITION) static_cast<void>(0);
#endif