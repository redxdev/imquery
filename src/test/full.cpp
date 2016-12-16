#include <imq/parser.h>
#include <imq/vm.h>
#include <imq/image.h>
#include <imq/cast.h>
#include <imq/errors.h>
#include <imq/library.h>
#include <gtest/gtest.h>

using namespace imq;

static const char* bad_script = "in input = image();input = 5;asdf = 99; foo = () => {input.blah()};if (false) {print(12345.23);}\n"
	"out output =";
static const char* copy_image =
	"in input = image();\n"
	"out output = image(input.w, input.h);" // the missing newline here is to test whether newlines are parsed correctly - this should still succeed.
	"output: {color.r,color.g,color.b,color.a} from input;\n"
	"test = {0.,0.,0.,0.};";

TEST(Full, Parse)
{
	QueryParser parser;
	VBlock* block;

	ASSERT_FALSE(parser.parseString(bad_script, &block));
	ASSERT_TRUE(parser.parseString(copy_image, &block));

	delete block;
}

TEST(Full, ImageCopy)
{
	QueryParser parser;
	VBlock* block;
	VMachine vm;

	ASSERT_TRUE(register_stdlib(&vm));

	ASSERT_TRUE(parser.parseString(copy_image, &block));

	QImage* srcImage;

	ASSERT_TRUE(QImage::loadFromFile(&vm, "images/checkerboard.png", &srcImage));

	vm.getRootContext()->setInput("input", QValue::Object(srcImage));

	ASSERT_TRUE(vm.execute(block));

	delete block;

	QValue value;
	ASSERT_TRUE(vm.getRootContext()->getValue("output", &value));

	QObject* imagePtr;
	QImage* image;
	ASSERT_TRUE(value.getObject(&imagePtr));
	image = objectCast<QImage>(imagePtr);
	ASSERT_NE(image, nullptr);

	QColor color(&vm);
	for (int32_t y = 0; y < 10; ++y)
	{
		for (int32_t x = 0; x < 10; ++x)
		{
			ASSERT_TRUE(image->getPixel(x, y, &color));
			if (x == y)
			{
				EXPECT_EQ(color, QColor(&vm, 1.f, 0.f, 0.f, 1.f));
			}
			else
			{
				if (y % 2 == 0)
				{
					if (x % 2 == 0)
					{
						EXPECT_EQ(color, QColor(&vm, 0.f, 0.f, 0.f, 1.f));
					}
					else
					{
						EXPECT_EQ(color, QColor(&vm, 1.f, 1.f, 1.f, 1.f));
					}
				}
				else
				{
					if (x % 2 == 0)
					{
						EXPECT_EQ(color, QColor(&vm, 1.f, 1.f, 1.f, 1.f));
					}
					else
					{
						EXPECT_EQ(color, QColor(&vm, 0.f, 0.f, 0.f, 1.f));
					}
				}
			}
		}
	}
}