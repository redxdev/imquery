#pragma once

#include <stdint.h>
#include <ostream>

namespace imq
{
	namespace utility
	{
		template<typename T>
		T clamp(T val, T min, T max)
		{
			if (val < min)
			{
				return min;
			}
			else if (val > max)
			{
				return max;
			}

			return val;
		}
	}

	struct VLocation
	{
		int32_t line;
		int32_t col;
	};

	std::ostream& operator<<(std::ostream& os, const VLocation& loc);
}