#pragma once

#include "platform.h"
#include "object.h"
#include "value.h"
#include "hash.h"

#include <unordered_map>

namespace imq
{
	class QTable : public QObject
	{
		IMQ_DECLARE_TYPE(QTable);

	public:
		QTable();
		QTable(const QTable& other);
		virtual ~QTable();

		QTable& operator=(const QTable& other);

		virtual String toString() const override;

		virtual bool equals(const QObject* other) const override;

		virtual Result getIndex(const QValue& index, QValue* result) override;
		virtual Result setIndex(const QValue& index, const QValue& value) override;

	private:
		std::unordered_map<QValue, QValue> map;
	};
}
