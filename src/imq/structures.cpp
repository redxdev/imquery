#include "structures.h"

#include <sstream>

#include "errors.h"
#include "cast.h"

namespace imq
{
	IMQ_DEFINE_TYPE_WITH_SIZE_FIELDS_CUSTOM(QTableEntry, fields, key.GC_getSize() + value.GC_getSize() - sizeof(QValue) * 2);

	QTableEntry::QTableEntry(VMachine* vm)
		: QObject(vm)
	{
		initializeObject();
	}

	QTableEntry::QTableEntry(VMachine* vm, const QValue& key, const QValue& value)
		: QObject(vm), key(key), value(value)
	{
		initializeObject();
	}

	QTableEntry::QTableEntry(const QTableEntry& other)
		: QObject(other.getVM()), key(other.key), value(other.value)
	{
		initializeObject();
	}

	QTableEntry::~QTableEntry()
	{
	}

	void QTableEntry::initializeObject()
	{
		fields.getter("key", [&](QValue* result) {
			*result = key;
			return true;
		});

		fields.setter("key", [&](const QValue& val) {
			key = val;
			return true;
		});

		fields.getter("value", [&](QValue* result) {
			*result = value;
			return true;
		});

		fields.setter("value", [&](const QValue& val) {
			value = val;
			return true;
		});
	}

	QTableEntry& QTableEntry::operator=(const QTableEntry& other)
	{
		key = other.key;
		value = other.value;
		return *this;
	}

	String QTableEntry::toString() const
	{
		std::stringstream ss;
		ss << "TableEntry[" << key.asString() << "," << value.asString() << "]";
		return ss.str();
	}

	bool QTableEntry::equals(const QObject* other) const
	{
		const QTableEntry* entry = objectCast<QTableEntry>(other);
		if (!entry)
			return false;

		return key == entry->key && value == entry->value;
	}

	Result QTableEntry::copyObject(QValue* result) const
	{
		*result = QValue::Object(new QTableEntry(*this));
		return true;
	}

	Result QTableEntry::getField(const String& name, QValue* result)
	{
		return fields.handleGet(this, name, result);
	}

	Result QTableEntry::setField(const String& name, const QValue& value)
	{
		return fields.handleSet(this, name, value);
	}

	const QValue& QTableEntry::getKey() const
	{
		return key;
	}

	const QValue& QTableEntry::getValue() const
	{
		return value;
	}

	QTableIterator::QTableIterator(VMachine* vm, const std::unordered_map<QValue, QValue, std::hash<QValue>>::iterator& begin, const std::unordered_map<QValue, QValue, std::hash<QValue>>::iterator& end)
		: vm(vm), it(begin), end(end)
	{
	}

	QTableIterator::~QTableIterator()
	{
	}

	bool QTableIterator::isValid() const
	{
		return it != end;
	}

	void QTableIterator::next()
	{
		++it;
	}

	QValue QTableIterator::getCurrentValue() const
	{
		return QValue::Object(new QTableEntry(vm, it->first, it->second));
	}

	IMQ_DEFINE_TYPE(QTable);

	size_t QTable::GC_getSize() const
	{
		return sizeof(QTable) + fields.GC_getSize() - sizeof(ObjectFieldHelper) + objSize;
	}

	QTable::QTable(VMachine* vm)
		: QObject(vm)
	{
		initializeObject();
	}

	QTable::QTable(const QTable& other)
		: QObject(other.getVM())
	{
		map = other.map;
		objSize = other.objSize;

		initializeObject();
	}

	QTable::QTable(VMachine* vm, const std::unordered_map<QValue, QValue>& map)
		: QObject(vm), map(map)
	{
		for (auto entry : map)
		{
			objSize += entry.first.GC_getSize() + entry.second.GC_getSize();
		}

		initializeObject();
	}

	QTable::~QTable()
	{
	}

