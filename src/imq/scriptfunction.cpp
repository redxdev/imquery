#include "scriptfunction.h"

#include "errors.h"

namespace imq
{
	ScriptFunction::ScriptFunction(const String& funcName, ContextPtr outerCtx, const std::shared_ptr<VBlock> block, const std::vector<String>& argNames)
		: funcName(funcName), outerCtx(outerCtx), block(block), argNames(argNames)
	{
	}

	ScriptFunction::~ScriptFunction()
	{
	}

	Result ScriptFunction::execute(int32_t argCount, QValue* args, QValue* result)
	{
		if (argCount != argNames.size())
			return errors::args_count(funcName, argNames.size(), argCount);

		if (!block)
			return true;

		ContextPtr subContext(new SubContext(outerCtx));
		subContext->setReturnable(true);

		for (int32_t i = 0; i < argCount; ++i)
		{
			Result res = subContext->setValue(argNames[i], args[i]);
			if (!res)
				return res;
		}

		Result res = block->execute(subContext);
		if (!res)
			return res;

		QValue value;
		subContext->getReturnValue(&value);
		*result = value;

		return true;
	}

	ScriptFunctor::ScriptFunctor()
		: funcPtr(nullptr)
	{
	}

	ScriptFunctor::ScriptFunctor(const std::shared_ptr<ScriptFunction> funcPtr)
		: funcPtr(funcPtr)
	{
	}

	ScriptFunctor::ScriptFunctor(const ScriptFunctor& other)
	{
		funcPtr = other.funcPtr;
	}

	ScriptFunctor::~ScriptFunctor()
	{
	}

	ScriptFunctor& ScriptFunctor::operator=(const ScriptFunctor& other)
	{
		funcPtr = other.funcPtr;
		return *this;
	}

	Result ScriptFunctor::operator()(int32_t argCount, QValue* args, QValue* result)
	{
		if (!funcPtr)
			return errors::func_generic_error("ScriptFunctor::funcPtr == nullptr");

		return funcPtr->execute(argCount, args, result);
	}

	const std::shared_ptr<ScriptFunction>& ScriptFunctor::getFunctionPointer() const
	{
		return funcPtr;
	}

	DefineFunctionExpr::DefineFunctionExpr(const String& funcName, VBlock* block, const std::vector<String>& argNames, const VLocation& loc)
		: VExpression(loc), funcName(funcName), block(block), argNames(argNames)
	{
	}

	DefineFunctionExpr::DefineFunctionExpr(VBlock* block, const std::vector<String>& argNames, const VLocation& loc)
		: DefineFunctionExpr("<anon>", block, argNames, loc)
	{
	}

	DefineFunctionExpr::~DefineFunctionExpr()
	{
	}

	String DefineFunctionExpr::getName() const
	{
		return "DefineFunction";
	}

	Result DefineFunctionExpr::execute(ContextPtr context, QValue* result)
	{
		std::shared_ptr<ScriptFunction> func(new ScriptFunction(funcName, context, block, argNames));
		*result = QValue::Function(ScriptFunctor(func));
		return true;
	}
}