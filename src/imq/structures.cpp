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