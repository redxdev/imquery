#include <iostream>
#include <string>
#include <signal.h>

#include "thirdparty/tclap/CmdLine.h"

#include <imq/vm.h>
#include <imq/parser.h>
#include <imq/result.h>
#include <imq/library.h>
#include <imq/value.h>
#include <imq/image.h>
#include <imq/errors.h>
#include <imq/cast.h>
#include <imq/platform.h>
#include <imq/gc.h>

using namespace imq;

bool bRunning = true;

Result iqc_stop(VMachine* vm, int32_t argCount, QValue* args, QValue* result)
{
	bRunning = false;
	return true;
}

struct InputArg
{
	InputArg(VMachine* vm, std::string name, QValue value)
		: name(name), value(value), scope(vm->getGC(), &value)
	{
	}

	std::string name;
	QValue value;
	ScopedRoot scope;
};

struct IOPair
{
	std::string name;
	std::string value;
};

struct IOPairException
{
	IOPairException(const std::string& err)
		: err(err)
	{
	}

	std::string err;
};

Result saveOutputs(VMachine* vm, const std::vector<IOPair> outputs, bool errorOnInvalidVariable)
{
	for (auto pair : outputs)
	{
		QValue value;
		Result res = vm->getRootContext()->getValue(pair.name, &value);
		if (!res)
		{
			if (errorOnInvalidVariable)
				return res;
			else
				continue;
		}

		QObject* obj;
		if (!value.getObject(&obj))
			return Result(false, "Output " + pair.name + " is not a QObject");

		QImage* img = objectCast<QImage>(obj);
		if (!img)
			return Result(false, "Output " + pair.name + " is not a QImage");

		res = img->saveToFile(pair.value.data());
		if (!res)
			return res;
	}

	return true;
}

std::vector<IOPair> parseIOPairs(const std::vector<std::string>& strings)
{
	std::vector<IOPair> results;
	results.reserve(strings.size());
	for (auto str : strings)
	{
		auto eqPos = str.find_first_of('=');
		if (eqPos == std::string::npos)
			throw IOPairException("Invalid expression (missing '=') in " + str);

		IOPair pair;
		pair.name = str.substr(0, eqPos);
		pair.value = str.substr(eqPos + 1);

		results.push_back(pair);
	}

	return results;
}

std::vector<InputArg> parseInputs(VMachine* vm, QueryParser* parser, const std::vector<std::string>& inputStrings)
{
	auto pairs = parseIOPairs(inputStrings);
	std::vector<InputArg> results;
	results.reserve(pairs.size());
	for (auto pair : pairs)
	{
		VExpression* expr;
		Result res = parser->parseExpression(pair.value, &expr);
		if (!res)
			throw IOPairException("Input parser - " + res.getErr());

		QValue value;
		res = expr->execute(vm->getRootContext(), &value);
		if (!res)
			throw IOPairException("Input parser - " + res.getErr());

		results.push_back(InputArg(vm, pair.name, value));
	}

	return results;
}

bool execute(VMachine* vm, VBlock* block, const std::vector<IOPair>& outputs, QueryParser* parser)
{
	if (block)
	{
		Result res = vm->execute(block);
		if (!res)
		{
			std::cerr << res.getErr() << std::endl;
			delete block;

			return false;
		}

		res = saveOutputs(vm, outputs, true);
		if (!res)
		{
			std::cerr << res.getErr() << std::endl;
			delete block;
			return false;
		}

		delete block;
		return true;
	}

	vm->getRootContext()->setValue("exit", QValue::Function(vm, iqc_stop));

	Result res;
	QValue lastResult;

	while (bRunning)
	{
		lastResult = QValue();
		std::cout << "> ";
		std::string line;
		std::getline(std::cin, line);
		if (line.empty())
			continue;

		res = parser->parseString(line, &block);
		if (!res)
		{
			std::cout << "parse error: " << res.getErr() << std::endl;
			continue;
		}

		if (!block)
			continue;

		block->setEmitLastResult(&lastResult);

		res = vm->execute(block);
		if (!res)
		{
			std::cout << "runtime error: " << res.getErr() << std::endl;
		}

		if (lastResult.getType() != QValue::Type::Nil)
		{
			std::cout << lastResult.asString() << std::endl;
		}

		res = saveOutputs(vm, outputs, false);
		if (!res)
		{
			std::cout << "output save error: " << res.getErr() << std::endl;
		}

		delete block;
	}

	return true;
}

