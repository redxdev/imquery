#include "scripttest.h"

using namespace imq;

ScriptTest::ScriptTest()
{
	register_stdlib(&vm);
}

Result ScriptTest::run(const char* script)
{
	QueryParser parser;
	VBlock* block;

	Result res = parser.parseString(script, &block);
	if (!res)
		return res;

	res = vm.execute(block);

	delete block;
	return res;
}

QValue ScriptTest::get(const String& name)
{
	QValue value;
	vm.getRootContext()->getValue(name, &value);
	return value;
}

bool ScriptTest::equal(const String& name, const QValue& check)
{
	QValue value;
	if (!vm.getRootContext()->getValue(name, &value))
		return false;

	return value == check;
}

VMachine* ScriptTest::getVM()
{
	return &vm;
}
