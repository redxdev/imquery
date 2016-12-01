#include "object.h"
#include "value.h"

#include <memory>

namespace imq
{
	template<typename T>
	T* objectCast(QObject* obj)
	{
		static_assert(std::is_base_of<QObject, T>::value, "objectCast is only valid for QObject types.");
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
		if (obj->getTypeIndex() == T::getStaticTypeIndex())
		{
			return reinterpret_cast<const T*>(obj);
		}
		else
		{
			return nullptr;
		}
	}
}