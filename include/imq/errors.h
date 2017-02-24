#pragma once

#include "platform.h"

#include <sstream>

#include "result.h"
#include "value.h"
#include "utility.h"

#define IMQ_ERROR_DEF(errName, fmt, ...) \
	inline IMQ_API Result errName(__VA_ARGS__) \
	{ \
		std::stringstream __ss; \
		__ss << fmt; \
		return imq::Result(false, __ss.str()); \
	}

namespace imq
{
	namespace errors
	{
		IMQ_ERROR_DEF(undefined_get_field, typeName << " does not have getField defined.", const String& typeName);
		IMQ_ERROR_DEF(undefined_set_field, typeName << " does not have setField defined.", const String& typeName);
		IMQ_ERROR_DEF(undefined_get_index, typeName << " does not have getIndex defined.", const String& typeName);
		IMQ_ERROR_DEF(undefined_set_index, typeName << " does not have setIndex defined.", const String& typeName);
		IMQ_ERROR_DEF(undefined_selection, typeName << " does not implement selection.", const String& typeName);
		IMQ_ERROR_DEF(undefined_iteration, typeName << " does not implement iteration.", const String& typeName);
		IMQ_ERROR_DEF(undefined_operator, typeName << " does not implement operator " << op, const String& typeName, const String& op);

		IMQ_ERROR_DEF(undefined_field, "Invalid field " << fieldName << " for type " << typeName, const String& typeName, const String& fieldName);

		IMQ_ERROR_DEF(undefined_index, "Invalid index " << index.asString() << " for type " << typeName, const String& typeName, const QValue& index);
		IMQ_ERROR_DEF(invalid_index_type, "Invalid index type " << QValue::getTypeString(index.getType()) << " for type " << typeName, const String& typeName, const QValue& index);
		IMQ_ERROR_DEF(index_out_of_range, "Index " << index.asString() << " is out of range", const QValue& index);

		IMQ_ERROR_DEF(immutable_obj, "Object " << typeName << " is immutable.", const String& typeName);
		IMQ_ERROR_DEF(uncopyable_obj, "Object " << typeName << " is not copyable.", const String& typeName);

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
		IMQ_ERROR_DEF(context_not_breakable, "The current context cannot be broken from.");
		IMQ_ERROR_DEF(context_not_returnable, "The current context cannot be returned from.");
		IMQ_ERROR_DEF(context_not_exportable, "The current context does not allow exporting.");

		IMQ_ERROR_DEF(image_load_error, "Image load error - " << reason, const String& reason);
		IMQ_ERROR_DEF(image_save_error, "Image save error - unable to save image file " << filename, const String& filename);

		IMQ_ERROR_DEF(vm_generic_error, "line " << loc << ": " << msg, const VLocation& loc, const String& msg);
		IMQ_ERROR_DEF(vm_from_call_error, "function call at " << loc << ": " << submsg, const VLocation& loc, const String& submsg);
		IMQ_ERROR_DEF(vm_invalid_block, "Invalid block.");

		IMQ_ERROR_DEF(selection_apply_error, "Unable to apply selection - " << msg, const String& msg);
		IMQ_ERROR_DEF(selection_create_error, "Unable to create selection - " << msg, const String& msg);

		IMQ_ERROR_DEF(math_operator_invalid, "Operator " << op << " is not valid for type " << t, const String& t, const String& op);
		IMQ_ERROR_DEF(math_operator_obj_invalid, "Operator " << op << " is not valid for types " << objType << " and " << QValue::getTypeString(val.getType()), const String& op, const String& objType, const QValue& val);
		IMQ_ERROR_DEF(math_operator_obj_invalid, "Operator " << op << " is not valid for types " << objType << " and " << valType, const String& op, const String& objType, const String& valType);
		IMQ_ERROR_DEF(math_object_order, "Operator " << op << " cannot operate on objects unless they are on the left-hand side.", const String& op);
		IMQ_ERROR_DEF(math_divide_by_zero, "Divide by zero error");
		IMQ_ERROR_DEF(math_mod_by_zero, "Mod by zero error");

		IMQ_ERROR_DEF(args_count, "Wrong number of arguments to " << funcName << " (expected " << expected << ", got " << actual << ")", const String& funcName, int32_t expected, int32_t actual);
		IMQ_ERROR_DEF(args_count, "Wrong number of arguments to " << funcName << " (expected between " << low << " and " << high << ", got " << actual << ")", const String& funcName, int32_t low, int32_t high, int32_t actual);
		IMQ_ERROR_DEF(args_count, "Wrong number of arguments to " << funcName << " (expected " << expected << ", got " << actual << ")", const String& funcName, const String& expected, int32_t actual);
		
		IMQ_ERROR_DEF(args_type, "Invalid type for argument #" << (argIndex + 1) << " to " << funcName << " (expected " << expected << ", got " << actual << ")", const String& funcName, int32_t argIndex, const String& expected, const String& actual);
		IMQ_ERROR_DEF(args_type, "Invalid type for argument #" << (argIndex + 1) << " to " << funcName << " (expected " << expected << ", got " << QValue::getTypeString(val.getType()) << ")", const String& funcName, int32_t argIndex, const String& expected, const QValue& val);

		IMQ_ERROR_DEF(args_bounds, "Argument #" << (argIndex + 1) << " to " << funcName << " is out of bounds - " << msg, const String& funcName, int32_t argIndex, const String& msg);

		IMQ_ERROR_DEF(args_invalid, "Argument #" << (argIndex + 1) << " to " << funcName << " is invalid - " << msg, const String& funcName, int32_t argIndex, const String& msg);
		
		IMQ_ERROR_DEF(return_type, "Invalid return type (expected " << expected << ", got " << actual << ")", const String& expected, const String& actual);
		IMQ_ERROR_DEF(return_type, "Invalid return type (expected " << expected << ", got " << QValue::getTypeString(val.getType()) << ")", const String& expected, const QValue& val);

		IMQ_ERROR_DEF(func_generic_error, msg, const String& msg);

		IMQ_ERROR_DEF(file_open, "Unable to open file " << filename, const String& filename);

		IMQ_ERROR_DEF(conversion, "Unable to convert " << QValue::getTypeString(value.getType()) << " to " << targetType, const QValue& value, const String& targetType);

		IMQ_ERROR_DEF(import_err, path << ": " << err, const String& path, const String& err);
	}
}

#undef IMQ_ERROR_DEF