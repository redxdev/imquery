#pragma once

#include "platform.h"
#include "vm.h"

namespace imq
{
	class TwoOperatorMathExpr : public VExpression
	{
	public:
		TwoOperatorMathExpr(VExpression* lhs, VExpression* rhs, const VLocation& loc);
		virtual ~TwoOperatorMathExpr();

		virtual Result execute(ContextPtr context, QValue* result) override;
		virtual Result operate(const QValue& lhs, const QValue& rhs, QValue* result) = 0;

	private:
		VExpression* lhsExpr;
		VExpression* rhsExpr;
	};

	class OneOperatorMathExpr : public VExpression
	{
	public:
		OneOperatorMathExpr(VExpression* expr, const VLocation& loc);
		virtual ~OneOperatorMathExpr();

		virtual Result execute(ContextPtr context, QValue* result) override;
		virtual Result operate(const QValue& value, QValue* result) = 0;

	private:
		VExpression* expr;
	};

	class AddExpr : public TwoOperatorMathExpr
	{
	public:
		AddExpr(VExpression* lhs, VExpression* rhs, const VLocation& loc);
		virtual ~AddExpr();

		virtual String getName() const override;
		virtual Result operate(const QValue& lhs, const QValue& rhs, QValue* result) override;
	};

	class SubExpr : public TwoOperatorMathExpr
	{
	public:
		SubExpr(VExpression* lhs, VExpression* rhs, const VLocation& loc);
		virtual ~SubExpr();

		virtual String getName() const override;
		virtual Result operate(const QValue& lhs, const QValue& rhs, QValue* result) override;
	};

	class MulExpr : public TwoOperatorMathExpr
	{
	public:
		MulExpr(VExpression* lhs, VExpression* rhs, const VLocation& loc);
		virtual ~MulExpr();

		virtual String getName() const override;
		virtual Result operate(const QValue& lhs, const QValue& rhs, QValue* result) override;
	};

	class DivExpr : public TwoOperatorMathExpr
	{
	public:
		DivExpr(VExpression* lhs, VExpression* rhs, const VLocation& loc);
		virtual ~DivExpr();

		virtual String getName() const override;
		virtual Result operate(const QValue& lhs, const QValue& rhs, QValue* result) override;
	};

	class ModExpr : public TwoOperatorMathExpr
	{
	public:
		ModExpr(VExpression* lhs, VExpression* rhs, const VLocation& loc);
		virtual ~ModExpr();

		virtual String getName() const override;
		virtual Result operate(const QValue& lhs, const QValue& rhs, QValue* result) override;
	};

	class AndExpr : public TwoOperatorMathExpr
	{
	public:
		AndExpr(VExpression* lhs, VExpression* rhs, const VLocation& loc);
		virtual ~AndExpr();

		virtual String getName() const override;
		virtual Result operate(const QValue& lhs, const QValue& rhs, QValue* result) override;
	};

	class OrExpr : public TwoOperatorMathExpr
	{
	public:
		OrExpr(VExpression* lhs, VExpression* rhs, const VLocation& loc);
		virtual ~OrExpr();

		virtual String getName() const override;
		virtual Result operate(const QValue& lhs, const QValue& rhs, QValue* result) override;
	};

	class NegateExpr : public OneOperatorMathExpr
	{
	public:
		NegateExpr(VExpression* expr, const VLocation& loc);
		virtual ~NegateExpr();

		virtual String getName() const override;
		virtual Result operate(const QValue& value, QValue* result) override;
	};

	class NotExpr : public OneOperatorMathExpr
	{
	public:
		NotExpr(VExpression* expr, const VLocation& loc);
		virtual ~NotExpr();

		virtual String getName() const override;
		virtual Result operate(const QValue& value, QValue* result) override;
	};

	class EqualExpr : public TwoOperatorMathExpr
	{
	public:
		EqualExpr(VExpression* lhs, VExpression* rhs, const VLocation& loc);
		virtual ~EqualExpr();

		virtual String getName() const;
		virtual Result operate(const QValue& lhs, const QValue& rhs, QValue* result) override;
	};

	class LessExpr : public TwoOperatorMathExpr
	{
	public:
		LessExpr(VExpression* lhs, VExpression* rhs, const VLocation& loc);
		virtual ~LessExpr();

		virtual String getName() const;
		virtual Result operate(const QValue& lhs, const QValue& rhs, QValue* result) override;
	};

	class LessEqExpr : public TwoOperatorMathExpr
	{
	public:
		LessEqExpr(VExpression* lhs, VExpression* rhs, const VLocation& loc);
		virtual ~LessEqExpr();

		virtual String getName() const;
		virtual Result operate(const QValue& lhs, const QValue& rhs, QValue* result) override;
	};

	class GreaterExpr : public TwoOperatorMathExpr
	{
	public:
		GreaterExpr(VExpression* lhs, VExpression* rhs, const VLocation& loc);
		virtual ~GreaterExpr();

		virtual String getName() const;
		virtual Result operate(const QValue& lhs, const QValue& rhs, QValue* result) override;
	};

	class GreaterEqExpr : public TwoOperatorMathExpr
	{
	public:
		GreaterEqExpr(VExpression* lhs, VExpression* rhs, const VLocation& loc);
		virtual ~GreaterEqExpr();

		virtual String getName() const;
		virtual Result operate(const QValue& lhs, const QValue& rhs, QValue* result) override;
	};
}