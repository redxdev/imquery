#include "vm.h"

#include <sstream>

#include "errors.h"

namespace imq
{
	VNode::VNode(const VLocation& loc)
		: location(loc)
	{
	}

	VNode::~VNode()
	{
	}

	const VLocation& VNode::getLocation() const
	{
		return location;
	}

	VStatement::VStatement(const VLocation& loc)
		: VNode(loc)
	{
	}

	VStatement::~VStatement()
	{
	}

	VExpression::VExpression(const VLocation& loc)
		: VNode(loc)
	{
	}

	VExpression::~VExpression()
	{
	}

	VExpressionAsStatement::VExpressionAsStatement(VExpression* expression, const VLocation& loc)
		: expression(expression), VStatement(loc)
	{
	}

	VExpressionAsStatement::~VExpressionAsStatement()
	{
		delete expression;
	}

	VExpression* VExpressionAsStatement::getExpression() const
	{
		return expression;
	}

	String VExpressionAsStatement::getName() const
	{
		std::stringstream ss;
		ss << "STM:" << expression->getName();
		return ss.str();
	}

	Result VExpressionAsStatement::execute(ContextPtr context)
	{
		QValue exprValue;
		return expression->execute(context, &exprValue);
	}

	VBlock::VBlock(int32_t count, VStatement** statements, const VLocation loc)
		: VStatement(loc), count(count), statements(statements), lastResult(nullptr)
	{
	}

	VBlock::~VBlock()
	{
		for (int32_t i = 0; i < count; ++i)
		{
			delete statements[i];
		}

		delete statements;
	}

	String VBlock::getName() const
	{
		return "Block";
	}

	Result VBlock::execute(ContextPtr context)
	{
		if (count < 0)
			return errors::vm_generic_error(getLocation(), "Invalid statement block - count < 0");

		for (int32_t i = 0; i < count; ++i)
		{
			if (context->isContextBroken() || context->isContextReturnedFrom())
				break;

			if (!statements[i])
				continue;

			if (i == count - 1 && lastResult)
			{
				VExpressionAsStatement* exprStm = dynamic_cast<VExpressionAsStatement*>(statements[i]);
				if (exprStm)
				{
					Result res = exprStm->getExpression()->execute(context, lastResult);
					if (!res)
						return res;

					return true;
				}
			}

			Result res = statements[i]->execute(context);
			if (!res)
				return res;
		}

		return true;
	}

	int32_t VBlock::getCount() const
	{
		return count;
	}

	VStatement** VBlock::getStatements() const
	{
		return statements;
	}

	void VBlock::setEmitLastResult(QValue* loc)
	{
		lastResult = loc;
	}

	VMachine::VMachine()
	{
		rootContext = std::shared_ptr<RootContext>(new RootContext());
	}

	VMachine::~VMachine()
	{
		// TODO: is this unsafe?
		delete rootContext.get();
	}

	std::shared_ptr<RootContext> VMachine::getRootContext() const
	{
		return rootContext;
	}

	Result VMachine::execute(VBlock* block)
	{
		if (!block)
			return errors::vm_invalid_block();

		return block->execute(rootContext);
	}
}