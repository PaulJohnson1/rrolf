#pragma once

#include <type_traits>

namespace app
{
    template <typename T, bool angle = false>
    T Lerp(T start, T end, T time)
    {
        if constexpr (angle)
        {
            return 0;
        }
        return (end - start) * time + start;
    }
}
