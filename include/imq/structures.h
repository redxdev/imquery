#pragma once

#include "platform.h"
#include "object.h"
#include "value.h"
#include "hash.h"

#include <unordered_map>

#define IMQ_STRUCTURE_STRING_LIMIT (10)

namespace imq
{
	class QTable : public QObject
	{
		IMQ_DECLARE_TYPE(QTable);

	public:
		QTable();
		QTable(const std::unordered_map<QValue, QValue>& map);
		QTable(const QTable& other);
		virtual ~QTable();

		void initializeObject();

		QTable& operator=(const QTable& other);

		virtual String toString() const override;

		virtual bool equals(const QObject* other) const override;

		virtual Result copyObject(QValue* result) const override;

		virtual Result getField(const String& name, QValue* result) override;

		virtual Result getIndex(const QValue& index, QValue* result) override;
		virtual Result setIndex(const QValue& index, const QValue& value) override;

		const std::unordered_map<QValue, QValue>& getMap() const;

	private:
		ObjectFieldHelper fields;

		std::unordered_map<QValue, QValue, std::hash<QValue>> map;
	};

	class QList : public QObject
	{
		IMQ_DECLARE_TYPE(QList);

	public:
		QList();
		QList(const std::vector<QValue>& vec);
		QList(const QList& other);
		virtual ~QList();

		QList& operator=(const QList& other);

		void initializeObject();

		virtual String toString() const override;

		virtual bool equals(const QObject* other) const override;

		virtual Result copyObject(QValue* result) const override;

		virtual Result getField(const String& name, QValue* result) override;

		virtual Result getIndex(const QValue& index, QValue* result) override;
		virtual Result setIndex(const QValue& index, const QValue& value) override;

		const std::vector<QValue>& getVector() const;

	private:
		ObjectFieldHelper fields;

		std::vector<QValue> vec;
	};
}