	void QTable::initializeObject()
	{
		fields.getter("has", [&](QValue* result) {
			*result = QValue::Function(getVM(), this, [&](VMachine* vm, int32_t argCount, QValue* args, QValue* result) -> Result {
				if (argCount != 1)
					return errors::args_count("QTable.has", 1, argCount);

				*result = QValue::Bool(map.find(args[0]) != map.end());
				return true;
			});
			return true;
		});

		fields.getter("erase", [&](QValue* result) {
			*result = QValue::Function(getVM(), this, [&](VMachine* vm, int32_t argCount, QValue* args, QValue* result) -> Result {
				if (argCount != 1)
					return errors::args_count("QTable.erase", 1, argCount);

				auto found = map.find(args[0]);
				if (found == map.end())
					return errors::undefined_index(getTypeString(), args[0]);

				objSize -= found->first.GC_getSize() + found->second.GC_getSize();
				map.erase(found);
				return true;
			});
			return true;
		});

		fields.getter("clear", [&](QValue* result) {
			*result = QValue::Function(getVM(), this, [&](VMachine* vm, int32_t argCount, QValue* args, QValue* result) -> Result {
				if (argCount != 0)
					return errors::args_count("QTable.clear", 0, argCount);

				map.clear();
				objSize = 0;
				return true;
			});
			return true;
		});

		fields.getter("length", [&](QValue* result) { *result = QValue::Integer((int32_t)map.size()); return true; });

		fields.getter("keys", [&](QValue* result) {
			std::vector<QValue> keys;
			for (auto entry : map)
			{
				keys.push_back(entry.first);
			}

			*result = QValue::Object(new QList(getVM(), keys));
			return true;
		});

		fields.getter("values", [&](QValue* result) {
			std::vector<QValue> values;
			for (auto entry : map)
			{
				values.push_back(entry.second);
			}

			*result = QValue::Object(new QList(getVM(), values));
			return true;
		});
	}

	QTable& QTable::operator=(const QTable& other)
	{
		map = other.map;
		objSize = other.objSize;
		return *this;
	}

	String QTable::toString() const
	{
		int32_t count = 0;
		std::stringstream ss;
		ss << "[!";
		for (auto entry : map)
		{
			++count;
			ss << entry.first.asString() << " = " << entry.second.asString();
			if (count != map.size())
			{
				ss << ", ";

				if (count >= IMQ_STRUCTURE_STRING_LIMIT)
					break;
			}
		}

		if (count == 0)
			ss << "empty table";
		else if (count != map.size())
			ss << "...";

		ss << "]";
		return ss.str();
	}

	bool QTable::equals(const QObject* other) const
	{
		const QTable* table = objectCast<QTable>(other);
		if (!table)
			return false;

		return map == table->map;
	}

	Result QTable::copyObject(QValue* result) const
	{
		*result = QValue::Object(new QTable(*this));
		return true;
	}

	Result QTable::getField(const String& name, QValue* result)
	{
		return fields.handleGet(this, name, result);
	}

	Result QTable::getIndex(const QValue& index, QValue* result)
	{
		auto found = map.find(index);
		if (found == map.end())
			return errors::undefined_index(getTypeString(), index);

		*result = found->second;
		return true;
	}

	Result QTable::setIndex(const QValue& index, const QValue& value)
	{
		auto found = map.find(index);
		if (found != map.end())
		{
			objSize -= found->first.GC_getSize() + found->second.GC_getSize();
		}

		objSize += index.GC_getSize() + value.GC_getSize();
		map[index] = value;
		return true;
	}

	Result QTable::iterate(Context* context, QIterator** result)
	{
		*result = new QTableIterator(getVM(), map.begin(), map.end());
		return true;
	}

	const std::unordered_map<imq::QValue, imq::QValue>& QTable::getMap() const
	{
		return map;
	}

	void QTable::GC_markChildren()
	{
		for (auto entry : map)
		{
			QValue key = entry.first;
			key.GC_mark(); // because it is const if we operate directly on the entry
			entry.second.GC_mark();
		}
	}

	QListIterator::QListIterator(const std::vector<QValue>::iterator& begin, const std::vector<QValue>::iterator& end)
		: it(begin), end(end)
	{
	}

	QListIterator::~QListIterator()
	{
	}

	bool QListIterator::isValid() const
	{
		return it != end;
	}

	void QListIterator::next()
	{
		++it;
	}

	QValue QListIterator::getCurrentValue() const
	{
		return *it;
	}

	IMQ_DEFINE_TYPE(QList);

	size_t QList::GC_getSize() const
	{
		return sizeof(QList) + fields.GC_getSize() - sizeof(ObjectFieldHelper) + objSize;
	}

	QList::QList(VMachine* vm)
		: QObject(vm)
	{
		initializeObject();
	}

	QList::QList(const QList& other)
		: QObject(other.getVM())
	{
		vec = other.vec;
		objSize = other.objSize;

		initializeObject();
	}

