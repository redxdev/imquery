#include <imq/context.h>
#include <gtest/gtest.h>

using namespace imq;

TEST(SimpleContext, Construct)
{
	SimpleContext ctx;
}

TEST(SimpleContext, Values)
{
	SimpleContext ctx;
	QValue value;

	EXPECT_FALSE(ctx.hasValue("foobar"));
	EXPECT_FALSE(ctx.getValue("foobar", &value));
	EXPECT_FALSE(ctx.deleteValue("foobar"));

	EXPECT_TRUE(ctx.setValue("foobar", QValue::Integer(123)));
	EXPECT_TRUE(ctx.hasValue("foobar"));
	EXPECT_TRUE(ctx.getValue("foobar", &value));
	EXPECT_EQ(value, QValue::Integer(123));

	EXPECT_TRUE(ctx.deleteValue("foobar"));
	EXPECT_FALSE(ctx.hasValue("foobar"));
	EXPECT_FALSE(ctx.getValue("foobar", &value));
	EXPECT_FALSE(ctx.deleteValue("foobar"));
}