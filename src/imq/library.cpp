#include "library.h"

#include <iostream>
#include <cmath>
#include <algorithm>
#include <memory>

#define _USE_MATH_DEFINES
#include <math.h>

#include "errors.h"
#include "parser.h"
#include "scriptfunction.h"
#include "image.h"
#include "structures.h"
#include "cast.h"
#include "value.h"
#include "hash.h"

namespace imq
{
	IMQ_LIB(register_stdlib)
	{
		IMQ_LIB_SUB(register_system);
		IMQ_LIB_SUB(register_gc);
		IMQ_LIB_SUB(register_conversion);
		IMQ_LIB_SUB(register_io);
		IMQ_LIB_SUB(register_math);
		IMQ_LIB_SUB(register_image);

		return true;
	}

	// copy(obj: Object) : Object
	// Copies an object and returns the copy, if the object allows copying.
	static Result system_copy(VMachine* vm, int32_t argCount, QValue* args, QValue* result)
	{
		if (argCount != 1)
			return errors::args_count("copy", 1, argCount);

		QObject* obj;
		if (!args[0].getObject(&obj))
		{
			return errors::args_type("copy", 0, "Object", args[0]);
		}

		return obj->copyObject(result);
	}

	// error(message?: Any)
	// Emits an error with the specified message. If no message is specified, a generic error is emitted.
	static Result system_error(VMachine* vm, int32_t argCount, QValue* args, QValue* result)
	{
		switch (argCount)
		{
		default:
			return errors::args_count("error", 0, 1, argCount);

		case 0:
			return errors::generic_script();

		case 1:
		{
			QValue strValue;
			if (!args[0].toString(&strValue))
				return errors::args_type("error", 0, "String", args[0]);

			String str;
			strValue.getString(&str);
			return errors::generic_script_message(str);
		}
		}
	}

	// hash(value: Any) : Integer
	// Calculate the hash of the given value.
	static Result system_hash(VMachine* vm, int32_t argCount, QValue* args, QValue* result)
	{
		if (argCount != 1)
		{
			return errors::args_count("hash", 1, argCount);
		}

		std::size_t value = std::hash<QValue>()(args[0]);
		*result = QValue::Integer((int32_t)value);
		return true;
	}

	// try(func: Function) : [result: Boolean, value: Any]
	// Attempt to call the given function. If an error occurs while calling the function, return `[false, error: string]` where `error`
	// is the error message. If the call is successful, return `[true, value: Any]` where `value` is the return value of the function.
	//
	// If an invalid function is passed to `try` or if a different type is passed, an error will be emitted (as opposed to returning an error
	// result).
	static Result system_try(VMachine* vm, int32_t argCount, QValue* args, QValue* result)
	{
		if (argCount != 1)
		{
			return errors::args_count("try", 1, argCount);
		}

		QFunction* func = nullptr;
		if (!args[0].getFunction(&func))
		{
			return errors::args_type("try", 0, "Function", args[0]);
		}

		QValue funcResult;
		Result res = func->execute(vm, 0, nullptr, &funcResult);
		std::vector<QValue> list;
		if (res)
		{
			list.push_back(QValue::Bool(true));
			list.push_back(funcResult);
		}
		else
		{
			list.push_back(QValue::Bool(false));
			list.push_back(QValue::String(res.getErr()));
		}

		*result = QValue::Object(new QList(vm, list));

		return true;
	}

	// compile(code: String) : Function
	// Parse and compile imquery code from a string. The result will be stored in the returned function, which can be called to execute said code.
	// The function returned will be a closure over the root context (local variables will not be available).
	//
	// Gotcha: This will always close over the root context, even if this is run in an imported file. As such, this function is more for
	// light metaprogramming and debugging the virtual machine than anything else.
	static Result system_compile(VMachine* vm, int32_t argCount, QValue* args, QValue* result)
	{
		if (argCount != 1)
		{
			return errors::args_count("compile", 1, argCount);
		}

		String codeString;
		if (!args[0].getString(&codeString))
		{
			return errors::args_type("compile", 0, "String", args[0]);
		}

		QueryParser parser;
		VBlock* block = nullptr;
		Result res = parser.parseString(codeString, &block);
		if (!res)
		{
			return res;
		}

		*result = QValue::Function(new ScriptFunction("<anon>", vm->getRootContext(), std::shared_ptr<VBlock>(block), std::vector<String>()));
		return true;
	}

