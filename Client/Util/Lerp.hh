#pragma once

#include <type_traits>

namespace app
{
	template <typename T>
	T Lerp(T start, T end, T time)
	{
		return (end - start) * time + start;
	}
}
