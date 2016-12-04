#include <imq/parser.h>
#include <imq/vm.h>
#include <imq/image.h>
#include <imq/cast.h>
#include <imq/errors.h>
#include <gtest/gtest.h>

using namespace imq;

const char* bad_query =
	"in input = image();\n"
	"out output = image(input.w, input.h);\n"
	"this_is_not_valid foobar;\n";

const char* copy_image =
	"in input = image();\n"
	"out output = image(input.w, input.h);" // the missing newline here is to test whether newlines are parsed correctly - this should still succeed.
	"output: color from input;";

TEST(Full, Parse)
{
	QueryParser parser;
	VBlock* block;
	ASSERT_FALSE(parser.parse(bad_query, &block));
	ASSERT_TRUE(parser.parse(copy_image, &block));

	delete block;
}

TEST(Full, ImageCopy)
{
	QueryParser parser;
	VBlock* block;
	VMachine vm;

	ASSERT_TRUE(parser.parse(copy_image, &block));

	QImage* srcImage;

	ASSERT_TRUE(QImage::loadFromFile("images/checkerboard.png", &srcImage));

	vm.getRootContext()->setInput("input", QValue::Object(srcImage));
	vm.getRootContext()->setValue("image", QValue::Function([](int32_t argCount, QValue* args, QValue* result) -> Result {
		if (argCount == 0)
		{
			*result = QValue::Object(new QImage());
			return true;
		}
		
		if (argCount != 2)
		{
			return errors::args_count("image", 2, argCount);
		}

		int32_t w;
		int32_t h;

		if (!args[0].getInteger(&w))
		{
			return errors::args_type("image", 1, "Integer", QValue::getTypeString(args[0].getType()));
		}

		if (!args[1].getInteger(&h))
		{
			return errors::args_type("image", 2, "Integer", QValue::getTypeString(args[1].getType()));
		}

		if (w < 0 || h < 0)
		{
			return errors::func_generic_error("Image dimensions must be >= 0");
		}

		*result = QValue::Object(new QImage(w, h));
		return true;
	}));

	ASSERT_TRUE(vm.execute(block));

	delete block;

	QValue value;
	ASSERT_TRUE(vm.getRootContext()->getValue("output", &value));

	QObjectPtr imagePtr;
	QImage* image;
	ASSERT_TRUE(value.getObject(&imagePtr));
	image = objectCast<QImage>(imagePtr.get());
	ASSERT_NE(image, nullptr);

	QColor color;
	for (int32_t y = 0; y < 10; ++y)
	{
		for (int32_t x = 0; x < 10; ++x)
		{
			ASSERT_TRUE(image->getPixel(x, y, &color));
			if (x == y)
			{
				EXPECT_EQ(color, QColor(1.f, 0.f, 0.f, 1.f));
			}
			else
			{
				if (y % 2 == 0)
				{
					if (x % 2 == 0)
					{
						EXPECT_EQ(color, QColor(0.f, 0.f, 0.f, 1.f));
					}
					else
					{
						EXPECT_EQ(color, QColor(1.f, 1.f, 1.f, 1.f));
					}
				}
				else
				{
					if (x % 2 == 0)
					{
						EXPECT_EQ(color, QColor(1.f, 1.f, 1.f, 1.f));
					}
					else
					{
						EXPECT_EQ(color, QColor(0.f, 0.f, 0.f, 1.f));
					}
				}
			}
		}
	}
}