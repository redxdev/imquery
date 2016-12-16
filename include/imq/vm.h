#pragma once

#include "platform.h"
#include "context.h"
#include "value.h"
#include "result.h"
#include "utility.h"
#include "gc.h"

#include <ostream>

namespace imq
{
	class VNode
	{
	public:
		VNode(const VLocation& loc);
		virtual ~VNode();

		const VLocation& getLocation() const;

		virtual String getName() const = 0;

		// Error state is set to true when there was an issue constructing the VNode tree.
		// When the destructor for a VNode is called and the error state is set, a node should
		// NOT delete any subnodes it contains (they will be cleaned up elsewhere).
		bool getErrorState() const;
		void setErrorState(bool bNewState);

	private:
		VLocation location;
		bool bErrorState = false;
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

	class VBlock : public VStatement
	{
	public:
		VBlock(int32_t count, VStatement** statements, const VLocation loc);
		virtual ~VBlock();

		virtual String getName() const override;
		virtual Result execute(ContextPtr context) override;

		int32_t getCount() const;
		VStatement** getStatements() const;

		void setEmitLastResult(QValue* loc);

	private:
		int32_t count;
		VStatement** statements;
		QValue* lastResult;
	};

	class VMachine
	{
	public:
		VMachine();
		~VMachine();

		RootContext* getRootContext() const;

		Result execute(VBlock* block);

		GarbageCollector* getGC();

	private:
		RootContext* rootContext;
		GarbageCollector* gc;
	};
}