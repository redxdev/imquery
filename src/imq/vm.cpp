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

	VMachine::VMachine()
	{
		rootContext = std::shared_ptr<RootContext>(new RootContext());
	}

	std::shared_ptr<RootContext> VMachine::getRootContext() const
	{
		return rootContext;
	}

	Result VMachine::execute(int32_t count, VStatement** statements)
	{
		if (count < 0)
			return errors::vm_invalid_statement_list();

		for (int32_t i = 0; i < count; ++i)
		{
			VStatement* stm = statements[i];
			if (stm != nullptr)
			{
				Result result = stm->execute(rootContext);
				if (!result)
				{
					return result;
				}
			}
		}

		return true;
	}
}