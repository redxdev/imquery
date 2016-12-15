#include "context.h"

#include "cast.h"
#include "errors.h"
#include "vm.h"

namespace imq
{

	Context::Context(VMachine* vm)
		: vm(vm)
	{
		if (vm)
		{
			vm->getGC()->manage(this);
		}
	}

	Context::~Context()
	{
	}

	bool Context::isContextReturnedFrom() const
	{
		QValue rv;
		return getReturnValue(&rv);
	}

	VMachine* Context::getVM() const
	{
		return vm;
	}

	SimpleContext::SimpleContext(VMachine* vm)
		: Context(vm)
	{
	}

	SimpleContext::~SimpleContext()
	{
	}

	bool SimpleContext::hasValue(const String& key) const
	{
		return values.find(key) != values.end();
	}

	Result SimpleContext::getValue(const String& key, QValue* result) const
	{
		auto found = values.find(key);
		if (found == values.end())
		{
			return errors::context_undefined_value(key);
		}

		*result = found->second;
		return true;
	}

	Result SimpleContext::setValue(const String& key, const QValue& value)
	{
		values[key] = value;
		return true;
	}

	Result SimpleContext::deleteValue(const String& key)
	{
		auto found = values.find(key);
		if (found == values.end())
			return errors::context_undefined_value(key);

		values.erase(key);
		return true;
	}

	Result SimpleContext::registerInput(const String& key, const QValue& value)
	{
		return errors::context_root_flags();
	}

	Result SimpleContext::registerOutput(const String& key, const QValue& value)
	{
		return errors::context_root_flags();
	}

	Result SimpleContext::setBreakable(bool bValue)
	{
		bBreakable = bValue;
		if (!bBreakable)
			bBroken = false;

		return true;
	}

	bool SimpleContext::isBreakable() const
	{
		return bBreakable;
	}

	Result SimpleContext::breakContext()
	{
		if (bBreakable)
		{
			bBroken = true;
			return true;
		}
		else
		{
			return errors::context_not_breakable();
		}
	}

	bool SimpleContext::isContextBroken() const
	{
		return bBreakable && bBroken;
	}

	Result SimpleContext::setReturnable(bool bValue)
	{
		bReturnable = bValue;
		if (!bReturnable)
			bReturned = false;

		return true;
	}

	bool SimpleContext::isReturnable() const
	{
		return bReturnable;
	}

	Result SimpleContext::returnContext(const QValue& value)
	{
		if (bReturnable)
		{
			bReturned = true;
			returnValue = value;
			return true;
		}
		else
		{
			return errors::context_not_returnable();
		}
	}

	bool SimpleContext::getReturnValue(QValue* result) const
	{
		if (bReturnable && bReturned)
		{
			*result = returnValue;
			return true;
		}

		return false;
	}

	void SimpleContext::GC_markChildren()
	{
		for (auto entry : values)
		{
			entry.second.GC_mark();
		}
	}

	RootContext::RootContext(VMachine* vm)
		: Context(vm)
	{
	}

	bool RootContext::hasValue(const String& key) const
	{
		return values.find(key) != values.end() || inputs.find(key) != inputs.end() || outputs.find(key) != outputs.end();
	}

	Result RootContext::getValue(const String& key, QValue* result) const
	{
		auto found = inputs.find(key);
		if (found != inputs.end())
		{
			*result = found->second;
			return true;
		}

		found = outputs.find(key);
		if (found != outputs.end())
		{
			*result = found->second;
			return true;
		}

		found = values.find(key);
		if (found != values.end())
		{
			*result = found->second;
			return true;
		}

		return errors::context_undefined_value(key);
	}

	Result RootContext::setValue(const String& key, const QValue& value)
	{
		if (inputs.find(key) != inputs.end())
		{
			return errors::context_input_set();
		}

		if (outputs.find(key) != outputs.end())
		{
			return errors::context_output_set();
		}

		values[key] = value;
		return true;
	}

	Result RootContext::deleteValue(const String& key)
	{
		if (inputs.find(key) != inputs.end())
		{
			return errors::context_input_delete();
		}

		if (outputs.find(key) != outputs.end())
		{
			return errors::context_output_delete();
		}

		auto found = values.find(key);
		if (found == values.end())
			return errors::context_undefined_value(key);

		values.erase(key);
		return true;
	}

	Result RootContext::registerInput(const String& key, const QValue& value)
	{
		auto valFound = values.find(key);
		if (valFound != values.end())
		{
			return errors::context_input_overwrite();
		}

		auto found = inputs.find(key);
		if (found != inputs.end())
		{
			if (!checkTypesEqual(value, found->second))
			{
				return errors::context_input_invalid_type(key);
			}

			// ignore, we've set the input elsewhere
			return true;
		}

		inputs[key] = value;
		return true;
	}

	Result RootContext::registerOutput(const String& key, const QValue& value)
	{
		auto valFound = values.find(key);
		if (valFound != values.end())
		{
			return errors::context_output_overwrite();
		}

		if (outputs.find(key) != outputs.end())
		{
			return errors::context_output_set();
		}

		outputs[key] = value;
		return true;
	}

