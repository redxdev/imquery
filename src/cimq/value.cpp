#include "value.h"

#include <imq/value.h>

using namespace imq;

CIMQ_API void imqDestroyValue(imqValue* value)
{
	delete reinterpret_cast<QValue*>(value);
}

imqValue* imqNilValue()
{
	return reinterpret_cast<imqValue*>(new QValue(QValue::Nil()));
}

imqValue* imqBoolValue(bool val)
{
	return reinterpret_cast<imqValue*>(new QValue(QValue::Bool(val)));
}

imqValue* imqIntegerValue(int val)
{
	return reinterpret_cast<imqValue*>(new QValue(QValue::Integer(val)));
}

imqValue* imqFloatValue(float val)
{
	return reinterpret_cast<imqValue*>(new QValue(QValue::Float(val)));
}

imqValue* imqStringValue(const imqString val)
{
	return reinterpret_cast<imqValue*>(new QValue(QValue::String(val)));
}

imqValue* imqFunctionValue(imqFunction* val)
{
	return reinterpret_cast<imqValue*>(new QValue(QValue::Function(reinterpret_cast<QFunction*>(val))));
}

imqValue* imqObjectValue(imqObject* val)
{
	return reinterpret_cast<imqValue*>(new QValue(QValue::Object(reinterpret_cast<QObject*>(val))));
}

imqType imqGetValueType(imqValue* value)
{
	if (value == nullptr)
		return IMQ_NIL;

	return (imqType)reinterpret_cast<QValue*>(value)->getType();
}

imqValue* imqGetValueTypeString(imqType typeId)
{
	return reinterpret_cast<imqValue*>(new QValue(QValue::String(QValue::getTypeString((QValue::Type)typeId))));
}

imqValue* imqValueAsString(imqValue* value)
{
	return reinterpret_cast<imqValue*>(new QValue(QValue::String(reinterpret_cast<QValue*>(value)->asString())));
}

imqValue* imqCopyValue(imqValue* value)
{
	return reinterpret_cast<imqValue*>(new QValue(*reinterpret_cast<QValue*>(value)));
}

bool imqGetBool(imqValue* value, bool* result)
{
	return reinterpret_cast<QValue*>(value)->getBool(result);
}

bool imqGetInteger(imqValue* value, int* result)
{
	return reinterpret_cast<QValue*>(value)->getInteger(result);
}

bool imqGetFloat(imqValue* value, float* result)
{
	return reinterpret_cast<QValue*>(value)->getFloat(result);
}

bool imqGetNumberAsInteger(imqValue* value, int* result)
{
	return reinterpret_cast<QValue*>(value)->getNumber(result);
}

bool imqGetNumberAsFloat(imqValue* value, float* result)
{
	return reinterpret_cast<QValue*>(value)->getNumber(result);
}

bool imqGetString(imqValue* value, imqString* result)
{
	return reinterpret_cast<QValue*>(value)->getString(result);
}

bool imqGetFunction(imqValue* value, imqFunction** result)
{
	QFunction* r;
	bool b = reinterpret_cast<QValue*>(value)->getFunction(&r);
	if (b)
	{
		*result = reinterpret_cast<imqFunction*>(r);
	}

	return b;
}

bool imqGetObject(imqValue* value, imqObject** result)
{
	QObject* o;
	bool b = reinterpret_cast<QValue*>(value)->getObject(&o);
	if (b)
	{
		*result = reinterpret_cast<imqObject*>(o);
	}

	return b;
}

imqValue* imqToBool(imqValue* value)
{
	QValue* v = new QValue();
	if (reinterpret_cast<QValue*>(value)->toBool(v))
	{
		return reinterpret_cast<imqValue*>(v);
	}

	return nullptr;
}

imqValue* imqToInteger(imqValue* value)
{
	QValue* v = new QValue();
	if (reinterpret_cast<QValue*>(value)->toInteger(v))
	{
		return reinterpret_cast<imqValue*>(v);
	}

	return nullptr;
}

imqValue* imqToFloat(imqValue* value)
{
	QValue* v = new QValue();
	if (reinterpret_cast<QValue*>(value)->toFloat(v))
	{
		return reinterpret_cast<imqValue*>(v);
	}

	return nullptr;
}

imqValue* imqToString(imqValue* value)
{
	QValue* v = new QValue();
	if (reinterpret_cast<QValue*>(value)->toString(v))
	{
		return reinterpret_cast<imqValue*>(v);
	}

	return nullptr;
}

bool imqValueEquals(imqValue* a, imqValue* b)
{
	return *reinterpret_cast<QValue*>(a) == *reinterpret_cast<QValue*>(b);
}
