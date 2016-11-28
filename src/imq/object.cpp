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