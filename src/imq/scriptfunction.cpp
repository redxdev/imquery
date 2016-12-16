#include "scriptfunction.h"

#include "errors.h"

namespace imq
{
	ScriptFunction::ScriptFunction(const String& funcName, ContextPtr outerCtx, const std::shared_ptr<VBlock> block, const std::vector<String>& argNames)
		: QFunction(outerCtx->getVM()), funcName(funcName), outerCtx(outerCtx), block(block), argNames(argNames)
	{
	}

	ScriptFunction::~ScriptFunction()
	{
	}

	Result ScriptFunction::execute(VMachine* vm, int32_t argCount, QValue* args, QValue* result)
	{
		if (argCount != argNames.size())
			return errors::args_count(funcName, argNames.size(), argCount);

		if (!block)
			return true;

		ContextPtr subContext(new SubContext(vm, outerCtx));
		subContext->setReturnable(true);
		ScopedRoot ctxRoot(vm->getGC(), subContext);

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

	void ScriptFunction::GC_markChildren()
	{
		outerCtx->GC_mark();
	}

	DefineFunctionExpr::DefineFunctionExpr(const String& funcName, VBlock* block, const std::vector<String>& argNames, const VLocation& loc)
		: VExpression(loc), funcName(funcName), initialBlock(block), argNames(argNames)
	{
	}

	DefineFunctionExpr::DefineFunctionExpr(VBlock* block, const std::vector<String>& argNames, const VLocation& loc)
		: DefineFunctionExpr("<anon>", block, argNames, loc)
	{
	}

	DefineFunctionExpr::~DefineFunctionExpr()
	{
		if (!getErrorState())
		{
			if (initialBlock)
				delete initialBlock;
		}
	}

	String DefineFunctionExpr::getName() const
	{
		return "DefineFunction";
	}

	Result DefineFunctionExpr::execute(ContextPtr context, QValue* result)
	{
		if (initialBlock)
		{
			block = std::shared_ptr<VBlock>(initialBlock);
			initialBlock = nullptr;
		}

		*result = QValue::Function(new ScriptFunction(funcName, context, block, argNames));
		return true;
	}
}