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

	imq::Result SimpleContext::deleteValue(const String& key)
	{
		auto found = values.find(key);
		if (found == values.end())
			return errors::context_undefined_value(key);

		values.erase(key);
		return true;
	}
}