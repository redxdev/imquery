#include <iostream>
#include <string>

#include "thirdparty/tclap/CmdLine.h"

#include <imq/vm.h>
#include <imq/parser.h>
#include <imq/result.h>
#include <imq/library.h>

using namespace imq;

bool execute(VMachine* vm, VBlock* block)
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

		delete block;
		return true;
	}

	QueryParser parser;
	Result res;

	while (true)
	{
		std::cout << "> ";
		std::string line;
		std::getline(std::cin, line);
		if (line.empty())
			continue;

		res = parser.parseString(line, &block);
		if (!res)
		{
			std::cout << "parse error: " << res.getErr() << std::endl;
			continue;
		}

		res = vm->execute(block);
		if (!res)
		{
			std::cout << "runtime error: " << res.getErr() << std::endl;
		}

		delete block;
	}
}

int main(int argc, char** argv)
{
	TCLAP::CmdLine cmd("Interactive frontend to imquery", ' ', "1.0");

	TCLAP::ValueArg<std::string> fileArg("f", "file", "The script file to load.", false, "", "string", cmd);

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
	VBlock* block = nullptr;

	Result res = register_stdlib(&vm);
	if (!res)
	{
		std::cerr << "Unable to register stdlib: " << res.getErr() << std::endl;
		return EXIT_FAILURE;
	}

	if (fileArg.isSet())
	{
		QueryParser parser;
		res = parser.parseFile(fileArg.getValue(), &block);
		if (!res)
		{
			std::cerr << res.getErr() << std::endl;
			return EXIT_FAILURE;
		}
	}

	return execute(&vm, block);
}