	QList::QList(VMachine* vm, const std::vector<QValue>& vec)
		: QObject(vm), vec(vec)
	{
		for (auto value : vec)
		{
			objSize += value.GC_getSize();
		}

		initializeObject();
	}

	QList::~QList()
	{
	}

	QList& QList::operator=(const QList& other)
	{
		vec = other.vec;
		objSize = other.objSize;
		return *this;
	}

	void QList::initializeObject()
	{
		fields.getter("length", [&](QValue* result) {
			*result = QValue::Integer((int32_t)vec.size());
			return true;
		});

		fields.getter("insert", [&](QValue* result) {
			*result = QValue::Function(getVM(), this, [&](VMachine* vm, int32_t argCount, QValue* args, QValue* result) -> Result {
				switch (argCount)
				{
				default:
					return errors::args_count("QList.insert", 1, 2, argCount);

				case 1:
					vec.push_back(args[0]);
					objSize += args[0].GC_getSize();
					return true;

				case 2:
				{
					int32_t index;
					if (!args[1].getInteger(&index))
						return errors::args_type("QList.insert", 1, "Integer", args[1]);

					vec.insert(vec.begin() + (size_t)index, args[0]);
					objSize += args[0].GC_getSize();
					return true;
				}
				}
			});
			return true;
		});

		fields.getter("erase", [&](QValue* result) {
			//QObjectPtr sptr = getSelfPointer().lock(); // TODO
			*result = QValue::Function(getVM(), this, [&](VMachine* vm, int32_t argCount, QValue* args, QValue* result) -> Result {
				if (argCount != 1)
					return errors::args_count("QList.erase", 1, argCount);

				int32_t index;
				if (!args[0].getInteger(&index))
					return errors::args_type("QList.erase", 0, "Integer", args[0]);

				if (index < 0 || index >= (int32_t)vec.size())
					return errors::index_out_of_range(args[0]);

				objSize -= vec[index].GC_getSize();
				vec.erase(vec.begin() + index);
				return true;
			});
			return true;
		});

		fields.getter("clear", [&](QValue* result) {
			//QObjectPtr sptr = getSelfPointer().lock(); // TODO
			*result = QValue::Function(getVM(), this, [&](VMachine* vm, int32_t argCount, QValue* args, QValue* result) -> Result {
				if (argCount != 0)
					return errors::args_count("QList.clear", 0, argCount);

				vec.clear();
				objSize = 0;
				return true;
			});
			return true;
		});
	}

	String QList::toString() const
	{
		int32_t count = 0;
		std::stringstream ss;
		ss << "[";
		for (auto val : vec)
		{
			++count;
			ss << val.asString();
			if (count != vec.size())
			{
				ss << ", ";

				if (count >= IMQ_STRUCTURE_STRING_LIMIT)
					break;
			}
		}

		if (count == 0)
			ss << "empty list";
		else if (count != vec.size())
			ss << "...";

		ss << "]";
		return ss.str();
	}

	bool QList::equals(const QObject* other) const
	{
		const QList* list = objectCast<QList>(other);
		if (!list)
			return false;

		return vec == list->vec;
	}

	Result QList::copyObject(QValue* result) const
	{
		*result = QValue::Object(new QList(*this));
		return true;
	}

	Result QList::getField(const String& name, QValue* result)
	{
		return fields.handleGet(this, name, result);
	}

	Result QList::getIndex(const QValue& index, QValue* result)
	{
		int32_t i;
		if (!index.getInteger(&i))
			return errors::invalid_index_type("Integer", index);

		if (i < 0 || i >= (int32_t)vec.size())
			return errors::index_out_of_range(index);

		*result = vec[i];
		return true;
	}

	Result QList::setIndex(const QValue& index, const QValue& value)
	{
		int32_t i;
		if (!index.getInteger(&i))
			return errors::invalid_index_type("Integer", index);

		if (i < 0 || i >= (int32_t)vec.size())
			return errors::index_out_of_range(index);

		objSize += value.GC_getSize() - vec[i].GC_getSize();
		vec[i] = value;
		return true;
	}

	Result QList::iterate(Context* context, QIterator** result)
	{
		*result = new QListIterator(vec.begin(), vec.end());
		return true;
	}

	const std::vector<imq::QValue>& QList::getVector() const
	{
		return vec;
	}

	void QList::GC_markChildren()
	{
		for (auto val : vec)
		{
			val.GC_mark();
		}
	}
}