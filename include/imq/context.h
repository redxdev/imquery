#pragma once

#include "platform.h"
#include "result.h"
#include "value.h"
#include "gc.h"

#include <unordered_map>
#include <memory>

namespace imq
{
	class VMachine;

	class IMQ_API Context : public GCObject
	{
	public:
		Context(VMachine* vm);
		virtual ~Context();

		virtual bool hasValue(const String& key) const = 0;
		virtual Result getValue(const String& key, QValue* result) const = 0;
		virtual Result setValue(const String& key, const QValue& value) = 0;
		virtual Result deleteValue(const String& key) = 0;

		virtual Result exportValue(const String& key, const QValue& value) = 0;

		virtual Result registerInput(const String& key, const QValue& value) = 0;
		virtual Result registerOutput(const String& key, const QValue& value) = 0;

		virtual Result setBreakable(bool bValue) = 0;
		virtual bool isBreakable() const = 0;
		virtual Result breakContext() = 0;
		virtual bool isContextBroken() const = 0;

		virtual Result setReturnable(bool bValue) = 0;
		virtual bool isReturnable() const = 0;
		virtual Result returnContext(const QValue& value) = 0;
		virtual bool getReturnValue(QValue* result) const = 0;
		bool isContextReturnedFrom() const;

		virtual bool isClosedOver() const { return false; }
		virtual void close() {}

		VMachine* getVM() const;

		virtual bool GC_isDynamic() const override { return true; }

	private:
		VMachine* vm;
	};

	// A simple form of context. This stores values in an unordered_map and allows both read and write access.
	// This type of context is really only used for testing since it can't have a parent. See SubContext if you
	// want to create a new context while still having access to the context hierarchy.
	class IMQ_API SimpleContext : public Context
	{
	public:
		SimpleContext(VMachine* vm);
		virtual ~SimpleContext();

		virtual bool hasValue(const String& key) const override;
		virtual Result getValue(const String& key, QValue* result) const override;
		virtual Result setValue(const String& key, const QValue& value) override;
		virtual Result deleteValue(const String& key) override;
		virtual Result exportValue(const String& key, const QValue& value) override;
		virtual Result registerInput(const String& key, const QValue& value) override;
		virtual Result registerOutput(const String& key, const QValue& value) override;
		virtual Result setBreakable(bool bValue) override;
		virtual bool isBreakable() const override;
		virtual Result breakContext() override;
		virtual bool isContextBroken() const override;
		virtual Result setReturnable(bool bValue) override;
		virtual bool isReturnable() const override;
		virtual Result returnContext(const QValue& value) override;
		virtual bool getReturnValue(QValue* result) const override;

		virtual size_t GC_getSize() const override;
		virtual void GC_markChildren() override;

	protected:
		std::unordered_map<String, QValue> values;
		bool bBreakable = false;
		bool bBroken = false;
		bool bReturnable = false;
		bool bReturned = false;
		QValue returnValue;
	};

	class IMQ_API RootContext : public Context
	{
	public:
		RootContext(VMachine* vm);
		virtual bool hasValue(const String& key) const override;
		virtual Result getValue(const String& key, QValue* result) const override;
		virtual Result setValue(const String& key, const QValue& value) override;
		virtual Result deleteValue(const String& key) override;
		virtual Result exportValue(const String& key, const QValue& value) override;
		virtual Result registerInput(const String& key, const QValue& value) override;
		virtual Result registerOutput(const String& key, const QValue& value) override;
		virtual Result setBreakable(bool bValue) override;
		virtual bool isBreakable() const override;
		virtual Result breakContext() override;
		virtual bool isContextBroken() const override;
		virtual Result setReturnable(bool bValue) override;
		virtual bool isReturnable() const override;
		virtual Result returnContext(const QValue& value) override;
		virtual bool getReturnValue(QValue* result) const override;

		virtual size_t GC_getSize() const override;
		virtual void GC_markChildren() override;

