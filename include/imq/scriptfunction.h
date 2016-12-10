#pragma once

#include "platform.h"
#include "value.h"
#include "vm.h"
#include "result.h"

#include <memory>
#include <vector>

namespace imq
{
	class ScriptFunction
	{
	public:
		ScriptFunction(const String& funcName, ContextPtr outerCtx, const std::shared_ptr<VBlock> block, const std::vector<String>& argNames);
		~ScriptFunction();

		Result execute(int32_t argCount, QValue* args, QValue* result);

	private:
		ScriptFunction(const ScriptFunction& other) = default;
		ScriptFunction& operator=(const ScriptFunction& other) = default;

		String funcName;
		ContextPtr outerCtx;
		std::shared_ptr<VBlock> block;
		std::vector<String> argNames;
	};

	class ScriptFunctor
	{
	public:
		ScriptFunctor();
		ScriptFunctor(const std::shared_ptr<ScriptFunction> funcPtr);
		ScriptFunctor(const ScriptFunctor& other);
		~ScriptFunctor();

		ScriptFunctor& operator=(const ScriptFunctor& other);

		Result operator()(int32_t argCount, QValue* args, QValue* result);

		const std::shared_ptr<ScriptFunction>& getFunctionPointer() const;

	private:
		std::shared_ptr<ScriptFunction> funcPtr;
	};

	class DefineFunctionExpr : public VExpression
	{
	public:
		DefineFunctionExpr(const String& funcName, VBlock* block, const std::vector<String>& argNames, const VLocation& loc);
		DefineFunctionExpr(VBlock* block, const std::vector<String>& argNames, const VLocation& loc);
		virtual ~DefineFunctionExpr();

		virtual String getName() const override;
		virtual Result execute(ContextPtr context, QValue* result) override;

	private:
		String funcName;
		std::shared_ptr<VBlock> block;
		std::vector<String> argNames;
	};
}