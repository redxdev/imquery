#include <imq/image.h>
#include <imq/value.h>
#include <imq/errors.h>
#include <gtest/gtest.h>

using namespace imq;

TEST(QColor, Construction)
{
	QColor color;

	EXPECT_FLOAT_EQ(color.getRed(), 0.f);
	EXPECT_FLOAT_EQ(color.getGreen(), 0.f);
	EXPECT_FLOAT_EQ(color.getBlue(), 0.f);
	EXPECT_FLOAT_EQ(color.getAlpha(), 1.f);

	color = QColor(0.5f, 0.3f, 0.2f, 0.1f);

	EXPECT_FLOAT_EQ(color.getRed(), 0.5f);
	EXPECT_FLOAT_EQ(color.getGreen(), 0.3f);
	EXPECT_FLOAT_EQ(color.getBlue(), 0.2f);
	EXPECT_FLOAT_EQ(color.getAlpha(), 0.1f);

	color = QColor(0.4f, 0.2f, 0.3f);

	EXPECT_FLOAT_EQ(color.getRed(), 0.4f);
	EXPECT_FLOAT_EQ(color.getGreen(), 0.2f);
	EXPECT_FLOAT_EQ(color.getBlue(), 0.3f);
	EXPECT_FLOAT_EQ(color.getAlpha(), 1.f);
}

TEST(QColor, Equality)
{
	QColor colorA;
	QColor colorB;

	EXPECT_TRUE(colorA.equals(&colorB));
	EXPECT_EQ(colorA, colorB);

	colorA = QColor(0.3f, 0.1f, 0.f);
	EXPECT_FALSE(colorA.equals(&colorB));
	EXPECT_NE(colorA, colorB);
}

TEST(QColor, Setters)
{
	QColor color;

	color.setRed(0.5f);
	color.setGreen(0.2f);
	color.setBlue(0.8f);
	color.setAlpha(0.25f);

	EXPECT_FLOAT_EQ(color.getRed(), 0.5f);
	EXPECT_FLOAT_EQ(color.getGreen(), 0.2f);
	EXPECT_FLOAT_EQ(color.getBlue(), 0.8f);
	EXPECT_FLOAT_EQ(color.getAlpha(), 0.25f);
}

TEST(QColor, Clamp)
{
	QColor color(2.f, 3.f, -1.f, 0.5f);
	color = color.clamp();

	EXPECT_FLOAT_EQ(color.getRed(), 1.f);
	EXPECT_FLOAT_EQ(color.getGreen(), 1.f);
	EXPECT_FLOAT_EQ(color.getBlue(), 0.f);
	EXPECT_FLOAT_EQ(color.getAlpha(), 0.5f);
}

TEST(QColor, ToString)
{
	QColor color(0.5f, 0.3f, 0.1f, 1.f);

	EXPECT_EQ(color.toString(), "{0.5,0.3,0.1,1}");
}

TEST(QColor, GetField)
{
	QColor color(0.5f, 1.f, 0.3f, 0.4f);
	QValue value;

	ASSERT_TRUE(color.getField("r", &value));
	EXPECT_EQ(value, QValue::Float(0.5f));

	ASSERT_TRUE(color.getField("red", &value));
	EXPECT_EQ(value, QValue::Float(0.5f));

	ASSERT_TRUE(color.getField("g", &value));
	EXPECT_EQ(value, QValue::Float(1.f));

	ASSERT_TRUE(color.getField("green", &value));
	EXPECT_EQ(value, QValue::Float(1.f));

	ASSERT_TRUE(color.getField("b", &value));
	EXPECT_EQ(value, QValue::Float(0.3f));

	ASSERT_TRUE(color.getField("blue", &value));
	EXPECT_EQ(value, QValue::Float(0.3f));

	ASSERT_TRUE(color.getField("a", &value));
	EXPECT_EQ(value, QValue::Float(0.4f));

	ASSERT_TRUE(color.getField("alpha", &value));
	EXPECT_EQ(value, QValue::Float(0.4f));

	ASSERT_FALSE(color.getField("foobar", &value));
}

