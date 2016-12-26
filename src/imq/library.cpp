#include "library.h"

#include <iostream>
#include <cmath>
#include <algorithm>

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
		IMQ_LIB_SUB(register_io);
		IMQ_LIB_SUB(register_math);
		IMQ_LIB_SUB(register_conversion);

		return true;
	}

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

	IMQ_LIB(register_system)
	{
		IMQ_LIB_FUNC("copy", system_copy);

		return true;
	}

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

	IMQ_LIB(register_io)
	{
		IMQ_LIB_FUNC("print", io_print);

		return true;
	}

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
		IMQ_LIB_FUNC("abs",		math_abs);
		IMQ_LIB_FUNC("sin",		math_sin);
		IMQ_LIB_FUNC("cos",		math_cos);
		IMQ_LIB_FUNC("tan",		math_tan);
		IMQ_LIB_FUNC("min",		math_min);
		IMQ_LIB_FUNC("max",		math_max);
		IMQ_LIB_FUNC("clamp",	math_clamp);
		IMQ_LIB_FUNC("pow",		math_pow);
		IMQ_LIB_FUNC("sqrt",	math_sqrt);
		IMQ_LIB_FUNC("lerp",	math_lerp);

		IMQ_LIB_VAL("pi", QValue::Float((float) M_PI));

		return true;
	}

	static Result convert_bool(VMachine* vm, int32_t argCount, QValue* args, QValue* result)
	{
		if (argCount != 1)
			return errors::args_count("bool", 1, argCount);

		if (args[0].toBool(result))
			return true;
		else
			return errors::conversion(args[0], "Bool");
	}

	static Result convert_integer(VMachine* vm, int32_t argCount, QValue* args, QValue* result)
	{
		if (argCount != 1)
			return errors::args_count("integer", 1, argCount);

		if (args[0].toInteger(result))
			return true;
		else
			return errors::conversion(args[0], "Integer");
	}

	static Result convert_float(VMachine* vm, int32_t argCount, QValue* args, QValue* result)
	{
		if (argCount != 1)
			return errors::args_count("float", 1, argCount);

		if (args[0].toFloat(result))
			return true;
		else
			return errors::conversion(args[0], "Float");
	}

	static Result convert_string(VMachine* vm, int32_t argCount, QValue* args, QValue* result)
	{
		if (argCount != 1)
			return errors::args_count("string", 1, argCount);

		if (args[0].toString(result))
			return true;
		else
			return errors::conversion(args[0], "String");
	}

	static Result convert_isbool(VMachine* vm, int32_t argCount, QValue* args, QValue* result)
	{
		if (argCount != 1)
			return errors::args_count("isbool", 1, argCount);

		*result = QValue::Bool(args[0].isBool());
		return true;
	}

	static Result convert_isinteger(VMachine* vm, int32_t argCount, QValue* args, QValue* result)
	{
		if (argCount != 1)
			return errors::args_count("isinteger", 1, argCount);

		*result = QValue::Bool(args[0].isInteger());
		return true;
	}

	static Result convert_isfloat(VMachine* vm, int32_t argCount, QValue* args, QValue* result)
	{
		if (argCount != 1)
			return errors::args_count("isfloat", 1, argCount);

		*result = QValue::Bool(args[0].isFloat());
		return true;
	}

	static Result convert_isnumber(VMachine* vm, int32_t argCount, QValue* args, QValue* result)
	{
		if (argCount != 1)
			return errors::args_count("isnumber", 1, argCount);

		*result = QValue::Bool(args[0].isInteger() || args[0].isFloat());
		return true;
	}

	static Result convert_isstring(VMachine* vm, int32_t argCount, QValue* args, QValue* result)
	{
		if (argCount != 1)
			return errors::args_count("isstring", 1, argCount);

		*result = QValue::Bool(args[0].isString());
		return true;
	}

	static Result convert_isobject(VMachine* vm, int32_t argCount, QValue* args, QValue* result)
	{
		if (argCount != 1)
			return errors::args_count("isobject", 1, argCount);

		*result = QValue::Bool(args[0].isObject());
		return true;
	}

	static Result convert_isfunction(VMachine* vm, int32_t argCount, QValue* args, QValue* result)
	{
		if (argCount != 1)
			return errors::args_count("isfunction", 1, argCount);

		*result = QValue::Bool(args[0].isFunction());
		return true;
	}

	static Result convert_sametypes(VMachine* vm, int32_t argCount, QValue* args, QValue* result)
	{
		if (argCount != 2)
			return errors::args_count("sametypes", 2, argCount);

		*result = QValue::Bool(checkTypesEqual(args[0], args[1]));
		return true;
	}

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
		IMQ_LIB_FUNC("bool",		convert_bool);
		IMQ_LIB_FUNC("integer",		convert_integer);
		IMQ_LIB_FUNC("float",		convert_float);
		IMQ_LIB_FUNC("string",		convert_string);

		IMQ_LIB_FUNC("isbool",		convert_isbool);
		IMQ_LIB_FUNC("isinteger",	convert_isinteger);
		IMQ_LIB_FUNC("isfloat",		convert_isfloat);
		IMQ_LIB_FUNC("isnumber",	convert_isnumber);
		IMQ_LIB_FUNC("isstring",	convert_isstring);
		IMQ_LIB_FUNC("isobject",	convert_isobject);
		IMQ_LIB_FUNC("isfunction",	convert_isfunction);

		IMQ_LIB_FUNC("sametypes",	convert_sametypes);

		IMQ_LIB_FUNC("isnan",		convert_isnan);

		IMQ_LIB_FUNC("typename",	convert_typename);

		return true;
	}
}