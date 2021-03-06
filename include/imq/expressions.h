#pragma once

#include "platform.h"
#include "vm.h"

#include <tuple>
#include <vector>

namespace imq
{
	class IMQ_API ConstantExpr : public VExpression
	{
	public:
		ConstantExpr(const QValue& value, const VLocation& loc);
		virtual ~ConstantExpr();

		virtual String getName() const override;
		virtual Result execute(Context* context, QValue* result) override;

	private:
		QValue value;
	};

	class IMQ_API ColorExpr : public VExpression
	{
	public:
		ColorExpr(VExpression* rExpr, VExpression* gExpr, VExpression* bExpr, VExpression* aExpr, const VLocation& loc);
		virtual ~ColorExpr();

		virtual String getName() const override;
		virtual Result execute(Context* context, QValue* result) override;

	private:
		VExpression* rExpr;
		VExpression* gExpr;
		VExpression* bExpr;
		VExpression* aExpr;
	};

	class IMQ_API ListExpr : public VExpression
	{
	public:
		ListExpr(const std::vector<VExpression*> values, const VLocation& loc);
		virtual ~ListExpr();

		virtual String getName() const override;
		virtual Result execute(Context* context, QValue* result) override;

	private:
		std::vector<VExpression*> values;
	};

	class IMQ_API TableExpr : public VExpression
	{
	public:
		TableExpr(const std::vector<std::tuple<VExpression*, VExpression*>> values, const VLocation& loc);
		virtual ~TableExpr();

		virtual String getName() const override;
		virtual Result execute(Context* context, QValue* result) override;

	private:
		std::vector<std::tuple<VExpression*, VExpression*>> values;
	};

	class IMQ_API RetrieveVariableExpr : public VExpression
	{
	public:
		RetrieveVariableExpr(const String& variable, const VLocation& loc);
		virtual ~RetrieveVariableExpr();

		virtual String getName() const override;
		virtual Result execute(Context* context, QValue* result) override;

	private:
		String variable;
	};

	class IMQ_API RetrieveFieldExpr : public VExpression
	{
	public:
		RetrieveFieldExpr(VExpression* objExpr, const String& field, const VLocation& loc);
		virtual ~RetrieveFieldExpr();

		virtual String getName() const override;
		virtual Result execute(Context* context, QValue* result) override;
	
	private:
		VExpression* objExpr;
		String field;
	};

	class IMQ_API RetrieveIndexExpr : public VExpression
	{
	public:
		RetrieveIndexExpr(VExpression* objExpr, VExpression* indexExpr, const VLocation& loc);
		virtual ~RetrieveIndexExpr();

		virtual String getName() const override;
		virtual Result execute(Context* context, QValue* result) override;

	private:
		VExpression* objExpr;
		VExpression* indexExpr;
	};

	class IMQ_API CallFunctionExpr : public VExpression
	{
	public:
		CallFunctionExpr(VExpression* funcExpr, int32_t argC, VExpression** args, const VLocation& loc);
		virtual ~CallFunctionExpr();

		virtual String getName() const override;
		virtual Result execute(Context* context, QValue* result) override;

	private:
		VExpression* funcExpr;
		int32_t argCount;
		VExpression** args;
	};

	class IMQ_API SetVariableStm : public VStatement
	{
	public:
		SetVariableStm(const String& variable, VExpression* valueExpr, const VLocation& loc);
		virtual ~SetVariableStm();

		virtual String getName() const override;
		virtual Result execute(Context* context) override;

	private:
		String variable;
		VExpression* valueExpr;
	};

	class IMQ_API SetFieldStm : public VStatement
	{
	public:
		SetFieldStm(VExpression* objExpr, const String& field, VExpression* valueExpr, const VLocation& loc);
		virtual ~SetFieldStm();

		virtual String getName() const override;
		virtual Result execute(Context* context) override;

	private:
		String field;
		VExpression* objExpr;
		VExpression* valueExpr;
	};

	class IMQ_API SetIndexStm : public VStatement
	{
	public:
		SetIndexStm(VExpression* objExpr, VExpression* indexExpr, VExpression* valueExpr, const VLocation& loc);
		virtual ~SetIndexStm();

		virtual String getName() const override;
		virtual Result execute(Context* context) override;

	private:
		VExpression* indexExpr;
		VExpression* objExpr;
		VExpression* valueExpr;
	};

	class IMQ_API DeleteVariableStm : public VStatement
	{
	public:
		DeleteVariableStm(const String& variable, const VLocation& loc);
		virtual ~DeleteVariableStm();

		virtual String getName() const override;
		virtual Result execute(Context* context) override;

	private:
		String variable;
	};

	class IMQ_API SelectStm : public VStatement
	{
	public:
		SelectStm(VExpression* destExpr, VExpression* srcExpr, VExpression* calcExpr, VExpression* whereExpr, VExpression* elseExpr, int32_t coordCount, VExpression** coordsExpr, const VLocation& loc);
		virtual ~SelectStm();

		virtual String getName() const override;
		virtual Result execute(Context* context) override;

	private:
		VExpression* destExpr;
		VExpression* srcExpr;
		VExpression* calcExpr;
		VExpression* whereExpr;
		VExpression* elseExpr;

