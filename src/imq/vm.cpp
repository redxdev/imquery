#include "vm.h"

#include <sstream>
#include <iostream>

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

	bool VNode::getErrorState() const
	{
		return bErrorState;
	}

	void VNode::setErrorState(bool bNewState)
	{
		bErrorState = bNewState;
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
		if (!getErrorState())
		{
			delete expression;
		}
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
		if (!getErrorState())
		{
			for (int32_t i = 0; i < count; ++i)
			{
				delete statements[i];
			}
		}

		delete[] statements;
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

			context->getVM()->getGC()->collect();
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
		gc = new GarbageCollector();
		rootContext = new RootContext(this);
		gc->addRoot(rootContext);
		gc->manage(rootContext);
	}

	VMachine::~VMachine()
	{
		gc->removeRoot(rootContext);
		gc->collect(true);

		if (gc->getManagedCount() > 0)
		{
			std::cerr << "VM leak: " << gc->getManagedCount() << " gc managed objects remaining" << std::endl;
		}

		delete gc;
	}

	RootContext* VMachine::getRootContext() const
	{
		return rootContext;
	}

	Result VMachine::execute(VBlock* block)
	{
		if (!block)
			return errors::vm_invalid_block();

		return block->execute(rootContext);
	}

	GarbageCollector* VMachine::getGC()
	{
		return gc;
	}
}