	IMQ_LIB(register_system)
	{
		IMQ_LIB_FUNC("copy", system_copy);
		IMQ_LIB_FUNC("error", system_error);
		IMQ_LIB_FUNC("hash", system_hash);
		IMQ_LIB_FUNC("try", system_try);
		IMQ_LIB_FUNC("compile", system_compile);

		return true;
	}

	// gc_memory() : Integer
	// Get the amount of memory the GC is tracking.
	static Result gc_memory(VMachine* vm, int32_t argCount, QValue* args, QValue* result)
	{
		if (argCount != 0)
			return errors::args_count("gc_memory", 0, 0, argCount);

		*result = QValue::Integer((int32_t)vm->getGC()->getTrackedMemory());

		return true;
	}

	// gc_managed() : Integer
	// Get the number of objects the GC is managing.
	static Result gc_managed(VMachine* vm, int32_t argCount, QValue* args, QValue* result)
	{
		if (argCount != 0)
			return errors::args_count("gc_managed", 0, argCount);

		*result = QValue::Integer((int32_t)vm->getGC()->getManagedCount());
		return true;
	}

	// gc_barrier() : Integer
	// Get the GC's memory barrier.
	static Result gc_barrier(VMachine* vm, int32_t argCount, QValue* args, QValue* result)
	{
		if (argCount != 0)
			return errors::args_count("gc_barrier", 0, argCount);

		*result = QValue::Integer((int32_t)vm->getGC()->getCollectionBarrier());
		return true;
	}

	// gc_collect(force?: Boolean) : Boolean
	// Run a garbage collection cycle. If certain metrics aren't met, this won't actually run garbage collection.
	// Garbage collection can be forced by passing `true` as the first argument.
	//
	// Returns whether a collection cycle was run as the result of this function.
	static Result gc_collect(VMachine* vm, int32_t argCount, QValue* args, QValue* result)
	{
		if (argCount > 1)
			return errors::args_count("gc_collect", 0, 1, argCount);

		bool val = false;

		if (argCount == 1)
		{
			if (!args[0].getBool(&val))
			{
				return errors::args_type("gc_collect", 0, "Bool", args[0]);
			}
		}

		*result = QValue::Bool(vm->getGC()->collect(val));
		return true;
	}

	// gc_mode(mode?: String) : String or nil
	// If `mode` isn't passed, get the name of the mode the GC is in. If `mode` is passed, set the GC mode.
	//
	// Available modes:
	// - `Barriers`: The GC will run a collection cycle when the amount of tracked memory is above a certain threshold (the "barrier").
	//               The barrier will be moved depending on how often collection cycles are running.
	// - `NoBarriers`: The GC will always run collection cycles when it is able, and the calculation of barriers will be disabled. This mode is the
	//                 one that will save the most memory, but at the possible cost of CPU time.
	// - `Always`: The GC will always run collection cycles when it is able, but it _will_ calculate barriers. This is primarily for debugging purposes.
	static Result gc_mode(VMachine* vm, int32_t argCount, QValue* args, QValue* result)
	{
		if (argCount > 1)
			return errors::args_count("gc_mode", 0, 1, argCount);

		if (argCount == 0)
		{
			switch (vm->getGC()->getCollectionMode())
			{
			default:
				*result = QValue::String("Unknown");
				return true;

			case GCCollectionMode::Barriers:
				*result = QValue::String("Barriers");
				return true;

			case GCCollectionMode::NoBarriers:
				*result = QValue::String("NoBarriers");
				return true;

			case GCCollectionMode::Always:
				*result = QValue::String("Always");
				return true;
			}
		}

		String val;
		if (!args[0].getString(&val))
		{
			return errors::args_type("gc_mode", 0, "String", args[0]);
		}

		if (val == "Barriers")
		{
			vm->getGC()->setCollectionMode(GCCollectionMode::Barriers);
		}
		else if (val == "NoBarriers")
		{
			vm->getGC()->setCollectionMode(GCCollectionMode::NoBarriers);
		}
		else if (val == "Always")
		{
			vm->getGC()->setCollectionMode(GCCollectionMode::Always);
		}
		else
		{
			return errors::args_invalid("gc_mode", 0, "Expected a string containing one of 'Barriers', 'NoBarriers', or 'Always'");
		}

		return true;
	}

