#include <imq/value.h>
#include <imq/object.h>
#include <imq/cast.h>
#include <imq/vm.h>
#include <gtest/gtest.h>

#include "test/sampleobject.h"

using namespace imq;

TEST(QValue, Creation)
{
	VMachine vm;

	bool b;
	int32_t i;
	float f;
	String str;
	char* cstr;
	QFunction* func;
	QObject* obj;

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

	value = QValue::String("foo bar baz");
	ASSERT_TRUE(value.isString());
	ASSERT_TRUE(value.getString(&str));
	ASSERT_EQ(str, "foo bar baz");
	ASSERT_TRUE(value.getString(&cstr));
	ASSERT_STREQ(cstr, "foo bar baz");

	value = QValue::Function(&vm, sampleNativeFunction);
	ASSERT_TRUE(value.isFunction());
	ASSERT_TRUE(value.getFunction(&func));
	ASSERT_TRUE(func->execute(&vm, 0, nullptr, &value));

	value = QValue::Object(new SampleObject(&vm));
	ASSERT_TRUE(value.isObject());
	ASSERT_TRUE(value.getObject(&obj));
	ASSERT_NE(objectCast<SampleObject>(obj), nullptr);
}

TEST(QValue, Conversion)
{
	QValue value;
	QValue result;
	bool b;
	int32_t i;
	float f;
	String str;

	// Nil -> x
	ASSERT_FALSE(value.toBool(&result));
	ASSERT_FALSE(value.toInteger(&result));
	ASSERT_FALSE(value.toFloat(&result));

	// Bool -> x
	value = QValue::Bool(false);
	ASSERT_TRUE(value.toBool(&result));
	ASSERT_TRUE(result.getBool(&b));
	ASSERT_FALSE(b);
	
	ASSERT_TRUE(value.toInteger(&result));
	ASSERT_TRUE(result.getInteger(&i));
	ASSERT_EQ(i, 0);

	ASSERT_TRUE(value.toFloat(&result));
	ASSERT_TRUE(result.getFloat(&f));
	ASSERT_FLOAT_EQ(f, 0.f);

	ASSERT_TRUE(value.toString(&result));
	ASSERT_TRUE(result.getString(&str));
	ASSERT_EQ(str, "false");

	value = QValue::Bool(true);
	ASSERT_TRUE(value.toBool(&result));
	ASSERT_TRUE(result.getBool(&b));
	ASSERT_TRUE(b);

	ASSERT_TRUE(value.toInteger(&result));
	ASSERT_TRUE(result.getInteger(&i));
	ASSERT_EQ(i, 1);

	ASSERT_TRUE(value.toFloat(&result));
	ASSERT_TRUE(result.getFloat(&f));
	ASSERT_FLOAT_EQ(f, 1.f);

	ASSERT_TRUE(value.toString(&result));
	ASSERT_TRUE(result.getString(&str));
	ASSERT_EQ(str, "true");
}

TEST(QValue, ToString)
{
	VMachine vm;
	QValue value;

	ASSERT_EQ(value.asString(), "");
	
	value = QValue::Bool(false);
	ASSERT_EQ(value.asString(), "false");

	value = QValue::Bool(true);
	ASSERT_EQ(value.asString(), "true");

	value = QValue::Integer(12345);
	ASSERT_EQ(value.asString(), "12345");

	value = QValue::Float(123.45f);
	ASSERT_EQ(value.asString(), "123.45");

	value = QValue::String("foo bar baz");
	ASSERT_EQ(value.asString(), "\"foo bar baz\"");

	value = QValue::Function(&vm, sampleNativeFunction);
	ASSERT_EQ(value.asString(), "<QFunction>");

	value = QValue::Object(new SampleObject(&vm));
	ASSERT_EQ(value.asString(), "<SampleObject>");
}

TEST(QValue, Equality)
{
	VMachine vm;

	QValue valueA;
	QValue valueB;
	QObject* objPtrA = new SampleObject(&vm);
	QObject* objPtrB = new SampleObject(&vm);

	ASSERT_EQ(valueA, valueB);

	valueB = QValue::Bool(false);
	ASSERT_NE(valueA, valueB);

	valueA = QValue::Bool(false);
	ASSERT_EQ(valueA, valueB);

	valueB = QValue::Bool(true);
	ASSERT_NE(valueA, valueB);

	valueA = QValue::Integer(123);
	ASSERT_NE(valueA, valueB);

	valueB = QValue::Integer(10);
	ASSERT_NE(valueA, valueB);

	valueA = QValue::Integer(10);
	ASSERT_EQ(valueA, valueB);

	valueB = QValue::Float(14.8f);
	ASSERT_NE(valueA, valueB);

	valueA = QValue::Float(10.34f);
	ASSERT_NE(valueA, valueB);

	valueB = QValue::Float(10.34f);
	ASSERT_EQ(valueA, valueB);

	valueA = QValue::Function(&vm, sampleNativeFunction);
	ASSERT_NE(valueA, valueB);

	valueB = QValue::Function(&vm, sampleNativeFunction);
	ASSERT_NE(valueA, valueB); // separate function references (even to the same function pointer) should not be equal

	valueB = valueA;
	ASSERT_EQ(valueA, valueB); // this should have copied the reference and so the values should be equal

	valueA = QValue::Object(objPtrA);
	ASSERT_NE(valueA, valueB);

	valueB = QValue::Object(objPtrB);
	ASSERT_NE(valueA, valueB);

	valueA = QValue::Object(objPtrB);
	ASSERT_EQ(valueA, valueB);
}