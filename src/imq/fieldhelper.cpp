#include "fieldhelper.h"

#include "value.h"
#include "object.h"

namespace imq
{
	void ObjectFieldHelper::getter(const String& name, std::function<Result(QValue*)> getFunc)
	{
		getters[name] = getFunc;
	}

	void ObjectFieldHelper::setter(const String& name, std::function<Result(const QValue&)> setFunc)
	{
		setters[name] = setFunc;
	}

	Result ObjectFieldHelper::handleGet(QObject* obj, const String& name, QValue* result)
	{
		auto found = getters.find(name);
		if (found == getters.end())
			return errors::undefined_field(obj->getTypeString(), name);

		return found->second(result);
	}

	Result ObjectFieldHelper::handleSet(QObject* obj, const String& name, const QValue& value)
	{
		auto found = setters.find(name);
		if (found == setters.end())
			return errors::undefined_field(obj->getTypeString(), name);

		return found->second(value);
	}

	size_t ObjectFieldHelper::GC_getSize() const
	{
		size_t sz = sizeof(ObjectFieldHelper);
		for (auto entry : getters)
		{
			sz += sizeof(String) + getStringSize(entry.first) + sizeof(std::function<Result(QValue*)>);
		}

		for (auto entry : setters)
		{
			sz += sizeof(String) + getStringSize(entry.first) + sizeof(std::function<Result(const QValue&)>);
		}

		return sz;
	}

	void ObjectFieldHelper::clear()
	{
		getters.clear();
		setters.clear();
	}
}