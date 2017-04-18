#include <imq/vm.h>
#include <imq/expressions.h>
#include <imq/mathexpr.h>
#include <imq/image.h>
#include <gtest/gtest.h>

using namespace imq;

TEST(VMachine, CallFunctionExpr)
{
	VMachine vm;

	bool functionCalled = false;
	QValue func = QValue::Function(&vm, [&](VMachine* vm, int32_t argCount, QValue* args, QValue* result) -> Result {
		if (argCount == 1)
		{
			*result = args[0];
		}
		else if (argCount == 2)
		{
			*result = QValue::Float(3.f);
		}
		else
		{
			*result = QValue::Integer(argCount);
		}

		functionCalled = true;

		return true;
	});

	CallFunctionExpr* expr = new CallFunctionExpr(new ConstantExpr(func, { 0, 0 }), 0, nullptr, { 0, 0 });
	QValue value;
	ASSERT_TRUE(expr->execute(vm.getRootContext(), &value));
	ASSERT_TRUE(functionCalled);
	ASSERT_EQ(value, QValue::Integer(0));

	functionCalled = false;
	delete expr;

	VExpression** args = new VExpression*[1]{ new ConstantExpr(QValue::Integer(321), {0,0}) };
	expr = new CallFunctionExpr(new ConstantExpr(func, { 0, 0 }), 1, args, { 0, 0 });
	ASSERT_TRUE(expr->execute(vm.getRootContext(), &value));
	ASSERT_TRUE(functionCalled);
	ASSERT_EQ(value, QValue::Integer(321));

	functionCalled = false;
	delete expr;

	args = new VExpression*[2]{ new ConstantExpr(QValue::Integer(321), {0,0}), new ConstantExpr(QValue::Integer(123), {0,0}) };
	expr = new CallFunctionExpr(new ConstantExpr(func, { 0,0 }), 2, args, { 0, 0 });
	ASSERT_TRUE(expr->execute(vm.getRootContext(), &value));
	ASSERT_TRUE(functionCalled);
	ASSERT_EQ(value, QValue::Float(3.f));

	delete expr;
}

TEST(VMachine, Variables)
{
	VMachine vm;
	QValue value;

	VExpression* expr = new RetrieveVariableExpr("foo", { 1, 2 });
	Result result = expr->execute(vm.getRootContext(), &value);
	ASSERT_FALSE(result);
	ASSERT_EQ(result.getErr(), "line 1:2: Unknown variable \"foo\"");

	VStatement* stm = new SetVariableStm("foo", new ConstantExpr(QValue::Integer(345), { 0, 0 }), { 0, 0 });
	ASSERT_TRUE(stm->execute(vm.getRootContext()));

	ASSERT_TRUE(expr->execute(vm.getRootContext(), &value));
	ASSERT_EQ(value, QValue::Integer(345));

	delete expr;
	delete stm;
}

TEST(VMachine, Fields)
{
	VMachine vm;
	QValue obj = QValue::Object(new QColor(&vm, 1.f, 0.3f, 0.4f, 1.f));
	QValue value;

	VExpression* expr = new RetrieveFieldExpr(new ConstantExpr(obj, { 0, 0 }), "foo", { 0, 0 });
	ASSERT_FALSE(expr->execute(vm.getRootContext(), &value));

	delete expr;
	expr = new RetrieveFieldExpr(new ConstantExpr(obj, { 0, 0 }), "g", { 0, 0 });
	ASSERT_TRUE(expr->execute(vm.getRootContext(), &value));
	ASSERT_EQ(value, QValue::Float(0.3f));

	VStatement* stm = new SetFieldStm(new ConstantExpr(obj, { 0, 0 }), "green", new ConstantExpr(QValue::Float(0.89f), { 0,0 }), { 0, 0 });
	ASSERT_FALSE(stm->execute(vm.getRootContext()));
	ASSERT_TRUE(expr->execute(vm.getRootContext(), &value));
	ASSERT_EQ(value, QValue::Float(0.3f));

	delete expr;
	delete stm;
}

TEST(VMachine, Indices)
{
	VMachine vm;
	QValue obj = QValue::Object(new QColor(&vm, 1.f, 0.3f, 0.4f, 1.f));
	QValue value;

	VExpression* expr = new RetrieveIndexExpr(new ConstantExpr(obj, { 0,0 }), new ConstantExpr(QValue::Integer(-1), { 0,0 }), { 0, 0 });
	ASSERT_FALSE(expr->execute(vm.getRootContext(), &value));

	delete expr;
	expr = new RetrieveIndexExpr(new ConstantExpr(obj, { 0,0 }), new ConstantExpr(QValue::Integer(2), { 0,0 }), { 0, 0 });
	ASSERT_TRUE(expr->execute(vm.getRootContext(), &value));
	ASSERT_EQ(value, QValue::Float(0.4f));

	VStatement* stm = new SetIndexStm(new ConstantExpr(obj, { 0, 0 }), new ConstantExpr(QValue::Integer(2), { 0,0 }), new ConstantExpr(QValue::Float(0.132f), { 0,0 }), { 0,0 });
	ASSERT_FALSE(stm->execute(vm.getRootContext()));
	ASSERT_TRUE(expr->execute(vm.getRootContext(), &value));
	ASSERT_EQ(value, QValue::Float(0.4f));

	delete expr;
	delete stm;
}

