#pragma once

#include "platform.h"

#include <sstream>

#include "result.h"
#include "value.h"
#include "utility.h"

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
		IMQ_ERROR_DEF(undefined_selection, typeName << " does not implement selection.", const String& typeName);
		IMQ_ERROR_DEF(undefined_operator, typeName << " does not implement operator " << op, const String& typeName, const String& op);

		IMQ_ERROR_DEF(undefined_field, "Invalid field " << fieldName << " for type " << typeName, const String& typeName, const String& fieldName);

		IMQ_ERROR_DEF(undefined_index, "Invalid index " << index.toString() << " for type " << typeName, const String& typeName, const QValue& index);
		IMQ_ERROR_DEF(invalid_index_type, "Invalid index type " << QValue::getTypeString(index.getType()) << " for type " << typeName, const String& typeName, const QValue& index);

		IMQ_ERROR_DEF(context_undefined_value, "Unknown variable \"" << key << "\"", const String& key);
		IMQ_ERROR_DEF(context_no_write_access, "Variables may not be defined in the current context.");
		IMQ_ERROR_DEF(context_no_delete_access, "Variables may not be deleted in the current context.");
		IMQ_ERROR_DEF(context_root_flags, "Inputs/outputs must be defined in the root context.");
		IMQ_ERROR_DEF(context_input_set, "Inputs may not be redefined.");
		IMQ_ERROR_DEF(context_output_set, "Outputs may not be redefined.");
		IMQ_ERROR_DEF(context_input_delete, "Inputs may not be deleted.");
		IMQ_ERROR_DEF(context_output_delete, "Outputs may not be deleted.");
		IMQ_ERROR_DEF(context_input_overwrite, "Inputs may not be defined on top of a variable.");
		IMQ_ERROR_DEF(context_output_overwrite, "Outputs may not be defined on top of a variable.");
		IMQ_ERROR_DEF(context_input_invalid_type, "Input " << key << " has the wrong type.", const String& key);

		IMQ_ERROR_DEF(image_load_error, "Image load error - " << reason, const String& reason);
		IMQ_ERROR_DEF(image_save_error, "Image save error - unable to save image file " << filename, const String& filename);

		IMQ_ERROR_DEF(vm_generic_error, loc << ": " << msg, const VLocation& loc, const String& msg);
		IMQ_ERROR_DEF(vm_invalid_block, "Invalid block.");

		IMQ_ERROR_DEF(selection_apply_error, "Unable to apply selection - " << msg, const String& msg);
		IMQ_ERROR_DEF(selection_create_error, "Unable to create selection - " << msg, const String& msg);

		IMQ_ERROR_DEF(math_operator_invalid, "Operator " << op << " is not valid for type " << t, const String& t, const String& op);
		IMQ_ERROR_DEF(math_object_order, "Operator " << op << " cannot operate on objects unless they are on the left-hand side.", const String& op);
		IMQ_ERROR_DEF(math_divide_by_zero, "Divide by zero error");
		IMQ_ERROR_DEF(math_mod_by_zero, "Mod by zero error");

		IMQ_ERROR_DEF(args_count, "Wrong number of arguments to " << funcName << " (expected " << expected << ", got " << actual << ")", const String& funcName, int32_t expected, int32_t actual);
		IMQ_ERROR_DEF(args_type, "Invalid type for argument #" << argNum << " to " << funcName << " (expected " << expected << ", got " << actual << ")", const String& funcName, int32_t argNum, const String& expected, const String& actual);
		
		IMQ_ERROR_DEF(func_generic_error, msg, const String& msg);
	}
}

#undef IMQ_ERROR_DEF