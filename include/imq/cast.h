#include "object.h"
#include "value.h"

#include <memory>

namespace imq
{
	template<typename T>
	T* objectCast(QObject* obj)
	{
		static_assert(std::is_base_of<QObject, T>::value, "objectCast is only valid for QObject types.");
		if (obj == nullptr)
		{
			return nullptr;
		}

		if (obj->getTypeIndex() == T::getStaticTypeIndex())
		{
			return reinterpret_cast<T*>(obj);
		}
		else
		{
			return nullptr;
		}
	}

	template<typename T>
	const T* objectCast(const QObject* obj)
	{
		static_assert(std::is_base_of<QObject, T>::value, "objectCast is only valid for QObject types.");
		if (obj == nullptr)
		{
			return nullptr;
		}

		if (obj->getTypeIndex() == T::getStaticTypeIndex())
		{
			return reinterpret_cast<const T*>(obj);
		}
		else
		{
			return nullptr;
		}
	}

	IMQ_API inline bool checkTypesEqual(const QValue& a, const QValue& b)
	{
		if (a.getType() != b.getType())
			return false;

		if (a.getType() != QValue::Type::Object)
			return true;

		QObject* objA;
		QObject* objB;

		if (!a.getObject(&objA) || !b.getObject(&objB))
			return false;

		return objA && objB && objA->getTypeIndex() == objB->getTypeIndex();
	}
}