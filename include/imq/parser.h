#pragma once

#include "platform.h"
#include "result.h"
#include "vm.h"

#include <antlr4-runtime.h>

namespace imq
{
	class SavedErrorListener : public antlr4::BaseErrorListener
	{
	public:
		SavedErrorListener(bool bDebugMode);

		virtual void syntaxError(antlr4::IRecognizer* recognizer, antlr4::Token* offendingSymbol, size_t line, size_t charPositionInLine, const std::string& msg, std::exception_ptr e) override;

		virtual void reportAmbiguity(antlr4::Parser *recognizer, const antlr4::dfa::DFA &dfa, size_t startIndex, size_t stopIndex, bool exact, const antlrcpp::BitSet &ambigAlts, antlr4::atn::ATNConfigSet *configs) override;

		const String& getLastMessage() const;

	private:
		String lastMessage;
		bool bDebugMode;
	};

	class IMQ_API QueryParser
	{
	public:
		Result parseString(const String& data, VBlock** result) const;

		Result parseFile(const String& filename, VBlock** result) const;

		Result parseStream(antlr4::ANTLRInputStream* stream, VBlock** result) const;

		Result parseExpression(const String& data, VExpression** result) const;

		inline void setDebugMode(bool bValue)
		{
			bDebugMode = bValue;
		}

	private:
		bool bDebugMode = false;
	};
}