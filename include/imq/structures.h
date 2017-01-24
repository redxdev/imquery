#pragma once

#include "platform.h"
#include "object.h"
#include "value.h"
#include "hash.h"

#include <unordered_map>
#include <vector>

#define IMQ_STRUCTURE_STRING_LIMIT (10)

namespace imq
{
	class VMachine;

	class QTableEntry : public QObject
	{
		IMQ_DECLARE_TYPE(QTableEntry);
		
	public:
		QTableEntry(VMachine* vm);
		QTableEntry(VMachine* vm, const QValue& key, const QValue& value);
		QTableEntry(const QTableEntry& other);

		virtual ~QTableEntry();

		void initializeObject();

		QTableEntry& operator=(const QTableEntry& other);

		virtual String toString() const override;

		virtual bool equals(const QObject* other) const override;

		virtual Result copyObject(QValue* result) const override;

		virtual Result getField(const String& name, QValue* result) override;
		virtual Result setField(const String& name, const QValue& value) override;

		const QValue& getKey() const;
		const QValue& getValue() const;

	private:
		ObjectFieldHelper fields;

		QValue key;
		QValue value;
	};

	class QTableIterator : public QIterator
	{
	public:
		QTableIterator(VMachine* vm, const std::unordered_map<QValue, QValue, std::hash<QValue>>::iterator& begin, const std::unordered_map<QValue, QValue, std::hash<QValue>>::iterator& end);
		virtual ~QTableIterator();

		virtual bool isValid() const override;
		virtual void next() override;
		virtual QValue getCurrentValue() const override;

	private:
		VMachine* vm;
		std::unordered_map<QValue, QValue, std::hash<QValue>>::iterator it;
		std::unordered_map<QValue, QValue, std::hash<QValue>>::iterator end;
	};

	class QTable : public QObject
	{
		IMQ_DECLARE_TYPE_DYNAMIC(QTable);

	public:
		QTable(VMachine* vm);
		QTable(VMachine* vm, const std::unordered_map<QValue, QValue>& map);
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

		virtual Result iterate(Context* context, QIterator** result) override;

		const std::unordered_map<QValue, QValue>& getMap() const;

	protected:

		virtual void GC_markChildren() override;

	private:
		ObjectFieldHelper fields;

		std::unordered_map<QValue, QValue, std::hash<QValue>> map;
	};

	class QListIterator : public QIterator
	{
	public:
		QListIterator(const std::vector<QValue>::iterator& begin, const std::vector<QValue>::iterator& end);
		virtual ~QListIterator();

		virtual bool isValid() const override;
		virtual void next() override;
		virtual QValue getCurrentValue() const override;

	private:
		std::vector<QValue>::iterator it;
		std::vector<QValue>::iterator end;
	};

	class QList : public QObject
	{
		IMQ_DECLARE_TYPE_DYNAMIC(QList);

	public:
		QList(VMachine* vm);
		QList(VMachine* vm, const std::vector<QValue>& vec);
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

		virtual Result iterate(Context* context, QIterator** result) override;

		const std::vector<QValue>& getVector() const;

	protected:

		virtual void GC_markChildren() override;

	private:
		ObjectFieldHelper fields;

		std::vector<QValue> vec;
	};
}