int main(int argc, char** argv)
{
	TCLAP::CmdLine cmd("Interactive frontend to imquery", ' ', getIMQVersion());

	TCLAP::ValueArg<std::string> fileArg("f", "file", "The script file to load.", false, "", "string", cmd);
	TCLAP::SwitchArg parserDebugArg("p", "parser-debug", "Enable parser debug mode", cmd, false);
	TCLAP::SwitchArg gcDebugArg("g", "gc-debug", "Enable gc debug mode", cmd, false);
	TCLAP::ValueArg<std::string> gcModeArg("m", "gc-mode", "Change the garbage collection mode. Valid values are Barriers, Always, and NoBarriers.", false, "", "string", cmd);

	TCLAP::MultiArg<std::string> inputArg("i", "input", "Inputs, in the form name=filepath", false, "string", cmd);
	TCLAP::MultiArg<std::string> outputArg("o", "output", "Outputs, in the form name=filepath", false, "string", cmd);

	TCLAP::MultiArg<std::string> searchPathArg("s", "search-path", "Search paths", false, "string", cmd);

	try
	{
		cmd.parse(argc, argv);
	}
	catch (const TCLAP::ArgException& e)
	{
		std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
		return EXIT_FAILURE;
	}

	VMachine vm;
	vm.getGC()->setDebugMode(gcDebugArg.getValue());

	if (gcModeArg.isSet())
	{
		if (gcModeArg.getValue() == "Barriers")
		{
			vm.getGC()->setCollectionMode(GCCollectionMode::Barriers);
		}
		else if (gcModeArg.getValue() == "NoBarriers")
		{
			vm.getGC()->setCollectionMode(GCCollectionMode::NoBarriers);
		}
		else if (gcModeArg.getValue() == "Always")
		{
			vm.getGC()->setCollectionMode(GCCollectionMode::Always);
		}
		else
		{
			std::cerr << "error: invalid garbage collection mode \"" << gcModeArg.getValue() << "\"";
			return EXIT_FAILURE;
		}
	}

	if (searchPathArg.isSet())
	{
		auto searchPaths = searchPathArg.getValue();
		for (auto path : searchPaths)
		{
			vm.addSearchPath(path);
		}
	}

	Result res = register_stdlib(&vm);
	if (!res)
	{
		std::cerr << "Unable to register stdlib: " << res.getErr() << std::endl;
		return EXIT_FAILURE;
	}

	QueryParser parser;
	parser.setDebugMode(parserDebugArg.getValue());

	std::vector<InputArg> inputs;
	std::vector<IOPair> outputs;

	try
	{
		inputs = parseInputs(&vm, &parser, inputArg.getValue());
		outputs = parseIOPairs(outputArg.getValue());
	}
	catch (const IOPairException& e)
	{
		std::cerr << e.err << std::endl;
		return EXIT_FAILURE;
	}

	for (auto input : inputs)
	{
		vm.getRootContext()->setInput(input.name, input.value);
	}

	VBlock* block = nullptr;

	if (fileArg.isSet())
	{
		res = parser.parseFile(fileArg.getValue(), &block);
		if (!res)
		{
			std::cerr << res.getErr() << std::endl;
			return EXIT_FAILURE;
		}
	}

	return execute(&vm, block, outputs, &parser) ? EXIT_SUCCESS : EXIT_FAILURE;
}