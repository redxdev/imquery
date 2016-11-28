#pragma once

#include "platform.h"
#include "context.h"
#include "value.h"
#include "result.h"

#include <ostream>

namespace imq
{
	struct VLocation
	{
		int32_t line;
		int32_t col;
	};

	std::ostream& operator<<(std::ostream& os, const VLocation& loc);

	class VNode
	{
	public:
		VNode(const VLocation& loc);
		virtual ~VNode();

		const VLocation& getLocation() const;

		virtual String getName() const = 0;

	private:
		VLocation location;
	};

	class VStatement : public VNode
	{
	public:
		VStatement(const VLocation& loc);
		virtual ~VStatement();

		virtual Result execute(ContextPtr context) = 0;
	};

	class VExpression : public VNode
	{
	public:
		VExpression(const VLocation& loc);
		virtual ~VExpression();

		virtual Result execute(ContextPtr context, QValue* result) = 0;
	};

	class VExpressionAsStatement : public VStatement
	{
	public:
		VExpressionAsStatement(VExpression* expression, const VLocation& loc);
		virtual ~VExpressionAsStatement();

		VExpression* getExpression() const;

		virtual String getName() const override;
		virtual Result execute(ContextPtr context) override;

	private:
		VExpression* expression;
	};
}