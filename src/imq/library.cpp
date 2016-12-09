#include "library.h"

#include <iostream>

#define _USE_MATH_DEFINES
#include <math.h>

#include "errors.h"
#include "image.h"
#include "structures.h"
#include "cast.h"
#include "value.h"

namespace imq
{
	IMQ_LIB(register_stdlib)
	{
		IMQ_LIB_SUB(register_system);
		IMQ_LIB_SUB(register_image);
		IMQ_LIB_SUB(register_structures);
		IMQ_LIB_SUB(register_io);
		IMQ_LIB_SUB(register_math);
		IMQ_LIB_SUB(register_conversion);

		return true;
	}

	static Result system_copy(int32_t argCount, QValue* args, QValue* result)
	{
		if (argCount != 1)
			return errors::args_count("copy", 1, argCount);

		QObjectPtr obj;
		if (!args[0].getObject(&obj))
		{
			return errors::args_type("copy", 0, "Object", args[0]);
		}

		return obj->copyObject(result);
	}

	IMQ_LIB(register_system)
	{
		IMQ_LIB_FUNC("copy", system_copy);

		return true;
	}

	static Result image_construct(int32_t argCount, QValue* args, QValue* result)
	{
		switch (argCount)
		{
		default:
			return errors::args_count("image", "0, 2, or 3", argCount);

		case 0:
			*result = QValue::Object(new QImage());
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

			*result = QValue::Object(new QImage(w, h));
			return true;
		}

		case 3:
		{
			int32_t w;
			int32_t h;
			QObjectPtr obj;
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

			color = objectCast<QColor>(obj.get());
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

			*result = QValue::Object(new QImage(w, h, *color));
			return true;
		}
		}
	}

	IMQ_LIB(register_image)
	{
		IMQ_LIB_FUNC("image", image_construct);

		return true;
	}

	static Result structures_table(int32_t argCount, QValue* args, QValue* result)
	{
		switch (argCount)
		{
		default:
			return errors::args_count("table", 0, argCount);

		case 0:
			*result = QValue::Object(new QTable());
			return true;
		}
	}

	static Result structures_list(int32_t argCount, QValue* args, QValue* result)
	{
		switch (argCount)
		{
		default:
			return errors::args_count("list", 0, argCount);

		case 0:
			*result = QValue::Object(new QList());
			return true;
		}
	}

	IMQ_LIB(register_structures)
	{
		IMQ_LIB_FUNC("table", structures_table);
		IMQ_LIB_FUNC("list", structures_list);

		return true;
	}

	static Result io_print(int32_t argCount, QValue* args, QValue* result)
	{
		for (int32_t i = 0; i < argCount; ++i)
		{
			std::cout << args[i].toString();
		}

		std::cout << std::endl;

		*result = QValue::Nil();
		return true;
	}

	IMQ_LIB(register_io)
	{
		IMQ_LIB_FUNC("print", io_print);

		return true;
	}

	static Result math_abs(int32_t argCount, QValue* args, QValue* result)
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

	static Result math_sin(int32_t argCount, QValue* args, QValue* result)
	{
		if (argCount != 1)
			return errors::args_count("sin", 1, argCount);

		float val;
		if (!args[0].getFloat(&val))
			return errors::args_type("sin", 0, "Float", args[0]);

		*result = QValue::Float(std::sin(val));
		return true;
	}

	static Result math_cos(int32_t argCount, QValue* args, QValue* result)
	{
		if (argCount != 1)
			return errors::args_count("cos", 1, argCount);

		float val;
		if (!args[0].getFloat(&val))
			return errors::args_type("cos", 0, "Float", args[0]);

		*result = QValue::Float(std::cos(val));
		return true;
	}

	static Result math_tan(int32_t argCount, QValue* args, QValue* result)
	{
		if (argCount != 1)
			return errors::args_count("tan", 1, argCount);

		float val;
		if (!args[0].getFloat(&val))
			return errors::args_type("tan", 0, "Float", args[0]);

		*result = QValue::Float(std::tan(val));
		return true;
	}

	IMQ_LIB(register_math)
	{
		IMQ_LIB_FUNC("abs", math_abs);
		IMQ_LIB_FUNC("sin", math_sin);
		IMQ_LIB_FUNC("cos", math_cos);
		IMQ_LIB_FUNC("tan", math_tan);

		IMQ_LIB_VAL("pi", QValue::Float((float) M_PI));

		return true;
	}

	static Result convert_bool(int32_t argCount, QValue* args, QValue* result)
	{
		if (argCount != 1)
			return errors::args_count("bool", 1, argCount);

		if (args[0].toBool(result))
			return true;
		else
			return errors::conversion(args[0], "Bool");
	}

	static Result convert_integer(int32_t argCount, QValue* args, QValue* result)
	{
		if (argCount != 1)
			return errors::args_count("integer", 1, argCount);

		if (args[0].toInteger(result))
			return true;
		else
			return errors::conversion(args[0], "Integer");
	}

	static Result convert_float(int32_t argCount, QValue* args, QValue* result)
	{
		if (argCount != 1)
			return errors::args_count("float", 1, argCount);

		if (args[0].toFloat(result))
			return true;
		else
			return errors::conversion(args[0], "float");
	}

	static Result convert_isbool(int32_t argCount, QValue* args, QValue* result)
	{
		if (argCount != 1)
			return errors::args_count("isbool", 1, argCount);

		*result = QValue::Bool(args[0].isBool());
		return true;
	}

	static Result convert_isinteger(int32_t argCount, QValue* args, QValue* result)
	{
		if (argCount != 1)
			return errors::args_count("isinteger", 1, argCount);

		*result = QValue::Bool(args[0].isInteger());
		return true;
	}

	static Result convert_isfloat(int32_t argCount, QValue* args, QValue* result)
	{
		if (argCount != 1)
			return errors::args_count("isfloat", 1, argCount);

		*result = QValue::Bool(args[0].isFloat());
		return true;
	}

	static Result convert_isnumber(int32_t argCount, QValue* args, QValue* result)
	{
		if (argCount != 1)
			return errors::args_count("isnumber", 1, argCount);

		*result = QValue::Bool(args[0].isInteger() || args[0].isFloat());
		return true;
	}

	static Result convert_isobject(int32_t argCount, QValue* args, QValue* result)
	{
		if (argCount != 1)
			return errors::args_count("isobject", 1, argCount);

		*result = QValue::Bool(args[0].isObject());
		return true;
	}

	static Result convert_isfunction(int32_t argCount, QValue* args, QValue* result)
	{
		if (argCount != 1)
			return errors::args_count("isfunction", 1, argCount);

		*result = QValue::Bool(args[0].isFunction());
		return true;
	}

	static Result convert_sametypes(int32_t argCount, QValue* args, QValue* result)
	{
		if (argCount != 2)
			return errors::args_count("sametypes", 2, argCount);

		*result = QValue::Bool(checkTypesEqual(args[0], args[1]));
		return true;
	}

	IMQ_LIB(register_conversion)
	{
		IMQ_LIB_FUNC("bool",		convert_bool);
		IMQ_LIB_FUNC("integer",		convert_integer);
		IMQ_LIB_FUNC("float",		convert_float);

		IMQ_LIB_FUNC("isbool",		convert_isbool);
		IMQ_LIB_FUNC("isinteger",	convert_isinteger);
		IMQ_LIB_FUNC("isfloat",		convert_isfloat);
		IMQ_LIB_FUNC("isnumber",	convert_isnumber);
		IMQ_LIB_FUNC("isobject",	convert_isobject);
		IMQ_LIB_FUNC("isfunction",	convert_isfunction);

		IMQ_LIB_FUNC("sametypes",	convert_sametypes);

		return true;
	}
}