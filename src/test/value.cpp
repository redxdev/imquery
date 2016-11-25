#include <imq/value.h>
#include <gtest/gtest.h>

#include "test/sampleobject.h"

using namespace imq;

TEST(QValue, Creation)
{
	bool b;
	int32_t i;
	float f;
	NativeFunction func;
	QObjectPtr obj;

	QValue value;
	ASSERT_TRUE(value.isNil());

	value = QValue::Nil();
	ASSERT_TRUE(value.isNil());

	value = QValue::Bool(true);
	ASSERT_TRUE(value.isBool());
	ASSERT_TRUE(value.getBool(&b));
	ASSERT_EQ(b, true);

	value = QValue::Integer(123);
	ASSERT_TRUE(value.isInteger());
	ASSERT_TRUE(value.getInteger(&i));
	ASSERT_EQ(i, 123);

	value = QValue::Float(123.45f);
	ASSERT_TRUE(value.isFloat());
	ASSERT_TRUE(value.getFloat(&f));
	ASSERT_EQ(f, 123.45f);

	value = QValue::Function(sampleNativeFunction);
	ASSERT_TRUE(value.isFunction());
	ASSERT_TRUE(value.getFunction(&func));
	ASSERT_EQ(func(0, nullptr, nullptr), false);

	value = QValue::Object(QObjectPtr(new SampleObject()));
	ASSERT_TRUE(value.isObject());
	ASSERT_TRUE(value.getObject(&obj));
	ASSERT_NE(objectCast<SampleObject>(obj.get()), nullptr);
}