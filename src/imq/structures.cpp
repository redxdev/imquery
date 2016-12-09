#include "structures.h"

#include <sstream>

#include "errors.h"
#include "cast.h"

namespace imq
{
	IMQ_DEFINE_TYPE(QTable);

	QTable::QTable()
	{
	}

	QTable::QTable(const QTable& other)
	{
		map = other.map;
	}

	QTable::QTable(const std::unordered_map<QValue, QValue>& map)
		: map(map)
	{
	}

	QTable::~QTable()
	{
	}

	QTable& QTable::operator=(const QTable& other)
	{
		map = other.map;
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
			ss << entry.first.toString() << " = " << entry.second.toString();
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
		if (name == "has")
		{
			QObjectPtr sptr = getSelfPointer().lock();
			*result = QValue::Function([&, sptr](int32_t argCount, QValue* args, QValue* result) -> Result {
				if (argCount != 1)
					return errors::args_count("QTable.has", 1, argCount);

				*result = QValue::Bool(map.find(args[0]) != map.end());
				return true;
			});
			return true;
		}
		else if (name == "erase")
		{
			QObjectPtr sptr = getSelfPointer().lock();
			*result = QValue::Function([&, sptr](int32_t argCount, QValue* args, QValue* result) -> Result {
				if (argCount != 1)
					return errors::args_count("QTable.erase", 1, argCount);

				auto found = map.find(args[0]);
				if (found == map.end())
					return errors::undefined_index(getTypeString(), args[0]);

				map.erase(found);
				return true;
			});
			return true;
		}
		else if (name == "length")
		{
			*result = QValue::Integer((int32_t)map.size());
			return true;
		}
		else if (name == "clear")
		{
			QObjectPtr sptr = getSelfPointer().lock();
			*result = QValue::Function([&, sptr](int32_t argCount, QValue* args, QValue* result) -> Result {
				if (argCount != 0)
					return errors::args_count("QList.clear", 0, argCount);

				map.clear();
				return true;
			});
			return true;
		}
		else if (name == "keys")
		{
			std::vector<QValue> keys;
			for (auto entry : map)
			{
				keys.push_back(entry.first);
			}

			*result = QValue::Object(new QList(keys));
			return true;
		}
		else if (name == "values")
		{
			std::vector<QValue> values;
			for (auto entry : map)
			{
				values.push_back(entry.second);
			}

			*result = QValue::Object(new QList(values));
			return true;
		}

		return errors::undefined_field(getTypeString(), name);
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
		map[index] = value;
		return true;
	}

	const std::unordered_map<imq::QValue, imq::QValue>& QTable::getMap() const
	{
		return map;
	}

	IMQ_DEFINE_TYPE(QList);

	QList::QList()
	{
	}

	QList::QList(const QList& other)
	{
		vec = other.vec;
	}

	QList::QList(const std::vector<QValue>& vec)
		: vec(vec)
	{
	}

	QList::~QList()
	{
	}

	QList& QList::operator=(const QList& other)
	{
		vec = other.vec;
		return *this;
	}

	String QList::toString() const
	{
		int32_t count = 0;
		std::stringstream ss;
		ss << "[";
		for (auto val : vec)
		{
			++count;
			ss << val.toString();
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
		if (name == "length")
		{
			*result = QValue::Integer((int32_t)vec.size());
			return true;
		}
		else if (name == "insert")
		{
			QObjectPtr sptr = getSelfPointer().lock();
			*result = QValue::Function([&, sptr](int32_t argCount, QValue* args, QValue* result) -> Result {
				switch (argCount)
				{
				default:
					return errors::args_count("QList.insert", 1, 2, argCount);

				case 1:
					vec.push_back(args[0]);
					return true;

				case 2:
				{
					int32_t index;
					if (!args[1].getInteger(&index))
						return errors::args_type("QList.insert", 1, "Integer", args[1]);

					vec.insert(vec.begin() + (size_t)index, args[0]);
					return true;
				}
				}
			});
			return true;
		}
		else if (name == "erase")
		{
			QObjectPtr sptr = getSelfPointer().lock();
			*result = QValue::Function([&, sptr](int32_t argCount, QValue* args, QValue* result) -> Result {
				if (argCount != 1)
					return errors::args_count("QList.erase", 1, argCount);

				int32_t index;
				if (!args[0].getInteger(&index))
					return errors::args_type("QList.erase", 0, "Integer", args[0]);

				if (index < 0 || index >= (int32_t)vec.size())
					return errors::index_out_of_range(args[0]);

				vec.erase(vec.begin() + index);
				return true;
			});
			return true;
		}
		else if (name == "clear")
		{
			QObjectPtr sptr = getSelfPointer().lock();
			*result = QValue::Function([&, sptr](int32_t argCount, QValue* args, QValue* result) -> Result {
				if (argCount != 0)
					return errors::args_count("QList.clear", 0, argCount);

				vec.clear();
				return true;
			});
			return true;
		}

		return errors::undefined_field(getTypeString(), name);
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

		vec[i] = value;
		return true;
	}

	const std::vector<imq::QValue>& QList::getVector() const
	{
		return vec;
	}

}