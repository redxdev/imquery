#pragma once

#include "platform.h"
#include "vm.h"

namespace imq
{
	class IMQ_API TwoOperatorMathExpr : public VExpression
	{
	public:
		TwoOperatorMathExpr(VExpression* lhs, VExpression* rhs, const VLocation& loc);
		virtual ~TwoOperatorMathExpr();

		virtual Result execute(Context* context, QValue* result) override;
		virtual Result operate(const QValue& lhs, const QValue& rhs, QValue* result) = 0;

	private:
		VExpression* lhsExpr;
		VExpression* rhsExpr;
	};

	class IMQ_API OneOperatorMathExpr : public VExpression
	{
	public:
		OneOperatorMathExpr(VExpression* expr, const VLocation& loc);
		virtual ~OneOperatorMathExpr();

		virtual Result execute(Context* context, QValue* result) override;
		virtual Result operate(const QValue& value, QValue* result) = 0;

	private:
		VExpression* expr;
	};

	class IMQ_API AddExpr : public TwoOperatorMathExpr
	{
	public:
		AddExpr(VExpression* lhs, VExpression* rhs, const VLocation& loc);
		virtual ~AddExpr();

		virtual String getName() const override;
		virtual Result operate(const QValue& lhs, const QValue& rhs, QValue* result) override;
	};

	class IMQ_API SubExpr : public TwoOperatorMathExpr
	{
	public:
		SubExpr(VExpression* lhs, VExpression* rhs, const VLocation& loc);
		virtual ~SubExpr();

		virtual String getName() const override;
		virtual Result operate(const QValue& lhs, const QValue& rhs, QValue* result) override;
	};

	class IMQ_API MulExpr : public TwoOperatorMathExpr
	{
	public:
		MulExpr(VExpression* lhs, VExpression* rhs, const VLocation& loc);
		virtual ~MulExpr();

		virtual String getName() const override;
		virtual Result operate(const QValue& lhs, const QValue& rhs, QValue* result) override;
	};

	class IMQ_API DivExpr : public TwoOperatorMathExpr
	{
	public:
		DivExpr(VExpression* lhs, VExpression* rhs, const VLocation& loc);
		virtual ~DivExpr();

		virtual String getName() const override;
		virtual Result operate(const QValue& lhs, const QValue& rhs, QValue* result) override;
	};

	class IMQ_API ModExpr : public TwoOperatorMathExpr
	{
	public:
		ModExpr(VExpression* lhs, VExpression* rhs, const VLocation& loc);
		virtual ~ModExpr();

		virtual String getName() const override;
		virtual Result operate(const QValue& lhs, const QValue& rhs, QValue* result) override;
	};

	class IMQ_API AndExpr : public TwoOperatorMathExpr
	{
	public:
		AndExpr(VExpression* lhs, VExpression* rhs, const VLocation& loc);
		virtual ~AndExpr();

		virtual String getName() const override;
		virtual Result operate(const QValue& lhs, const QValue& rhs, QValue* result) override;
	};

	class IMQ_API OrExpr : public TwoOperatorMathExpr
	{
	public:
		OrExpr(VExpression* lhs, VExpression* rhs, const VLocation& loc);
		virtual ~OrExpr();

		virtual String getName() const override;
		virtual Result operate(const QValue& lhs, const QValue& rhs, QValue* result) override;
	};

	class IMQ_API NegateExpr : public OneOperatorMathExpr
	{
	public:
		NegateExpr(VExpression* expr, const VLocation& loc);
		virtual ~NegateExpr();

		virtual String getName() const override;
		virtual Result operate(const QValue& value, QValue* result) override;
	};

	class IMQ_API NotExpr : public OneOperatorMathExpr
	{
	public:
		NotExpr(VExpression* expr, const VLocation& loc);
		virtual ~NotExpr();

		virtual String getName() const override;
		virtual Result operate(const QValue& value, QValue* result) override;
	};

	class IMQ_API EqualExpr : public TwoOperatorMathExpr
	{
	public:
		EqualExpr(VExpression* lhs, VExpression* rhs, const VLocation& loc);
		virtual ~EqualExpr();

		virtual String getName() const;
		virtual Result operate(const QValue& lhs, const QValue& rhs, QValue* result) override;
	};

	class IMQ_API NotEqualExpr : public TwoOperatorMathExpr
	{
	public:
		NotEqualExpr(VExpression* lhs, VExpression* rhs, const VLocation& loc);
		virtual ~NotEqualExpr();

		virtual String getName() const;
		virtual Result operate(const QValue& lhs, const QValue& rhs, QValue* result) override;
	};

	class IMQ_API LessExpr : public TwoOperatorMathExpr
	{
	public:
		LessExpr(VExpression* lhs, VExpression* rhs, const VLocation& loc);
		virtual ~LessExpr();

		virtual String getName() const;
		virtual Result operate(const QValue& lhs, const QValue& rhs, QValue* result) override;
	};

	class IMQ_API LessEqExpr : public TwoOperatorMathExpr
	{
	public:
		LessEqExpr(VExpression* lhs, VExpression* rhs, const VLocation& loc);
		virtual ~LessEqExpr();

		virtual String getName() const;
		virtual Result operate(const QValue& lhs, const QValue& rhs, QValue* result) override;
	};

	class IMQ_API GreaterExpr : public TwoOperatorMathExpr
	{
	public:
		GreaterExpr(VExpression* lhs, VExpression* rhs, const VLocation& loc);
		virtual ~GreaterExpr();

		virtual String getName() const;
		virtual Result operate(const QValue& lhs, const QValue& rhs, QValue* result) override;
	};

	class IMQ_API GreaterEqExpr : public TwoOperatorMathExpr
	{
	public:
		GreaterEqExpr(VExpression* lhs, VExpression* rhs, const VLocation& loc);
		virtual ~GreaterEqExpr();

		virtual String getName() const;
		virtual Result operate(const QValue& lhs, const QValue& rhs, QValue* result) override;
	};
}