#pragma once

#include "platform.h"
#include "context.h"
#include "gc.h"
#include "fieldhelper.h"

namespace imq
{
	typedef uint32_t TypeIndex;

	class QValue;

	class IMQ_API QSelection
	{
	public:
		virtual ~QSelection();

		virtual Context* getContext() const = 0;
		virtual bool isValid() const = 0;
		virtual void next() = 0;
		virtual Result apply(const QValue& value, int32_t coordCount, QValue* coords) = 0;
	};

	class IMQ_API QIterator
	{
	public:
		virtual ~QIterator();

		virtual bool isValid() const = 0;
		virtual void next() = 0;
		virtual QValue getCurrentValue() const = 0;
	};

	enum class IMQ_API OperationOrder
	{
		LHS, // object is on the left-hand side
		RHS // object is on the right-hand side
	};

	class IMQ_API QObject : public GCObject
	{
	public:
		QObject(VMachine* vm);
		virtual ~QObject();

		virtual String toString() const;

		virtual bool equals(const QObject* other) const = 0;

		virtual Result copyObject(QValue* result) const;

		virtual std::size_t getHash() const;

		// Do not implement yourself - use the IMQ_DECLARE_TYPE and IMQ_DEFINE_TYPE macros.
		virtual TypeIndex getTypeIndex() const = 0;
		virtual String getTypeString() const = 0;

		virtual Result getField(const String& name, QValue* result);
		virtual Result setField(const String& name, const QValue& value);

		virtual Result getIndex(const QValue& index, QValue* result);
		virtual Result setIndex(const QValue& index, const QValue& value);

		virtual Result selection(Context* context, const QValue& value, QSelection** result);
		virtual Result iterate(Context* context, QIterator** result);

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

		VMachine* getVM() const;

	private:
		VMachine* vm;
	};

	// Do not use yourself - use the IMQ_DECLARE_TYPE and IMQ_DEFINE_TYPE macros.
	class IMQ_API ObjectRegistry
	{
	public:
		static TypeIndex createTypeIndex();

		ObjectRegistry();

		TypeIndex getTypeIndex() const;

	private:
		static TypeIndex nextTypeIndex;

		TypeIndex typeIndex;
	};

#define __IMQ_DECLARE_TYPE(name) \
	private: static imq::ObjectRegistry __objreg_##name; \
	public: virtual imq::TypeIndex getTypeIndex() const override; \
	static imq::TypeIndex getStaticTypeIndex(); \
	virtual imq::String getTypeString() const override {return #name;} \
	virtual size_t GC_getSize() const override;

#define IMQ_DECLARE_TYPE(name) \
	__IMQ_DECLARE_TYPE(name) \
	virtual bool GC_isDynamic() const override {return false;}

#define IMQ_DECLARE_TYPE_DYNAMIC(name) \
	__IMQ_DECLARE_TYPE(name) \
	virtual bool GC_isDynamic() const override {return true;}

#define IMQ_DEFINE_TYPE(name) \
	static_assert(std::is_base_of<imq::QObject, name>::value, "IMQ_DEFINE_TYPE is only valid for QObject types."); \
	imq::ObjectRegistry name::__objreg_##name; \
	imq::TypeIndex name::getTypeIndex() const {return __objreg_##name.getTypeIndex();} \
	imq::TypeIndex name::getStaticTypeIndex() {return __objreg_##name.getTypeIndex();}

#define IMQ_DEFINE_TYPE_WITH_CUSTOM(name, val) \
	IMQ_DEFINE_TYPE(name); \
	size_t name::GC_getSize() const {return (val);}

#define IMQ_DEFINE_TYPE_WITH_FIELDS_CUSTOM(name, fields, val) \
	IMQ_DEFINE_TYPE(name); \
	size_t name::GC_getSize() const {return fields.GC_getSize() - sizeof(imq::ObjectFieldHelper) + (val);}

#define IMQ_DEFINE_TYPE_WITH_SIZE(name) \
	IMQ_DEFINE_TYPE(name); \
	size_t name::GC_getSize() const {return sizeof(name);}

#define IMQ_DEFINE_TYPE_WITH_SIZE_FIELDS(name, fields) \
	IMQ_DEFINE_TYPE(name); \
	size_t name::GC_getSize() const {return sizeof(name) + fields.GC_getSize() - sizeof(imq::ObjectFieldHelper);}

#define IMQ_DEFINE_TYPE_WITH_SIZE_CUSTOM(name, val) \
	IMQ_DEFINE_TYPE(name); \
	size_t name::GC_getSize() const {return sizeof(name) + (val);}

#define IMQ_DEFINE_TYPE_WITH_SIZE_FIELDS_CUSTOM(name, fields, val) \
	IMQ_DEFINE_TYPE(name); \
	size_t name::GC_getSize() const {return sizeof(name) + fields.GC_getSize() - sizeof(imq::ObjectFieldHelper) + (val);}
}