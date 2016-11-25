#include "value.h"

#include <sstream>
#include <limits>
#include <cmath>

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

	QValue QValue::Function(QFunction val)
	{
		QValue result;
		result.valueType = Type::Function;
		new (&result.func) QFunction();
		result.func = val;
		return result;
	}

	QValue QValue::Object(QObjectPtr val)
	{
		QValue result;
		result.valueType = Type::Object;
		new (&result.obj) QObjectPtr();
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
			new (&obj) QObjectPtr();
			obj = other.obj;
			break;

		case Type::Function:
			new (&func) QFunction();
			func = other.func;
			break;
		}
	}

	QValue::~QValue()
	{
		switch (valueType)
		{
		case Type::Object:
			obj.~shared_ptr();
			break;

		case Type::Function:
			func.~function();
			break;
		}
	}

	QValue::Type QValue::getType() const
	{
		return valueType;
	}

	imq::String QValue::getString() const
	{
		switch (valueType)
		{
		default:
			return "<?>";

		case Type::Nil:
			return "";
			
		case Type::Bool:
			return b ? "true" : "false";

		case Type::Integer:
		{
			std::stringstream ss;
			ss << i;
			return ss.str();
		}

		case Type::Float:
		{
			std::stringstream ss;
			ss << f;
			return ss.str();
		}

		case Type::Function:
			return "QFunction";

		case Type::Object:
			return obj->toString();
		}
	}

	bool QValue::isNil() const
	{
		return valueType == Type::Nil;
	}

	bool QValue::isBool() const
	{
		return valueType == Type::Bool;
	}

	bool QValue::isInteger() const
	{
		return valueType == Type::Integer;
	}

	bool QValue::isFloat() const
	{
		return valueType == Type::Float;
	}

	bool QValue::isFunction() const
	{
		return valueType == Type::Function;
	}

	bool QValue::isObject() const
	{
		return valueType == Type::Object;
	}

	bool QValue::getBool(bool* result) const
	{
		if (isBool())
		{
			*result = b;
			return true;
		}

		return false;
	}

	bool QValue::getInteger(int32_t* result) const
	{
		if (isInteger())
		{
			*result = i;
			return true;
		}

		return false;
	}

	bool QValue::getFloat(float* result) const
	{
		if (isFloat())
		{
			*result = f;
			return true;
		}

		return false;
	}

	bool QValue::getFunction(QFunction* result) const
	{
		if (isFunction())
		{
			*result = func;
			return true;
		}

		return false;
	}

	bool QValue::getObject(QObjectPtr* result) const
	{
		if (isObject())
		{
			*result = obj;
			return true;
		}

		return false;
	}

	bool QValue::toBool(QValue* result) const
	{
		switch (valueType)
		{
		default:
			return false;

		case Type::Bool:
			*result = QValue(*this);
			return true;

		case Type::Integer:
			*result = QValue::Bool(i != 0);
			return true;

		case Type::Float:
			*result = QValue::Bool(std::abs(f) < std::numeric_limits<float>::epsilon());
			return true;
		}
	}

	bool QValue::toInteger(QValue* result) const
	{
		switch (valueType)
		{
		default:
			return false;

		case Type::Bool:
			*result = QValue::Integer(b ? 1 : 0);
			return true;

		case Type::Integer:
			*result = QValue(*this);
			return true;

		case Type::Float:
			*result = QValue::Integer((int32_t)f);
			return true;
		}
	}

	bool QValue::toFloat(QValue* result) const
	{
		switch (valueType)
		{
		default:
			return false;

		case Type::Bool:
			*result = QValue::Float(b ? 1.f : 0.f);
			return true;

		case Type::Integer:
			*result = QValue::Float((float)i);
			return true;

		case Type::Float:
			*result = QValue(*this);
			return true;
		}
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
			new (&obj) QObjectPtr();
			obj = other.obj;
			break;

		case Type::Function:
			new (&func) QFunction();
			func = other.func;
			break;
		}

		return *this;
	}

	bool operator==(const QValue& a, const QValue& b)
	{
		if (a.valueType != b.valueType)
			return false;

		switch (a.valueType)
		{
		default:
			return false;

		case QValue::Type::Nil:
			return true;

		case QValue::Type::Bool:
			return a.b == b.b;

		case QValue::Type::Integer:
			return a.i == b.i;

		case QValue::Type::Float:
			return a.f == b.f;

		case QValue::Type::Function:
			// NOTE - functions do not have equality operators, so we always return false here.
			return false;

		case QValue::Type::Object:
			return a.obj->equals(b.obj.get());
		}
	}

	bool operator!=(const QValue& a, const QValue& b)
	{
		return !(a == b);
	}
}