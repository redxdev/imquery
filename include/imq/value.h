#pragma once

#include "platform.h"

#include <memory>
#include <functional>

#include "errors.h"

namespace imq
{
	typedef uint32_t TypeIndex;

	class QValue;

	class QObject
	{
	public:
		virtual ~QObject();

		virtual String toString() const;

		virtual bool equals(QObject* other) const = 0;

		// Do not implement yourself - use the IMQ_DECLARE_TYPE and IMQ_DEFINE_TYPE macros.
		virtual TypeIndex getTypeIndex() const = 0;
		virtual String getTypeString() const = 0;

		virtual bool getField(const String& name, QValue* result) const;
		virtual bool setField(const String& name, const QValue& value);

		virtual bool getIndex(const QValue& index, QValue* result) const;
		virtual bool setIndex(const QValue& index, const QValue& value);
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

	typedef std::shared_ptr<QObject> QObjectPtr;

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

	// bool NativeFunction(int32_t argCount, QValue** args, QValue* result);
	typedef std::function<bool(int32_t, QValue**, QValue*)> NativeFunction;

    class QValue
    {
    public:
        enum class Type
        {
            Nil,
			Bool,
            Integer,
            Float,
            Function,
            Object
        };

		static QValue Nil();
		static QValue Bool(bool val);
		static QValue Integer(int32_t val);
		static QValue Float(float val);
		static QValue Function(NativeFunction val);
		static QValue Object(QObjectPtr val);

		QValue();
		QValue(const QValue& other);
		QValue& operator=(const QValue& other);

		~QValue();

		Type getType() const;

		bool isNil() const;
		bool isBool() const;
		bool isInteger() const;
		bool isFloat() const;
		bool isFunction() const;
		bool isObject() const;

		bool getBool(bool* result) const;
		bool getInteger(int32_t* result) const;
		bool getFloat(float* result) const;
		bool getFunction(NativeFunction* result) const;
		bool getObject(QObjectPtr* result) const;

    private:
		Type valueType;

		union
		{
			bool b;
			int32_t i;
			float f;
			QObjectPtr obj;
			NativeFunction func;
		};
    };
}