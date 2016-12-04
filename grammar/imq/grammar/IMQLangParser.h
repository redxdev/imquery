
    #include "expressions.h"
    #include "mathexpr.h"
    #include "value.h"
    #include "object.h"
    #include "image.h"
    #include "parseutils.h"
    #include "platform.h"

    #include <string>
    #include <memory>
    #include <vector>


// Generated from grammar/IMQLang.g4 by ANTLR 4.6

#pragma once


#include "antlr4-runtime.h"


using namespace antlr4;

namespace imq {


class IMQLangParser : public Parser {
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

  enum {
    RuleCompileUnit = 0, RuleStatements = 1, RuleStatement = 2, RuleDefine_input_stm = 3, 
    RuleDefine_output_stm = 4, RuleSet_variable_stm = 5, RuleSet_field_stm = 6, 
    RuleDelete_variable_stm = 7, RuleSelect_stm = 8, RuleBranch_stm = 9, 
    RuleFor_loop_stm = 10, RuleWhile_loop_stm = 11, RuleExpression = 12, 
    RuleOrExpr = 13, RuleAndExpr = 14, RuleEqualityExpr = 15, RuleAddExpr = 16, 
    RuleMulExpr = 17, RuleNotExpr = 18, RuleAtom = 19, RuleValue = 20, RuleConst_value = 21, 
    RuleBoolean = 22, RuleColor = 23, RuleVariable = 24, RuleResolved_variable = 25, 
    RuleResolved_field = 26, RuleFunc_parameters = 27, RuleIndex_parameters = 28
  };

  IMQLangParser(TokenStream *input);
  ~IMQLangParser();

  virtual std::string getGrammarFileName() const override;
  virtual const atn::ATN& getATN() const override { return _atn; };
  virtual const std::vector<std::string>& getTokenNames() const override { return _tokenNames; }; // deprecated: use vocabulary instead.
  virtual const std::vector<std::string>& getRuleNames() const override;
  virtual dfa::Vocabulary& getVocabulary() const override;


  class CompileUnitContext;
  class StatementsContext;
  class StatementContext;
  class Define_input_stmContext;
  class Define_output_stmContext;
  class Set_variable_stmContext;
  class Set_field_stmContext;
  class Delete_variable_stmContext;
  class Select_stmContext;
  class Branch_stmContext;
  class For_loop_stmContext;
  class While_loop_stmContext;
  class ExpressionContext;
  class OrExprContext;
  class AndExprContext;
  class EqualityExprContext;
  class AddExprContext;
  class MulExprContext;
  class NotExprContext;
  class AtomContext;
  class ValueContext;
  class Const_valueContext;
  class BooleanContext;
  class ColorContext;
  class VariableContext;
  class Resolved_variableContext;
  class Resolved_fieldContext;
  class Func_parametersContext;
  class Index_parametersContext; 

  class CompileUnitContext : public ParserRuleContext {
  public:
    VBlock* block;
    IMQLangParser::StatementsContext *statementsContext = nullptr;;
    CompileUnitContext(ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    tree::TerminalNode *EOF();
    StatementsContext *statements();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;
   
  };

  CompileUnitContext* compileUnit();

  class StatementsContext : public ParserRuleContext {
  public:
    int32_t count;
    VStatement** stmArr;
    std::vector<VStatement*> stmList;
    IMQLangParser::StatementContext *statementContext = nullptr;;
    StatementsContext(ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;
   
  };

  StatementsContext* statements();

  class StatementContext : public ParserRuleContext {
  public:
    VStatement* stm;
    IMQLangParser::Define_input_stmContext *define_input_stmContext = nullptr;;
    IMQLangParser::Define_output_stmContext *define_output_stmContext = nullptr;;
    IMQLangParser::Set_variable_stmContext *set_variable_stmContext = nullptr;;
    IMQLangParser::Set_field_stmContext *set_field_stmContext = nullptr;;
    IMQLangParser::Delete_variable_stmContext *delete_variable_stmContext = nullptr;;
    IMQLangParser::Select_stmContext *select_stmContext = nullptr;;
    IMQLangParser::Branch_stmContext *branch_stmContext = nullptr;;
    IMQLangParser::For_loop_stmContext *for_loop_stmContext = nullptr;;
    IMQLangParser::While_loop_stmContext *while_loop_stmContext = nullptr;;
    IMQLangParser::ExpressionContext *expressionContext = nullptr;;
    StatementContext(ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Define_input_stmContext *define_input_stm();
    tree::TerminalNode *SEMICOLON();
    Define_output_stmContext *define_output_stm();
    Set_variable_stmContext *set_variable_stm();
    Set_field_stmContext *set_field_stm();
    Delete_variable_stmContext *delete_variable_stm();
    Select_stmContext *select_stm();
    Branch_stmContext *branch_stm();
    For_loop_stmContext *for_loop_stm();
    While_loop_stmContext *while_loop_stm();
    ExpressionContext *expression();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;
   
  };

