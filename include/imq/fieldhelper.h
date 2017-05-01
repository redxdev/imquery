#pragma once

#include "platform.h"
#include "result.h"

#include <unordered_map>
#include <functional>

namespace imq
{
	class QObject;
	class QValue;

	class IMQ_API ObjectFieldHelper
	{
	public:
		void getter(const String& name, std::function<Result(QValue*)> getFunc);
		void setter(const String& name, std::function<Result(const QValue&)> setFunc);

		Result handleGet(QObject* obj, const String& name, QValue* result);
		Result handleSet(QObject* obj, const String& name, const QValue& value);

		size_t GC_getSize() const;

		void clear();

	private:
		std::unordered_map<String, std::function<Result(QValue*)>> getters;
		std::unordered_map<String, std::function<Result(const QValue&)>> setters;
	};
}