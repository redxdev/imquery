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

		// Operators
		virtual Result opAdd(const QValue& rhs, QValue* result) const;
		virtual Result opSub(const QValue& rhs, QValue* result) const;
		virtual Result opMul(const QValue& rhs, QValue* result) const;
		virtual Result opDiv(const QValue& rhs, QValue* result) const;
		virtual Result opMod(const QValue& rhs, QValue* result) const;
		virtual Result opNegate(QValue* result) const;
		virtual Result opNot(QValue* result) const;
		virtual Result opAnd(const QValue& rhs, QValue* result) const;
		virtual Result opOr(const QValue& rhs, QValue* result) const;
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