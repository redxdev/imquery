#pragma once

#include "platform.h"

#include <sstream>

#include "result.h"
#include "value.h"

#define IMQ_ERROR_DEF(errName, fmt, ...) \
	inline Result errName(__VA_ARGS__) \
	{ \
		std::stringstream __ss; \
		__ss << fmt; \
		return imq::Result(false, __ss.str()); \
	}

namespace imq
{
	namespace errors
	{
		IMQ_ERROR_DEF(undefined_get_field, typeName << " does not have get_field defined.", const String& typeName);
		IMQ_ERROR_DEF(undefined_set_field, typeName << " does not have set_field defined.", const String& typeName);
		IMQ_ERROR_DEF(undefined_get_index, typeName << " does not have get_index defined.", const String& typeName);
		IMQ_ERROR_DEF(undefined_set_index, typeName << " does not have set_index defined.", const String& typeName);

		IMQ_ERROR_DEF(undefined_field, "Invalid field " << fieldName << " for type " << typeName, const String& typeName, const String& fieldName);

		IMQ_ERROR_DEF(undefined_index, "Invalid index " << index.toString() << " for type " << typeName, const String& typeName, const QValue& index);
		IMQ_ERROR_DEF(invalid_index_type, "Invalid index type " << QValue::getTypeString(index.getType()) << " for type " << typeName, const String& typeName, const QValue& index);

		IMQ_ERROR_DEF(image_load_error, "Image load error - " << reason, const String& reason);
		IMQ_ERROR_DEF(image_save_error, "Image save error - unable to save image file " << filename, const String& filename);
	}
}

#undef IMQ_ERROR_DEF