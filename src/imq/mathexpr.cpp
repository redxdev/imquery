#include "mathexpr.h"

#include "errors.h"

namespace imq
{
	TwoOperatorMathExpr::TwoOperatorMathExpr(VExpression* lhs, VExpression* rhs, const VLocation& loc)
		: VExpression(loc), lhsExpr(lhs), rhsExpr(rhs)
	{
	}

	TwoOperatorMathExpr::~TwoOperatorMathExpr()
	{
		if (!getErrorState())
		{
			delete lhsExpr;
			delete rhsExpr;
		}
	}

	Result TwoOperatorMathExpr::execute(Context* context, QValue* result)
	{
		if (!lhsExpr)
		{
			return errors::vm_generic_error(getLocation(), "Invalid left-hand subexpression for " + getName());
		}

		if (!rhsExpr)
		{
			return errors::vm_generic_error(getLocation(), "Invalid right-hand subexpression for " + getName());
		}

		QValue lhs;
		QValue rhs;

		Result res = lhsExpr->execute(context, &lhs);
		if (!res)
		{
			return res;
		}

		res = rhsExpr->execute(context, &rhs);
		if (!res)
		{
			return res;
		}

		return operate(lhs, rhs, result);
	}

	OneOperatorMathExpr::OneOperatorMathExpr(VExpression* expr, const VLocation& loc)
		: VExpression(loc), expr(expr)
	{
	}

	OneOperatorMathExpr::~OneOperatorMathExpr()
	{
		if (!getErrorState())
		{
			delete expr;
		}
	}

	Result OneOperatorMathExpr::execute(Context* context, QValue* result)
	{
		if (!expr)
		{
			return errors::vm_generic_error(getLocation(), "Invalid subexpression for " + getName());
		}

		QValue value;

		Result res = expr->execute(context, &value);
		if (!res)
		{
			return res;
		}

		return operate(value, result);
	}

	AddExpr::AddExpr(VExpression* lhs, VExpression* rhs, const VLocation& loc)
		: TwoOperatorMathExpr(lhs, rhs, loc)
	{
	}

	AddExpr::~AddExpr()
	{
	}

	String AddExpr::getName() const
	{
		return "Add";
	}

	Result AddExpr::operate(const QValue& lhs, const QValue& rhs, QValue* result)
	{
		Result res = lhs.opAdd(rhs, result);
		if (!res)
		{
			return errors::vm_generic_error(getLocation(), res.getErr());
		}

		return true;
	}

	SubExpr::SubExpr(VExpression* lhs, VExpression* rhs, const VLocation& loc)
		: TwoOperatorMathExpr(lhs, rhs, loc)
	{
	}

	SubExpr::~SubExpr()
	{
	}

	String SubExpr::getName() const
	{
		return "Sub";
	}

	Result SubExpr::operate(const QValue& lhs, const QValue& rhs, QValue* result)
	{
		Result res = lhs.opSub(rhs, result);
		if (!res)
		{
			return errors::vm_generic_error(getLocation(), res.getErr());
		}

		return true;
	}

	MulExpr::MulExpr(VExpression* lhs, VExpression* rhs, const VLocation& loc)
		: TwoOperatorMathExpr(lhs, rhs, loc)
	{
	}

	MulExpr::~MulExpr()
	{
	}

	String MulExpr::getName() const
	{
		return "Mul";
	}

	Result MulExpr::operate(const QValue& lhs, const QValue& rhs, QValue* result)
	{
		Result res = lhs.opMul(rhs, result);
		if (!res)
		{
			return errors::vm_generic_error(getLocation(), res.getErr());
		}

		return true;
	}

	DivExpr::DivExpr(VExpression* lhs, VExpression* rhs, const VLocation& loc)
		: TwoOperatorMathExpr(lhs, rhs, loc)
	{
	}

	DivExpr::~DivExpr()
	{
	}

	String DivExpr::getName() const
	{
		return "Div";
	}

	Result DivExpr::operate(const QValue& lhs, const QValue& rhs, QValue* result)
	{
		Result res = lhs.opDiv(rhs, result);
		if (!res)
		{
			return errors::vm_generic_error(getLocation(), res.getErr());
		}

		return true;
	}

	ModExpr::ModExpr(VExpression* lhs, VExpression* rhs, const VLocation& loc)
		: TwoOperatorMathExpr(lhs, rhs, loc)
	{
	}

	ModExpr::~ModExpr()
	{
	}

	String ModExpr::getName() const
	{
		return "Mod";
	}

	Result ModExpr::operate(const QValue& lhs, const QValue& rhs, QValue* result)
	{
		Result res = lhs.opMod(rhs, result);
		if (!res)
		{
			return errors::vm_generic_error(getLocation(), res.getErr());
		}

		return true;
	}

	AndExpr::AndExpr(VExpression* lhs, VExpression* rhs, const VLocation& loc)
		: TwoOperatorMathExpr(lhs, rhs, loc)
	{
	}

	AndExpr::~AndExpr()
	{
	}

	String AndExpr::getName() const
	{
		return "And";
	}