TEST(VMachine, Select)
{
	VMachine vm;

	QImage* imageA = new QImage(&vm, 100, 100, QColor(&vm, 1.f, 1.f, 1.f, 1.f));
	QImage* imageB = new QImage(&vm, 100, 100, QColor(&vm, 0.f, 0.f, 0.f, 0.f));

	VStatement* stm = new SelectStm(
		new ConstantExpr(QValue::Object(imageB), { 0, 0 }),
		new ConstantExpr(QValue::Object(imageA), { 0, 0 }),
		new RetrieveVariableExpr("color", { 0, 0 }),
		nullptr,
		nullptr,
		0,
		nullptr,
		{ 0, 0 }
	);
	ASSERT_TRUE(stm->execute(vm.getRootContext()));

	QColor color(&vm);
	for (int32_t y = 0; y < 100; ++y)
	{
		for (int32_t x = 0; x < 100; ++x)
		{
			ASSERT_TRUE(imageB->getPixel(x, y, &color));
			ASSERT_EQ(color, QColor(&vm, 1.f, 1.f, 1.f, 1.f));
		}
	}

	delete stm;
}

TEST(VMachine, MathExpressions)
{
	VMachine vm;

	// (8 + (5 - 3)) / 2 * 4
	VExpression* expr = new MulExpr(
		new DivExpr(
			new AddExpr(
				new ConstantExpr(QValue::Integer(8), { 0,0 }),
				new SubExpr(
					new ConstantExpr(QValue::Integer(5), { 0,0 }),
					new ConstantExpr(QValue::Integer(3), { 0,0 }),
					{ 0,0 }
				),
				{ 0,0 }
			),
			new ConstantExpr(QValue::Integer(2), { 0,0 }),
			{ 0,0 }
		),
		new ConstantExpr(QValue::Integer(4), { 0,0 }),
		{ 0,0 }
	);

	QValue value;
	int32_t i;
	ASSERT_TRUE(expr->execute(vm.getRootContext(), &value));
	ASSERT_TRUE(value.getInteger(&i));
	ASSERT_EQ(i, 20);

	delete expr;

	// 25.8 / 2
	expr = new DivExpr(
		new ConstantExpr(QValue::Float(25.8f), { 0,0 }),
		new ConstantExpr(QValue::Integer(2), { 0,0 }),
		{ 0,0 }
	);

	float f;
	ASSERT_TRUE(expr->execute(vm.getRootContext(), &value));
	ASSERT_TRUE(value.getFloat(&f));
	ASSERT_FLOAT_EQ(f, 12.9f);

	delete expr;

	// true || (false && !(5 == 5))
	expr = new OrExpr(
		new ConstantExpr(QValue::Bool(true), { 0,0 }),
		new AndExpr(
			new ConstantExpr(QValue::Bool(false), { 0,0 }),
			new NotExpr(
				new EqualExpr(
					new ConstantExpr(QValue::Integer(5), { 0,0 }),
					new ConstantExpr(QValue::Integer(5), { 0,0 }),
					{ 0,0 }
				),
				{ 0,0 }
			),
			{ 0,0 }
		),
		{ 0,0 }
	);

	bool b;
	ASSERT_TRUE(expr->execute(vm.getRootContext(), &value));
	ASSERT_TRUE(value.getBool(&b));
	ASSERT_TRUE(b);

	delete expr;
}

TEST(VMachine, DefineInput)
{
	VMachine vm;
	Context* ctx = new SimpleContext(&vm);
	VStatement* stm = new DefineInputStm("foo", new ConstantExpr(QValue::Nil(), { 0,0 }), { 0,0 });
	Result res = stm->execute(ctx);
	ASSERT_FALSE(res);
	ASSERT_EQ(res.getErr(), "line 0:0: Inputs/outputs must be defined in the root context.");

	delete stm;
	RootContext* rootCtx = new RootContext(&vm);

	stm = new DefineInputStm("foo", new ConstantExpr(QValue::Nil(), { 0,0 }), { 0,0 });
	ASSERT_TRUE(stm->execute(rootCtx));
	ASSERT_TRUE(rootCtx->hasValue("foo"));
	
	QValue value;
	ASSERT_TRUE(rootCtx->getValue("foo", &value));
	ASSERT_EQ(value, QValue::Nil());

	rootCtx->setInput("foo", QValue::Integer(123));
	ASSERT_TRUE(rootCtx->getValue("foo", &value));
	ASSERT_EQ(value, QValue::Integer(123));

	res = stm->execute(rootCtx);
	ASSERT_FALSE(res);
	ASSERT_EQ(res.getErr(), "line 0:0: Input foo has the wrong type.");

	delete stm;
	
	stm = new DefineInputStm("bar", new ConstantExpr(QValue::Float(1.34f), { 0,0 }), { 0,0 });
	ASSERT_TRUE(stm->execute(rootCtx));
	ASSERT_TRUE(rootCtx->hasValue("bar"));

	ASSERT_TRUE(rootCtx->getValue("bar", &value));
	ASSERT_EQ(value, QValue::Float(1.34f));

	delete stm;
}

