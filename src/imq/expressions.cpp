#include "expressions.h"

#include "errors.h"

namespace imq
{
	ConstantExpr::ConstantExpr(const QValue& value, const VLocation& loc)
		: VExpression(loc), value(value)
	{

	}

	ConstantExpr::~ConstantExpr()
	{

	}

	String ConstantExpr::getName() const
	{
		return "Constant(" + value.toString() + ")";
	}

	Result ConstantExpr::execute(ContextPtr context, QValue* result)
	{
		*result = value;
		return true;
	}

	RetrieveVariableExpr::RetrieveVariableExpr(const String& variable, const VLocation& loc)
		: VExpression(loc), variable(variable)
	{

	}

	RetrieveVariableExpr::~RetrieveVariableExpr()
	{

	}

	String RetrieveVariableExpr::getName() const
	{
		return "Variable(" + variable + ")";
	}

	Result RetrieveVariableExpr::execute(ContextPtr context, QValue* result)
	{
		Result res = context->getValue(variable, result);
		if (!result)
		{
			return errors::vm_generic_error(getLocation(), res.getErr());
		}

		return true;
	}

	RetrieveFieldExpr::RetrieveFieldExpr(VExpression* objExpr, const String& field, const VLocation& loc)
		: VExpression(loc), objExpr(objExpr), field(field)
	{

	}

	RetrieveFieldExpr::~RetrieveFieldExpr()
	{
		delete objExpr;
	}


	String RetrieveFieldExpr::getName() const
	{
		return "Field(" + field + ")";
	}

	Result RetrieveFieldExpr::execute(ContextPtr context, QValue* result)
	{
		if (!objExpr)
		{
			return errors::vm_generic_error(getLocation(), "Invalid object subexpression for RetrieveField");
		}

		QValue value;
		Result res = objExpr->execute(context, &value);
		if (!res)
		{
			return res;
		}

		QObjectPtr obj;
		if (!value.getObject(&obj))
		{
			return errors::vm_generic_error(getLocation(), "Expected valid QObject subexpression for RetrieveField");
		}

		if (!obj)
		{
			return errors::vm_generic_error(getLocation(), "Expected valid QObject subexpression for RetrieveField (found null)");
		}

		res = obj->getField(field, result);
		if (!res)
		{
			return errors::vm_generic_error(getLocation(), res.getErr());
		}

		return true;
	}

	RetrieveIndexExpr::RetrieveIndexExpr(VExpression* objExpr, VExpression* indexExpr, const VLocation& loc)
		: VExpression(loc), objExpr(objExpr), indexExpr(indexExpr)
	{

	}

	RetrieveIndexExpr::~RetrieveIndexExpr()
	{
		delete objExpr;
		delete indexExpr;
	}

	String RetrieveIndexExpr::getName() const
	{
		return "Index";
	}

	Result RetrieveIndexExpr::execute(ContextPtr context, QValue* result)
	{
		if (!objExpr)
		{
			return errors::vm_generic_error(getLocation(), "Invalid object subexpression for RetrieveField");
		}

		if (!indexExpr)
		{
			return errors::vm_generic_error(getLocation(), "Invalid index subexpression for RetrieveIndex");
		}

		QValue value;
		Result res = objExpr->execute(context, &value);
		if (!res)
		{
			return res;
		}

		QObjectPtr obj;
		if (!value.getObject(&obj))
		{
			return errors::vm_generic_error(getLocation(), "Expected valid QObject subexpression for RetrieveIndex");
		}

		if (!obj)
		{
			return errors::vm_generic_error(getLocation(), "Expected valid QObject subexpression for RetrieveIndex (found null)");
		}

		res = indexExpr->execute(context, &value);
		if (!res)
		{
			return res;
		}

		res = obj->getIndex(value, result);
		if (!res)
		{
			return errors::vm_generic_error(getLocation(), res.getErr());
		}

		return true;
	}

	CallFunctionExpr::CallFunctionExpr(VExpression* funcExpr, int32_t argC, VExpression** args, const VLocation& loc)
		: VExpression(loc), funcExpr(funcExpr), argCount(argC), args(args)
	{

	}

	CallFunctionExpr::~CallFunctionExpr()
	{
		delete funcExpr;
		for (int32_t i = 0; i < argCount; ++i)
		{
			delete args[i];
		}
	}

	String CallFunctionExpr::getName() const
	{
		return "Call";
	}

	Result CallFunctionExpr::execute(ContextPtr context, QValue* result)
	{
		if (!funcExpr)
		{
			return errors::vm_generic_error(getLocation(), "Invalid function subexpression for CallFunction");
		}

		QValue value;
		Result res = funcExpr->execute(context, &value);
		if (!res)
		{
			return res;
		}

		QFunction func;
		if (!value.getFunction(&func))
		{
			return errors::vm_generic_error(getLocation(), "Expected valid QFunction subexpression for RetrieveField");
		}

		QValue* argValues = new QValue[argCount];
		for (int32_t i = 0; i < argCount; ++i)
		{
			VExpression* expr = args[i];
			if (!expr)
			{
				return errors::vm_generic_error(getLocation(), "Invalid argument subexpression for CallFunction");
			}
		}

		return true;
	}
}