#pragma once

#include "platform.h"
#include "result.h"
#include "value.h"

#include <unordered_map>

namespace imq
{
	class Context
	{
	public:
		virtual ~Context();

		virtual bool hasValue(const String& key) const = 0;
		virtual Result getValue(const String& key, QValue* result) const = 0;
		virtual Result setValue(const String& key, const QValue& value) = 0;
		virtual Result deleteValue(const String& key) = 0;
	};

	// A simple form of context. This stores values in an unordered_map and allows both read and write access.
	// This type of context is generally used as the root context.
	class SimpleContext : public Context
	{
	public:
		virtual ~SimpleContext();

		virtual bool hasValue(const String& key) const override;
		virtual Result getValue(const String& key, QValue* result) const override;
		virtual Result setValue(const String& key, const QValue& value) override;
		virtual Result deleteValue(const String& key) override;

	private:
		std::unordered_map<String, QValue> values;
	};
}