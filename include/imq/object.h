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

	enum class OperationOrder
	{
		LHS, // object is on the left-hand side
		RHS // object is on the right-hand side
	};

	class QObject
	{
	public:
		virtual ~QObject();

		virtual String toString() const;

		virtual bool equals(const QObject* other) const = 0;

		virtual std::size_t getHash() const;

		// Do not implement yourself - use the IMQ_DECLARE_TYPE and IMQ_DEFINE_TYPE macros.
		virtual TypeIndex getTypeIndex() const = 0;
		virtual String getTypeString() const = 0;

		virtual Result getField(const String& name, QValue* result);
		virtual Result setField(const String& name, const QValue& value);

		virtual Result getIndex(const QValue& index, QValue* result);
		virtual Result setIndex(const QValue& index, const QValue& value);

		virtual Result selection(ContextPtr context, const QValue& value, QSelection** result);

		// Operators - order is the position this object is in (RHS for right-hand, LHS for left-hand).
		virtual Result opAdd(OperationOrder order, const QValue& other, QValue* result) const;
		virtual Result opSub(OperationOrder order, const QValue& other, QValue* result) const;
		virtual Result opMul(OperationOrder order, const QValue& other, QValue* result) const;
		virtual Result opDiv(OperationOrder order, const QValue& other, QValue* result) const;
		virtual Result opMod(OperationOrder order, const QValue& other, QValue* result) const;
		virtual Result opNegate(QValue* result) const;
		virtual Result opNot(QValue* result) const;
		virtual Result opAnd(OperationOrder order, const QValue& other, QValue* result) const;
		virtual Result opOr(OperationOrder order, const QValue& other, QValue* result) const;
		virtual Result opLess(OperationOrder order, const QValue& other, QValue* result) const;
		virtual Result opLessEq(OperationOrder order, const QValue& other, QValue* result) const;
		virtual Result opGreater(OperationOrder order, const QValue& other, QValue* result) const;
		virtual Result opGreaterEq(OperationOrder order, const QValue& other, QValue* result) const;

		void updateSelfPointer(const std::shared_ptr<QObject> ptr);
		const std::weak_ptr<QObject>& getSelfPointer() const;

	private:
		std::weak_ptr<QObject> selfPtr;
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
}