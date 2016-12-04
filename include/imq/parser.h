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
		virtual void syntaxError(antlr4::IRecognizer* recognizer, antlr4::Token* offendingSymbol, size_t line, size_t charPositionInLine, const std::string& msg, std::exception_ptr e) override;

		const String& getLastMessage() const;

	private:
		String lastMessage;
	};

	class QueryParser
	{
	public:
		Result parse(const String& data, VBlock** result) const;

		Result parseStream(antlr4::ANTLRInputStream* stream, VBlock** result) const;
	};
}