  StatementContext* statement();

  class Define_input_stmContext : public ParserRuleContext {
  public:
    VStatement* stm;
    Token *inputToken = nullptr;;
    Token *identToken = nullptr;;
    IMQLangParser::ExpressionContext *expressionContext = nullptr;;
    Define_input_stmContext(ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    tree::TerminalNode *INPUT();
    tree::TerminalNode *IDENT();
    tree::TerminalNode *EQUAL();
    ExpressionContext *expression();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;
   
  };

  Define_input_stmContext* define_input_stm();

  class Define_output_stmContext : public ParserRuleContext {
  public:
    VStatement* stm;
    VExpression* valueExpr = nullptr;
    Token *outputToken = nullptr;;
    Token *identToken = nullptr;;
    IMQLangParser::ExpressionContext *expressionContext = nullptr;;
    Define_output_stmContext(ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    tree::TerminalNode *OUTPUT();
    tree::TerminalNode *IDENT();
    tree::TerminalNode *EQUAL();
    ExpressionContext *expression();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;
   
  };

  Define_output_stmContext* define_output_stm();

  class Set_variable_stmContext : public ParserRuleContext {
  public:
    VStatement* stm;
    Token *identToken = nullptr;;
    IMQLangParser::ExpressionContext *expressionContext = nullptr;;
    Set_variable_stmContext(ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    tree::TerminalNode *IDENT();
    tree::TerminalNode *EQUAL();
    ExpressionContext *expression();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;
   
  };

  Set_variable_stmContext* set_variable_stm();

  class Set_field_stmContext : public ParserRuleContext {
  public:
    VStatement* stm;
    IMQLangParser::VariableContext *variableContext = nullptr;;
    Token *identToken = nullptr;;
    IMQLangParser::ExpressionContext *expressionContext = nullptr;;
    Set_field_stmContext(ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    VariableContext *variable();
    tree::TerminalNode *DOT();
    tree::TerminalNode *IDENT();
    tree::TerminalNode *EQUAL();
    ExpressionContext *expression();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;
   
  };

  Set_field_stmContext* set_field_stm();

  class Delete_variable_stmContext : public ParserRuleContext {
  public:
    VStatement* stm;
    Token *deleteToken = nullptr;;
    Token *identToken = nullptr;;
    Delete_variable_stmContext(ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    tree::TerminalNode *DELETE();
    tree::TerminalNode *IDENT();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;
   
  };

  Delete_variable_stmContext* delete_variable_stm();

  class Select_stmContext : public ParserRuleContext {
  public:
    VStatement* stm;
    IMQLangParser::ExpressionContext *dest = nullptr;;
    IMQLangParser::ExpressionContext *calc = nullptr;;
    IMQLangParser::ExpressionContext *src = nullptr;;
    Select_stmContext(ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    tree::TerminalNode *COLON();
    tree::TerminalNode *FROM();
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;
   
  };

  Select_stmContext* select_stm();

  class Branch_stmContext : public ParserRuleContext {
  public:
    VStatement* stm;
    VBlock* trueBlock = nullptr;
    VStatement* falseBlock = nullptr;
    IMQLangParser::StatementsContext *statementsContext = nullptr;;
    IMQLangParser::Branch_stmContext *elif = nullptr;;
    IMQLangParser::Branch_stmContext *branch_stmContext = nullptr;;
    Branch_stmContext(ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    tree::TerminalNode *IF();
    ExpressionContext *expression();
    std::vector<tree::TerminalNode *> L_BRACE();
    tree::TerminalNode* L_BRACE(size_t i);
    std::vector<tree::TerminalNode *> R_BRACE();
    tree::TerminalNode* R_BRACE(size_t i);
    std::vector<StatementsContext *> statements();
    StatementsContext* statements(size_t i);
    tree::TerminalNode *ELSE();
    Branch_stmContext *branch_stm();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;
   
  };

  Branch_stmContext* branch_stm();

  class For_loop_stmContext : public ParserRuleContext {
  public:
    VStatement* stm;
    VBlock* block = nullptr;
    Token *forToken = nullptr;;
    IMQLangParser::StatementContext *init = nullptr;;
    IMQLangParser::ExpressionContext *expressionContext = nullptr;;
    IMQLangParser::StatementContext *incr = nullptr;;
    IMQLangParser::StatementsContext *statementsContext = nullptr;;
    For_loop_stmContext(ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    tree::TerminalNode *FOR();
    ExpressionContext *expression();
    tree::TerminalNode *SEMICOLON();
    tree::TerminalNode *L_BRACE();
    tree::TerminalNode *R_BRACE();
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);
    StatementsContext *statements();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;
   
  };