TEST(QColor, GetIndex)
{
	QColor color(0.5f, 1.f, 0.3f, 0.4f);
	QValue value;

	ASSERT_TRUE(color.getIndex(QValue::Integer(0), &value));
	EXPECT_EQ(value, QValue::Float(0.5f));

	ASSERT_TRUE(color.getIndex(QValue::Integer(1), &value));
	EXPECT_EQ(value, QValue::Float(1.f));

	ASSERT_TRUE(color.getIndex(QValue::Integer(2), &value));
	EXPECT_EQ(value, QValue::Float(0.3f));

	ASSERT_TRUE(color.getIndex(QValue::Integer(3), &value));
	EXPECT_EQ(value, QValue::Float(0.4f));

	ASSERT_FALSE(color.getIndex(QValue::Integer(-123), &value));
	ASSERT_FALSE(color.getIndex(QValue::Integer(123), &value));
}

TEST(QColor, SetField)
{
	QColor color(0.f, 0.f, 0.f, 0.f);
	
	ASSERT_FALSE(color.setField("r", QValue::Float(0.1f)));
	ASSERT_FALSE(color.setField("g", QValue::Float(0.3f)));
	ASSERT_FALSE(color.setField("b", QValue::Float(0.25f)));
	ASSERT_FALSE(color.setField("a", QValue::Float(0.56f)));

	EXPECT_FLOAT_EQ(color.getRed(), 0.f);
	EXPECT_FLOAT_EQ(color.getGreen(), 0.f);
	EXPECT_FLOAT_EQ(color.getBlue(), 0.f);
	EXPECT_FLOAT_EQ(color.getAlpha(), 0.f);

	ASSERT_FALSE(color.setField("red", QValue::Float(0.12f)));
	ASSERT_FALSE(color.setField("green", QValue::Float(0.33f)));
	ASSERT_FALSE(color.setField("blue", QValue::Float(0.256f)));
	ASSERT_FALSE(color.setField("alpha", QValue::Float(0.561f)));

	EXPECT_FLOAT_EQ(color.getRed(), 0.f);
	EXPECT_FLOAT_EQ(color.getGreen(), 0.f);
	EXPECT_FLOAT_EQ(color.getBlue(), 0.f);
	EXPECT_FLOAT_EQ(color.getAlpha(), 0.f);
}

TEST(QColor, SetIndex)
{
	QColor color(0.f, 0.f, 0.f, 0.f);

	ASSERT_FALSE(color.setIndex(QValue::Integer(0), QValue::Float(0.1f)));
	ASSERT_FALSE(color.setIndex(QValue::Integer(1), QValue::Float(0.3f)));
	ASSERT_FALSE(color.setIndex(QValue::Integer(2), QValue::Float(0.25f)));
	ASSERT_FALSE(color.setIndex(QValue::Integer(3), QValue::Float(0.56f)));

	EXPECT_FLOAT_EQ(color.getRed(), 0.f);
	EXPECT_FLOAT_EQ(color.getGreen(), 0.f);
	EXPECT_FLOAT_EQ(color.getBlue(), 0.f);
	EXPECT_FLOAT_EQ(color.getAlpha(), 0.f);
}

TEST(QImage, Construction)
{
	QImage image;
	QColor color;

	ASSERT_EQ(image.getWidth(), 0);
	ASSERT_EQ(image.getHeight(), 0);
	ASSERT_EQ(image.getData(), nullptr);

	image = QImage(100, 123);

	ASSERT_EQ(image.getWidth(), 100);
	ASSERT_EQ(image.getHeight(), 123);
	ASSERT_NE(image.getData(), nullptr);

	for (int32_t y = 0; y < 123; ++y)
	{
		for (int32_t x = 0; x < 100; ++x)
		{
			ASSERT_TRUE(image.getPixel(x, y, &color));
			EXPECT_EQ(color, QColor(0.f, 0.f, 0.f, 1.f));
		}
	}

	image = QImage(100, 123, QColor(0.3f, 0.5f, 0.2f, 0.8f));

	ASSERT_EQ(image.getWidth(), 100);
	ASSERT_EQ(image.getHeight(), 123);
	ASSERT_NE(image.getData(), nullptr);

	for (int32_t y = 0; y < 123; ++y)
	{
		for (int32_t x = 0; x < 100; ++x)
		{
			ASSERT_TRUE(image.getPixel(x, y, &color));
			EXPECT_EQ(color, QColor(0.3f, 0.5f, 0.2f, 0.8f));
		}
	}
}