	IMQ_LIB(register_gc)
	{
		IMQ_LIB_FUNC("gc_memory", gc_memory);
		IMQ_LIB_FUNC("gc_managed", gc_managed);
		IMQ_LIB_FUNC("gc_barrier", gc_barrier);
		IMQ_LIB_FUNC("gc_collect", gc_collect);
		IMQ_LIB_FUNC("gc_mode", gc_mode);

		return true;
	}

	// bool(value: Any) : Boolean
	// Convert a value to a boolean if possible, and return the result.
	static Result convert_bool(VMachine* vm, int32_t argCount, QValue* args, QValue* result)
	{
		if (argCount != 1)
			return errors::args_count("bool", 1, argCount);

		if (args[0].toBool(result))
			return true;
		else
			return errors::conversion(args[0], "Bool");
	}

	// integer(value: Any) : Integer
	// Convert a value to an integer if possible, and return the result.
	static Result convert_integer(VMachine* vm, int32_t argCount, QValue* args, QValue* result)
	{
		if (argCount != 1)
			return errors::args_count("integer", 1, argCount);

		if (args[0].toInteger(result))
			return true;
		else
			return errors::conversion(args[0], "Integer");
	}

	// float(value: Any) : Float
	// Convert a value to a float if possible, and return the result.
	static Result convert_float(VMachine* vm, int32_t argCount, QValue* args, QValue* result)
	{
		if (argCount != 1)
			return errors::args_count("float", 1, argCount);

		if (args[0].toFloat(result))
			return true;
		else
			return errors::conversion(args[0], "Float");
	}

	// string(value: Any) : String
	// Convert a value to a string if possible, and return the result.
	static Result convert_string(VMachine* vm, int32_t argCount, QValue* args, QValue* result)
	{
		if (argCount != 1)
			return errors::args_count("string", 1, argCount);

		if (args[0].toString(result))
			return true;
		else
			return errors::conversion(args[0], "String");
	}

	// isbool(value: Any) : Boolean
	// Return whether or not the passed value is a boolean.
	static Result convert_isbool(VMachine* vm, int32_t argCount, QValue* args, QValue* result)
	{
		if (argCount != 1)
			return errors::args_count("isbool", 1, argCount);

		*result = QValue::Bool(args[0].isBool());
		return true;
	}

	// isinteger(value: Any) : Boolean
	// Return whether or not the passed value is an integer.
	static Result convert_isinteger(VMachine* vm, int32_t argCount, QValue* args, QValue* result)
	{
		if (argCount != 1)
			return errors::args_count("isinteger", 1, argCount);

		*result = QValue::Bool(args[0].isInteger());
		return true;
	}

	// isfloat(value: Any) : Boolean
	// Return whether or not the passed value is a float.
	static Result convert_isfloat(VMachine* vm, int32_t argCount, QValue* args, QValue* result)
	{
		if (argCount != 1)
			return errors::args_count("isfloat", 1, argCount);

		*result = QValue::Bool(args[0].isFloat());
		return true;
	}

	// isnumber(value: Any) : Boolean
	// Return whether or not the passed value is a float or an integer.
	static Result convert_isnumber(VMachine* vm, int32_t argCount, QValue* args, QValue* result)
	{
		if (argCount != 1)
			return errors::args_count("isnumber", 1, argCount);

		*result = QValue::Bool(args[0].isInteger() || args[0].isFloat());
		return true;
	}

	// isstring(value: Any) : Boolean
	// Return whether or not the passed value is a string.
	static Result convert_isstring(VMachine* vm, int32_t argCount, QValue* args, QValue* result)
	{
		if (argCount != 1)
			return errors::args_count("isstring", 1, argCount);

		*result = QValue::Bool(args[0].isString());
		return true;
	}

