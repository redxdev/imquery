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

	imq::Result QObject::opAdd(const QValue& rhs, QValue* result) const
	{
		return errors::undefined_operator(getTypeString(), "add");
	}

	imq::Result QObject::opSub(const QValue& rhs, QValue* result) const
	{
		return errors::undefined_operator(getTypeString(), "sub");
	}

	imq::Result QObject::opMul(const QValue& rhs, QValue* result) const
	{
		return errors::undefined_operator(getTypeString(), "mul");
	}

	imq::Result QObject::opDiv(const QValue& rhs, QValue* result) const
	{
		return errors::undefined_operator(getTypeString(), "div");
	}

	imq::Result QObject::opMod(const QValue& rhs, QValue* result) const
	{
		return errors::undefined_operator(getTypeString(), "mod");
	}

	imq::Result QObject::opNegate(QValue* result) const
	{
		return errors::undefined_operator(getTypeString(), "negate");
	}

	imq::Result QObject::opNot(QValue* result) const
	{
		return errors::undefined_operator(getTypeString(), "not");
	}

	imq::Result QObject::opAnd(const QValue& rhs, QValue* result) const
	{
		return errors::undefined_operator(getTypeString(), "and");
	}

	imq::Result QObject::opOr(const QValue& rhs, QValue* result) const
	{
		return errors::undefined_operator(getTypeString(), "or");
	}

	imq::Result QObject::opLess(const QValue& rhs, QValue* result) const
	{
		return errors::undefined_operator(getTypeString(), "less");
	}

	imq::Result QObject::opLessEq(const QValue& rhs, QValue* result) const
	{
		return errors::undefined_operator(getTypeString(), "lesseq");
	}

	imq::Result QObject::opGreater(const QValue& rhs, QValue* result) const
	{
		return errors::undefined_operator(getTypeString(), "greater");
	}

	imq::Result QObject::opGreaterEq(const QValue& rhs, QValue* result) const
	{
		return errors::undefined_operator(getTypeString(), "greatereq");
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