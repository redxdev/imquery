#include "utility.h"

namespace imq
{
	std::ostream& operator<<(std::ostream& os, const VLocation& loc)
	{
		os << loc.line << ":" << loc.col;
		return os;
	}
}