TEST(VMachine, DefineOutput)
{
	VMachine vm;
	Context* ctx = new SimpleContext(&vm);
	VStatement* stm = new DefineOutputStm("foo", nullptr, { 0,0 });
	Result res = stm->execute(ctx);
	ASSERT_FALSE(res);
	ASSERT_EQ(res.getErr(), "line 0:0: Inputs/outputs must be defined in the root context.");

	delete stm;
	RootContext* rootCtx = new RootContext(&vm);

	stm = new DefineOutputStm("foo", nullptr, { 0,0 });
	ASSERT_TRUE(stm->execute(rootCtx));
	ASSERT_TRUE(rootCtx->hasValue("foo"));

	QValue value;
	ASSERT_TRUE(rootCtx->getValue("foo", &value));
	ASSERT_EQ(value, QValue::Nil());

	rootCtx->setOutput("foo", QValue::Integer(123));
	ASSERT_TRUE(rootCtx->getValue("foo", &value));
	ASSERT_EQ(value, QValue::Integer(123));

	res = stm->execute(rootCtx);
	ASSERT_TRUE(res);

	// outputs may be redefined as of 0.5.0
	//ASSERT_EQ(res.getErr(), "line 0:0: Outputs may not be redefined.");

	delete stm;

	stm = new DefineOutputStm("bar", new ConstantExpr(QValue::Float(1.34f), { 0,0 }), { 0,0 });
	ASSERT_TRUE(stm->execute(rootCtx));
	ASSERT_TRUE(rootCtx->hasValue("bar"));

	ASSERT_TRUE(rootCtx->getValue("bar", &value));
	ASSERT_EQ(value, QValue::Float(1.34f));

	delete stm;
}

TEST(VMachine, Branch)
{
	VMachine vm;
	bool trueCalled = false;
	bool falseCalled = false;
	QValue trueFunc = QValue::Function(&vm, [&](VMachine* vm, int32_t argCount, QValue* args, QValue* result) -> Result {
		trueCalled = true;
		*result = QValue::Nil();
		return true;
	});
	QValue falseFunc = QValue::Function(&vm, [&](VMachine* vm, int32_t argCount, QValue* args, QValue* result) -> Result {
		falseCalled = true;
		*result = QValue::Nil();
		return true;
	});

	VStatement* stm = new BranchStm(new ConstantExpr(QValue::Integer(123), { 0,0 }), nullptr, nullptr, { 0,0 });
	Result res = stm->execute(vm.getRootContext());
	ASSERT_FALSE(res);
	ASSERT_EQ(res.getErr(), "line 0:0: Subexpression must return a boolean within a Branch");

	delete stm;

	stm = new BranchStm(
		new ConstantExpr(QValue::Bool(false), { 0,0 }),
		new VExpressionAsStatement(new CallFunctionExpr(new ConstantExpr(trueFunc, { 0,0 }), 0, nullptr, { 0,0 }), { 0,0 }),
		new VExpressionAsStatement(new CallFunctionExpr(new ConstantExpr(falseFunc, { 0,0 }), 0, nullptr, { 0,0 }), { 0,0 }),
		{ 0,0 }
	);

	ASSERT_TRUE(stm->execute(vm.getRootContext()));
	EXPECT_FALSE(trueCalled);
	EXPECT_TRUE(falseCalled);

	trueCalled = false;
	falseCalled = false;
	delete stm;

	stm = new BranchStm(
		new ConstantExpr(QValue::Bool(true), { 0,0 }),
		new VExpressionAsStatement(new CallFunctionExpr(new ConstantExpr(trueFunc, { 0,0 }), 0, nullptr, { 0,0 }), { 0,0 }),
		new VExpressionAsStatement(new CallFunctionExpr(new ConstantExpr(falseFunc, { 0,0 }), 0, nullptr, { 0,0 }), { 0,0 }),
		{ 0,0 }
	);

	ASSERT_TRUE(stm->execute(vm.getRootContext()));
	EXPECT_TRUE(trueCalled);
	EXPECT_FALSE(falseCalled);

	delete stm;
}