  For_loop_stmContext* for_loop_stm();

  class While_loop_stmContext : public ParserRuleContext {
  public:
    VStatement* stm;
    VBlock* block = nullptr;
    Token *whileToken = nullptr;;
    IMQLangParser::ExpressionContext *expressionContext = nullptr;;
    IMQLangParser::StatementsContext *statementsContext = nullptr;;
    While_loop_stmContext(ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    tree::TerminalNode *WHILE();
    ExpressionContext *expression();
    tree::TerminalNode *L_BRACE();
    tree::TerminalNode *R_BRACE();
    StatementsContext *statements();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;
   
  };

  While_loop_stmContext* while_loop_stm();

  class ExpressionContext : public ParserRuleContext {
  public:
    VExpression* expr;
    IMQLangParser::OrExprContext *orExprContext = nullptr;;
    ExpressionContext(ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    OrExprContext *orExpr();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;
   
  };

  ExpressionContext* expression();

  class OrExprContext : public ParserRuleContext {
  public:
    VExpression* expr;
    IMQLangParser::AndExprContext *andExprContext = nullptr;;
    IMQLangParser::OrExprContext *orExprContext = nullptr;;
    OrExprContext(ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AndExprContext *andExpr();
    tree::TerminalNode *OR();
    OrExprContext *orExpr();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;
   
  };

  OrExprContext* orExpr();

  class AndExprContext : public ParserRuleContext {
  public:
    VExpression* expr;
    IMQLangParser::EqualityExprContext *equalityExprContext = nullptr;;
    IMQLangParser::AndExprContext *andExprContext = nullptr;;
    AndExprContext(ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    EqualityExprContext *equalityExpr();
    tree::TerminalNode *AND();
    AndExprContext *andExpr();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;
   
  };

  AndExprContext* andExpr();

  class EqualityExprContext : public ParserRuleContext {
  public:
    VExpression* expr;
    IMQLangParser::AddExprContext *addExprContext = nullptr;;
    IMQLangParser::EqualityExprContext *equalityExprContext = nullptr;;
    EqualityExprContext(ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AddExprContext *addExpr();
    std::vector<tree::TerminalNode *> EQUAL();
    tree::TerminalNode* EQUAL(size_t i);
    EqualityExprContext *equalityExpr();
    tree::TerminalNode *BANG();
    tree::TerminalNode *LESS();
    tree::TerminalNode *GREATER();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;
   
  };

  EqualityExprContext* equalityExpr();

  class AddExprContext : public ParserRuleContext {
  public:
    VExpression* expr;
    IMQLangParser::MulExprContext *mulExprContext = nullptr;;
    IMQLangParser::AddExprContext *addExprContext = nullptr;;
    AddExprContext(ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    MulExprContext *mulExpr();
    tree::TerminalNode *PLUS();
    AddExprContext *addExpr();
    tree::TerminalNode *MINUS();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;
   
  };

  AddExprContext* addExpr();

  class MulExprContext : public ParserRuleContext {
  public:
    VExpression* expr;
    IMQLangParser::NotExprContext *notExprContext = nullptr;;
    IMQLangParser::MulExprContext *mulExprContext = nullptr;;
    MulExprContext(ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    NotExprContext *notExpr();
    tree::TerminalNode *MULTIPLY();
    MulExprContext *mulExpr();
    tree::TerminalNode *DIVIDE();
    tree::TerminalNode *MODULUS();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;
   
  };

  MulExprContext* mulExpr();

  class NotExprContext : public ParserRuleContext {
  public:
    VExpression* expr;
    Token *notToken = nullptr;;
    IMQLangParser::NotExprContext *notExprContext = nullptr;;
    Token *minusToken = nullptr;;
    IMQLangParser::AtomContext *atomContext = nullptr;;
    NotExprContext(ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    tree::TerminalNode *NOT();
    NotExprContext *notExpr();
    tree::TerminalNode *MINUS();
    AtomContext *atom();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;
   
  };

  NotExprContext* notExpr();

  class AtomContext : public ParserRuleContext {
  public:
    VExpression* expr;
    IMQLangParser::ValueContext *valueContext = nullptr;;
    IMQLangParser::VariableContext *variableContext = nullptr;;
    IMQLangParser::ExpressionContext *expressionContext = nullptr;;
    AtomContext(ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ValueContext *value();
    VariableContext *variable();
    tree::TerminalNode *L_PAREN();
    ExpressionContext *expression();
    tree::TerminalNode *R_PAREN();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;
   
  };

  AtomContext* atom();

