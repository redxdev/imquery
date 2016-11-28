#include <imq/image.h>
#include <imq/value.h>
#include <gtest/gtest.h>

using namespace imq;

TEST(QColor, Construction)
{
	QColor color;

	ASSERT_FLOAT_EQ(color.getRed(), 0.f);
	ASSERT_FLOAT_EQ(color.getGreen(), 0.f);
	ASSERT_FLOAT_EQ(color.getBlue(), 0.f);
	ASSERT_FLOAT_EQ(color.getAlpha(), 1.f);

	color = QColor(0.5f, 0.3f, 0.2f, 0.1f);

	ASSERT_FLOAT_EQ(color.getRed(), 0.5f);
	ASSERT_FLOAT_EQ(color.getGreen(), 0.3f);
	ASSERT_FLOAT_EQ(color.getBlue(), 0.2f);
	ASSERT_FLOAT_EQ(color.getAlpha(), 0.1f);

	color = QColor(0.4f, 0.2f, 0.3f);

	ASSERT_FLOAT_EQ(color.getRed(), 0.4f);
	ASSERT_FLOAT_EQ(color.getGreen(), 0.2f);
	ASSERT_FLOAT_EQ(color.getBlue(), 0.3f);
	ASSERT_FLOAT_EQ(color.getAlpha(), 1.f);
}

TEST(QColor, Setters)
{
	QColor color;

	color.setRed(0.5f);
	color.setGreen(0.2f);
	color.setBlue(0.8f);
	color.setAlpha(0.25f);

	ASSERT_FLOAT_EQ(color.getRed(), 0.5f);
	ASSERT_FLOAT_EQ(color.getGreen(), 0.2f);
	ASSERT_FLOAT_EQ(color.getBlue(), 0.8f);
	ASSERT_FLOAT_EQ(color.getAlpha(), 0.25f);
}

TEST(QColor, Clamp)
{
	QColor color(2.f, 3.f, -1.f, 0.5f);
	color = color.clamp();

	ASSERT_FLOAT_EQ(color.getRed(), 1.f);
	ASSERT_FLOAT_EQ(color.getGreen(), 1.f);
	ASSERT_FLOAT_EQ(color.getBlue(), 0.f);
	ASSERT_FLOAT_EQ(color.getAlpha(), 0.5f);
}