TEST(QImage, ToString)
{
	QImage image;

	EXPECT_EQ(image.toString(), "QImage[0,0]");

	image = QImage(103, 48);
	EXPECT_EQ(image.toString(), "QImage[103,48]");
}

TEST(QImage, Equality)
{
	QImage imageA(100, 100, QColor(0.4f, 0.3f, 0.2f, 0.1f));
	QImage imageB(100, 100, QColor(0.4f, 0.3f, 0.2f, 0.1f));
	EXPECT_TRUE(imageA.equals(&imageB));
	
	imageA = QImage(100, 100, QColor(0.4f, 0.4f, 0.4f, 0.4f));
	EXPECT_FALSE(imageA.equals(&imageB));

	imageA = QImage(103, 100, QColor(0.4f, 0.3f, 0.2f, 0.1f));
	EXPECT_FALSE(imageA.equals(&imageB));

	imageA = QImage(100, 103, QColor(0.4f, 0.3f, 0.2f, 0.1f));
	EXPECT_FALSE(imageA.equals(&imageB));
}

TEST(QImage, GetPixel)
{
	QImage image(100, 100, QColor(0.5f, 0.3f, 0.2f, 0.1f));
	QColor color;

	ASSERT_FALSE(image.getPixel(-1, 0, &color));
	ASSERT_FALSE(image.getPixel(0, -1, &color));
	ASSERT_FALSE(image.getPixel(105, 0, &color));
	ASSERT_FALSE(image.getPixel(0, 105, &color));

	for (int32_t y = 0; y < 100; ++y)
	{
		for (int32_t x = 0; x < 100; ++x)
		{
			EXPECT_TRUE(image.getPixel(x, y, &color));
		}
	}
}

TEST(QImage, SetPixel)
{
	QImage image(100, 100, QColor(0.f, 0.f, 0.f, 1.f));
	QColor color;

	ASSERT_FALSE(image.setPixel(-1, 0, QColor()));
	ASSERT_FALSE(image.setPixel(0, -1, QColor()));
	ASSERT_FALSE(image.setPixel(105, 0, QColor()));
	ASSERT_FALSE(image.setPixel(0, 105, QColor()));

	for (int32_t i = 0; i < 10; ++i)
	{
		ASSERT_TRUE(image.setPixel(i * 2, i * 3, QColor(1.f, 0.f, 0.f, 1.f)));
	}

	int32_t i = 0;

	for (int32_t y = 0; y < 100; ++y)
	{
		for (int32_t x = 0; x < 100; ++x)
		{
			ASSERT_TRUE(image.getPixel(x, y, &color));

			if (x == i * 2 && y == i * 3 && i < 10)
			{
				EXPECT_EQ(color, QColor(1.f, 0.f, 0.f, 1.f));
				++i;
			}
			else
			{
				EXPECT_EQ(color, QColor(0.f, 0.f, 0.f, 1.f));
			}
		}
	}
}

TEST(QImage, Clear)
{
	QImage image(100, 100);
	QColor color;

	image.clear(QColor(1.f, 0.f, 0.f, 1.f));
	for (int32_t y = 0; y < 100; ++y)
	{
		for (int32_t x = 0; x < 100; ++x)
		{
			ASSERT_TRUE(image.getPixel(x, y, &color));
			EXPECT_EQ(color, QColor(1.f, 0.f, 0.f, 1.f));
		}
	}

	image.clear(QColor(1.f, 1.f, 1.f, 1.f));
	for (int32_t y = 0; y < 100; ++y)
	{
		for (int32_t x = 0; x < 100; ++x)
		{
			ASSERT_TRUE(image.getPixel(x, y, &color));
			EXPECT_EQ(color, QColor(1.f, 1.f, 1.f, 1.f));
		}
	}
}

