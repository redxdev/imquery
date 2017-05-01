#include "object.h"

#include <cassert>
#include <functional>

#include "value.h"
#include "errors.h"
#include "vm.h"

namespace imq
{

	QObject::QObject(VMachine* vm)
		: vm(vm)
	{
		if (vm != nullptr)
		{
			vm->getGC()->manage(this);
		}
	}

	QObject::~QObject()
	{
		if (vm != nullptr)
		{
			vm->getGC()->unmanage(this);
		}
	}

	String QObject::toString() const
	{
		std::stringstream ss;
		ss << "<" << getTypeString() << ">";
		return ss.str();
	}

	Result QObject::copyObject(QValue* result) const
	{
		return errors::uncopyable_obj(getTypeString());
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

	Result QObject::selection(Context* context, const QValue& value, QSelection** result)
	{
		return errors::undefined_selection(getTypeString());
	}

	Result QObject::iterate(Context* context, QIterator** result)
	{
		return errors::undefined_iteration(getTypeString());
	}

	Result QObject::opAdd(OperationOrder order, const QValue& other, QValue* result) const
	{
		return errors::undefined_operator(getTypeString(), "add");
	}

	Result QObject::opSub(OperationOrder order, const QValue& other, QValue* result) const
	{
		return errors::undefined_operator(getTypeString(), "sub");
	}

	Result QObject::opMul(OperationOrder order, const QValue& other, QValue* result) const
	{
		return errors::undefined_operator(getTypeString(), "mul");
	}

	Result QObject::opDiv(OperationOrder order, const QValue& other, QValue* result) const
	{
		return errors::undefined_operator(getTypeString(), "div");
	}

	Result QObject::opMod(OperationOrder order, const QValue& other, QValue* result) const
	{
		return errors::undefined_operator(getTypeString(), "mod");
	}

	Result QObject::opNegate(QValue* result) const
	{
		return errors::undefined_operator(getTypeString(), "negate");
	}

	Result QObject::opNot(QValue* result) const
	{
		return errors::undefined_operator(getTypeString(), "not");
	}

	Result QObject::opAnd(OperationOrder order, const QValue& other, QValue* result) const
	{
		return errors::undefined_operator(getTypeString(), "and");
	}

	Result QObject::opOr(OperationOrder order, const QValue& other, QValue* result) const
	{
		return errors::undefined_operator(getTypeString(), "or");
	}

	Result QObject::opLess(OperationOrder order, const QValue& other, QValue* result) const
	{
		return errors::undefined_operator(getTypeString(), "less");
	}

	Result QObject::opLessEq(OperationOrder order, const QValue& other, QValue* result) const
	{
		return errors::undefined_operator(getTypeString(), "lesseq");
	}

	Result QObject::opGreater(OperationOrder order, const QValue& other, QValue* result) const
	{
		return errors::undefined_operator(getTypeString(), "greater");
	}

	Result QObject::opGreaterEq(OperationOrder order, const QValue& other, QValue* result) const
	{
		return errors::undefined_operator(getTypeString(), "greatereq");
	}

	VMachine* QObject::getVM() const
	{
		return vm;
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

	QIterator::~QIterator()
	{

	}
}