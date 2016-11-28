#include <imq/context.h>
#include <imq/errors.h>
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

TEST(SubContext, Construct)
{
	ContextPtr parent(new SimpleContext());
	SubContext ctx(parent);

	EXPECT_EQ(ctx.getParent(), parent);
}

TEST(SubContext, Values)
{
	ContextPtr parent(new SimpleContext());
	SubContext ctx(parent);
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

	ASSERT_TRUE(parent->setValue("baz", QValue::Integer(321)));
	EXPECT_TRUE(ctx.hasValue("baz"));
	EXPECT_TRUE(ctx.getValue("baz", &value));
	EXPECT_EQ(value, QValue::Integer(321));

	EXPECT_TRUE(ctx.setValue("baz", QValue::Integer(123)));
	EXPECT_TRUE(parent->getValue("baz", &value));
	EXPECT_EQ(value, QValue::Integer(321));
	EXPECT_TRUE(ctx.getValue("baz", &value));
	EXPECT_EQ(value, QValue::Integer(123));

	EXPECT_TRUE(ctx.deleteValue("baz"));
	EXPECT_TRUE(ctx.hasValue("baz"));
	EXPECT_TRUE(ctx.deleteValue("baz"));
	EXPECT_FALSE(ctx.hasValue("baz"));
	EXPECT_FALSE(parent->hasValue("baz"));
}

TEST(RestrictedSubContext, Construct)
{
	ContextPtr parent(new SimpleContext());
	RestrictedSubContext ctx(parent);

	EXPECT_EQ(ctx.getParent(), parent);
}

TEST(RestrictedSubContext, Values)
{
	ContextPtr parent(new SimpleContext());
	RestrictedSubContext ctx(parent);
	QValue value;

	EXPECT_FALSE(ctx.hasValue("foobar"));
	EXPECT_FALSE(ctx.getValue("foobar", &value));
	EXPECT_FALSE(ctx.deleteValue("foobar"));

	Result result = ctx.setValue("foobar", QValue::Integer(123));
	ASSERT_FALSE(result);
	EXPECT_EQ(result.getErr(), errors::context_no_write_access().getErr());

	result = ctx.deleteValue("foobar");
	ASSERT_FALSE(result);
	EXPECT_EQ(result.getErr(), errors::context_no_delete_access().getErr());

	ASSERT_TRUE(parent->setValue("baz", QValue::Integer(321)));
	EXPECT_TRUE(ctx.hasValue("baz"));
	EXPECT_TRUE(ctx.getValue("baz", &value));
	EXPECT_EQ(value, QValue::Integer(321));

	EXPECT_FALSE(ctx.deleteValue("baz"));
	EXPECT_TRUE(ctx.hasValue("baz"));
	EXPECT_TRUE(parent->deleteValue("baz"));
	EXPECT_FALSE(ctx.hasValue("baz"));
	EXPECT_FALSE(parent->hasValue("baz"));
}