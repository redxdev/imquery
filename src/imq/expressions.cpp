#include "expressions.h"

#include "object.h"
#include "image.h"
#include "errors.h"
#include "structures.h"

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
		return "Constant(" + value.asString() + ")";
	}

	Result ConstantExpr::execute(Context* context, QValue* result)
	{
		*result = value;
		return true;
	}

	ColorExpr::ColorExpr(VExpression* rExpr, VExpression* gExpr, VExpression* bExpr, VExpression* aExpr, const VLocation& loc)
		: VExpression(loc), rExpr(rExpr), gExpr(gExpr), bExpr(bExpr), aExpr(aExpr)
	{
	}

	ColorExpr::~ColorExpr()
	{
		if (!getErrorState())
		{
			delete rExpr;
			delete gExpr;
			delete bExpr;
			delete aExpr;
		}
	}

	String ColorExpr::getName() const
	{
		return "Color";
	}

	Result ColorExpr::execute(Context* context, QValue* result)
	{
		Result res;
		QValue value;
		float red = 0.f;
		float green = 0.f;
		float blue = 0.f;
		float alpha = 1.f;

		bool r = false;
		bool g = false;
		bool b = false;
		bool a = false;

		if (rExpr)
		{
			res = rExpr->execute(context, &value);
			if (!res)
			{
				return res;
			}

			if (!value.toFloat(&value))
			{
				return errors::vm_generic_error(getLocation(), "Expected number for color components");
			}

			if (!value.getFloat(&red))
			{
				return errors::vm_generic_error(getLocation(), "Expected floats for color components");
			}

			r = true;
		}

		if (gExpr)
		{
			res = gExpr->execute(context, &value);
			if (!res)
			{
				return res;
			}

			if (!value.toFloat(&value))
			{
				return errors::vm_generic_error(getLocation(), "Expected number for color components");
			}

			if (!value.getFloat(&green))
			{
				return errors::vm_generic_error(getLocation(), "Expected floats for color components");
			}

			g = true;
		}

		if (bExpr)
		{
			res = bExpr->execute(context, &value);
			if (!res)
			{
				return res;
			}

			if (!value.toFloat(&value))
			{
				return errors::vm_generic_error(getLocation(), "Expected number for color components");
			}

			if (!value.getFloat(&blue))
			{
				return errors::vm_generic_error(getLocation(), "Expected floats for color components");
			}

			b = true;
		}

		if (aExpr)
		{
			res = aExpr->execute(context, &value);
			if (!res)
			{
				return res;
			}

			if (!value.toFloat(&value))
			{
				return errors::vm_generic_error(getLocation(), "Expected number for color components");
			}

			if (!value.getFloat(&alpha))
			{
				return errors::vm_generic_error(getLocation(), "Expected floats for color components");
			}

			a = true;
		}

		if (r && !g && !b)
		{
			green = red;
			blue = red;
		}

		*result = QValue::Object(new QColor(context->getVM(), red, green, blue, alpha));
		return true;
	}

	ListExpr::ListExpr(const std::vector<VExpression *> values, const VLocation& loc)
		: VExpression(loc), values(values)
	{
	}

	ListExpr::~ListExpr()
	{
		if (!getErrorState())
		{
			for (auto expr : values)
			{
				delete expr;
			}
		}
	}

	String ListExpr::getName() const
	{
		return "List";
	}

	Result ListExpr::execute(Context* context, QValue* result)
	{
		std::vector<QValue> results;
		for (auto expr : values)
		{
			if (!expr)
				return errors::vm_generic_error(getLocation(), "Invalid subexpression for List");

			QValue value;
			Result res = expr->execute(context, &value);
			if (!res)
				return res;

			results.push_back(value);
		}

		*result = QValue::Object(new QList(context->getVM(), results));
		return true;
	}

	TableExpr::TableExpr(const std::vector<std::tuple<VExpression *, VExpression *>> values, const VLocation& loc)
		: VExpression(loc), values(values)
	{
	}

	TableExpr::~TableExpr()
	{
		if (!getErrorState())
		{
			for (auto val : values)
			{
				delete std::get<0>(val);
				delete std::get<1>(val);
			}
		}
	}

	String TableExpr::getName() const
	{
		return "Table";
	}

	Result TableExpr::execute(Context* context, QValue* result)
	{
		std::unordered_map<QValue, QValue> results;
		for (auto val : values)
		{
			VExpression* keyExpr = std::get<0>(val);
			VExpression* valueExpr = std::get<1>(val);

			if (!keyExpr)
				return errors::vm_generic_error(getLocation(), "Invalid key subexpression for Table");

			if (!valueExpr)
				return errors::vm_generic_error(getLocation(), "Invalid value subexpression for Table");

			QValue key;
			QValue value;

			Result res = keyExpr->execute(context, &key);
			if (!res)
				return res;

			res = valueExpr->execute(context, &value);
			if (!res)
				return res;

			results.insert({ key, value });
		}

		*result = QValue::Object(new QTable(context->getVM(), results));
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

	Result RetrieveVariableExpr::execute(Context* context, QValue* result)
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
		if (!getErrorState())
		{
			delete objExpr;
		}
	}


	String RetrieveFieldExpr::getName() const
	{
		return "Field(" + field + ")";
	}

	Result RetrieveFieldExpr::execute(Context* context, QValue* result)
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

		QObject* obj;
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
		if (!getErrorState())
		{
			delete objExpr;
			delete indexExpr;
		}
	}

	String RetrieveIndexExpr::getName() const
	{
		return "Index";
	}

	Result RetrieveIndexExpr::execute(Context* context, QValue* result)
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

		QObject* obj;
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
		if (!getErrorState())
		{
			delete funcExpr;
			for (int32_t i = 0; i < argCount; ++i)
			{
				delete args[i];
			}
		}

		delete[] args;
	}

	String CallFunctionExpr::getName() const
	{
		return "Call";
	}

	Result CallFunctionExpr::execute(Context* context, QValue* result)
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

		QFunction* func;
		if (!value.getFunction(&func))
		{
			return errors::vm_generic_error(getLocation(), "Expected valid QFunction subexpression for RetrieveField");
		}

		QValue* argValues = nullptr;
		if (argCount > 0)
			argValues = new QValue[argCount];

		for (int32_t i = 0; i < argCount; ++i)
		{
			VExpression* expr = args[i];
			if (!expr)
			{
				delete[] argValues;
				return errors::vm_generic_error(getLocation(), "Invalid argument subexpression for CallFunction");
			}

			res = expr->execute(context, &argValues[i]);
			if (!res)
			{
				delete[] argValues;
				return res;
			}
		}

		res = func->execute(context->getVM(), argCount, argValues, result);
		delete[] argValues;
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
		if (!getErrorState())
		{
			delete valueExpr;
		}
	}

	String SetVariableStm::getName() const
	{
		return "SetVariable(" + variable + ")";
	}

	Result SetVariableStm::execute(Context* context)
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
		if (!getErrorState())
		{
			delete valueExpr;
			delete objExpr;
		}
	}

	String SetFieldStm::getName() const
	{
		return "SetField(" + field + ")";
	}

	Result SetFieldStm::execute(Context* context)
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

		QObject* obj;
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
		if (!getErrorState())
		{
			delete indexExpr;
			delete objExpr;
			delete valueExpr;
		}
	}

	String SetIndexStm::getName() const
	{
		return "SetIndex";
	}

	Result SetIndexStm::execute(Context* context)
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

		QObject* obj;
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

	Result DeleteVariableStm::execute(Context* context)
	{
		Result res = context->deleteValue(variable);
		if (!res)
		{
			return errors::vm_generic_error(getLocation(), res.getErr());
		}

		return true;
	}

	SelectStm::SelectStm(VExpression* destExpr, VExpression* srcExpr, VExpression* calcExpr, VExpression* whereExpr, VExpression* elseExpr, int32_t coordCount, VExpression** coordsExpr, const VLocation& loc)
		: VStatement(loc), destExpr(destExpr), srcExpr(srcExpr), calcExpr(calcExpr), whereExpr(whereExpr), elseExpr(elseExpr), coordCount(coordCount), coordsExpr(coordsExpr)
	{
	}

	SelectStm::~SelectStm()
	{
		if (!getErrorState())
		{
			delete destExpr;
			delete srcExpr;
			delete calcExpr;
			delete whereExpr;
			delete elseExpr;

			for (int32_t i = 0; i < coordCount; ++i)
			{
				delete coordsExpr[i];
			}
		}

		delete[] coordsExpr;
	}

	String SelectStm::getName() const
	{
		return "Select";
	}

	Result SelectStm::execute(Context* context)
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

		if (coordCount < 0)
		{
			return errors::vm_generic_error(getLocation(), "Invalid coordinate rewrite subexpressions for Select");
		}

		QValue sourceVal;
		Result res = srcExpr->execute(context, &sourceVal);
		if (!res)
		{
			return res;
		}

		QObject* source;
		if (!sourceVal.getObject(&source))
		{
			return errors::vm_generic_error(getLocation(), "Source subexpression for Select must return a QObject");
		}

		auto gc = context->getVM()->getGC();
		ScopedRoot sourceRoot(gc, source);

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
		while (selection->isValid() && !selection->getContext()->isContextBroken() && !selection->getContext()->isContextReturnedFrom())
		{
			bool bShouldExecute = true;
			if (whereExpr)
			{
				res = whereExpr->execute(selection->getContext(), &value);
				if (!res)
				{
					delete selection;
					return res;
				}

				if (!value.getBool(&bShouldExecute))
				{
					delete selection;
					return errors::vm_generic_error(getLocation(), "Selection \"where\" expression must return a Bool.");
				}
			}

			std::vector<QValue> coords;
			coords.reserve(coordCount);
			if (bShouldExecute || elseExpr)
			{
				for (int32_t i = 0; i < coordCount; ++i)
				{
					Result res = coordsExpr[i]->execute(selection->getContext(), &value);
					if (!res)
						return res;

					coords.push_back(value);
				}
			}

			if (bShouldExecute)
			{
				res = calcExpr->execute(selection->getContext(), &value);
				if (!res)
				{
					delete selection;
					return res;
				}

				res = selection->apply(value, coordCount, coords.data());
				if (!res)
				{
					delete selection;
					return errors::vm_generic_error(getLocation(), res.getErr());
				}
			}
			else if (elseExpr)
			{
				res = elseExpr->execute(selection->getContext(), &value);
				if (!res)
				{
					delete selection;
					return res;
				}

				res = selection->apply(value, coordCount, coords.data());
				if (!res)
				{
					delete selection;
					return errors::vm_generic_error(getLocation(), res.getErr());
				}
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
		if (!getErrorState())
		{
			delete valueExpr;
		}
	}

	String DefineInputStm::getName() const
	{
		return "Input";
	}

	Result DefineInputStm::execute(Context* context)
	{
		if (!valueExpr)
		{
			return errors::vm_generic_error(getLocation(), "Invalid value subexpression for DefineInput");
		}

		QValue value;
		Result res = valueExpr->execute(context, &value);
		if (!res)
		{
			return res;
		}

		res = context->registerInput(name, value);
		if (!res)
		{
			return errors::vm_generic_error(getLocation(), res.getErr());
		}

		return true;
	}

	DefineOutputStm::DefineOutputStm(const String& name, VExpression* valueExpr, const VLocation& loc)
		: VStatement(loc), name(name), valueExpr(valueExpr)
	{
	}

	DefineOutputStm::~DefineOutputStm()
	{
		if (!getErrorState())
		{
			delete valueExpr;
		}
	}

	String DefineOutputStm::getName() const
	{
		return "Output";
	}

	Result DefineOutputStm::execute(Context* context)
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

		Result res = context->registerOutput(name, value);
		if (!res)
		{
			return errors::vm_generic_error(getLocation(), res.getErr());
		}

		return true;
	}

	BranchStm::BranchStm(VExpression* checkExpr, VStatement* trueStm, VStatement* falseStm, const VLocation& loc)
		: VStatement(loc), checkExpr(checkExpr), trueStm(trueStm), falseStm(falseStm)
	{
	}

	BranchStm::~BranchStm()
	{
		if (!getErrorState())
		{
			delete checkExpr;
			delete trueStm;
			delete falseStm;
		}
	}

	String BranchStm::getName() const
	{
		return "Branch";
	}

	Result BranchStm::execute(Context* context)
	{
		if (!checkExpr)
			return errors::vm_generic_error(getLocation(), "Invalid check subexpression for Branch");

		Context* subContext(new SubContext(context->getVM(), context));
		auto gc = context->getVM()->getGC();
		gc->manage(subContext);
		ScopedRoot ctxRoot(gc, subContext);
		QValue value;
		Result res = checkExpr->execute(subContext, &value);

		bool result;
		if (!value.getBool(&result))
		{
			return errors::vm_generic_error(getLocation(), "Subexpression must return a boolean within a Branch");
		}

		if (result)
		{
			if (trueStm)
			{
				return trueStm->execute(subContext);
			}

			return true;
		}
		else
		{
			if (falseStm)
			{
				return falseStm->execute(subContext);
			}

			return true;
		}
	}

	ForLoopStm::ForLoopStm(VStatement* initStm, VExpression* checkExpr, VStatement* incrStm, VStatement* execStm, const VLocation& loc)
		: VStatement(loc), initStm(initStm), checkExpr(checkExpr), incrStm(incrStm), execStm(execStm)
	{
	}

	ForLoopStm::~ForLoopStm()
	{
		if (!getErrorState())
		{
			delete initStm;
			delete checkExpr;
			delete incrStm;
			delete execStm;
		}
	}

	String ForLoopStm::getName() const
	{
		return "For";
	}

	Result ForLoopStm::execute(Context* context)
	{
		if (!checkExpr)
		{
			return errors::vm_generic_error(getLocation(), "Invalid check subexpression for For");
		}

		Context* subContext(new SubContext(context->getVM(), context));
		subContext->setBreakable(true);
		auto gc = context->getVM()->getGC();
		gc->manage(subContext);
		ScopedRoot ctxRoot(gc, subContext);
		Result res;

		if (initStm)
		{
			res = initStm->execute(subContext);
			if (!res)
			{
				return res;
			}
		}

		QValue value;
		bool checkResult;

		res = checkExpr->execute(subContext, &value);
		if (!res)
		{
			return res;
		}

		if (!value.getBool(&checkResult))
		{
			return errors::vm_generic_error(getLocation(), "For loop check subexpression must return a boolean");
		}

		while (checkResult)
		{
			if (execStm)
			{
				res = execStm->execute(subContext);
				if (!res)
				{
					return res;
				}
			}

			if (subContext->isContextBroken() || subContext->isContextReturnedFrom())
				break;

			if (incrStm)
			{
				res = incrStm->execute(subContext);
				if (!res)
				{
					return res;
				}
			}

			res = checkExpr->execute(subContext, &value);
			if (!res)
			{
				return res;
			}

			if (!value.getBool(&checkResult))
			{
				return errors::vm_generic_error(getLocation(), "For loop check subexpression must return a boolean");
			}
		}

		return true;
	}

	WhileLoopStm::WhileLoopStm(VExpression* checkExpr, VStatement* execStm, const VLocation& loc)
		: VStatement(loc), checkExpr(checkExpr), execStm(execStm)
	{
	}

	WhileLoopStm::~WhileLoopStm()
	{
		if (!getErrorState())
		{
			delete checkExpr;
			delete execStm;
		}
	}

	String WhileLoopStm::getName() const
	{
		return "While";
	}

	Result WhileLoopStm::execute(Context* context)
	{
		if (!checkExpr)
		{
			return errors::vm_generic_error(getLocation(), "Invalid check subexpression for While");
		}

		Context* subContext(new SubContext(context->getVM(), context));
		subContext->setBreakable(true);
		auto gc = context->getVM()->getGC();
		gc->manage(subContext);
		ScopedRoot ctxRoot(gc, subContext);
		Result res;

		QValue value;
		bool checkResult;
		res = checkExpr->execute(subContext, &value);
		if (!res)
		{
			return res;
		}

		if (!value.getBool(&checkResult))
		{
			return errors::vm_generic_error(getLocation(), "While loop check subexpression must return a boolean");
		}

		while (checkResult)
		{
			if (execStm)
			{
				res = execStm->execute(subContext);
				if (!res)
				{
					return res;
				}
			}

			if (subContext->isContextBroken() || subContext->isContextReturnedFrom())
				break;

			res = checkExpr->execute(subContext, &value);
			if (!res)
			{
				return res;
			}

			if (!value.getBool(&checkResult))
			{
				return errors::vm_generic_error(getLocation(), "While loop check subexpression must return a boolean");
			}
		}

		return true;
	}

	InfiniteLoopStm::InfiniteLoopStm(VStatement* execStm, const VLocation& loc)
		: VStatement(loc), execStm(execStm)
	{
	}

	InfiniteLoopStm::~InfiniteLoopStm()
	{
		if (!getErrorState())
		{
			delete execStm;
		}
	}

	String InfiniteLoopStm::getName() const
	{
		return "Loop";
	}

	Result InfiniteLoopStm::execute(Context* context)
	{
		Context* subContext(new SubContext(context->getVM(), context));
		subContext->setBreakable(true);
		auto gc = context->getVM()->getGC();
		gc->manage(subContext);
		ScopedRoot ctxRoot(gc, subContext);
		Result res;

		while (true)
		{
			if (execStm)
			{
				res = execStm->execute(subContext);
				if (!res)
				{
					return res;
				}
			}

			if (subContext->isContextBroken() || subContext->isContextReturnedFrom())
				break;
		}

		return true;
	}

	ForEachStm::ForEachStm(const String& varName, VExpression* iterExpr, VStatement* execStm, const VLocation& loc)
		: VStatement(loc), varName(varName), iterExpr(iterExpr), execStm(execStm)
	{
	}

	ForEachStm::~ForEachStm()
	{
		if (!getErrorState())
		{
			delete iterExpr;
			delete execStm;
		}
	}

	String ForEachStm::getName() const
	{
		return "ForEach";
	}

	Result ForEachStm::execute(Context* context)
	{
		if (!iterExpr)
		{
			return errors::vm_generic_error(getLocation(), "Invalid iterator subexpression for ForEach");
		}

		Context* subContext(new SubContext(context->getVM(), context));
		subContext->setBreakable(true);
		auto gc = context->getVM()->getGC();
		gc->manage(subContext);
		ScopedRoot ctxRoot(gc, subContext);

		QValue value;
		Result res = iterExpr->execute(subContext, &value);
		if (!res)
			return res;

		QObject* obj;
		if (!value.getObject(&obj))
		{
			return errors::vm_generic_error(getLocation(), "Iterator expression must return an object");
		}

		ScopedRoot objRoot(gc, obj);

		QIterator* iter = nullptr;
		res = obj->iterate(subContext, &iter);
		if (!res)
			return errors::vm_generic_error(getLocation(), res.getErr());

		while (iter->isValid() && !subContext->isContextBroken() && !subContext->isContextReturnedFrom())
		{
			value = iter->getCurrentValue();
			res = subContext->setValue(varName, value);
			if (!res)
			{
				delete iter;
				return errors::vm_generic_error(getLocation(), res.getErr());
			}

			if (execStm)
			{
				res = execStm->execute(subContext);
				if (!res)
				{
					delete iter;
					return res;
				}
			}

			iter->next();
		}

		delete iter;
		return true;
	}

	BreakStm::BreakStm(const VLocation& loc)
		: VStatement(loc)
	{
	}

	BreakStm::~BreakStm()
	{
	}

	String BreakStm::getName() const
	{
		return "Break";
	}

	Result BreakStm::execute(Context* context)
	{
		Result res = context->breakContext();
		if (!res)
		{
			return errors::vm_generic_error(getLocation(), res.getErr());
		}

		return true;
	}

	ReturnStm::ReturnStm(VExpression* valueExpr, const VLocation& loc)
		: VStatement(loc), valueExpr(valueExpr)
	{
	}

	ReturnStm::~ReturnStm()
	{
		if (!getErrorState())
		{
			delete valueExpr;
		}
	}

	String ReturnStm::getName() const
	{
		return "Return";
	}

	Result ReturnStm::execute(Context* context)
	{
		QValue value;
		if (valueExpr)
		{
			Result res = valueExpr->execute(context, &value);
			if (!res)
				return res;
		}

		Result res = context->returnContext(value);
		if (!res)
		{
			return errors::vm_generic_error(getLocation(), res.getErr());
		}

		return true;
	}

	NoOpStm::NoOpStm(const VLocation& loc)
		: VStatement(loc)
	{
	}

	NoOpStm::~NoOpStm()
	{
	}

	String NoOpStm::getName() const
	{
		return "NoOp";
	}

	Result NoOpStm::execute(Context* context)
	{
		return true;
	}

	TernaryExpr::TernaryExpr(VExpression* checkExpr, VExpression* trueExpr, VExpression* falseExpr, const VLocation& loc)
		: VExpression(loc), checkExpr(checkExpr), trueExpr(trueExpr), falseExpr(falseExpr)
	{
	}

	TernaryExpr::~TernaryExpr()
	{
		if (!getErrorState())
		{
			delete checkExpr;
			delete trueExpr;
			delete falseExpr;
		}
	}

	String TernaryExpr::getName() const
	{
		return "Ternary";
	}

	Result TernaryExpr::execute(Context* context, QValue* result)
	{
		if (!checkExpr)
		{
			return errors::vm_generic_error(getLocation(), "Invalid check subexpression for Ternary");
		}

		if (!trueExpr)
		{
			return errors::vm_generic_error(getLocation(), "Invalid true subexpression for Ternary");
		}

		if (!falseExpr)
		{
			return errors::vm_generic_error(getLocation(), "Invalid false subexpression for Ternary");
		}

		QValue value;
		bool bCheckResult;

		Result res = checkExpr->execute(context, &value);
		if (!res)
		{
			return res;
		}

		if (!value.getBool(&bCheckResult))
		{
			return errors::vm_generic_error(getLocation(), "Check subexpression must return a Bool for Ternary");
		}

		VExpression* expr = bCheckResult ? trueExpr : falseExpr;
		res = expr->execute(context, result);
		if (!res)
		{
			return res;
		}

		return true;
	}
}