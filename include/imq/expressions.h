#pragma once

#include "platform.h"
#include "vm.h"

#include <tuple>
#include <vector>

namespace imq
{
	class ConstantExpr : public VExpression
	{
	public:
		ConstantExpr(const QValue& value, const VLocation& loc);
		virtual ~ConstantExpr();

		virtual String getName() const override;
		virtual Result execute(ContextPtr context, QValue* result) override;

	private:
		QValue value;
	};

	class ColorExpr : public VExpression
	{
	public:
		ColorExpr(VExpression* rExpr, VExpression* gExpr, VExpression* bExpr, VExpression* aExpr, const VLocation& loc);
		virtual ~ColorExpr();

		virtual String getName() const override;
		virtual Result execute(ContextPtr context, QValue* result) override;

	private:
		VExpression* rExpr;
		VExpression* gExpr;
		VExpression* bExpr;
		VExpression* aExpr;
	};

	class ListExpr : public VExpression
	{
	public:
		ListExpr(const std::vector<VExpression*> values, const VLocation& loc);
		virtual ~ListExpr();

		virtual String getName() const override;
		virtual Result execute(ContextPtr context, QValue* result) override;

	private:
		std::vector<VExpression*> values;
	};

	class TableExpr : public VExpression
	{
	public:
		TableExpr(const std::vector<std::tuple<VExpression*, VExpression*>> values, const VLocation& loc);
		virtual ~TableExpr();

		virtual String getName() const override;
		virtual Result execute(ContextPtr context, QValue* result) override;

	private:
		std::vector<std::tuple<VExpression*, VExpression*>> values;
	};

	class RetrieveVariableExpr : public VExpression
	{
	public:
		RetrieveVariableExpr(const String& variable, const VLocation& loc);
		virtual ~RetrieveVariableExpr();

		virtual String getName() const override;
		virtual Result execute(ContextPtr context, QValue* result) override;

	private:
		String variable;
	};

	class RetrieveFieldExpr : public VExpression
	{
	public:
		RetrieveFieldExpr(VExpression* objExpr, const String& field, const VLocation& loc);
		virtual ~RetrieveFieldExpr();

		virtual String getName() const override;
		virtual Result execute(ContextPtr context, QValue* result) override;
	
	private:
		VExpression* objExpr;
		String field;
	};

	class RetrieveIndexExpr : public VExpression
	{
	public:
		RetrieveIndexExpr(VExpression* objExpr, VExpression* indexExpr, const VLocation& loc);
		virtual ~RetrieveIndexExpr();

		virtual String getName() const override;
		virtual Result execute(ContextPtr context, QValue* result) override;

	private:
		VExpression* objExpr;
		VExpression* indexExpr;
	};

	class CallFunctionExpr : public VExpression
	{
	public:
		CallFunctionExpr(VExpression* funcExpr, int32_t argC, VExpression** args, const VLocation& loc);
		virtual ~CallFunctionExpr();

		virtual String getName() const override;
		virtual Result execute(ContextPtr context, QValue* result) override;

	private:
		VExpression* funcExpr;
		int32_t argCount;
		VExpression** args;
	};

	class SetVariableStm : public VStatement
	{
	public:
		SetVariableStm(const String& variable, VExpression* valueExpr, const VLocation& loc);
		virtual ~SetVariableStm();

		virtual String getName() const override;
		virtual Result execute(ContextPtr context) override;

	private:
		String variable;
		VExpression* valueExpr;
	};

	class SetFieldStm : public VStatement
	{
	public:
		SetFieldStm(VExpression* objExpr, const String& field, VExpression* valueExpr, const VLocation& loc);
		virtual ~SetFieldStm();

		virtual String getName() const override;
		virtual Result execute(ContextPtr context) override;

	private:
		String field;
		VExpression* objExpr;
		VExpression* valueExpr;
	};

	class SetIndexStm : public VStatement
	{
	public:
		SetIndexStm(VExpression* objExpr, VExpression* indexExpr, VExpression* valueExpr, const VLocation& loc);
		virtual ~SetIndexStm();

		virtual String getName() const override;
		virtual Result execute(ContextPtr context) override;

	private:
		VExpression* indexExpr;
		VExpression* objExpr;
		VExpression* valueExpr;
	};

