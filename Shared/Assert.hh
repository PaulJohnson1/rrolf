#pragma once

#include <iostream>

// taken from assert.h

/* Version 2.4 and later of GCC define a magical variable `__PRETTY_FUNCTION__'
   which contains the name of the function currently being defined.
   This is broken in G++ before version 2.6.
   C9x has a similar variable called __func__, but prefer the GCC one since
   it demangles C++ function names.  */
#if defined __cplusplus ? __GNUC_PREREQ(2, 6) : __GNUC_PREREQ(2, 4)
#define __ASSERT_FUNCTION __extension__ __PRETTY_FUNCTION__
#else
#if defined __STDC_VERSION__ && __STDC_VERSION__ >= 199901L
#define __ASSERT_FUNCTION __func__
#else
#define __ASSERT_FUNCTION ((const char *)0)
#endif
#endif

#ifdef RROLF_ENABLE_ASSERTIONS
#define RROLF_ASSERT(CONDITION, ERROR)                                                                                                        \
    if (!static_cast<bool>(CONDITION))                                                                                                        \
    {                                                                                                                                         \
        std::cerr << __FILE__ << ':' << __LINE__ << " in " << __ASSERT_FUNCTION << " assertion failed `" << #CONDITION << "` " ERROR << '\n'; \
        abort();                                                                                                                              \
    }
#else
#define RROLF_ASSERT(CONDITION, ERROR) static_cast<void>(0);
#endif