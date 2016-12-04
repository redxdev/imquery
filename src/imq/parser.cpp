#include "parser.h"

#include <sstream>

#include "imq/grammar/IMQLangLexer.h"
#include "imq/grammar/IMQLangParser.h"

using namespace antlr4;

namespace imq
{
	void SavedErrorListener::syntaxError(antlr4::IRecognizer* recognizer, antlr4::Token* offendingSymbol, size_t line, size_t charPositionInLine, const std::string& msg, std::exception_ptr e)
	{
		std::stringstream ss;
		ss << "line " << line << ":" << charPositionInLine << ": " << msg;
		lastMessage = ss.str();
	}

	const String& SavedErrorListener::getLastMessage() const
	{
		return lastMessage;
	}

	Result QueryParser::parse(const String& data, VBlock** result) const
	{
		ANTLRInputStream stream(data);
		return parseStream(&stream, result);
	}

	Result QueryParser::parseStream(ANTLRInputStream* stream, VBlock** result) const
	{
		IMQLangLexer lexer(stream);
		CommonTokenStream tokens(&lexer);

		Ref<BailErrorStrategy> errorStrategy(new BailErrorStrategy());
		SavedErrorListener errorListener;
		IMQLangParser parser(&tokens);
		parser.removeErrorListeners();
		parser.addErrorListener(&errorListener);
		parser.setErrorHandler(errorStrategy);

		try
		{
			auto outCtx = parser.compileUnit();
			*result = outCtx->block;
		}
		catch (const std::exception& outer)
		{
			if (!errorListener.getLastMessage().empty())
			{
				return Result(false, errorListener.getLastMessage());
			}

			try
			{
				std::rethrow_if_nested(outer);
			}
			catch (const std::exception& inner)
			{
				return Result(false, inner.what());
			}

			return Result(false, outer.what());
		}

		return true;
	}

}