		void setInput(const String& key, const QValue& value);
		void setOutput(const String& key, const QValue& value);

		const std::unordered_map<String, QValue>& getInputs() const;
		const std::unordered_map<String, QValue>& getOutputs() const;

		// resets this context's internal state
		void reset();

	protected:
		std::unordered_map<String, QValue> values;
		std::unordered_map<String, QValue> inputs;
		std::unordered_map<String, QValue> outputs;

		size_t objSize = 0;
	};

	// A context that has a parent and passes undefined get/deletes to it.
	class IMQ_API SubContext : public Context
	{
	public:
		SubContext(VMachine* vm, Context* parent);
		virtual ~SubContext();

		Context* getParent() const;

		virtual bool hasValue(const String& key) const override;
		virtual Result getValue(const String& key, QValue* result) const override;
		virtual Result setValue(const String& key, const QValue& value) override;
		virtual Result deleteValue(const String& key) override;
		virtual Result exportValue(const String& key, const QValue& value) override;
		virtual Result registerInput(const String& key, const QValue& value) override;
		virtual Result registerOutput(const String& key, const QValue& value) override;
		virtual Result setBreakable(bool bValue) override;
		virtual bool isBreakable() const override;
		virtual Result breakContext() override;
		virtual bool isContextBroken() const override;
		virtual Result setReturnable(bool bValue) override;
		virtual bool isReturnable() const override;
		virtual Result returnContext(const QValue& value) override;
		virtual bool getReturnValue(QValue* result) const override;

		virtual size_t GC_getSize() const override;
		virtual void GC_markChildren() override;

		virtual bool isClosedOver() const override;
		virtual void close() override;

	protected:
		Context* parent;
		std::unordered_map<String, QValue> values;
		bool bBreakable = false;
		bool bBroken = false;
		bool bReturnable = false;
		bool bReturned = false;
		QValue returnValue;

		// This is an optimization - if the context hasn't been closed over then we can delete it freely instead of
		// waiting for garbage collection to pick it up.
		bool bClosedOver = false;

		size_t objSize = 0;
	};

	class IMQ_API RestrictedSubContext : public SubContext
	{
	public:
		RestrictedSubContext(VMachine* vm, Context* parent);
		virtual ~RestrictedSubContext();

		// Allows you to bypass the lock on setValue
		void setRawValue(const String& key, const QValue& value);

		virtual Result setValue(const String& key, const QValue& value) override;
		virtual Result deleteValue(const String& key) override;
		virtual Result exportValue(const String& key, const QValue& value) override;
	};

	// This automatically deletes a context (if it hasn't been closed over) at the end of a scope.
	class IMQ_API ScopedContext
	{
	public:
		ScopedContext(Context* ctx);
		~ScopedContext();

	private:
		Context* context;
	};

	class IMQ_API ImportContext : public Context
	{
	public:
		ImportContext(VMachine* vm, Context* parent);
		virtual ~ImportContext();

		virtual bool hasValue(const String& key) const override;
		virtual Result getValue(const String& key, QValue* result) const override;
		virtual Result setValue(const String& key, const QValue& value) override;
		virtual Result deleteValue(const String& key) override;
		virtual Result exportValue(const String& key, const QValue& value) override;
		virtual Result registerInput(const String& key, const QValue& value) override;
		virtual Result registerOutput(const String& key, const QValue& value) override;
		virtual Result setBreakable(bool bValue) override;
		virtual bool isBreakable() const override;
		virtual Result breakContext() override;
		virtual bool isContextBroken() const override;
		virtual Result setReturnable(bool bValue) override;
		virtual bool isReturnable() const override;
		virtual Result returnContext(const QValue& value) override;
		virtual bool getReturnValue(QValue* result) const override;

		virtual size_t GC_getSize() const override;
		virtual void GC_markChildren() override;

		const std::unordered_map<String, QValue>& getExports() const;

	protected:
		Context* parent;
		std::unordered_map<String, QValue> exports;
		size_t objSize = 0;
	};
}