	// isobject(value: Any) : Boolean
	// Return whether or not the passed value is an object.
	static Result convert_isobject(VMachine* vm, int32_t argCount, QValue* args, QValue* result)
	{
		if (argCount != 1)
			return errors::args_count("isobject", 1, argCount);

		*result = QValue::Bool(args[0].isObject());
		return true;
	}

	// isfunction(value: Any) : Boolean
	// Return whether or not the passed value is a function.
	static Result convert_isfunction(VMachine* vm, int32_t argCount, QValue* args, QValue* result)
	{
		if (argCount != 1)
			return errors::args_count("isfunction", 1, argCount);

		*result = QValue::Bool(args[0].isFunction());
		return true;
	}

	// sametypes(a: Any, b: Any) : Boolean
	// Return whether or not the two values have the same types. If both values are object types, then the underlying
	// interface types are compared.
	static Result convert_sametypes(VMachine* vm, int32_t argCount, QValue* args, QValue* result)
	{
		if (argCount != 2)
			return errors::args_count("sametypes", 2, argCount);

		*result = QValue::Bool(checkTypesEqual(args[0], args[1]));
		return true;
	}

	// isnan(value: Float) : Boolean
	// Return whether or not the given float is NaN.
	static Result convert_isnan(VMachine* vm, int32_t argCount, QValue* args, QValue* result)
	{
		if (argCount != 1)
			return errors::args_count("isnan", 1, argCount);

		float val;
		if (!args[0].getFloat(&val))
		{
			*result = QValue::Bool(false);
			return true;
		}

		*result = QValue::Bool(std::isnan(val));
		return true;
	}

	// typename(value: Any) : String
	// Get the name of the type. This will get the name of the underlying interface for object types.
	static Result convert_typename(VMachine* vm, int32_t argCount, QValue* args, QValue* result)
	{
		if (argCount != 1)
			return errors::args_count("typename", 1, argCount);

		if (args[0].getType() == QValue::Type::Object)
		{
			QObject* obj;
			args[0].getObject(&obj);
			*result = QValue::String(obj->getTypeString());
			return true;
		}

		*result = QValue::String(QValue::getTypeString(args[0].getType()));
		return true;
	}

	IMQ_LIB(register_conversion)
	{
		IMQ_LIB_FUNC("bool", convert_bool);
		IMQ_LIB_FUNC("integer", convert_integer);
		IMQ_LIB_FUNC("float", convert_float);
		IMQ_LIB_FUNC("string", convert_string);

		IMQ_LIB_FUNC("isbool", convert_isbool);
		IMQ_LIB_FUNC("isinteger", convert_isinteger);
		IMQ_LIB_FUNC("isfloat", convert_isfloat);
		IMQ_LIB_FUNC("isnumber", convert_isnumber);
		IMQ_LIB_FUNC("isstring", convert_isstring);
		IMQ_LIB_FUNC("isobject", convert_isobject);
		IMQ_LIB_FUNC("isfunction", convert_isfunction);

		IMQ_LIB_FUNC("sametypes", convert_sametypes);

		IMQ_LIB_FUNC("isnan", convert_isnan);

		IMQ_LIB_FUNC("typename", convert_typename);

		return true;
	}

	// print(value...: Any)
	// Print a string to stdout (with a newline at the end). Arguments will be concatinated.
	static Result io_print(VMachine* vm, int32_t argCount, QValue* args, QValue* result)
	{
		QValue value;
		for (int32_t i = 0; i < argCount; ++i)
		{
			if (args[i].toString(&value))
			{
				String str;
				value.getString(&str);
				std::cout << str;
			}
			else
			{
				std::cout << args[i].asString();
			}
		}

		std::cout << std::endl;

		*result = QValue::Nil();
		return true;
	}

	// getline() : String
	// Get a line from cin.
	static Result io_getline(VMachine* vm, int32_t argCount, QValue* args, QValue* result)
	{
		if (argCount != 0)
			return errors::args_count("getline", 0, argCount);

		String line;
		std::getline(std::cin, line);

		*result = QValue::String(line);
		return true;
	}

