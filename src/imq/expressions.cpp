#include "expressions.h"

#include "object.h"
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
		if (!res)
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

		delete args;
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

			res = expr->execute(context, &argValues[i]);
			if (!res)
			{
				return res;
			}
		}

		res = func(argCount, argValues, result);
		if (!res)
		{
			return errors::vm_generic_error(getLocation(), res.getErr());
		}

		return true;
	}

	SetVariableStm::SetVariableStm(const String& variable, VExpression* valueExpr, const VLocation& loc)
		: VStatement(loc), variable(variable), valueExpr(valueExpr)
	{
	}

	SetVariableStm::~SetVariableStm()
	{
		delete valueExpr;
	}

	String SetVariableStm::getName() const
	{
		return "SetVariable(" + variable + ")";
	}

	Result SetVariableStm::execute(ContextPtr context)
	{
		if (!valueExpr)
		{
			return errors::vm_generic_error(getLocation(), "Invalid value subexpression for SetVariable");
		}

		QValue value;
		Result res = valueExpr->execute(context, &value);
		if (!res)
		{
			return res;
		}

		res = context->setValue(variable, value);
		if (!res)
		{
			return errors::vm_generic_error(getLocation(), res.getErr());
		}

		return true;
	}

	SetFieldStm::SetFieldStm(VExpression* objExpr, const String& field, VExpression* valueExpr, const VLocation& loc)
		: VStatement(loc), field(field), objExpr(objExpr), valueExpr(valueExpr)
	{
	}

	SetFieldStm::~SetFieldStm()
	{
		delete valueExpr;
		delete objExpr;
	}

	String SetFieldStm::getName() const
	{
		return "SetField(" + field + ")";
	}

	Result SetFieldStm::execute(ContextPtr context)
	{
		if (!objExpr)
		{
			return errors::vm_generic_error(getLocation(), "Invalid object subexpression for SetField");
		}

		if (!valueExpr)
		{
			return errors::vm_generic_error(getLocation(), "Invalid value subexpression for SetField");
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
			return errors::vm_generic_error(getLocation(), "Expected valid QObject subexpression for SetField");
		}

		if (!obj)
		{
			return errors::vm_generic_error(getLocation(), "Expected valid QObject subexpression for SetField (found null)");
		}

		res = valueExpr->execute(context, &value);
		if (!res)
		{
			return res;
		}

		res = obj->setField(field, value);
		if (!res)
		{
			return errors::vm_generic_error(getLocation(), res.getErr());
		}

		return true;
	}

	SetIndexStm::SetIndexStm(VExpression* objExpr, VExpression* indexExpr, VExpression* valueExpr, const VLocation& loc)
		: VStatement(loc), indexExpr(indexExpr), objExpr(objExpr), valueExpr(valueExpr)
	{
	}

	SetIndexStm::~SetIndexStm()
	{
		delete indexExpr;
		delete objExpr;
		delete valueExpr;
	}

	String SetIndexStm::getName() const
	{
		return "SetIndex";
	}

	Result SetIndexStm::execute(ContextPtr context)
	{
		if (!objExpr)
		{
			return errors::vm_generic_error(getLocation(), "Invalid object subexpression for SetIndex");
		}
		
		if (!indexExpr)
		{
			return errors::vm_generic_error(getLocation(), "Invalid index subexpression for SetIndex");
		}

		if (!valueExpr)
		{
			return errors::vm_generic_error(getLocation(), "Invalid value subexpression for SetIndex");
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
			return errors::vm_generic_error(getLocation(), "Expected valid QObject subexpression for SetIndex");
		}

		if (!obj)
		{
			return errors::vm_generic_error(getLocation(), "Expected valid QObject subexpression for SetIndex (found null)");
		}

		QValue index;
		res = indexExpr->execute(context, &index);
		if (!res)
		{
			return res;
		}

		res = valueExpr->execute(context, &value);
		if (!res)
		{
			return res;
		}

		res = obj->setIndex(index, value);
		if (!res)
		{
			return errors::vm_generic_error(getLocation(), res.getErr());
		}

		return true;
	}

	DeleteVariableStm::DeleteVariableStm(const String& variable, const VLocation& loc)
		: VStatement(loc), variable(variable)
	{
	}

	DeleteVariableStm::~DeleteVariableStm()
	{
	}

	String DeleteVariableStm::getName() const
	{
		return "Delete(" + variable + ")";
	}

	Result DeleteVariableStm::execute(ContextPtr context)
	{
		Result res = context->deleteValue(variable);
		if (!res)
		{
			return errors::vm_generic_error(getLocation(), res.getErr());
		}

		return true;
	}

	SelectStm::SelectStm(VExpression* destExpr, VExpression* srcExpr, VExpression* calcExpr, const VLocation& loc)
		: VStatement(loc), destExpr(destExpr), srcExpr(srcExpr), calcExpr(calcExpr)
	{
	}

	SelectStm::~SelectStm()
	{
		delete destExpr;
		delete srcExpr;
		delete calcExpr;
	}

	String SelectStm::getName() const
	{
		return "Select";
	}

	Result SelectStm::execute(ContextPtr context)
	{
		if (!srcExpr)
		{
			return errors::vm_generic_error(getLocation(), "Invalid source subexpression for Select");
		}

		if (!destExpr)
		{
			return errors::vm_generic_error(getLocation(), "Invalid destination subexpression for Select");
		}

		if (!calcExpr)
		{
			return errors::vm_generic_error(getLocation(), "Invalid calc subexpression for Select");
		}

		QValue sourceVal;
		Result res = srcExpr->execute(context, &sourceVal);
		if (!res)
		{
			return res;
		}

		QObjectPtr source;
		if (!sourceVal.getObject(&source))
		{
			return errors::vm_generic_error(getLocation(), "Source subexpression for Select must return a QObject");
		}

		QValue dest;
		res = destExpr->execute(context, &dest);
		if (!res)
		{
			return res;
		}

		QSelection* selection = nullptr;
		res = source->selection(context, dest, &selection);
		if (!res)
		{
			return errors::vm_generic_error(getLocation(), res.getErr());
		}

		if (!selection)
		{
			return errors::vm_generic_error(getLocation(), source->getTypeString() + " did not return a QSelection for Select, unable to continue.");
		}

		QValue value;
		while (selection->isValid())
		{
			res = calcExpr->execute(selection->getContext(), &value);
			if (!res)
			{
				return res;
			}

			res = selection->apply(value);
			if (!res)
			{
				delete selection;
				return errors::vm_generic_error(getLocation(), res.getErr());
			}

			selection->next();
		}

		delete selection;

		return true;
	}

	DefineInputStm::DefineInputStm(const String& name, VExpression* valueExpr, const VLocation& loc)
		: VStatement(loc), name(name), valueExpr(valueExpr)
	{
	}

	DefineInputStm::~DefineInputStm()
	{
		delete valueExpr;
	}

	String DefineInputStm::getName() const
	{
		return "Input";
	}

	Result DefineInputStm::execute(ContextPtr context)
	{
		QValue value;
		if (valueExpr)
		{
			Result res = valueExpr->execute(context, &value);
			if (!res)
			{
				return res;
			}
		}

		return context->registerInput(name, value);
	}

	DefineOutputStm::DefineOutputStm(const String& name, VExpression* valueExpr, const VLocation& loc)
		: VStatement(loc), name(name), valueExpr(valueExpr)
	{
	}

	DefineOutputStm::~DefineOutputStm()
	{
		delete valueExpr;
	}

	String DefineOutputStm::getName() const
	{
		return "Output";
	}

	Result DefineOutputStm::execute(ContextPtr context)
	{
		QValue value;
		if (valueExpr)
		{
			Result res = valueExpr->execute(context, &value);
			if (!res)
			{
				return res;
			}
		}

		return context->registerOutput(name, value);
	}
}