  class ValueContext : public ParserRuleContext {
  public:
    VExpression* expr;
    IMQLangParser::Const_valueContext *const_valueContext = nullptr;;
    IMQLangParser::ColorContext *colorContext = nullptr;;
    ValueContext(ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Const_valueContext *const_value();
    ColorContext *color();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;
   
  };

  ValueContext* value();

  class Const_valueContext : public ParserRuleContext {
  public:
    QValue val;
    Token *integerToken = nullptr;;
    Token *floatToken = nullptr;;
    IMQLangParser::BooleanContext *booleanContext = nullptr;;
    Const_valueContext(ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    tree::TerminalNode *INTEGER();
    tree::TerminalNode *FLOAT();
    BooleanContext *boolean();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;
   
  };

  Const_valueContext* const_value();

  class BooleanContext : public ParserRuleContext {
  public:
    bool val;
    BooleanContext(ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    tree::TerminalNode *B_TRUE();
    tree::TerminalNode *B_FALSE();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;
   
  };

  BooleanContext* boolean();

  class ColorContext : public ParserRuleContext {
  public:
    VExpression* expr;
    VExpression* rExpr = nullptr;
    VExpression* gExpr = nullptr;
    VExpression* bExpr = nullptr;
    VExpression* aExpr = nullptr;
    Token *l_braceToken = nullptr;;
    IMQLangParser::ExpressionContext *r = nullptr;;
    IMQLangParser::ExpressionContext *g = nullptr;;
    IMQLangParser::ExpressionContext *b = nullptr;;
    IMQLangParser::ExpressionContext *a = nullptr;;
    ColorContext(ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    tree::TerminalNode *L_BRACE();
    tree::TerminalNode *R_BRACE();
    std::vector<tree::TerminalNode *> COMMA();
    tree::TerminalNode* COMMA(size_t i);
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;
   
  };

  ColorContext* color();

  class VariableContext : public ParserRuleContext {
  public:
    VExpression* expr;
    IMQLangParser::Resolved_variableContext *resolved_variableContext = nullptr;;
    IMQLangParser::Resolved_fieldContext *resolved_fieldContext = nullptr;;
    VariableContext(ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Resolved_variableContext *resolved_variable();
    std::vector<tree::TerminalNode *> DOT();
    tree::TerminalNode* DOT(size_t i);
    std::vector<Resolved_fieldContext *> resolved_field();
    Resolved_fieldContext* resolved_field(size_t i);

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;
   
  };

  VariableContext* variable();

  class Resolved_variableContext : public ParserRuleContext {
  public:
    VExpression* expr;
    Token *identToken = nullptr;;
    IMQLangParser::Func_parametersContext *func_parametersContext = nullptr;;
    IMQLangParser::Index_parametersContext *index_parametersContext = nullptr;;
    Resolved_variableContext(ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    tree::TerminalNode *IDENT();
    Func_parametersContext *func_parameters();
    Index_parametersContext *index_parameters();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;
   
  };

  Resolved_variableContext* resolved_variable();

  class Resolved_fieldContext : public ParserRuleContext {
  public:
    VExpression* subexpr;
    VExpression* expr;
    Token *identToken = nullptr;;
    IMQLangParser::Func_parametersContext *func_parametersContext = nullptr;;
    IMQLangParser::Index_parametersContext *index_parametersContext = nullptr;;
    Resolved_fieldContext(ParserRuleContext *parent, size_t invokingState);
    Resolved_fieldContext(ParserRuleContext *parent, size_t invokingState, VExpression* subexpr);
    virtual size_t getRuleIndex() const override;
    tree::TerminalNode *IDENT();
    Func_parametersContext *func_parameters();
    Index_parametersContext *index_parameters();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;
   
  };

  Resolved_fieldContext* resolved_field(VExpression* subexpr);

  class Func_parametersContext : public ParserRuleContext {
  public:
    int32_t count;
    VExpression** args;
    std::vector<VExpression*> exprList;
    IMQLangParser::ExpressionContext *first = nullptr;;
    IMQLangParser::ExpressionContext *n = nullptr;;
    Func_parametersContext(ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    tree::TerminalNode *L_PAREN();
    tree::TerminalNode *R_PAREN();
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    std::vector<tree::TerminalNode *> COMMA();
    tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;
   
  };

  Func_parametersContext* func_parameters();

  class Index_parametersContext : public ParserRuleContext {
  public:
    VExpression* expr;
    IMQLangParser::ExpressionContext *expressionContext = nullptr;;
    Index_parametersContext(ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    tree::TerminalNode *L_BRACKET();
    ExpressionContext *expression();
    tree::TerminalNode *R_BRACKET();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;
   
  };

  Index_parametersContext* index_parameters();


private:
  static std::vector<dfa::DFA> _decisionToDFA;
  static atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static dfa::Vocabulary _vocabulary;
  static atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

}  // namespace imq
