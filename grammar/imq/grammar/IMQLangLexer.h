
// Generated from grammar/IMQLang.g4 by ANTLR 4.6

#pragma once


#include "antlr4-runtime.h"


using namespace antlr4;

namespace imq {


class IMQLangLexer : public Lexer {
public:
  enum {
    SEMICOLON = 1, DELETE = 2, INPUT = 3, OUTPUT = 4, FROM = 5, IF = 6, 
    ELSE = 7, FOR = 8, WHILE = 9, DO = 10, L_PAREN = 11, R_PAREN = 12, L_BRACKET = 13, 
    R_BRACKET = 14, L_BRACE = 15, R_BRACE = 16, COMMA = 17, COLON = 18, 
    DOT = 19, NOT = 20, AND = 21, OR = 22, EQUAL = 23, BANG = 24, GREATER = 25, 
    LESS = 26, PLUS = 27, MINUS = 28, MULTIPLY = 29, DIVIDE = 30, MODULUS = 31, 
    B_TRUE = 32, B_FALSE = 33, FLOAT = 34, INTEGER = 35, IDENT = 36, WS = 37, 
    COMMENT = 38
  };

  IMQLangLexer(CharStream *input);
  ~IMQLangLexer();

  virtual std::string getGrammarFileName() const override;
  virtual const std::vector<std::string>& getRuleNames() const override;

  virtual const std::vector<std::string>& getModeNames() const override;
  virtual const std::vector<std::string>& getTokenNames() const override; // deprecated, use vocabulary instead
  virtual dfa::Vocabulary& getVocabulary() const override;

  virtual const std::vector<uint16_t> getSerializedATN() const override;
  virtual const atn::ATN& getATN() const override;

private:
  static std::vector<dfa::DFA> _decisionToDFA;
  static atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;
  static std::vector<std::string> _modeNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static dfa::Vocabulary _vocabulary;
  static atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

}  // namespace imq
