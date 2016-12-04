#include "library.h"

#include <iostream>

#include "errors.h"
#include "image.h"
#include "cast.h"
#include "value.h"

namespace imq
{
	IMQ_LIB(register_stdlib)
	{
		IMQ_LIB_SUB(register_image);
		IMQ_LIB_SUB(register_io);

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

	Result io_print(int32_t argCount, QValue* args, QValue* result)
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
}