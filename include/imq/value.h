#pragma once

#include "platform.h"

#include <memory>
#include <functional>

#include "result.h"
#include "gc.h"

namespace imq
{
	class QObject;
	class QValue;
	class VMachine;

	typedef std::function<Result(VMachine*, int32_t, QValue*, QValue*)> QFunctionPtr;

	class QFunction : public GCObject
	{
	public:
		QFunction(VMachine* vm);
		virtual ~QFunction();

		virtual Result execute(VMachine* vm, int32_t argCount, QValue* args, QValue* result) = 0;

	private:
		VMachine* vm;
	};

	class QSimpleFunction : public QFunction
	{
	public:
		QSimpleFunction(VMachine* vm, QFunctionPtr func);
		virtual ~QSimpleFunction();

		virtual Result execute(VMachine* vm, int32_t argCount, QValue* args, QValue* result) override;

		virtual size_t GC_getSize() const override;
		virtual bool GC_isDynamic() const override { return false; }

	private:
		QFunctionPtr func;
	};

	class QBoundFunction : public QSimpleFunction
	{
	public:
		QBoundFunction(VMachine* vm, QObject* obj, QFunctionPtr func);
		virtual ~QBoundFunction();

		virtual size_t GC_getSize() const override;
		virtual bool GC_isDynamic() const override { return false; }

	protected:

		virtual void GC_markChildren() override;

	private:
		QObject* obj;
	};

    class QValue : public GCTraceable
    {
    public:
		friend struct std::hash<imq::QValue>;

        enum class Type
        {
            Nil,
			Bool,
            Integer,
            Float,
			String,
            Function,
            Object
        };

		static QValue Nil();
		static QValue Bool(bool val);
		static QValue Integer(int32_t val);
		static QValue Float(float val);
		static QValue String(const CString val);
		static QValue String(const imq::String& val);
		static QValue Function(QFunction* val);
		static QValue Function(VMachine* vm, QFunctionPtr val);
		static QValue Function(VMachine* vm, QObject* obj, QFunctionPtr val);
		static QValue Object(QObject* val);

		static imq::String getTypeString(Type t);

		QValue();
		QValue(const QValue& other);
		QValue& operator=(const QValue& other);

		~QValue();

		Type getType() const;

		// This is _not_ equivalent to the other toX methods - it doesn't
		// create a new String QValue. This gets the string representation of
		// this QValue and returns it.
		imq::String asString() const;

		bool isNil() const;
		bool isBool() const;
		bool isInteger() const;
		bool isFloat() const;
		bool isString() const;
		bool isFunction() const;
		bool isObject() const;

		bool getBool(bool* result) const;
		bool getInteger(int32_t* result) const;
		bool getFloat(float* result) const;
		bool getNumber(int32_t* result) const;
		bool getNumber(float* result) const;
		bool getString(CString* result) const;
		bool getString(imq::String* result) const;
		bool getFunction(QFunction** result) const;
		bool getObject(QObject** result) const;

		bool toBool(QValue* result) const;
		bool toInteger(QValue* result) const;
		bool toFloat(QValue* result) const;
		bool toString(QValue* result) const;

		friend bool operator==(const QValue& a, const QValue& b);
		friend bool operator!=(const QValue& a, const QValue& b);

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

		virtual void GC_mark() override;

		size_t GC_getSize() const;

    private:
		Type valueType;

		union
		{
			bool b;
			int32_t i;
			float f;
			CString s;
			QObject* obj;
			QFunction* func;
		};
    };

	bool operator==(const QValue& a, const QValue& b);
	bool operator!=(const QValue& a, const QValue& b);
}