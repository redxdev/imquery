#include "object.h"

#include <cassert>
#include <functional>

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

	std::size_t QObject::getHash() const
	{
		return std::hash<void*>()((void*)this);
	}

	Result QObject::getField(const String& name, QValue* result)
	{
		return errors::undefined_get_field(getTypeString());
	}

	Result QObject::setField(const String& name, const QValue& value)
	{
		return errors::undefined_set_field(getTypeString());
	}

	Result QObject::getIndex(const QValue& index, QValue* result)
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

	imq::Result QObject::opAdd(OperationOrder order, const QValue& other, QValue* result) const
	{
		return errors::undefined_operator(getTypeString(), "add");
	}

	imq::Result QObject::opSub(OperationOrder order, const QValue& other, QValue* result) const
	{
		return errors::undefined_operator(getTypeString(), "sub");
	}

	imq::Result QObject::opMul(OperationOrder order, const QValue& other, QValue* result) const
	{
		return errors::undefined_operator(getTypeString(), "mul");
	}

	imq::Result QObject::opDiv(OperationOrder order, const QValue& other, QValue* result) const
	{
		return errors::undefined_operator(getTypeString(), "div");
	}

	imq::Result QObject::opMod(OperationOrder order, const QValue& other, QValue* result) const
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

	imq::Result QObject::opAnd(OperationOrder order, const QValue& other, QValue* result) const
	{
		return errors::undefined_operator(getTypeString(), "and");
	}

	imq::Result QObject::opOr(OperationOrder order, const QValue& other, QValue* result) const
	{
		return errors::undefined_operator(getTypeString(), "or");
	}

	imq::Result QObject::opLess(OperationOrder order, const QValue& other, QValue* result) const
	{
		return errors::undefined_operator(getTypeString(), "less");
	}

	imq::Result QObject::opLessEq(OperationOrder order, const QValue& other, QValue* result) const
	{
		return errors::undefined_operator(getTypeString(), "lesseq");
	}

	imq::Result QObject::opGreater(OperationOrder order, const QValue& other, QValue* result) const
	{
		return errors::undefined_operator(getTypeString(), "greater");
	}

	imq::Result QObject::opGreaterEq(OperationOrder order, const QValue& other, QValue* result) const
	{
		return errors::undefined_operator(getTypeString(), "greatereq");
	}

	void QObject::updateSelfPointer(const std::shared_ptr<QObject> ptr)
	{
		assert(ptr.get() == this && "updateSelfPointer() called with pointer to different object");

		selfPtr = ptr;
	}

	const std::weak_ptr<imq::QObject>& QObject::getSelfPointer() const
	{
		return selfPtr;
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