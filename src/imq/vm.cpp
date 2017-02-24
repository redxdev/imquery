#include "vm.h"

#include <sstream>
#include <iostream>

#include "errors.h"
#include "thirdparty/filesystem/path.h"
#include "thirdparty/filesystem/resolver.h"

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

	Result VExpressionAsStatement::execute(Context* context)
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

	Result VBlock::execute(Context* context)
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

					// We need to hold lastResult as a root so it doesn't get cleaned up before we return it.
					ScopedRoot resultRoot(context->getVM()->getGC(), lastResult);

					context->getVM()->getGC()->collect();

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
		setWorkingDirectory(".");
		gc = new GarbageCollector();
		rootContext = new RootContext(this);
		gc->addRoot(rootContext);
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

	bool VMachine::setWorkingDirectory(const String& newDir)
	{
		try
		{
			filesystem::path path = filesystem::path(newDir).make_absolute();
			if (!path.is_directory())
				return false;

			workingDirectory = path.str();
			return true;
		}
		catch (std::exception&)
		{
			return false;
		}
	}

	const String& VMachine::getWorkingDirectory() const
	{
		return workingDirectory;
	}

	void VMachine::addSearchPath(const String& path)
	{
		searchPaths.push_back(path);
	}

	String VMachine::buildPath(const String& path, bool useSearchPaths) const
	{
		try
		{
			filesystem::path newPath(path);

			if (newPath.is_absolute())
				return newPath.str();
			else if (useSearchPaths)
			{
				filesystem::resolver resolver;
				resolver.append(filesystem::path(workingDirectory));

				for (auto searchPath : searchPaths)
				{
					resolver.append(filesystem::path(searchPath));
				}

				return resolver.resolve(newPath).str();
			}
			else
			{
				filesystem::path workingPath(workingDirectory);
				return (workingPath / newPath).str();
			}
		}
		catch (std::exception&)
		{
			return path; // uh oh
		}
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