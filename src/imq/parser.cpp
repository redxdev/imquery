#include "parser.h"

#include <sstream>
#include <fstream>

#include "imq/grammar/IMQLangLexer.h"
#include "imq/grammar/IMQLangParser.h"

#include "errors.h"

using namespace antlr4;

namespace imq
{

	SavedErrorListener::SavedErrorListener(bool bDebugMode)
		: bDebugMode(bDebugMode)
	{
	}

	void SavedErrorListener::syntaxError(antlr4::Recognizer* recognizer, antlr4::Token* offendingSymbol, size_t line, size_t charPositionInLine, const std::string& msg, std::exception_ptr e)
	{
		std::stringstream ss;
		ss << "line " << line << ":" << charPositionInLine << ": " << msg;
		lastMessage = ss.str();
	}

	void SavedErrorListener::reportAmbiguity(Parser *recognizer, const dfa::DFA &dfa, size_t startIndex, size_t stopIndex, bool exact, const antlrcpp::BitSet &ambigAlts, atn::ATNConfigSet *configs)
	{
		if (!bDebugMode)
			return;

		auto token = recognizer->getCurrentToken();
		std::cerr << "line " << token->getLine() << ":" << token->getCharPositionInLine() << ": ambiguity around here - " << startIndex << " to " << stopIndex << std::endl;
	}

	const String& SavedErrorListener::getLastMessage() const
	{
		return lastMessage;
	}

	Result QueryParser::parseString(const String& data, VBlock** result) const
	{
		ANTLRInputStream stream(data);
		return parseStream(&stream, result);
	}

	Result QueryParser::parseFile(const String& filename, VBlock** result) const
	{
		std::fstream fs;
		fs.open(filename.data(), std::ios::in);
		if (!fs.is_open())
		{
			return errors::file_open(filename);
		}

		ANTLRInputStream stream(fs);
		return parseStream(&stream, result);
	}

	Result QueryParser::parseStream(ANTLRInputStream* stream, VBlock** result) const
	{
		IMQLangLexer lexer(stream);
		CommonTokenStream tokens(&lexer);

		Ref<BailErrorStrategy> errorStrategy(new BailErrorStrategy());
		SavedErrorListener errorListener(bDebugMode);
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
			for (auto node : parser.generatedVNodes)
			{
				node->setErrorState(true);
				delete node;
			}

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

	imq::Result QueryParser::parseExpression(const String& data, VExpression** result) const
	{
		ANTLRInputStream stream(data);
		IMQLangLexer lexer(&stream);
		CommonTokenStream tokens(&lexer);

		Ref<BailErrorStrategy> errorStrategy(new BailErrorStrategy());
		SavedErrorListener errorListener(bDebugMode);
		IMQLangParser parser(&tokens);
		parser.removeErrorListeners();
		parser.addErrorListener(&errorListener);
		parser.setErrorHandler(errorStrategy);

		try
		{
			auto outCtx = parser.expression();
			*result = outCtx->expr;
		}
		catch (const std::exception& outer)
		{
			for (auto node : parser.generatedVNodes)
			{
				node->setErrorState(true);
				delete node;
			}

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