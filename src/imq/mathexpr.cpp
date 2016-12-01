#include "mathexpr.h"

#include "errors.h"

namespace imq
{
	AddExpr::AddExpr(VExpression* lhs, VExpression* rhs, const VLocation& loc)
		: VExpression(loc), lhs(lhs), rhs(rhs)
	{
	}

	AddExpr::~AddExpr()
	{
		delete lhs;
		delete rhs;
	}

	String AddExpr::getName() const
	{
		return "Add";
	}

	Result AddExpr::execute(ContextPtr context, QValue* result)
	{
		if (!lhs)
		{
			return errors::vm_generic_error(getLocation(), "Invalid left-hand subexpression for Add");
		}

		if (!rhs)
		{
			return errors::vm_generic_error(getLocation(), "Invalid right-hand subexpression for Add");
		}

		QValue lvalue;
		QValue rvalue;

		Result res = lhs->execute(context, &lvalue);
		if (!res)
		{
			return res;
		}

		res = rhs->execute(context, &rvalue);
		if (!res)
		{
			return res;
		}

		// TODO: Add stuff
	}
}