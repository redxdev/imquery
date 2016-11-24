#include "value.hpp"

namespace imq
{
	QObject::~QObject()
	{

	}

	String QObject::toString() const
	{
		return getTypeString();
	}

	bool QObject::getField(const String& name, QValue* result) const
	{
		return false;
	}

	bool QObject::setField(const String& name, const QValue& value)
	{
		return false;
	}

	bool QObject::getIndex(const QValue& index, QValue* result) const
	{
		return false;
	}

	bool QObject::setIndex(const QValue& index, const QValue& value)
	{
		return false;
	}

	TypeIndex ObjectRegistry::nextTypeIndex = 0;

	TypeIndex ObjectRegistry::createTypeIndex()
	{
		uint32_t index = nextTypeIndex;
		++nextTypeIndex;
		return index;
	}

	ObjectRegistry::ObjectRegistry()
	{
		typeIndex = ObjectRegistry::createTypeIndex();
	}

	TypeIndex ObjectRegistry::getTypeIndex() const
	{
		return typeIndex;
	}

	QValue QValue::Nil()
	{
		return QValue();
	}

	QValue QValue::Bool(bool val)
	{
		QValue result;
		result.valueType = Type::Bool;
		result.b = val;
		return result;
	}

	imq::QValue QValue::Integer(int32_t val)
	{
		QValue result;
		result.valueType = Type::Integer;
		result.i = val;
		return result;
	}

	QValue QValue::Float(float val)
	{
		QValue result;
		result.valueType = Type::Float;
		result.f = val;
		return result;
	}

	QValue QValue::Function(NativeFunction val)
	{
		QValue result;
		result.valueType = Type::Function;
		result.func = val;
		return result;
	}

	QValue QValue::Object(QObjectPtr val)
	{
		QValue result;
		result.valueType = Type::Object;
		result.obj = val;
		return result;
	}

	QValue::QValue()
	{
		valueType = Type::Nil;
	}

	QValue::QValue(const QValue& other)
	{
		valueType = other.valueType;
		switch (valueType)
		{
		default:
			break;

		case Type::Bool:
			b = other.b;
			break;

		case Type::Integer:
			i = other.i;
			break;

		case Type::Float:
			f = other.f;
			break;

		case Type::Object:
			obj = other.obj;
			break;

		case Type::Function:
			func = other.func;
			break;
		}
	}

	QValue::~QValue()
	{

	}

	QValue& QValue::operator=(const QValue& other)
	{
		valueType = other.valueType;
		switch (valueType)
		{
		default:
			break;

		case Type::Bool:
			b = other.b;
			break;

		case Type::Integer:
			i = other.i;
			break;

		case Type::Float:
			f = other.f;
			break;

		case Type::Object:
			obj = other.obj;
			break;

		case Type::Function:
			func = other.func;
			break;
		}

		return *this;
	}

}