	// getcwd() : String
	// Get the current working directory.
	static Result io_getcwd(VMachine* vm, int32_t argCount, QValue* args, QValue* result)
	{
		if (argCount != 0)
			return errors::args_count("getcwd", 0, argCount);

		*result = QValue::String(vm->getWorkingDirectory());
		return true;
	}

	// buildpath(path: String) : String
	// Try to build a path to an existing file or directory based on the list of search paths passed to the VM.
	// This is useful if you need a full path to an asset or file.
	static Result io_buildpath(VMachine* vm, int32_t argCount, QValue* args, QValue* result)
	{
		if (argCount != 1)
			return errors::args_count("buildpath", 1, argCount);

		String str;
		if (!args[0].getString(&str))
		{
			return errors::args_type("buildpath", 0, "String", args[0]);
		}

		*result = QValue::String(vm->buildPath(str));
		return true;
	}

	IMQ_LIB(register_io)
	{
		IMQ_LIB_FUNC("print",		io_print);
		IMQ_LIB_FUNC("getline",		io_getline);
		IMQ_LIB_FUNC("getcwd",		io_getcwd);
		IMQ_LIB_FUNC("buildpath",	io_buildpath);

		return true;
	}

	// abs(a: Number) : Number
	static Result math_abs(VMachine* vm, int32_t argCount, QValue* args, QValue* result)
	{
		if (argCount != 1)
			return errors::args_count("abs", 1, argCount);

		switch (args[0].getType())
		{
		default:
			return errors::args_type("abs", 0, "Integer or Float", args[0]);

		case QValue::Type::Integer:
		{
			int32_t i;
			if (!args[0].getInteger(&i))
				return errors::func_generic_error("Something went wrong during QValue::getInteger");

			*result = QValue::Integer(std::abs(i));
			return true;
		}

		case QValue::Type::Float:
		{
			float f;
			if (!args[0].getFloat(&f))
				return errors::func_generic_error("Something went wrong during QValue::getFloat");

			*result = QValue::Float(std::fabs(f));
			return true;
		}
		}
	}

	// sin(radians: Number) : Float
	static Result math_sin(VMachine* vm, int32_t argCount, QValue* args, QValue* result)
	{
		if (argCount != 1)
			return errors::args_count("sin", 1, argCount);

		float val;
		if (!args[0].getNumber(&val))
			return errors::args_type("sin", 0, "Number", args[0]);

		*result = QValue::Float(std::sin(val));
		return true;
	}

	// cos(radians: Number) : Float
	static Result math_cos(VMachine* vm, int32_t argCount, QValue* args, QValue* result)
	{
		if (argCount != 1)
			return errors::args_count("cos", 1, argCount);

		float val;
		if (!args[0].getNumber(&val))
			return errors::args_type("cos", 0, "Number", args[0]);

		*result = QValue::Float(std::cos(val));
		return true;
	}

	// tan(radians: Number) : Float
	static Result math_tan(VMachine* vm, int32_t argCount, QValue* args, QValue* result)
	{
		if (argCount != 1)
			return errors::args_count("tan", 1, argCount);

		float val;
		if (!args[0].getNumber(&val))
			return errors::args_type("tan", 0, "Number", args[0]);

		*result = QValue::Float(std::tan(val));
		return true;
	}

	// min(a: Number, b: Number) : Number
	static Result math_min(VMachine* vm, int32_t argCount, QValue* args, QValue* result)
	{
		if (argCount != 2)
			return errors::args_count("min", 2, argCount);

		switch (args[0].getType())
		{
		default:
			return errors::args_type("min", 0, "Number", args[0]);

		case QValue::Type::Integer:
		{
			int32_t a;
			int32_t b;
			args[0].getInteger(&a);
			if (!args[1].getInteger(&b))
			{
				return errors::args_type("min", 1, "Integer", args[1]);
			}

			*result = QValue::Integer(std::min<int32_t>(a, b));
			return true;
		}

		case QValue::Type::Float:
		{
			float a;
			float b;
			args[0].getFloat(&a);
			if (!args[1].getFloat(&b))
			{
				return errors::args_type("min", 1, "Float", args[1]);
			}

			*result = QValue::Float(std::min<float>(a, b));
			return true;
		}
		}
	}