	imq::Result RootContext::setBreakable(bool bValue)
	{
		return errors::context_not_breakable();
	}

	bool RootContext::isBreakable() const
	{
		return false;
	}

	Result RootContext::breakContext()
	{
		return errors::context_not_breakable();
	}

	bool RootContext::isContextBroken() const
	{
		return false;
	}

	Result RootContext::setReturnable(bool bValue)
	{
		return errors::context_not_returnable();
	}

	bool RootContext::isReturnable() const
	{
		return false;
	}

	Result RootContext::returnContext(const QValue& value)
	{
		return errors::context_not_returnable();
	}

	bool RootContext::getReturnValue(QValue* result) const
	{
		return false;
	}

	void RootContext::GC_markChildren()
	{
		for (auto entry : inputs)
		{
			entry.second.GC_mark();
		}

		for (auto entry : outputs)
		{
			entry.second.GC_mark();
		}

		for (auto entry : values)
		{
			entry.second.GC_mark();
		}
	}

	void RootContext::setInput(const String& key, const QValue& value)
	{
		inputs[key] = value;
	}

	void RootContext::setOutput(const String& key, const QValue& value)
	{
		outputs[key] = value;
	}

	const std::unordered_map<String, QValue>& RootContext::getInputs() const
	{
		return inputs;
	}

	const std::unordered_map<String, QValue>& RootContext::getOutputs() const
	{
		return outputs;
	}

	void RootContext::reset()
	{
		inputs.clear();
		outputs.clear();
		values.clear();
	}

	SubContext::SubContext(VMachine* vm, ContextPtr parent)
		: Context(vm), parent(parent)
	{
	}

	SubContext::~SubContext()
	{
	}

	ContextPtr SubContext::getParent() const
	{
		return parent;
	}

	bool SubContext::hasValue(const String& key) const
	{
		if (values.find(key) != values.end())
			return true;

		return parent && parent->hasValue(key);
	}

	Result SubContext::getValue(const String& key, QValue* result) const
	{
		auto found = values.find(key);
		if (found == values.end())
		{
			if (parent)
				return parent->getValue(key, result);
			else
				return errors::context_undefined_value(key);
		}

		*result = found->second;
		return true;
	}

	Result SubContext::setValue(const String& key, const QValue& value)
	{
		if (parent && parent->hasValue(key))
		{
			return parent->setValue(key, value);
		}

		values[key] = value;
		return true;
	}

	Result SubContext::deleteValue(const String& key)
	{
		auto found = values.find(key);
		if (found == values.end())
		{
			if (parent)
				return parent->deleteValue(key);
			else
				return errors::context_undefined_value(key);
		}

		values.erase(found);
		return true;
	}

	Result SubContext::registerInput(const String& key, const QValue& value)
	{
		return errors::context_root_flags();
	}

	Result SubContext::registerOutput(const String& key, const QValue& value)
	{
		return errors::context_root_flags();
	}

	imq::Result SubContext::setBreakable(bool bValue)
	{
		bBreakable = bValue;
		if (!bBreakable)
			bBroken = false;

		return true;
	}

	bool SubContext::isBreakable() const
	{
		return bBreakable || parent->isBreakable();
	}

	imq::Result SubContext::breakContext()
	{
		if (bBreakable)
		{
			bBroken = true;
			return true;
		}

		return parent->breakContext();
	}

	bool SubContext::isContextBroken() const
	{
		return (bBreakable && bBroken) || parent->isContextBroken();
	}

	Result SubContext::setReturnable(bool bValue)
	{
		bReturnable = bValue;
		if (!bReturnable)
			bReturned = false;

		return true;
	}

	bool SubContext::isReturnable() const
	{
		return bReturned;
	}

	Result SubContext::returnContext(const QValue& value)
	{
		if (bReturnable)
		{
			bReturned = true;
			returnValue = value;
			return true;
		}

		return parent->returnContext(value);
	}

	bool SubContext::getReturnValue(QValue* result) const
	{
		if (bReturnable && bReturned)
		{
			*result = returnValue;
			return true;
		}

		return parent->getReturnValue(result);
	}

	void SubContext::GC_markChildren()
	{
		for (auto entry : values)
		{
			entry.second.GC_mark();
		}
	}

	RestrictedSubContext::RestrictedSubContext(VMachine* vm, ContextPtr parent)
		: SubContext(vm, parent)
	{
	}

	RestrictedSubContext::~RestrictedSubContext()
	{
	}

	void RestrictedSubContext::setRawValue(const String& key, const QValue& value)
	{
		values[key] = value;
	}

	Result RestrictedSubContext::setValue(const String& key, const QValue& value)
	{
		return errors::context_no_write_access();
	}

	Result RestrictedSubContext::deleteValue(const String& key)
	{
		return errors::context_no_delete_access();
	}
}