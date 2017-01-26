#pragma once

#include "platform.h"
#include "value.h"
#include "vm.h"
#include "result.h"

#include <memory>
#include <vector>

namespace imq
{
	class IMQ_API ScriptFunction : public QFunction
	{
	public:
		ScriptFunction(const String& funcName, Context* outerCtx, const std::shared_ptr<VBlock> block, const std::vector<String>& argNames);
		virtual ~ScriptFunction();

		virtual Result execute(VMachine* vm, int32_t argCount, QValue* args, QValue* result) override;

		virtual size_t GC_getSize() const override;
		virtual bool GC_isDynamic() const override { return false; }

	protected:

		virtual void GC_markChildren() override;

	private:
		ScriptFunction(const ScriptFunction& other) = default;
		ScriptFunction& operator=(const ScriptFunction& other) = default;

		String funcName;
		Context* outerCtx;
		std::shared_ptr<VBlock> block;
		std::vector<String> argNames;
	};

	class IMQ_API DefineFunctionExpr : public VExpression
	{
	public:
		DefineFunctionExpr(const String& funcName, VBlock* block, const std::vector<String>& argNames, const VLocation& loc);
		DefineFunctionExpr(VBlock* block, const std::vector<String>& argNames, const VLocation& loc);
		virtual ~DefineFunctionExpr();

		virtual String getName() const override;
		virtual Result execute(Context* context, QValue* result) override;

	private:
		String funcName;
		VBlock* initialBlock;
		std::shared_ptr<VBlock> block;
		std::vector<String> argNames;
	};
}