TEST(QImage, Clamp)
{
	QImage image(100, 100);
	QColor color;

	for (int32_t y = 0; y < 100; ++y)
	{
		for (int32_t x = 0; x < 100; ++x)
		{
			if (x == y)
			{
				ASSERT_TRUE(image.setPixel(x, y, QColor(0.f, 1.f, 0.5f, 0.3f)));
			}
			else if (x % 2 == 0)
			{
				ASSERT_TRUE(image.setPixel(x, y, QColor(2.f, 3.f, -0.2f, 0.5f)));
			}
			else
			{
				ASSERT_TRUE(image.setPixel(x, y, QColor(-1.f, 0.3f, 1.89f, -2.5f)));
			}
		}
	}

	image.clamp();

	for (int32_t y = 0; y < 100; ++y)
	{
		for (int32_t x = 0; x < 100; ++x)
		{
			ASSERT_TRUE(image.getPixel(x, y, &color));
			if (x == y)
			{
				EXPECT_EQ(color, QColor(0.f, 1.f, 0.5f, 0.3f));
			}
			else if (x % 2 == 0)
			{
				EXPECT_EQ(color, QColor(1.f, 1.f, 0.f, 0.5f));
			}
			else
			{
				EXPECT_EQ(color, QColor(0.f, 0.3f, 1.f, 0.f));
			}
		}
	}
}

TEST(QImage, GetField)
{
	QImage image(123, 456);
	QValue value;

	ASSERT_TRUE(image.getField("width", &value));
	EXPECT_EQ(value, QValue::Integer(123));

	ASSERT_TRUE(image.getField("w", &value));
	EXPECT_EQ(value, QValue::Integer(123));

	ASSERT_TRUE(image.getField("height", &value));
	EXPECT_EQ(value, QValue::Integer(456));

	ASSERT_TRUE(image.getField("h", &value));
	EXPECT_EQ(value, QValue::Integer(456));

	ASSERT_FALSE(image.getField("foo bar", &value));
}

TEST(QImage, LoadFromFile)
{
	QImage* image;
	QColor color;
	
	Result result = QImage::loadFromFile("does_not_exist.png", &image);
	ASSERT_FALSE(result);
	EXPECT_EQ(result.getErr(), errors::image_load_error("Unable to open file").getErr());

	ASSERT_TRUE(QImage::loadFromFile("images/checkerboard.png", &image));
	ASSERT_EQ(image->getWidth(), 10);
	ASSERT_EQ(image->getHeight(), 10);

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

	delete image;
}

TEST(QImage, SaveToFile)
{
	QImage* image = new QImage(100, 100);
	QColor color;

	for (int32_t y = 0; y < 100; ++y)
	{
		for (int32_t x = 0; x < 100; ++x)
		{
			if (x == y)
			{
				ASSERT_TRUE(image->setPixel(x, y, QColor(0.f, 0.f, 1.f, 1.f)));
			}
			else if (x % 2 == 0)
			{
				ASSERT_TRUE(image->setPixel(x, y, QColor(0.f, 0.f, 0.f, 1.f)));
			}
			else
			{
				ASSERT_TRUE(image->setPixel(x, y, QColor(1.f, 1.f, 1.f, 1.f)));
			}
		}
	}

	ASSERT_TRUE(image->saveToFile("images/test.png"));
	delete image;
	ASSERT_TRUE(QImage::loadFromFile("images/test.png", &image));

	for (int32_t y = 0; y < 100; ++y)
	{
		for (int32_t x = 0; x < 100; ++x)
		{
			ASSERT_TRUE(image->getPixel(x, y, &color));
			if (x == y)
			{
				EXPECT_EQ(color, QColor(0.f, 0.f, 1.f, 1.f));
			}
			else if (x % 2 == 0)
			{
				EXPECT_EQ(color, QColor(0.f, 0.f, 0.f, 1.f));
			}
			else
			{
				EXPECT_EQ(color, QColor(1.f, 1.f, 1.f, 1.f));
			}
		}
	}

	delete image;
}