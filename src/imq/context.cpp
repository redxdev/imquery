#include "context.h"

#include "errors.h"

namespace imq
{
	Context::~Context()
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

	SubContext::SubContext(ContextPtr parent)
		: parent(parent), Context()
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

	RestrictedSubContext::RestrictedSubContext(ContextPtr parent)
		: SubContext(parent)
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