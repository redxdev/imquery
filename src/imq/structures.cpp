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
}