	class DeleteVariableStm : public VStatement
	{
	public:
		DeleteVariableStm(const String& variable, const VLocation& loc);
		virtual ~DeleteVariableStm();

		virtual String getName() const override;
		virtual Result execute(ContextPtr context) override;

	private:
		String variable;
	};

	class SelectStm : public VStatement
	{
	public:
		SelectStm(VExpression* destExpr, VExpression* srcExpr, VExpression* calcExpr, VExpression* whereExpr, VExpression* elseExpr, int32_t coordCount, VExpression** coordsExpr, const VLocation& loc);
		virtual ~SelectStm();

		virtual String getName() const override;
		virtual Result execute(ContextPtr context) override;

	private:
		VExpression* destExpr;
		VExpression* srcExpr;
		VExpression* calcExpr;
		VExpression* whereExpr;
		VExpression* elseExpr;

		VExpression** coordsExpr;
		int32_t coordCount;
	};

	class DefineInputStm : public VStatement
	{
	public:
		DefineInputStm(const String& name, VExpression* valueExpr, const VLocation& loc);
		virtual ~DefineInputStm();

		virtual String getName() const override;
		virtual Result execute(ContextPtr context) override;

	private:
		String name;
		VExpression* valueExpr;
	};

	class DefineOutputStm : public VStatement
	{
	public:
		DefineOutputStm(const String& name, VExpression* valueExpr, const VLocation& loc);
		virtual ~DefineOutputStm();

		virtual String getName() const override;
		virtual Result execute(ContextPtr context) override;

	private:
		String name;
		VExpression* valueExpr;
	};

	class BranchStm : public VStatement
	{
	public:
		BranchStm(VExpression* checkExpr, VStatement* trueStm, VStatement* falseStm, const VLocation& loc);
		virtual ~BranchStm();

		virtual String getName() const override;
		virtual Result execute(ContextPtr context) override;

	private:
		VExpression* checkExpr;
		VStatement* trueStm;
		VStatement* falseStm;
	};

	class ForLoopStm : public VStatement
	{
	public:
		ForLoopStm(VStatement* initStm, VExpression* checkExpr, VStatement* incrStm, VStatement* execStm, const VLocation& loc);
		virtual ~ForLoopStm();

		virtual String getName() const override;
		virtual Result execute(ContextPtr context) override;

	private:
		VStatement* initStm;
		VExpression* checkExpr;
		VStatement* incrStm;
		VStatement* execStm;
	};

	class WhileLoopStm : public VStatement
	{
	public:
		WhileLoopStm(VExpression* checkExpr, VStatement* execStm, const VLocation& loc);
		virtual ~WhileLoopStm();

		virtual String getName() const override;
		virtual Result execute(ContextPtr context) override;

	private:
		VExpression* checkExpr;
		VStatement* execStm;
	};

	class InfiniteLoopStm : public VStatement
	{
	public:
		InfiniteLoopStm(VStatement* execStm, const VLocation& loc);
		virtual ~InfiniteLoopStm();

		virtual String getName() const override;
		virtual Result execute(ContextPtr context) override;
		
	private:
		VStatement* execStm;
	};

	class BreakStm : public VStatement
	{
	public:
		BreakStm(const VLocation& loc);
		virtual ~BreakStm();

		virtual String getName() const override;
		virtual Result execute(ContextPtr context) override;
	};

	class ReturnStm : public VStatement
	{
	public:
		ReturnStm(VExpression* valueExpr, const VLocation& loc);
		virtual ~ReturnStm();

		virtual String getName() const override;
		virtual Result execute(ContextPtr context) override;

	private:
		VExpression* valueExpr;
	};

	class NoOpStm : public VStatement
	{
	public:
		NoOpStm(const VLocation& loc);
		virtual ~NoOpStm();

		virtual String getName() const override;
		virtual Result execute(ContextPtr context) override;
	};

	class TernaryExpr : public VExpression
	{
	public:
		TernaryExpr(VExpression* checkExpr, VExpression* trueExpr, VExpression* falseExpr, const VLocation& loc);
		virtual ~TernaryExpr();

		virtual String getName() const override;
		virtual Result execute(ContextPtr context, QValue* result) override;

	private:
		VExpression* checkExpr;
		VExpression* trueExpr;
		VExpression* falseExpr;
	};
}