	// max(a: Number, b: Number) : Number
	static Result math_max(VMachine* vm, int32_t argCount, QValue* args, QValue* result)
	{
		if (argCount != 2)
			return errors::args_count("max", 2, argCount);

		switch (args[0].getType())
		{
		default:
			return errors::args_type("max", 0, "Number", args[0]);

		case QValue::Type::Integer:
		{
			int32_t a;
			int32_t b;
			args[0].getInteger(&a);
			if (!args[1].getInteger(&b))
			{
				return errors::args_type("max", 1, "Integer", args[1]);
			}

			*result = QValue::Integer(std::max<int32_t>(a, b));
			return true;
		}

		case QValue::Type::Float:
		{
			float a;
			float b;
			args[0].getFloat(&a);
			if (!args[1].getFloat(&b))
			{
				return errors::args_type("max", 1, "Float", args[1]);
			}

			*result = QValue::Float(std::max<float>(a, b));
			return true;
		}
		}
	}

	// clamp(value: Number, low: Number, high: Number) : Number
	static Result math_clamp(VMachine* vm, int32_t argCount, QValue* args, QValue* result)
	{
		if (argCount != 3)
			return errors::args_count("clamp", 2, argCount);

		switch (args[0].getType())
		{
		default:
			return errors::args_type("clamp", 0, "Number", args[0]);

		case QValue::Type::Integer:
		{
			int32_t v;
			int32_t low;
			int32_t high;
			args[0].getInteger(&v);
			if (!args[1].getInteger(&low))
			{
				return errors::args_type("clamp", 1, "Integer", args[1]);
			}

			if (!args[2].getInteger(&high))
			{
				return errors::args_type("clamp", 2, "Integer", args[2]);
			}

			if (low >= high)
			{
				return errors::func_generic_error("low >= high in clamp");
			}

			if (v < low)
			{
				*result = QValue::Integer(low);
			}
			else if (v > high)
			{
				*result = QValue::Integer(high);
			}
			else
			{
				*result = QValue::Integer(v);
			}

			return true;
		}

		case QValue::Type::Float:
		{
			float v;
			float low;
			float high;
			args[0].getFloat(&v);
			if (!args[1].getFloat(&low))
			{
				return errors::args_type("clamp", 1, "Float", args[1]);
			}

			if (!args[2].getFloat(&high))
			{
				return errors::args_type("clamp", 2, "Float", args[2]);
			}

			if (low >= high)
			{
				return errors::func_generic_error("low >= high in clamp");
			}

			if (v < low)
			{
				*result = QValue::Float(low);
			}
			else if (v > high)
			{
				*result = QValue::Float(high);
			}
			else
			{
				*result = QValue::Float(v);
			}

			return true;
		}
		}
	}

	// pow(base: Number, exp: Number) : Float
	static Result math_pow(VMachine* vm, int32_t argCount, QValue* args, QValue* result)
	{
		if (argCount != 2)
		{
			return errors::args_count("pow", 2, argCount);
		}

		float base;
		float exp;

		if (!args[0].getNumber(&base))
		{
			return errors::args_type("pow", 0, "Number", args[0]);
		}

		if (!args[1].getNumber(&exp))
		{
			return errors::args_type("pow", 1, "Number", args[1]);
		}

		*result = QValue::Float(std::pow(base, exp));
		return true;
	}

	// sqrt(value: Number) : Float
	static Result math_sqrt(VMachine* vm, int32_t argCount, QValue* args, QValue* result)
	{
		if (argCount != 1)
		{
			return errors::args_count("sqrt", 1, argCount);
		}

		float arg;
		if (!args[0].getNumber(&arg))
		{
			return errors::args_type("sqrt", 0, "Number", args[0]);
		}

		*result = QValue::Float(std::sqrt(arg));
		return true;
	}