	Result AndExpr::operate(const QValue& lhs, const QValue& rhs, QValue* result)
	{
		Result res = lhs.opAnd(rhs, result);
		if (!res)
		{
			return errors::vm_generic_error(getLocation(), res.getErr());
		}

		return true;
	}

	OrExpr::OrExpr(VExpression* lhs, VExpression* rhs, const VLocation& loc)
		: TwoOperatorMathExpr(lhs, rhs, loc)
	{
	}

	OrExpr::~OrExpr()
	{
	}

	String OrExpr::getName() const
	{
		return "Or";
	}

	Result OrExpr::operate(const QValue& lhs, const QValue& rhs, QValue* result)
	{
		Result res = lhs.opOr(rhs, result);
		if (!res)
		{
			return errors::vm_generic_error(getLocation(), res.getErr());
		}

		return true;
	}

	NegateExpr::NegateExpr(VExpression* expr, const VLocation& loc)
		: OneOperatorMathExpr(expr, loc)
	{
	}

	NegateExpr::~NegateExpr()
	{
	}

	String NegateExpr::getName() const
	{
		return "Negate";
	}

	Result NegateExpr::operate(const QValue& value, QValue* result)
	{
		Result res = value.opNegate(result);
		if (!res)
		{
			return errors::vm_generic_error(getLocation(), res.getErr());
		}

		return true;
	}

	NotExpr::NotExpr(VExpression* expr, const VLocation& loc)
		: OneOperatorMathExpr(expr, loc)
	{
	}

	NotExpr::~NotExpr()
	{
	}

	String NotExpr::getName() const
	{
		return "Not";
	}

	Result NotExpr::operate(const QValue& value, QValue* result)
	{
		Result res = value.opNot(result);
		if (!res)
		{
			return errors::vm_generic_error(getLocation(), res.getErr());
		}

		return true;
	}

	EqualExpr::EqualExpr(VExpression* lhs, VExpression* rhs, const VLocation& loc)
		: TwoOperatorMathExpr(lhs, rhs, loc)
	{
	}

	EqualExpr::~EqualExpr()
	{
	}

	String EqualExpr::getName() const
	{
		return "Equal";
	}

	Result EqualExpr::operate(const QValue& lhs, const QValue& rhs, QValue* result)
	{
		*result = QValue::Bool(lhs == rhs);
		return true;
	}

	NotEqualExpr::NotEqualExpr(VExpression* lhs, VExpression* rhs, const VLocation& loc)
		: TwoOperatorMathExpr(lhs, rhs, loc)
	{
	}

	NotEqualExpr::~NotEqualExpr()
	{
	}

	String NotEqualExpr::getName() const
	{
		return "NotEqual";
	}

	Result NotEqualExpr::operate(const QValue& lhs, const QValue& rhs, QValue* result)
	{
		*result = QValue::Bool(lhs != rhs);
		return true;
	}

	LessExpr::LessExpr(VExpression* lhs, VExpression* rhs, const VLocation& loc)
		: TwoOperatorMathExpr(lhs, rhs, loc)
	{
	}

	LessExpr::~LessExpr()
	{
	}

	String LessExpr::getName() const
	{
		return "Less";
	}

	Result LessExpr::operate(const QValue& lhs, const QValue& rhs, QValue* result)
	{
		Result res = lhs.opLess(rhs, result);
		if (!res)
		{
			return errors::vm_generic_error(getLocation(), res.getErr());
		}

		return true;
	}

	LessEqExpr::LessEqExpr(VExpression* lhs, VExpression* rhs, const VLocation& loc)
		: TwoOperatorMathExpr(lhs, rhs, loc)
	{
	}

	LessEqExpr::~LessEqExpr()
	{
	}

	String LessEqExpr::getName() const
	{
		return "LessEq";
	}

	Result LessEqExpr::operate(const QValue& lhs, const QValue& rhs, QValue* result)
	{
		Result res = lhs.opLessEq(rhs, result);
		if (!res)
		{
			return errors::vm_generic_error(getLocation(), res.getErr());
		}

		return true;
	}

	GreaterExpr::GreaterExpr(VExpression* lhs, VExpression* rhs, const VLocation& loc)
		: TwoOperatorMathExpr(lhs, rhs, loc)
	{
	}

	GreaterExpr::~GreaterExpr()
	{
	}

	String GreaterExpr::getName() const
	{
		return "Greater";
	}

	Result GreaterExpr::operate(const QValue& lhs, const QValue& rhs, QValue* result)
	{
		Result res = lhs.opGreater(rhs, result);
		if (!res)
		{
			return errors::vm_generic_error(getLocation(), res.getErr());
		}

		return true;
	}

	GreaterEqExpr::GreaterEqExpr(VExpression* lhs, VExpression* rhs, const VLocation& loc)
		: TwoOperatorMathExpr(lhs, rhs, loc)
	{
	}

	GreaterEqExpr::~GreaterEqExpr()
	{
	}

	String GreaterEqExpr::getName() const
	{
		return "GreaterEq";
	}

	Result GreaterEqExpr::operate(const QValue& lhs, const QValue& rhs, QValue* result)
	{
		Result res = lhs.opGreaterEq(rhs, result);
		if (!res)
		{
			return errors::vm_generic_error(getLocation(), res.getErr());
		}

		return true;
	}
}