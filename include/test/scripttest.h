#pragma once

#include <imq/parser.h>
#include <imq/vm.h>
#include <imq/image.h>
#include <imq/cast.h>
#include <imq/errors.h>
#include <imq/library.h>

class ScriptTest
{
public:
	ScriptTest();

	imq::Result run(const char* script);

	// defaults to nil if not found
	imq::QValue get(const imq::String& name);

	bool equal(const imq::String& name, const imq::QValue& check);

private:
	imq::VMachine vm;
};