		VExpression** coordsExpr;
		int32_t coordCount;
	};

	class IMQ_API DefineInputStm : public VStatement
	{
	public:
		DefineInputStm(const String& name, VExpression* valueExpr, const VLocation& loc);
		virtual ~DefineInputStm();

		virtual String getName() const override;
		virtual Result execute(Context* context) override;

	private:
		String name;
		VExpression* valueExpr;
	};

	class IMQ_API DefineOutputStm : public VStatement
	{
	public:
		DefineOutputStm(const String& name, VExpression* valueExpr, const VLocation& loc);
		virtual ~DefineOutputStm();

		virtual String getName() const override;
		virtual Result execute(Context* context) override;

	private:
		String name;
		VExpression* valueExpr;
	};

	class IMQ_API BranchStm : public VStatement
	{
	public:
		BranchStm(VExpression* checkExpr, VStatement* trueStm, VStatement* falseStm, const VLocation& loc);
		virtual ~BranchStm();

		virtual String getName() const override;
		virtual Result execute(Context* context) override;

	private:
		VExpression* checkExpr;
		VStatement* trueStm;
		VStatement* falseStm;
	};

	class IMQ_API ForLoopStm : public VStatement
	{
	public:
		ForLoopStm(VStatement* initStm, VExpression* checkExpr, VStatement* incrStm, VStatement* execStm, const VLocation& loc);
		virtual ~ForLoopStm();

		virtual String getName() const override;
		virtual Result execute(Context* context) override;

	private:
		VStatement* initStm;
		VExpression* checkExpr;
		VStatement* incrStm;
		VStatement* execStm;
	};

	class IMQ_API WhileLoopStm : public VStatement
	{
	public:
		WhileLoopStm(VExpression* checkExpr, VStatement* execStm, const VLocation& loc);
		virtual ~WhileLoopStm();

		virtual String getName() const override;
		virtual Result execute(Context* context) override;

	private:
		VExpression* checkExpr;
		VStatement* execStm;
	};

	class IMQ_API InfiniteLoopStm : public VStatement
	{
	public:
		InfiniteLoopStm(VStatement* execStm, const VLocation& loc);
		virtual ~InfiniteLoopStm();

		virtual String getName() const override;
		virtual Result execute(Context* context) override;
		
	private:
		VStatement* execStm;
	};

	class IMQ_API ForEachStm : public VStatement
	{
	public:
		ForEachStm(const String& varName, VExpression* iterExpr, VStatement* execStm, const VLocation& loc);
		virtual ~ForEachStm();

		virtual String getName() const override;
		virtual Result execute(Context* context) override;

	private:
		String varName;
		VExpression* iterExpr;
		VStatement* execStm;
	};

	class IMQ_API BreakStm : public VStatement
	{
	public:
		BreakStm(const VLocation& loc);
		virtual ~BreakStm();

		virtual String getName() const override;
		virtual Result execute(Context* context) override;
	};

	class IMQ_API ReturnStm : public VStatement
	{
	public:
		ReturnStm(VExpression* valueExpr, const VLocation& loc);
		virtual ~ReturnStm();

		virtual String getName() const override;
		virtual Result execute(Context* context) override;

	private:
		VExpression* valueExpr;
	};

	class IMQ_API NoOpStm : public VStatement
	{
	public:
		NoOpStm(const VLocation& loc);
		virtual ~NoOpStm();

		virtual String getName() const override;
		virtual Result execute(Context* context) override;
	};

	class IMQ_API TernaryExpr : public VExpression
	{
	public:
		TernaryExpr(VExpression* checkExpr, VExpression* trueExpr, VExpression* falseExpr, const VLocation& loc);
		virtual ~TernaryExpr();

		virtual String getName() const override;
		virtual Result execute(Context* context, QValue* result) override;

	private:
		VExpression* checkExpr;
		VExpression* trueExpr;
		VExpression* falseExpr;
	};

	class IMQ_API ExportStm : public VStatement
	{
	public:
		ExportStm(const String& key, VExpression* exportExpr, const VLocation& loc);
		virtual ~ExportStm();

		virtual String getName() const override;
		virtual Result execute(Context* context) override;

	private:
		String key;
		VExpression* exportExpr;
	};

	struct ImportInputPair
	{
		ImportInputPair(String inputName, VExpression* expression)
			: inputName(inputName), expression(expression)
		{
		}

		String inputName;
		VExpression* expression;
	};

	struct ImportOutputPair
	{
		ImportOutputPair(String outputName, String variableName)
			: outputName(outputName), variableName(variableName)
		{
		}

		String outputName;
		String variableName;
	};

	class IMQ_API ImportStm : public VStatement
	{
	public:
		ImportStm(const String& path, bool forceImport, const std::vector<ImportInputPair>& inputs, const std::vector<ImportOutputPair>& outputs, const VLocation& loc);
		virtual ~ImportStm();

		virtual String getName() const override;
		virtual Result execute(Context* context) override;

	private:
		String path;
		bool bForceImport;

		std::vector<ImportInputPair> inputRewrites;
		std::vector<ImportOutputPair> outputRewrites;
	};
}