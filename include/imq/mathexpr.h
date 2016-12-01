#pragma once

#include "platform.h"
#include "vm.h"

namespace imq
{
	class AddExpr : public VExpression
	{
	public:
		AddExpr(VExpression* lhs, VExpression* rhs, const VLocation& loc);
		virtual ~AddExpr();

		virtual String getName() const override;
		virtual Result execute(ContextPtr context, QValue* result) override;

	private:
		VExpression* lhs;
		VExpression* rhs;
	};
}