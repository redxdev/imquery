#pragma once

#include "platform.h"

#include <memory>
#include <functional>

#include "result.h"

namespace imq
{
	class QObject;
	class QValue;

	typedef std::shared_ptr<QObject> QObjectPtr;

	// Result QFunction(int32_t argCount, QValue* args, QValue* result);
	typedef std::function<Result(int32_t, QValue*, QValue*)> QFunction;

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
		static QValue Function(QFunction val);
		static QValue Object(QObjectPtr val);
		static QValue Object(QObject* val);

		static String getTypeString(Type t);

		QValue();
		QValue(const QValue& other);
		QValue& operator=(const QValue& other);

		~QValue();

		Type getType() const;

		// This is _not_ equivalent to the other toX methods - it doesn't
		// create a new String QValue. This gets the string representation of
		// this QValue and returns it.
		String toString() const;

		bool isNil() const;
		bool isBool() const;
		bool isInteger() const;
		bool isFloat() const;
		bool isFunction() const;
		bool isObject() const;

		bool getBool(bool* result) const;
		bool getInteger(int32_t* result) const;
		bool getFloat(float* result) const;
		bool getFunction(QFunction* result) const;
		bool getObject(QObjectPtr* result) const;

		bool toBool(QValue* result) const;
		bool toInteger(QValue* result) const;
		bool toFloat(QValue* result) const;

		friend bool operator==(const QValue& a, const QValue& b);
		friend bool operator!=(const QValue& a, const QValue& b);

		// TODO: Support rhs objects
		Result opAdd(const QValue& rhs, QValue* result) const;
		Result opSub(const QValue& rhs, QValue* result) const;
		Result opMul(const QValue& rhs, QValue* result) const;
		Result opDiv(const QValue& rhs, QValue* result) const;
		Result opMod(const QValue& rhs, QValue* result) const;
		Result opNegate(QValue* result) const;
		Result opNot(QValue* result) const;
		Result opAnd(const QValue& rhs, QValue* result) const;
		Result opOr(const QValue& rhs, QValue* result) const;
		Result opLess(const QValue& rhs, QValue* result) const;
		Result opLessEq(const QValue& rhs, QValue* result) const;
		Result opGreater(const QValue& rhs, QValue* result) const;
		Result opGreaterEq(const QValue& rhs, QValue* result) const;

    private:
		Type valueType;

		union
		{
			bool b;
			int32_t i;
			float f;
			QObjectPtr obj;
			QFunction func;
		};
    };

	bool operator==(const QValue& a, const QValue& b);
	bool operator!=(const QValue& a, const QValue& b);
}