	// lerp(x: Any, y: Any, alpha: Float) : Any
	// `x` and `y` can be any types that implement `opMul` and `opAdd`. The return value will have a type defined by
	// the `opAdd` implementation for `x`
	static Result math_lerp(VMachine* vm, int32_t argCount, QValue* args, QValue* result)
	{
		if (argCount != 3)
		{
			return errors::args_count("lerp", 3, argCount);
		}

		QValue x = args[0];
		QValue y = args[1];
		float alpha;

		if (!args[2].getFloat(&alpha))
		{
			return errors::args_type("lerp", 2, "Float", args[2]);
		}

		QValue vX;
		Result res = x.opMul(QValue::Float(1 - alpha), &vX);
		if (!res)
			return res;

		QValue vY;
		res = y.opMul(QValue::Float(alpha), &vY);
		if (!res)
			return res;

		return vX.opAdd(vY, result);
	}

	IMQ_LIB(register_math)
	{
		IMQ_LIB_FUNC("abs", math_abs);
		IMQ_LIB_FUNC("sin", math_sin);
		IMQ_LIB_FUNC("cos", math_cos);
		IMQ_LIB_FUNC("tan", math_tan);
		IMQ_LIB_FUNC("min", math_min);
		IMQ_LIB_FUNC("max", math_max);
		IMQ_LIB_FUNC("clamp", math_clamp);
		IMQ_LIB_FUNC("pow", math_pow);
		IMQ_LIB_FUNC("sqrt", math_sqrt);
		IMQ_LIB_FUNC("lerp", math_lerp);

		IMQ_LIB_VAL("pi", QValue::Float((float)M_PI));

		return true;
	}

	// image() : QImage
	// Construct an empty image.
	//
	// image(width: Integer, height: Integer, color?: QColor) : QImage
	// Construct an image of a specific width and height. If `color` is specified, all pixels will be set to that color. Otherwise, the color defaults to
	// {0, 0, 0, 1}.
	static Result image_construct(VMachine* vm, int32_t argCount, QValue* args, QValue* result)
	{
		switch (argCount)
		{
		default:
			return errors::args_count("image", "0, 2, or 3", argCount);

		case 0:
			*result = QValue::Object(new QImage(vm));
			return true;

		case 2:
		{
			int32_t w;
			int32_t h;

			if (!args[0].getInteger(&w))
			{
				return errors::args_type("image", 0, "Integer", args[0]);
			}

			if (!args[1].getInteger(&h))
			{
				return errors::args_type("image", 1, "Integer", args[1]);
			}

			if (w < 0)
			{
				return errors::args_bounds("image", 0, "argument must be >= 0");
			}

			if (h < 0)
			{
				return errors::args_bounds("image", 1, "argument must be >= 0");
			}

			*result = QValue::Object(new QImage(vm, w, h));
			return true;
		}

		case 3:
		{
			int32_t w;
			int32_t h;
			QObject* obj;
			QColor* color;

			if (!args[0].getInteger(&w))
			{
				return errors::args_type("image", 0, "Integer", args[0]);
			}

			if (!args[1].getInteger(&h))
			{
				return errors::args_type("image", 1, "Integer", args[1]);
			}

			if (!args[2].getObject(&obj))
			{
				return errors::args_type("image", 2, "Object", args[2]);
			}

			color = objectCast<QColor>(obj);
			if (!color)
			{
				return errors::args_type("image", 2, "Color", "Object");
			}

			if (w < 0)
			{
				return errors::args_bounds("image", 0, "argument must be >= 0");
			}

			if (h < 0)
			{
				return errors::args_bounds("image", 1, "argument must be >= 0");
			}

			*result = QValue::Object(new QImage(vm, w, h, *color));
			return true;
		}
		}
	}

	// image_load(path: String) : Qimage
	// Load an image from a file.
	static Result image_load(VMachine* vm, int32_t argCount, QValue* args, QValue* result)
	{
		if (argCount != 1)
			return errors::args_count("image_load", 1, argCount);

		char* path;
		if (!args[0].getString(&path))
		{
			return errors::args_type("image_load", 0, "String", args[0]);
		}

		QImage* image;

		Result res = QImage::loadFromFile(vm, path, &image);
		if (!res)
			return res;

		*result = QValue::Object(image);
		return true;
	}

	IMQ_LIB(register_image)
	{
		IMQ_LIB_FUNC("image", image_construct);
		IMQ_LIB_FUNC("image_load", image_load);

		return true;
	}
}