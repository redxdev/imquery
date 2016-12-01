#include "object.h"

#include "value.h"
#include "errors.h"

namespace imq
{
	QObject::~QObject()
	{

	}

	String QObject::toString() const
	{
		std::stringstream ss;
		ss << "<" << getTypeString() << ">";
		return ss.str();
	}

	Result QObject::getField(const String& name, QValue* result) const
	{
		return errors::undefined_get_field(getTypeString());
	}

	Result QObject::setField(const String& name, const QValue& value)
	{
		return errors::undefined_set_field(getTypeString());
	}

	Result QObject::getIndex(const QValue& index, QValue* result) const
	{
		return errors::undefined_get_index(getTypeString());
	}

	Result QObject::setIndex(const QValue& index, const QValue& value)
	{
		return errors::undefined_set_index(getTypeString());
	}

	Result QObject::selection(ContextPtr context, const QValue& value, QSelection** result)
	{
		return errors::undefined_selection(getTypeString());
	}

	imq::Result QObject::add(const QValue& rhs, QValue* result) const
	{
		return errors::undefined_operator(getTypeString(), "add");
	}

	imq::Result QObject::sub(const QValue& rhs, QValue* result) const
	{
		return errors::undefined_operator(getTypeString(), "sub");
	}

	imq::Result QObject::mul(const QValue& rhs, QValue* result) const
	{
		return errors::undefined_operator(getTypeString(), "mul");
	}

	imq::Result QObject::div(const QValue& rhs, QValue* result) const
	{
		return errors::undefined_operator(getTypeString(), "div");
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

	QSelection::~QSelection()
	{
	}
}