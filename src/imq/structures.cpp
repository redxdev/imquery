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
		std::stringstream ss;
		ss << "QTable[" << map.size() << "]";
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
			QObjectPtr sptr = getSelfPointer().lock();
			*result = QValue::Function([&, sptr](int32_t argCount, QValue* args, QValue* result) -> Result {
				if (argCount != 0)
					return errors::args_count("QTable.length", 0, argCount);

				*result = QValue::Integer((int32_t)map.size());
				return true;
			});
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

	IMQ_DEFINE_TYPE(QList);

	QList::QList()
	{
	}

	QList::QList(const QList& other)
	{
		vec = other.vec;
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
		std::stringstream ss;
		ss << "QList[" << vec.size() << "]";
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
			QObjectPtr sptr = getSelfPointer().lock();
			*result = QValue::Function([&, sptr](int32_t argCount, QValue* args, QValue* result) -> Result {
				if (argCount != 0)
					return errors::args_count("QList.length", 0, argCount);

				*result = QValue::Integer((int32_t)vec.size());
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

		if (i < 0 || i > (int32_t)vec.size())
			return errors::index_out_of_range(index);

		*result = vec[i];
		return true;
	}

	Result QList::setIndex(const QValue& index, const QValue& value)
	{
		int32_t i;
		if (!index.getInteger(&i))
			return errors::invalid_index_type("Integer", index);

		if (i < 0 || i > vec.size())
			return errors::index_out_of_range(index);

		vec[i] = value;
		return true;
	}
}