#pragma once

#include "platform.h"

#include <sstream>

#define IMQ_ERROR_DEF(errName, fmt, ...) \
	inline String errName(__VA_ARGS__) \
	{ \
		std::stringstream __ss; \
		__ss << fmt; \
		return __ss.str(); \
	}

namespace imq
{
	namespace errors
	{
		IMQ_ERROR_DEF(undefined_get_field, typeName << " does not have get_field defined.", const String& typeName);
		IMQ_ERROR_DEF(undefined_set_field, typeName << " does not have set_field defined.", const String& typeName);
		IMQ_ERROR_DEF(undefined_get_index, typeName << " does not have get_index defined.", const String& typeName);
		IMQ_ERROR_DEF(undefined_set_index, typeName << " does not have set_index defined.", const String& typeName);
	}
}