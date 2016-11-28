#pragma once

#include "platform.h"
#include "context.h"

namespace imq
{
	typedef uint32_t TypeIndex;

	class QValue;

	class QSelection
	{
	public:
		virtual ~QSelection();

		virtual ContextPtr getContext() const = 0;
		virtual bool isValid() const = 0;
		virtual void next() = 0;
		virtual Result apply(const QValue& value) = 0;
	};

	class QObject
	{
	public:
		virtual ~QObject();

		virtual String toString() const;

		virtual bool equals(const QObject* other) const = 0;

		// Do not implement yourself - use the IMQ_DECLARE_TYPE and IMQ_DEFINE_TYPE macros.
		virtual TypeIndex getTypeIndex() const = 0;
		virtual String getTypeString() const = 0;

		virtual Result getField(const String& name, QValue* result) const;
		virtual Result setField(const String& name, const QValue& value);

		virtual Result getIndex(const QValue& index, QValue* result) const;
		virtual Result setIndex(const QValue& index, const QValue& value);

		virtual Result selection(ContextPtr context, const QValue& value, QSelection** result);
	};

	// Do not use yourself - use the IMQ_DECLARE_TYPE and IMQ_DEFINE_TYPE macros.
	class ObjectRegistry
	{
	public:
		static TypeIndex createTypeIndex();

		ObjectRegistry();

		TypeIndex getTypeIndex() const;

	private:
		static TypeIndex nextTypeIndex;

		TypeIndex typeIndex;
	};

#define IMQ_DECLARE_TYPE(name) \
	private: static imq::ObjectRegistry __objreg_##name; \
	public: virtual imq::TypeIndex getTypeIndex() const override {return __objreg_##name##.getTypeIndex();} \
	static imq::TypeIndex getStaticTypeIndex() {return __objreg_##name##.getTypeIndex();} \
	virtual imq::String getTypeString() const override {return #name;}
#define IMQ_DEFINE_TYPE(name) \
	static_assert(std::is_base_of<imq::QObject, name>::value, "IMQ_DEFINE_TYPE is only valid for QObject types."); \
	imq::ObjectRegistry name::__objreg_##name;

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