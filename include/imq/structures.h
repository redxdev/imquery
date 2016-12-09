#pragma once

#include "platform.h"
#include "object.h"
#include "value.h"
#include "hash.h"

#include <unordered_map>

#define IMQ_STRUCTURE_STRING_LIMIT (5)

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

		virtual Result copyObject(QValue* result) const override;

		virtual Result getField(const String& name, QValue* result) override;

		virtual Result getIndex(const QValue& index, QValue* result) override;
		virtual Result setIndex(const QValue& index, const QValue& value) override;

		const std::unordered_map<QValue, QValue>& getMap() const;

	private:
		std::unordered_map<QValue, QValue> map;
	};

	class QList : public QObject
	{
		IMQ_DECLARE_TYPE(QList);

	public:
		QList();
		QList(const QList& other);
		virtual ~QList();

		QList& operator=(const QList& other);

		virtual String toString() const override;

		virtual bool equals(const QObject* other) const override;

		virtual Result copyObject(QValue* result) const override;

		virtual Result getField(const String& name, QValue* result) override;

		virtual Result getIndex(const QValue& index, QValue* result) override;
		virtual Result setIndex(const QValue& index, const QValue& value) override;

		const std::vector<QValue>& getVector() const;

	private:
		std::vector<QValue> vec;
	};
}
