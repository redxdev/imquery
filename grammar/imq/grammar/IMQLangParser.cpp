
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


#include "IMQLangListener.h"

#include "IMQLangParser.h"


using namespace antlrcpp;
using namespace imq;
using namespace antlr4;

IMQLangParser::IMQLangParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

IMQLangParser::~IMQLangParser() {
  delete _interpreter;
}

std::string IMQLangParser::getGrammarFileName() const {
  return "IMQLang.g4";
}

const std::vector<std::string>& IMQLangParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& IMQLangParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- CompileUnitContext ------------------------------------------------------------------

IMQLangParser::CompileUnitContext::CompileUnitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IMQLangParser::CompileUnitContext::EOF() {
  return getToken(IMQLangParser::EOF, 0);
}

IMQLangParser::StatementsContext* IMQLangParser::CompileUnitContext::statements() {
  return getRuleContext<IMQLangParser::StatementsContext>(0);
}


size_t IMQLangParser::CompileUnitContext::getRuleIndex() const {
  return IMQLangParser::RuleCompileUnit;
}

void IMQLangParser::CompileUnitContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IMQLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCompileUnit(this);
}

void IMQLangParser::CompileUnitContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IMQLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCompileUnit(this);
}

IMQLangParser::CompileUnitContext* IMQLangParser::compileUnit() {
  CompileUnitContext *_localctx = _tracker.createInstance<CompileUnitContext>(_ctx, getState());
  enterRule(_localctx, 0, IMQLangParser::RuleCompileUnit);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(64);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case IMQLangParser::EOF: {
        enterOuterAlt(_localctx, 1);
        setState(58);
        match(IMQLangParser::EOF);
        dynamic_cast<CompileUnitContext *>(_localctx)->block =  nullptr;
        break;
      }

      case IMQLangParser::SEMICOLON:
      case IMQLangParser::DELETE:
      case IMQLangParser::INPUT:
      case IMQLangParser::OUTPUT:
      case IMQLangParser::IF:
      case IMQLangParser::FOR:
      case IMQLangParser::WHILE:
      case IMQLangParser::L_PAREN:
      case IMQLangParser::L_BRACE:
      case IMQLangParser::NOT:
      case IMQLangParser::MINUS:
      case IMQLangParser::B_TRUE:
      case IMQLangParser::B_FALSE:
      case IMQLangParser::FLOAT:
      case IMQLangParser::INTEGER:
      case IMQLangParser::IDENT: {
        enterOuterAlt(_localctx, 2);
        setState(60);
        dynamic_cast<CompileUnitContext *>(_localctx)->statementsContext = statements();
        setState(61);
        match(IMQLangParser::EOF);
        dynamic_cast<CompileUnitContext *>(_localctx)->block =  createNodeFromToken<VBlock>((dynamic_cast<CompileUnitContext *>(_localctx)->statementsContext != nullptr ? (dynamic_cast<CompileUnitContext *>(_localctx)->statementsContext->start) : nullptr), dynamic_cast<CompileUnitContext *>(_localctx)->statementsContext->count, dynamic_cast<CompileUnitContext *>(_localctx)->statementsContext->stmArr);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementsContext ------------------------------------------------------------------

IMQLangParser::StatementsContext::StatementsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<IMQLangParser::StatementContext *> IMQLangParser::StatementsContext::statement() {
  return getRuleContexts<IMQLangParser::StatementContext>();
}

IMQLangParser::StatementContext* IMQLangParser::StatementsContext::statement(size_t i) {
  return getRuleContext<IMQLangParser::StatementContext>(i);
}


size_t IMQLangParser::StatementsContext::getRuleIndex() const {
  return IMQLangParser::RuleStatements;
}

void IMQLangParser::StatementsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IMQLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStatements(this);
}

void IMQLangParser::StatementsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IMQLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStatements(this);
}

IMQLangParser::StatementsContext* IMQLangParser::statements() {
  StatementsContext *_localctx = _tracker.createInstance<StatementsContext>(_ctx, getState());
  enterRule(_localctx, 2, IMQLangParser::RuleStatements);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(69); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(66);
      dynamic_cast<StatementsContext *>(_localctx)->statementContext = statement();
      _localctx->stmList.push_back(dynamic_cast<StatementsContext *>(_localctx)->statementContext->stm);
      setState(71); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << IMQLangParser::SEMICOLON)
      | (1ULL << IMQLangParser::DELETE)
      | (1ULL << IMQLangParser::INPUT)
      | (1ULL << IMQLangParser::OUTPUT)
      | (1ULL << IMQLangParser::IF)
      | (1ULL << IMQLangParser::FOR)
      | (1ULL << IMQLangParser::WHILE)
      | (1ULL << IMQLangParser::L_PAREN)
      | (1ULL << IMQLangParser::L_BRACE)
      | (1ULL << IMQLangParser::NOT)
      | (1ULL << IMQLangParser::MINUS)
      | (1ULL << IMQLangParser::B_TRUE)
      | (1ULL << IMQLangParser::B_FALSE)
      | (1ULL << IMQLangParser::FLOAT)
      | (1ULL << IMQLangParser::INTEGER)
      | (1ULL << IMQLangParser::IDENT))) != 0));

                dynamic_cast<StatementsContext *>(_localctx)->count =  _localctx->stmList.size();
                dynamic_cast<StatementsContext *>(_localctx)->stmArr =  new VStatement*[_localctx->stmList.size()];
                std::copy(_localctx->stmList.begin(), _localctx->stmList.end(), _localctx->stmArr);
            
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

IMQLangParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IMQLangParser::Define_input_stmContext* IMQLangParser::StatementContext::define_input_stm() {
  return getRuleContext<IMQLangParser::Define_input_stmContext>(0);
}

tree::TerminalNode* IMQLangParser::StatementContext::SEMICOLON() {
  return getToken(IMQLangParser::SEMICOLON, 0);
}

IMQLangParser::Define_output_stmContext* IMQLangParser::StatementContext::define_output_stm() {
  return getRuleContext<IMQLangParser::Define_output_stmContext>(0);
}

IMQLangParser::Set_variable_stmContext* IMQLangParser::StatementContext::set_variable_stm() {
  return getRuleContext<IMQLangParser::Set_variable_stmContext>(0);
}

IMQLangParser::Set_field_stmContext* IMQLangParser::StatementContext::set_field_stm() {
  return getRuleContext<IMQLangParser::Set_field_stmContext>(0);
}

IMQLangParser::Delete_variable_stmContext* IMQLangParser::StatementContext::delete_variable_stm() {
  return getRuleContext<IMQLangParser::Delete_variable_stmContext>(0);
}

IMQLangParser::Select_stmContext* IMQLangParser::StatementContext::select_stm() {
  return getRuleContext<IMQLangParser::Select_stmContext>(0);
}

IMQLangParser::Branch_stmContext* IMQLangParser::StatementContext::branch_stm() {
  return getRuleContext<IMQLangParser::Branch_stmContext>(0);
}

IMQLangParser::For_loop_stmContext* IMQLangParser::StatementContext::for_loop_stm() {
  return getRuleContext<IMQLangParser::For_loop_stmContext>(0);
}

IMQLangParser::While_loop_stmContext* IMQLangParser::StatementContext::while_loop_stm() {
  return getRuleContext<IMQLangParser::While_loop_stmContext>(0);
}

IMQLangParser::ExpressionContext* IMQLangParser::StatementContext::expression() {
  return getRuleContext<IMQLangParser::ExpressionContext>(0);
}


size_t IMQLangParser::StatementContext::getRuleIndex() const {
  return IMQLangParser::RuleStatement;
}

void IMQLangParser::StatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IMQLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStatement(this);
}

void IMQLangParser::StatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IMQLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStatement(this);
}

IMQLangParser::StatementContext* IMQLangParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 4, IMQLangParser::RuleStatement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(114);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(75);
      dynamic_cast<StatementContext *>(_localctx)->define_input_stmContext = define_input_stm();
      setState(76);
      match(IMQLangParser::SEMICOLON);
      dynamic_cast<StatementContext *>(_localctx)->stm =  dynamic_cast<StatementContext *>(_localctx)->define_input_stmContext->stm;
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(79);
      dynamic_cast<StatementContext *>(_localctx)->define_output_stmContext = define_output_stm();
      setState(80);
      match(IMQLangParser::SEMICOLON);
      dynamic_cast<StatementContext *>(_localctx)->stm =  dynamic_cast<StatementContext *>(_localctx)->define_output_stmContext->stm;
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(83);
      dynamic_cast<StatementContext *>(_localctx)->set_variable_stmContext = set_variable_stm();
      setState(84);
      match(IMQLangParser::SEMICOLON);
      dynamic_cast<StatementContext *>(_localctx)->stm =  dynamic_cast<StatementContext *>(_localctx)->set_variable_stmContext->stm;
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(87);
      dynamic_cast<StatementContext *>(_localctx)->set_field_stmContext = set_field_stm();
      setState(88);
      match(IMQLangParser::SEMICOLON);
      dynamic_cast<StatementContext *>(_localctx)->stm =  dynamic_cast<StatementContext *>(_localctx)->set_field_stmContext->stm;
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(91);
      dynamic_cast<StatementContext *>(_localctx)->delete_variable_stmContext = delete_variable_stm();
      setState(92);
      match(IMQLangParser::SEMICOLON);
      dynamic_cast<StatementContext *>(_localctx)->stm =  dynamic_cast<StatementContext *>(_localctx)->delete_variable_stmContext->stm;
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(95);
      dynamic_cast<StatementContext *>(_localctx)->select_stmContext = select_stm();
      setState(96);
      match(IMQLangParser::SEMICOLON);
      dynamic_cast<StatementContext *>(_localctx)->stm =  dynamic_cast<StatementContext *>(_localctx)->select_stmContext->stm;
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(99);
      dynamic_cast<StatementContext *>(_localctx)->branch_stmContext = branch_stm();
      dynamic_cast<StatementContext *>(_localctx)->stm =  dynamic_cast<StatementContext *>(_localctx)->branch_stmContext->stm;
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(102);
      dynamic_cast<StatementContext *>(_localctx)->for_loop_stmContext = for_loop_stm();
      dynamic_cast<StatementContext *>(_localctx)->stm =  dynamic_cast<StatementContext *>(_localctx)->for_loop_stmContext->stm;
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(105);
      dynamic_cast<StatementContext *>(_localctx)->while_loop_stmContext = while_loop_stm();
      dynamic_cast<StatementContext *>(_localctx)->stm =  dynamic_cast<StatementContext *>(_localctx)->while_loop_stmContext->stm;
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(108);
      dynamic_cast<StatementContext *>(_localctx)->expressionContext = expression();
      setState(109);
      match(IMQLangParser::SEMICOLON);
      dynamic_cast<StatementContext *>(_localctx)->stm =  createNodeFromToken<VExpressionAsStatement>((dynamic_cast<StatementContext *>(_localctx)->expressionContext != nullptr ? (dynamic_cast<StatementContext *>(_localctx)->expressionContext->start) : nullptr), dynamic_cast<StatementContext *>(_localctx)->expressionContext->expr);
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(112);
      match(IMQLangParser::SEMICOLON);
      dynamic_cast<StatementContext *>(_localctx)->stm =  nullptr;
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Define_input_stmContext ------------------------------------------------------------------

IMQLangParser::Define_input_stmContext::Define_input_stmContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IMQLangParser::Define_input_stmContext::INPUT() {
  return getToken(IMQLangParser::INPUT, 0);
}

tree::TerminalNode* IMQLangParser::Define_input_stmContext::IDENT() {
  return getToken(IMQLangParser::IDENT, 0);
}

tree::TerminalNode* IMQLangParser::Define_input_stmContext::EQUAL() {
  return getToken(IMQLangParser::EQUAL, 0);
}

IMQLangParser::ExpressionContext* IMQLangParser::Define_input_stmContext::expression() {
  return getRuleContext<IMQLangParser::ExpressionContext>(0);
}


size_t IMQLangParser::Define_input_stmContext::getRuleIndex() const {
  return IMQLangParser::RuleDefine_input_stm;
}

void IMQLangParser::Define_input_stmContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IMQLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDefine_input_stm(this);
}

void IMQLangParser::Define_input_stmContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IMQLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDefine_input_stm(this);
}

IMQLangParser::Define_input_stmContext* IMQLangParser::define_input_stm() {
  Define_input_stmContext *_localctx = _tracker.createInstance<Define_input_stmContext>(_ctx, getState());
  enterRule(_localctx, 6, IMQLangParser::RuleDefine_input_stm);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(116);
    dynamic_cast<Define_input_stmContext *>(_localctx)->inputToken = match(IMQLangParser::INPUT);
    setState(117);
    dynamic_cast<Define_input_stmContext *>(_localctx)->identToken = match(IMQLangParser::IDENT);
    setState(118);
    match(IMQLangParser::EQUAL);
    setState(119);
    dynamic_cast<Define_input_stmContext *>(_localctx)->expressionContext = expression();
    dynamic_cast<Define_input_stmContext *>(_localctx)->stm =  createNodeFromToken<DefineInputStm>(dynamic_cast<Define_input_stmContext *>(_localctx)->inputToken, (dynamic_cast<Define_input_stmContext *>(_localctx)->identToken != nullptr ? dynamic_cast<Define_input_stmContext *>(_localctx)->identToken->getText() : ""), dynamic_cast<Define_input_stmContext *>(_localctx)->expressionContext->expr);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Define_output_stmContext ------------------------------------------------------------------

IMQLangParser::Define_output_stmContext::Define_output_stmContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IMQLangParser::Define_output_stmContext::OUTPUT() {
  return getToken(IMQLangParser::OUTPUT, 0);
}

tree::TerminalNode* IMQLangParser::Define_output_stmContext::IDENT() {
  return getToken(IMQLangParser::IDENT, 0);
}

tree::TerminalNode* IMQLangParser::Define_output_stmContext::EQUAL() {
  return getToken(IMQLangParser::EQUAL, 0);
}

IMQLangParser::ExpressionContext* IMQLangParser::Define_output_stmContext::expression() {
  return getRuleContext<IMQLangParser::ExpressionContext>(0);
}


size_t IMQLangParser::Define_output_stmContext::getRuleIndex() const {
  return IMQLangParser::RuleDefine_output_stm;
}

void IMQLangParser::Define_output_stmContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IMQLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDefine_output_stm(this);
}

void IMQLangParser::Define_output_stmContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IMQLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDefine_output_stm(this);
}

IMQLangParser::Define_output_stmContext* IMQLangParser::define_output_stm() {
  Define_output_stmContext *_localctx = _tracker.createInstance<Define_output_stmContext>(_ctx, getState());
  enterRule(_localctx, 8, IMQLangParser::RuleDefine_output_stm);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(122);
    dynamic_cast<Define_output_stmContext *>(_localctx)->outputToken = match(IMQLangParser::OUTPUT);
    setState(123);
    dynamic_cast<Define_output_stmContext *>(_localctx)->identToken = match(IMQLangParser::IDENT);
    setState(128);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IMQLangParser::EQUAL) {
      setState(124);
      match(IMQLangParser::EQUAL);
      setState(125);
      dynamic_cast<Define_output_stmContext *>(_localctx)->expressionContext = expression();
      dynamic_cast<Define_output_stmContext *>(_localctx)->valueExpr =  dynamic_cast<Define_output_stmContext *>(_localctx)->expressionContext->expr;
    }
    dynamic_cast<Define_output_stmContext *>(_localctx)->stm =  createNodeFromToken<DefineOutputStm>(dynamic_cast<Define_output_stmContext *>(_localctx)->outputToken, (dynamic_cast<Define_output_stmContext *>(_localctx)->identToken != nullptr ? dynamic_cast<Define_output_stmContext *>(_localctx)->identToken->getText() : ""), _localctx->valueExpr);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Set_variable_stmContext ------------------------------------------------------------------

IMQLangParser::Set_variable_stmContext::Set_variable_stmContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IMQLangParser::Set_variable_stmContext::IDENT() {
  return getToken(IMQLangParser::IDENT, 0);
}

tree::TerminalNode* IMQLangParser::Set_variable_stmContext::EQUAL() {
  return getToken(IMQLangParser::EQUAL, 0);
}

IMQLangParser::ExpressionContext* IMQLangParser::Set_variable_stmContext::expression() {
  return getRuleContext<IMQLangParser::ExpressionContext>(0);
}


size_t IMQLangParser::Set_variable_stmContext::getRuleIndex() const {
  return IMQLangParser::RuleSet_variable_stm;
}

void IMQLangParser::Set_variable_stmContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IMQLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSet_variable_stm(this);
}

void IMQLangParser::Set_variable_stmContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IMQLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSet_variable_stm(this);
}

IMQLangParser::Set_variable_stmContext* IMQLangParser::set_variable_stm() {
  Set_variable_stmContext *_localctx = _tracker.createInstance<Set_variable_stmContext>(_ctx, getState());
  enterRule(_localctx, 10, IMQLangParser::RuleSet_variable_stm);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(132);
    dynamic_cast<Set_variable_stmContext *>(_localctx)->identToken = match(IMQLangParser::IDENT);
    setState(133);
    match(IMQLangParser::EQUAL);
    setState(134);
    dynamic_cast<Set_variable_stmContext *>(_localctx)->expressionContext = expression();
    dynamic_cast<Set_variable_stmContext *>(_localctx)->stm =  createNodeFromToken<SetVariableStm>(dynamic_cast<Set_variable_stmContext *>(_localctx)->identToken, (dynamic_cast<Set_variable_stmContext *>(_localctx)->identToken != nullptr ? dynamic_cast<Set_variable_stmContext *>(_localctx)->identToken->getText() : ""), dynamic_cast<Set_variable_stmContext *>(_localctx)->expressionContext->expr);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Set_field_stmContext ------------------------------------------------------------------

IMQLangParser::Set_field_stmContext::Set_field_stmContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IMQLangParser::VariableContext* IMQLangParser::Set_field_stmContext::variable() {
  return getRuleContext<IMQLangParser::VariableContext>(0);
}

tree::TerminalNode* IMQLangParser::Set_field_stmContext::DOT() {
  return getToken(IMQLangParser::DOT, 0);
}

tree::TerminalNode* IMQLangParser::Set_field_stmContext::IDENT() {
  return getToken(IMQLangParser::IDENT, 0);
}

tree::TerminalNode* IMQLangParser::Set_field_stmContext::EQUAL() {
  return getToken(IMQLangParser::EQUAL, 0);
}

IMQLangParser::ExpressionContext* IMQLangParser::Set_field_stmContext::expression() {
  return getRuleContext<IMQLangParser::ExpressionContext>(0);
}


size_t IMQLangParser::Set_field_stmContext::getRuleIndex() const {
  return IMQLangParser::RuleSet_field_stm;
}

void IMQLangParser::Set_field_stmContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IMQLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSet_field_stm(this);
}

void IMQLangParser::Set_field_stmContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IMQLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSet_field_stm(this);
}

IMQLangParser::Set_field_stmContext* IMQLangParser::set_field_stm() {
  Set_field_stmContext *_localctx = _tracker.createInstance<Set_field_stmContext>(_ctx, getState());
  enterRule(_localctx, 12, IMQLangParser::RuleSet_field_stm);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(137);
    dynamic_cast<Set_field_stmContext *>(_localctx)->variableContext = variable();
    setState(138);
    match(IMQLangParser::DOT);
    setState(139);
    dynamic_cast<Set_field_stmContext *>(_localctx)->identToken = match(IMQLangParser::IDENT);
    setState(140);
    match(IMQLangParser::EQUAL);
    setState(141);
    dynamic_cast<Set_field_stmContext *>(_localctx)->expressionContext = expression();
    dynamic_cast<Set_field_stmContext *>(_localctx)->stm =  createNodeFromToken<SetFieldStm>((dynamic_cast<Set_field_stmContext *>(_localctx)->variableContext != nullptr ? (dynamic_cast<Set_field_stmContext *>(_localctx)->variableContext->start) : nullptr), dynamic_cast<Set_field_stmContext *>(_localctx)->variableContext->expr, (dynamic_cast<Set_field_stmContext *>(_localctx)->identToken != nullptr ? dynamic_cast<Set_field_stmContext *>(_localctx)->identToken->getText() : ""), dynamic_cast<Set_field_stmContext *>(_localctx)->expressionContext->expr);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Delete_variable_stmContext ------------------------------------------------------------------

IMQLangParser::Delete_variable_stmContext::Delete_variable_stmContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IMQLangParser::Delete_variable_stmContext::DELETE() {
  return getToken(IMQLangParser::DELETE, 0);
}

tree::TerminalNode* IMQLangParser::Delete_variable_stmContext::IDENT() {
  return getToken(IMQLangParser::IDENT, 0);
}


size_t IMQLangParser::Delete_variable_stmContext::getRuleIndex() const {
  return IMQLangParser::RuleDelete_variable_stm;
}

void IMQLangParser::Delete_variable_stmContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IMQLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDelete_variable_stm(this);
}

void IMQLangParser::Delete_variable_stmContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IMQLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDelete_variable_stm(this);
}

IMQLangParser::Delete_variable_stmContext* IMQLangParser::delete_variable_stm() {
  Delete_variable_stmContext *_localctx = _tracker.createInstance<Delete_variable_stmContext>(_ctx, getState());
  enterRule(_localctx, 14, IMQLangParser::RuleDelete_variable_stm);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(144);
    dynamic_cast<Delete_variable_stmContext *>(_localctx)->deleteToken = match(IMQLangParser::DELETE);
    setState(145);
    dynamic_cast<Delete_variable_stmContext *>(_localctx)->identToken = match(IMQLangParser::IDENT);
    dynamic_cast<Delete_variable_stmContext *>(_localctx)->stm =  createNodeFromToken<DeleteVariableStm>(dynamic_cast<Delete_variable_stmContext *>(_localctx)->deleteToken, (dynamic_cast<Delete_variable_stmContext *>(_localctx)->identToken != nullptr ? dynamic_cast<Delete_variable_stmContext *>(_localctx)->identToken->getText() : ""));
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Select_stmContext ------------------------------------------------------------------

IMQLangParser::Select_stmContext::Select_stmContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IMQLangParser::Select_stmContext::COLON() {
  return getToken(IMQLangParser::COLON, 0);
}

tree::TerminalNode* IMQLangParser::Select_stmContext::FROM() {
  return getToken(IMQLangParser::FROM, 0);
}

std::vector<IMQLangParser::ExpressionContext *> IMQLangParser::Select_stmContext::expression() {
  return getRuleContexts<IMQLangParser::ExpressionContext>();
}

IMQLangParser::ExpressionContext* IMQLangParser::Select_stmContext::expression(size_t i) {
  return getRuleContext<IMQLangParser::ExpressionContext>(i);
}


size_t IMQLangParser::Select_stmContext::getRuleIndex() const {
  return IMQLangParser::RuleSelect_stm;
}

void IMQLangParser::Select_stmContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IMQLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSelect_stm(this);
}

void IMQLangParser::Select_stmContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IMQLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSelect_stm(this);
}

IMQLangParser::Select_stmContext* IMQLangParser::select_stm() {
  Select_stmContext *_localctx = _tracker.createInstance<Select_stmContext>(_ctx, getState());
  enterRule(_localctx, 16, IMQLangParser::RuleSelect_stm);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(148);
    dynamic_cast<Select_stmContext *>(_localctx)->dest = expression();
    setState(149);
    match(IMQLangParser::COLON);
    setState(150);
    dynamic_cast<Select_stmContext *>(_localctx)->calc = expression();
    setState(151);
    match(IMQLangParser::FROM);
    setState(152);
    dynamic_cast<Select_stmContext *>(_localctx)->src = expression();
    dynamic_cast<Select_stmContext *>(_localctx)->stm =  createNodeFromToken<SelectStm>((dynamic_cast<Select_stmContext *>(_localctx)->dest != nullptr ? (dynamic_cast<Select_stmContext *>(_localctx)->dest->start) : nullptr), dynamic_cast<Select_stmContext *>(_localctx)->dest->expr, dynamic_cast<Select_stmContext *>(_localctx)->src->expr, dynamic_cast<Select_stmContext *>(_localctx)->calc->expr);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Branch_stmContext ------------------------------------------------------------------

IMQLangParser::Branch_stmContext::Branch_stmContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IMQLangParser::Branch_stmContext::IF() {
  return getToken(IMQLangParser::IF, 0);
}

IMQLangParser::ExpressionContext* IMQLangParser::Branch_stmContext::expression() {
  return getRuleContext<IMQLangParser::ExpressionContext>(0);
}

std::vector<tree::TerminalNode *> IMQLangParser::Branch_stmContext::L_BRACE() {
  return getTokens(IMQLangParser::L_BRACE);
}

tree::TerminalNode* IMQLangParser::Branch_stmContext::L_BRACE(size_t i) {
  return getToken(IMQLangParser::L_BRACE, i);
}

std::vector<tree::TerminalNode *> IMQLangParser::Branch_stmContext::R_BRACE() {
  return getTokens(IMQLangParser::R_BRACE);
}

tree::TerminalNode* IMQLangParser::Branch_stmContext::R_BRACE(size_t i) {
  return getToken(IMQLangParser::R_BRACE, i);
}

std::vector<IMQLangParser::StatementsContext *> IMQLangParser::Branch_stmContext::statements() {
  return getRuleContexts<IMQLangParser::StatementsContext>();
}

IMQLangParser::StatementsContext* IMQLangParser::Branch_stmContext::statements(size_t i) {
  return getRuleContext<IMQLangParser::StatementsContext>(i);
}

tree::TerminalNode* IMQLangParser::Branch_stmContext::ELSE() {
  return getToken(IMQLangParser::ELSE, 0);
}

IMQLangParser::Branch_stmContext* IMQLangParser::Branch_stmContext::branch_stm() {
  return getRuleContext<IMQLangParser::Branch_stmContext>(0);
}


size_t IMQLangParser::Branch_stmContext::getRuleIndex() const {
  return IMQLangParser::RuleBranch_stm;
}

void IMQLangParser::Branch_stmContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IMQLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBranch_stm(this);
}

void IMQLangParser::Branch_stmContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IMQLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBranch_stm(this);
}

IMQLangParser::Branch_stmContext* IMQLangParser::branch_stm() {
  Branch_stmContext *_localctx = _tracker.createInstance<Branch_stmContext>(_ctx, getState());
  enterRule(_localctx, 18, IMQLangParser::RuleBranch_stm);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(155);
    match(IMQLangParser::IF);
    setState(156);
    expression();
    setState(157);
    match(IMQLangParser::L_BRACE);
    setState(159);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << IMQLangParser::SEMICOLON)
      | (1ULL << IMQLangParser::DELETE)
      | (1ULL << IMQLangParser::INPUT)
      | (1ULL << IMQLangParser::OUTPUT)
      | (1ULL << IMQLangParser::IF)
      | (1ULL << IMQLangParser::FOR)
      | (1ULL << IMQLangParser::WHILE)
      | (1ULL << IMQLangParser::L_PAREN)
      | (1ULL << IMQLangParser::L_BRACE)
      | (1ULL << IMQLangParser::NOT)
      | (1ULL << IMQLangParser::MINUS)
      | (1ULL << IMQLangParser::B_TRUE)
      | (1ULL << IMQLangParser::B_FALSE)
      | (1ULL << IMQLangParser::FLOAT)
      | (1ULL << IMQLangParser::INTEGER)
      | (1ULL << IMQLangParser::IDENT))) != 0)) {
      setState(158);
      dynamic_cast<Branch_stmContext *>(_localctx)->statementsContext = statements();
    }
    setState(161);
    match(IMQLangParser::R_BRACE);
    setState(174);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx)) {
    case 1: {
      setState(162);
      match(IMQLangParser::ELSE);
      setState(163);
      dynamic_cast<Branch_stmContext *>(_localctx)->elif = dynamic_cast<Branch_stmContext *>(_localctx)->branch_stmContext = branch_stm();
      dynamic_cast<Branch_stmContext *>(_localctx)->falseBlock =  dynamic_cast<Branch_stmContext *>(_localctx)->branch_stmContext->stm;
      break;
    }

    case 2: {
      setState(166);
      match(IMQLangParser::ELSE);
      setState(167);
      match(IMQLangParser::L_BRACE);
      setState(171);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << IMQLangParser::SEMICOLON)
        | (1ULL << IMQLangParser::DELETE)
        | (1ULL << IMQLangParser::INPUT)
        | (1ULL << IMQLangParser::OUTPUT)
        | (1ULL << IMQLangParser::IF)
        | (1ULL << IMQLangParser::FOR)
        | (1ULL << IMQLangParser::WHILE)
        | (1ULL << IMQLangParser::L_PAREN)
        | (1ULL << IMQLangParser::L_BRACE)
        | (1ULL << IMQLangParser::NOT)
        | (1ULL << IMQLangParser::MINUS)
        | (1ULL << IMQLangParser::B_TRUE)
        | (1ULL << IMQLangParser::B_FALSE)
        | (1ULL << IMQLangParser::FLOAT)
        | (1ULL << IMQLangParser::INTEGER)
        | (1ULL << IMQLangParser::IDENT))) != 0)) {
        setState(168);
        dynamic_cast<Branch_stmContext *>(_localctx)->statementsContext = statements();
        dynamic_cast<Branch_stmContext *>(_localctx)->falseBlock =  createNodeFromToken<VBlock>((dynamic_cast<Branch_stmContext *>(_localctx)->statementsContext != nullptr ? (dynamic_cast<Branch_stmContext *>(_localctx)->statementsContext->start) : nullptr), dynamic_cast<Branch_stmContext *>(_localctx)->statementsContext->count, dynamic_cast<Branch_stmContext *>(_localctx)->statementsContext->stmArr);
      }
      setState(173);
      match(IMQLangParser::R_BRACE);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- For_loop_stmContext ------------------------------------------------------------------

IMQLangParser::For_loop_stmContext::For_loop_stmContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IMQLangParser::For_loop_stmContext::FOR() {
  return getToken(IMQLangParser::FOR, 0);
}

IMQLangParser::ExpressionContext* IMQLangParser::For_loop_stmContext::expression() {
  return getRuleContext<IMQLangParser::ExpressionContext>(0);
}

tree::TerminalNode* IMQLangParser::For_loop_stmContext::SEMICOLON() {
  return getToken(IMQLangParser::SEMICOLON, 0);
}

tree::TerminalNode* IMQLangParser::For_loop_stmContext::L_BRACE() {
  return getToken(IMQLangParser::L_BRACE, 0);
}

tree::TerminalNode* IMQLangParser::For_loop_stmContext::R_BRACE() {
  return getToken(IMQLangParser::R_BRACE, 0);
}

std::vector<IMQLangParser::StatementContext *> IMQLangParser::For_loop_stmContext::statement() {
  return getRuleContexts<IMQLangParser::StatementContext>();
}

IMQLangParser::StatementContext* IMQLangParser::For_loop_stmContext::statement(size_t i) {
  return getRuleContext<IMQLangParser::StatementContext>(i);
}

IMQLangParser::StatementsContext* IMQLangParser::For_loop_stmContext::statements() {
  return getRuleContext<IMQLangParser::StatementsContext>(0);
}


size_t IMQLangParser::For_loop_stmContext::getRuleIndex() const {
  return IMQLangParser::RuleFor_loop_stm;
}

void IMQLangParser::For_loop_stmContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IMQLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFor_loop_stm(this);
}

void IMQLangParser::For_loop_stmContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IMQLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFor_loop_stm(this);
}

IMQLangParser::For_loop_stmContext* IMQLangParser::for_loop_stm() {
  For_loop_stmContext *_localctx = _tracker.createInstance<For_loop_stmContext>(_ctx, getState());
  enterRule(_localctx, 20, IMQLangParser::RuleFor_loop_stm);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(176);
    dynamic_cast<For_loop_stmContext *>(_localctx)->forToken = match(IMQLangParser::FOR);
    setState(177);
    dynamic_cast<For_loop_stmContext *>(_localctx)->init = statement();
    setState(178);
    dynamic_cast<For_loop_stmContext *>(_localctx)->expressionContext = expression();
    setState(179);
    match(IMQLangParser::SEMICOLON);
    setState(180);
    dynamic_cast<For_loop_stmContext *>(_localctx)->incr = statement();
    setState(181);
    match(IMQLangParser::L_BRACE);
    setState(185);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << IMQLangParser::SEMICOLON)
      | (1ULL << IMQLangParser::DELETE)
      | (1ULL << IMQLangParser::INPUT)
      | (1ULL << IMQLangParser::OUTPUT)
      | (1ULL << IMQLangParser::IF)
      | (1ULL << IMQLangParser::FOR)
      | (1ULL << IMQLangParser::WHILE)
      | (1ULL << IMQLangParser::L_PAREN)
      | (1ULL << IMQLangParser::L_BRACE)
      | (1ULL << IMQLangParser::NOT)
      | (1ULL << IMQLangParser::MINUS)
      | (1ULL << IMQLangParser::B_TRUE)
      | (1ULL << IMQLangParser::B_FALSE)
      | (1ULL << IMQLangParser::FLOAT)
      | (1ULL << IMQLangParser::INTEGER)
      | (1ULL << IMQLangParser::IDENT))) != 0)) {
      setState(182);
      dynamic_cast<For_loop_stmContext *>(_localctx)->statementsContext = statements();
      dynamic_cast<For_loop_stmContext *>(_localctx)->block =  createNodeFromToken<VBlock>((dynamic_cast<For_loop_stmContext *>(_localctx)->statementsContext != nullptr ? (dynamic_cast<For_loop_stmContext *>(_localctx)->statementsContext->start) : nullptr), dynamic_cast<For_loop_stmContext *>(_localctx)->statementsContext->count, dynamic_cast<For_loop_stmContext *>(_localctx)->statementsContext->stmArr);
    }
    setState(187);
    match(IMQLangParser::R_BRACE);

                dynamic_cast<For_loop_stmContext *>(_localctx)->stm =  createNodeFromToken<ForLoopStm>(dynamic_cast<For_loop_stmContext *>(_localctx)->forToken, dynamic_cast<For_loop_stmContext *>(_localctx)->init->stm, dynamic_cast<For_loop_stmContext *>(_localctx)->expressionContext->expr, dynamic_cast<For_loop_stmContext *>(_localctx)->incr->stm, _localctx->block);
            
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- While_loop_stmContext ------------------------------------------------------------------

IMQLangParser::While_loop_stmContext::While_loop_stmContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IMQLangParser::While_loop_stmContext::WHILE() {
  return getToken(IMQLangParser::WHILE, 0);
}

IMQLangParser::ExpressionContext* IMQLangParser::While_loop_stmContext::expression() {
  return getRuleContext<IMQLangParser::ExpressionContext>(0);
}

tree::TerminalNode* IMQLangParser::While_loop_stmContext::L_BRACE() {
  return getToken(IMQLangParser::L_BRACE, 0);
}

tree::TerminalNode* IMQLangParser::While_loop_stmContext::R_BRACE() {
  return getToken(IMQLangParser::R_BRACE, 0);
}

IMQLangParser::StatementsContext* IMQLangParser::While_loop_stmContext::statements() {
  return getRuleContext<IMQLangParser::StatementsContext>(0);
}


size_t IMQLangParser::While_loop_stmContext::getRuleIndex() const {
  return IMQLangParser::RuleWhile_loop_stm;
}

void IMQLangParser::While_loop_stmContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IMQLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterWhile_loop_stm(this);
}

void IMQLangParser::While_loop_stmContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IMQLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitWhile_loop_stm(this);
}

IMQLangParser::While_loop_stmContext* IMQLangParser::while_loop_stm() {
  While_loop_stmContext *_localctx = _tracker.createInstance<While_loop_stmContext>(_ctx, getState());
  enterRule(_localctx, 22, IMQLangParser::RuleWhile_loop_stm);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(190);
    dynamic_cast<While_loop_stmContext *>(_localctx)->whileToken = match(IMQLangParser::WHILE);
    setState(191);
    dynamic_cast<While_loop_stmContext *>(_localctx)->expressionContext = expression();
    setState(192);
    match(IMQLangParser::L_BRACE);
    setState(196);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << IMQLangParser::SEMICOLON)
      | (1ULL << IMQLangParser::DELETE)
      | (1ULL << IMQLangParser::INPUT)
      | (1ULL << IMQLangParser::OUTPUT)
      | (1ULL << IMQLangParser::IF)
      | (1ULL << IMQLangParser::FOR)
      | (1ULL << IMQLangParser::WHILE)
      | (1ULL << IMQLangParser::L_PAREN)
      | (1ULL << IMQLangParser::L_BRACE)
      | (1ULL << IMQLangParser::NOT)
      | (1ULL << IMQLangParser::MINUS)
      | (1ULL << IMQLangParser::B_TRUE)
      | (1ULL << IMQLangParser::B_FALSE)
      | (1ULL << IMQLangParser::FLOAT)
      | (1ULL << IMQLangParser::INTEGER)
      | (1ULL << IMQLangParser::IDENT))) != 0)) {
      setState(193);
      dynamic_cast<While_loop_stmContext *>(_localctx)->statementsContext = statements();
      dynamic_cast<While_loop_stmContext *>(_localctx)->block =  createNodeFromToken<VBlock>((dynamic_cast<While_loop_stmContext *>(_localctx)->statementsContext != nullptr ? (dynamic_cast<While_loop_stmContext *>(_localctx)->statementsContext->start) : nullptr), dynamic_cast<While_loop_stmContext *>(_localctx)->statementsContext->count, dynamic_cast<While_loop_stmContext *>(_localctx)->statementsContext->stmArr);
    }
    setState(198);
    match(IMQLangParser::R_BRACE);

                dynamic_cast<While_loop_stmContext *>(_localctx)->stm =  createNodeFromToken<WhileLoopStm>(dynamic_cast<While_loop_stmContext *>(_localctx)->whileToken, dynamic_cast<While_loop_stmContext *>(_localctx)->expressionContext->expr, _localctx->block);
            
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionContext ------------------------------------------------------------------

IMQLangParser::ExpressionContext::ExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IMQLangParser::OrExprContext* IMQLangParser::ExpressionContext::orExpr() {
  return getRuleContext<IMQLangParser::OrExprContext>(0);
}


size_t IMQLangParser::ExpressionContext::getRuleIndex() const {
  return IMQLangParser::RuleExpression;
}

void IMQLangParser::ExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IMQLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpression(this);
}

void IMQLangParser::ExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IMQLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpression(this);
}

IMQLangParser::ExpressionContext* IMQLangParser::expression() {
  ExpressionContext *_localctx = _tracker.createInstance<ExpressionContext>(_ctx, getState());
  enterRule(_localctx, 24, IMQLangParser::RuleExpression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(201);
    dynamic_cast<ExpressionContext *>(_localctx)->orExprContext = orExpr();
    dynamic_cast<ExpressionContext *>(_localctx)->expr =  dynamic_cast<ExpressionContext *>(_localctx)->orExprContext->expr;
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OrExprContext ------------------------------------------------------------------

IMQLangParser::OrExprContext::OrExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IMQLangParser::AndExprContext* IMQLangParser::OrExprContext::andExpr() {
  return getRuleContext<IMQLangParser::AndExprContext>(0);
}

tree::TerminalNode* IMQLangParser::OrExprContext::OR() {
  return getToken(IMQLangParser::OR, 0);
}

IMQLangParser::OrExprContext* IMQLangParser::OrExprContext::orExpr() {
  return getRuleContext<IMQLangParser::OrExprContext>(0);
}


size_t IMQLangParser::OrExprContext::getRuleIndex() const {
  return IMQLangParser::RuleOrExpr;
}

void IMQLangParser::OrExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IMQLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOrExpr(this);
}

void IMQLangParser::OrExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IMQLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOrExpr(this);
}

IMQLangParser::OrExprContext* IMQLangParser::orExpr() {
  OrExprContext *_localctx = _tracker.createInstance<OrExprContext>(_ctx, getState());
  enterRule(_localctx, 26, IMQLangParser::RuleOrExpr);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(212);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(204);
      dynamic_cast<OrExprContext *>(_localctx)->andExprContext = andExpr();
      dynamic_cast<OrExprContext *>(_localctx)->expr =  dynamic_cast<OrExprContext *>(_localctx)->andExprContext->expr;
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(207);
      dynamic_cast<OrExprContext *>(_localctx)->andExprContext = andExpr();
      setState(208);
      match(IMQLangParser::OR);
      setState(209);
      dynamic_cast<OrExprContext *>(_localctx)->orExprContext = orExpr();
      dynamic_cast<OrExprContext *>(_localctx)->expr =  createNodeFromToken<OrExpr>((dynamic_cast<OrExprContext *>(_localctx)->andExprContext != nullptr ? (dynamic_cast<OrExprContext *>(_localctx)->andExprContext->start) : nullptr), dynamic_cast<OrExprContext *>(_localctx)->andExprContext->expr, dynamic_cast<OrExprContext *>(_localctx)->orExprContext->expr);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AndExprContext ------------------------------------------------------------------

IMQLangParser::AndExprContext::AndExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IMQLangParser::EqualityExprContext* IMQLangParser::AndExprContext::equalityExpr() {
  return getRuleContext<IMQLangParser::EqualityExprContext>(0);
}

tree::TerminalNode* IMQLangParser::AndExprContext::AND() {
  return getToken(IMQLangParser::AND, 0);
}

IMQLangParser::AndExprContext* IMQLangParser::AndExprContext::andExpr() {
  return getRuleContext<IMQLangParser::AndExprContext>(0);
}


size_t IMQLangParser::AndExprContext::getRuleIndex() const {
  return IMQLangParser::RuleAndExpr;
}

void IMQLangParser::AndExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IMQLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAndExpr(this);
}

void IMQLangParser::AndExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IMQLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAndExpr(this);
}

IMQLangParser::AndExprContext* IMQLangParser::andExpr() {
  AndExprContext *_localctx = _tracker.createInstance<AndExprContext>(_ctx, getState());
  enterRule(_localctx, 28, IMQLangParser::RuleAndExpr);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(222);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(214);
      dynamic_cast<AndExprContext *>(_localctx)->equalityExprContext = equalityExpr();
      dynamic_cast<AndExprContext *>(_localctx)->expr =  dynamic_cast<AndExprContext *>(_localctx)->equalityExprContext->expr;
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(217);
      dynamic_cast<AndExprContext *>(_localctx)->equalityExprContext = equalityExpr();
      setState(218);
      match(IMQLangParser::AND);
      setState(219);
      dynamic_cast<AndExprContext *>(_localctx)->andExprContext = andExpr();
      dynamic_cast<AndExprContext *>(_localctx)->expr =  createNodeFromToken<AndExpr>((dynamic_cast<AndExprContext *>(_localctx)->equalityExprContext != nullptr ? (dynamic_cast<AndExprContext *>(_localctx)->equalityExprContext->start) : nullptr), dynamic_cast<AndExprContext *>(_localctx)->equalityExprContext->expr, dynamic_cast<AndExprContext *>(_localctx)->andExprContext->expr);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EqualityExprContext ------------------------------------------------------------------

IMQLangParser::EqualityExprContext::EqualityExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IMQLangParser::AddExprContext* IMQLangParser::EqualityExprContext::addExpr() {
  return getRuleContext<IMQLangParser::AddExprContext>(0);
}

std::vector<tree::TerminalNode *> IMQLangParser::EqualityExprContext::EQUAL() {
  return getTokens(IMQLangParser::EQUAL);
}

tree::TerminalNode* IMQLangParser::EqualityExprContext::EQUAL(size_t i) {
  return getToken(IMQLangParser::EQUAL, i);
}

IMQLangParser::EqualityExprContext* IMQLangParser::EqualityExprContext::equalityExpr() {
  return getRuleContext<IMQLangParser::EqualityExprContext>(0);
}

tree::TerminalNode* IMQLangParser::EqualityExprContext::BANG() {
  return getToken(IMQLangParser::BANG, 0);
}

tree::TerminalNode* IMQLangParser::EqualityExprContext::LESS() {
  return getToken(IMQLangParser::LESS, 0);
}

tree::TerminalNode* IMQLangParser::EqualityExprContext::GREATER() {
  return getToken(IMQLangParser::GREATER, 0);
}


size_t IMQLangParser::EqualityExprContext::getRuleIndex() const {
  return IMQLangParser::RuleEqualityExpr;
}

void IMQLangParser::EqualityExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IMQLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEqualityExpr(this);
}

void IMQLangParser::EqualityExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IMQLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEqualityExpr(this);
}

IMQLangParser::EqualityExprContext* IMQLangParser::equalityExpr() {
  EqualityExprContext *_localctx = _tracker.createInstance<EqualityExprContext>(_ctx, getState());
  enterRule(_localctx, 30, IMQLangParser::RuleEqualityExpr);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(261);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(224);
      dynamic_cast<EqualityExprContext *>(_localctx)->addExprContext = addExpr();
      dynamic_cast<EqualityExprContext *>(_localctx)->expr =  dynamic_cast<EqualityExprContext *>(_localctx)->addExprContext->expr;
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(227);
      dynamic_cast<EqualityExprContext *>(_localctx)->addExprContext = addExpr();
      setState(228);
      match(IMQLangParser::EQUAL);
      setState(229);
      match(IMQLangParser::EQUAL);
      setState(230);
      dynamic_cast<EqualityExprContext *>(_localctx)->equalityExprContext = equalityExpr();
      dynamic_cast<EqualityExprContext *>(_localctx)->expr =  createNodeFromToken<EqualExpr>((dynamic_cast<EqualityExprContext *>(_localctx)->addExprContext != nullptr ? (dynamic_cast<EqualityExprContext *>(_localctx)->addExprContext->start) : nullptr), dynamic_cast<EqualityExprContext *>(_localctx)->addExprContext->expr, dynamic_cast<EqualityExprContext *>(_localctx)->equalityExprContext->expr);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(233);
      dynamic_cast<EqualityExprContext *>(_localctx)->addExprContext = addExpr();
      setState(234);
      match(IMQLangParser::BANG);
      setState(235);
      match(IMQLangParser::EQUAL);
      setState(236);
      dynamic_cast<EqualityExprContext *>(_localctx)->equalityExprContext = equalityExpr();
      dynamic_cast<EqualityExprContext *>(_localctx)->expr =  createNodeFromToken<NotEqualExpr>((dynamic_cast<EqualityExprContext *>(_localctx)->addExprContext != nullptr ? (dynamic_cast<EqualityExprContext *>(_localctx)->addExprContext->start) : nullptr), dynamic_cast<EqualityExprContext *>(_localctx)->addExprContext->expr, dynamic_cast<EqualityExprContext *>(_localctx)->equalityExprContext->expr);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(239);
      dynamic_cast<EqualityExprContext *>(_localctx)->addExprContext = addExpr();
      setState(240);
      match(IMQLangParser::LESS);
      setState(241);
      dynamic_cast<EqualityExprContext *>(_localctx)->equalityExprContext = equalityExpr();
      dynamic_cast<EqualityExprContext *>(_localctx)->expr =  createNodeFromToken<LessExpr>((dynamic_cast<EqualityExprContext *>(_localctx)->addExprContext != nullptr ? (dynamic_cast<EqualityExprContext *>(_localctx)->addExprContext->start) : nullptr), dynamic_cast<EqualityExprContext *>(_localctx)->addExprContext->expr, dynamic_cast<EqualityExprContext *>(_localctx)->equalityExprContext->expr);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(244);
      dynamic_cast<EqualityExprContext *>(_localctx)->addExprContext = addExpr();
      setState(245);
      match(IMQLangParser::LESS);
      setState(246);
      match(IMQLangParser::EQUAL);
      setState(247);
      dynamic_cast<EqualityExprContext *>(_localctx)->equalityExprContext = equalityExpr();
      dynamic_cast<EqualityExprContext *>(_localctx)->expr =  createNodeFromToken<LessEqExpr>((dynamic_cast<EqualityExprContext *>(_localctx)->addExprContext != nullptr ? (dynamic_cast<EqualityExprContext *>(_localctx)->addExprContext->start) : nullptr), dynamic_cast<EqualityExprContext *>(_localctx)->addExprContext->expr, dynamic_cast<EqualityExprContext *>(_localctx)->equalityExprContext->expr);
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(250);
      dynamic_cast<EqualityExprContext *>(_localctx)->addExprContext = addExpr();
      setState(251);
      match(IMQLangParser::GREATER);
      setState(252);
      dynamic_cast<EqualityExprContext *>(_localctx)->equalityExprContext = equalityExpr();
      dynamic_cast<EqualityExprContext *>(_localctx)->expr =  createNodeFromToken<GreaterExpr>((dynamic_cast<EqualityExprContext *>(_localctx)->addExprContext != nullptr ? (dynamic_cast<EqualityExprContext *>(_localctx)->addExprContext->start) : nullptr), dynamic_cast<EqualityExprContext *>(_localctx)->addExprContext->expr, dynamic_cast<EqualityExprContext *>(_localctx)->equalityExprContext->expr);
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(255);
      dynamic_cast<EqualityExprContext *>(_localctx)->addExprContext = addExpr();
      setState(256);
      match(IMQLangParser::GREATER);
      setState(257);
      match(IMQLangParser::EQUAL);
      setState(258);
      dynamic_cast<EqualityExprContext *>(_localctx)->equalityExprContext = equalityExpr();
      dynamic_cast<EqualityExprContext *>(_localctx)->expr =  createNodeFromToken<GreaterEqExpr>((dynamic_cast<EqualityExprContext *>(_localctx)->addExprContext != nullptr ? (dynamic_cast<EqualityExprContext *>(_localctx)->addExprContext->start) : nullptr), dynamic_cast<EqualityExprContext *>(_localctx)->addExprContext->expr, dynamic_cast<EqualityExprContext *>(_localctx)->equalityExprContext->expr);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AddExprContext ------------------------------------------------------------------

IMQLangParser::AddExprContext::AddExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IMQLangParser::MulExprContext* IMQLangParser::AddExprContext::mulExpr() {
  return getRuleContext<IMQLangParser::MulExprContext>(0);
}

tree::TerminalNode* IMQLangParser::AddExprContext::PLUS() {
  return getToken(IMQLangParser::PLUS, 0);
}

IMQLangParser::AddExprContext* IMQLangParser::AddExprContext::addExpr() {
  return getRuleContext<IMQLangParser::AddExprContext>(0);
}

tree::TerminalNode* IMQLangParser::AddExprContext::MINUS() {
  return getToken(IMQLangParser::MINUS, 0);
}


size_t IMQLangParser::AddExprContext::getRuleIndex() const {
  return IMQLangParser::RuleAddExpr;
}

void IMQLangParser::AddExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IMQLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAddExpr(this);
}

void IMQLangParser::AddExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IMQLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAddExpr(this);
}

IMQLangParser::AddExprContext* IMQLangParser::addExpr() {
  AddExprContext *_localctx = _tracker.createInstance<AddExprContext>(_ctx, getState());
  enterRule(_localctx, 32, IMQLangParser::RuleAddExpr);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(276);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(263);
      dynamic_cast<AddExprContext *>(_localctx)->mulExprContext = mulExpr();
      dynamic_cast<AddExprContext *>(_localctx)->expr =  dynamic_cast<AddExprContext *>(_localctx)->mulExprContext->expr;
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(266);
      dynamic_cast<AddExprContext *>(_localctx)->mulExprContext = mulExpr();
      setState(267);
      match(IMQLangParser::PLUS);
      setState(268);
      dynamic_cast<AddExprContext *>(_localctx)->addExprContext = addExpr();
      dynamic_cast<AddExprContext *>(_localctx)->expr =  createNodeFromToken<AddExpr>((dynamic_cast<AddExprContext *>(_localctx)->mulExprContext != nullptr ? (dynamic_cast<AddExprContext *>(_localctx)->mulExprContext->start) : nullptr), dynamic_cast<AddExprContext *>(_localctx)->mulExprContext->expr, dynamic_cast<AddExprContext *>(_localctx)->addExprContext->expr);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(271);
      dynamic_cast<AddExprContext *>(_localctx)->mulExprContext = mulExpr();
      setState(272);
      match(IMQLangParser::MINUS);
      setState(273);
      dynamic_cast<AddExprContext *>(_localctx)->addExprContext = addExpr();
      dynamic_cast<AddExprContext *>(_localctx)->expr =  createNodeFromToken<SubExpr>((dynamic_cast<AddExprContext *>(_localctx)->mulExprContext != nullptr ? (dynamic_cast<AddExprContext *>(_localctx)->mulExprContext->start) : nullptr), dynamic_cast<AddExprContext *>(_localctx)->mulExprContext->expr, dynamic_cast<AddExprContext *>(_localctx)->addExprContext->expr);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MulExprContext ------------------------------------------------------------------

IMQLangParser::MulExprContext::MulExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IMQLangParser::NotExprContext* IMQLangParser::MulExprContext::notExpr() {
  return getRuleContext<IMQLangParser::NotExprContext>(0);
}

tree::TerminalNode* IMQLangParser::MulExprContext::MULTIPLY() {
  return getToken(IMQLangParser::MULTIPLY, 0);
}

IMQLangParser::MulExprContext* IMQLangParser::MulExprContext::mulExpr() {
  return getRuleContext<IMQLangParser::MulExprContext>(0);
}

tree::TerminalNode* IMQLangParser::MulExprContext::DIVIDE() {
  return getToken(IMQLangParser::DIVIDE, 0);
}

tree::TerminalNode* IMQLangParser::MulExprContext::MODULUS() {
  return getToken(IMQLangParser::MODULUS, 0);
}


size_t IMQLangParser::MulExprContext::getRuleIndex() const {
  return IMQLangParser::RuleMulExpr;
}

void IMQLangParser::MulExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IMQLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMulExpr(this);
}

void IMQLangParser::MulExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IMQLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMulExpr(this);
}

IMQLangParser::MulExprContext* IMQLangParser::mulExpr() {
  MulExprContext *_localctx = _tracker.createInstance<MulExprContext>(_ctx, getState());
  enterRule(_localctx, 34, IMQLangParser::RuleMulExpr);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(296);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(278);
      dynamic_cast<MulExprContext *>(_localctx)->notExprContext = notExpr();
      dynamic_cast<MulExprContext *>(_localctx)->expr =  dynamic_cast<MulExprContext *>(_localctx)->notExprContext->expr;
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(281);
      dynamic_cast<MulExprContext *>(_localctx)->notExprContext = notExpr();
      setState(282);
      match(IMQLangParser::MULTIPLY);
      setState(283);
      dynamic_cast<MulExprContext *>(_localctx)->mulExprContext = mulExpr();
      dynamic_cast<MulExprContext *>(_localctx)->expr =  createNodeFromToken<MulExpr>((dynamic_cast<MulExprContext *>(_localctx)->notExprContext != nullptr ? (dynamic_cast<MulExprContext *>(_localctx)->notExprContext->start) : nullptr), dynamic_cast<MulExprContext *>(_localctx)->notExprContext->expr, dynamic_cast<MulExprContext *>(_localctx)->mulExprContext->expr);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(286);
      dynamic_cast<MulExprContext *>(_localctx)->notExprContext = notExpr();
      setState(287);
      match(IMQLangParser::DIVIDE);
      setState(288);
      dynamic_cast<MulExprContext *>(_localctx)->mulExprContext = mulExpr();
      dynamic_cast<MulExprContext *>(_localctx)->expr =  createNodeFromToken<DivExpr>((dynamic_cast<MulExprContext *>(_localctx)->notExprContext != nullptr ? (dynamic_cast<MulExprContext *>(_localctx)->notExprContext->start) : nullptr), dynamic_cast<MulExprContext *>(_localctx)->notExprContext->expr, dynamic_cast<MulExprContext *>(_localctx)->mulExprContext->expr);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(291);
      dynamic_cast<MulExprContext *>(_localctx)->notExprContext = notExpr();
      setState(292);
      match(IMQLangParser::MODULUS);
      setState(293);
      dynamic_cast<MulExprContext *>(_localctx)->mulExprContext = mulExpr();
      dynamic_cast<MulExprContext *>(_localctx)->expr =  createNodeFromToken<ModExpr>((dynamic_cast<MulExprContext *>(_localctx)->notExprContext != nullptr ? (dynamic_cast<MulExprContext *>(_localctx)->notExprContext->start) : nullptr), dynamic_cast<MulExprContext *>(_localctx)->notExprContext->expr, dynamic_cast<MulExprContext *>(_localctx)->mulExprContext->expr);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NotExprContext ------------------------------------------------------------------

IMQLangParser::NotExprContext::NotExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IMQLangParser::NotExprContext::NOT() {
  return getToken(IMQLangParser::NOT, 0);
}

IMQLangParser::NotExprContext* IMQLangParser::NotExprContext::notExpr() {
  return getRuleContext<IMQLangParser::NotExprContext>(0);
}

tree::TerminalNode* IMQLangParser::NotExprContext::MINUS() {
  return getToken(IMQLangParser::MINUS, 0);
}

IMQLangParser::AtomContext* IMQLangParser::NotExprContext::atom() {
  return getRuleContext<IMQLangParser::AtomContext>(0);
}


size_t IMQLangParser::NotExprContext::getRuleIndex() const {
  return IMQLangParser::RuleNotExpr;
}

void IMQLangParser::NotExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IMQLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNotExpr(this);
}

void IMQLangParser::NotExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IMQLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNotExpr(this);
}

IMQLangParser::NotExprContext* IMQLangParser::notExpr() {
  NotExprContext *_localctx = _tracker.createInstance<NotExprContext>(_ctx, getState());
  enterRule(_localctx, 36, IMQLangParser::RuleNotExpr);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(309);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case IMQLangParser::NOT: {
        enterOuterAlt(_localctx, 1);
        setState(298);
        dynamic_cast<NotExprContext *>(_localctx)->notToken = match(IMQLangParser::NOT);
        setState(299);
        dynamic_cast<NotExprContext *>(_localctx)->notExprContext = notExpr();
        dynamic_cast<NotExprContext *>(_localctx)->expr =  createNodeFromToken<NotExpr>(dynamic_cast<NotExprContext *>(_localctx)->notToken, dynamic_cast<NotExprContext *>(_localctx)->notExprContext->expr);
        break;
      }

      case IMQLangParser::MINUS: {
        enterOuterAlt(_localctx, 2);
        setState(302);
        dynamic_cast<NotExprContext *>(_localctx)->minusToken = match(IMQLangParser::MINUS);
        setState(303);
        dynamic_cast<NotExprContext *>(_localctx)->notExprContext = notExpr();
        dynamic_cast<NotExprContext *>(_localctx)->expr =  createNodeFromToken<NegateExpr>(dynamic_cast<NotExprContext *>(_localctx)->minusToken, dynamic_cast<NotExprContext *>(_localctx)->notExprContext->expr);
        break;
      }

      case IMQLangParser::L_PAREN:
      case IMQLangParser::L_BRACE:
      case IMQLangParser::B_TRUE:
      case IMQLangParser::B_FALSE:
      case IMQLangParser::FLOAT:
      case IMQLangParser::INTEGER:
      case IMQLangParser::IDENT: {
        enterOuterAlt(_localctx, 3);
        setState(306);
        dynamic_cast<NotExprContext *>(_localctx)->atomContext = atom();
        dynamic_cast<NotExprContext *>(_localctx)->expr =  dynamic_cast<NotExprContext *>(_localctx)->atomContext->expr;
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AtomContext ------------------------------------------------------------------

IMQLangParser::AtomContext::AtomContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IMQLangParser::ValueContext* IMQLangParser::AtomContext::value() {
  return getRuleContext<IMQLangParser::ValueContext>(0);
}

IMQLangParser::VariableContext* IMQLangParser::AtomContext::variable() {
  return getRuleContext<IMQLangParser::VariableContext>(0);
}

tree::TerminalNode* IMQLangParser::AtomContext::L_PAREN() {
  return getToken(IMQLangParser::L_PAREN, 0);
}

IMQLangParser::ExpressionContext* IMQLangParser::AtomContext::expression() {
  return getRuleContext<IMQLangParser::ExpressionContext>(0);
}

tree::TerminalNode* IMQLangParser::AtomContext::R_PAREN() {
  return getToken(IMQLangParser::R_PAREN, 0);
}


size_t IMQLangParser::AtomContext::getRuleIndex() const {
  return IMQLangParser::RuleAtom;
}

void IMQLangParser::AtomContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IMQLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAtom(this);
}

void IMQLangParser::AtomContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IMQLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAtom(this);
}

IMQLangParser::AtomContext* IMQLangParser::atom() {
  AtomContext *_localctx = _tracker.createInstance<AtomContext>(_ctx, getState());
  enterRule(_localctx, 38, IMQLangParser::RuleAtom);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(322);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case IMQLangParser::L_BRACE:
      case IMQLangParser::B_TRUE:
      case IMQLangParser::B_FALSE:
      case IMQLangParser::FLOAT:
      case IMQLangParser::INTEGER: {
        enterOuterAlt(_localctx, 1);
        setState(311);
        dynamic_cast<AtomContext *>(_localctx)->valueContext = value();
        dynamic_cast<AtomContext *>(_localctx)->expr =  dynamic_cast<AtomContext *>(_localctx)->valueContext->expr;
        break;
      }

      case IMQLangParser::IDENT: {
        enterOuterAlt(_localctx, 2);
        setState(314);
        dynamic_cast<AtomContext *>(_localctx)->variableContext = variable();
        dynamic_cast<AtomContext *>(_localctx)->expr =  dynamic_cast<AtomContext *>(_localctx)->variableContext->expr;
        break;
      }

      case IMQLangParser::L_PAREN: {
        enterOuterAlt(_localctx, 3);
        setState(317);
        match(IMQLangParser::L_PAREN);
        setState(318);
        dynamic_cast<AtomContext *>(_localctx)->expressionContext = expression();
        setState(319);
        match(IMQLangParser::R_PAREN);
        dynamic_cast<AtomContext *>(_localctx)->expr =  dynamic_cast<AtomContext *>(_localctx)->expressionContext->expr;
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ValueContext ------------------------------------------------------------------

IMQLangParser::ValueContext::ValueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IMQLangParser::Const_valueContext* IMQLangParser::ValueContext::const_value() {
  return getRuleContext<IMQLangParser::Const_valueContext>(0);
}

IMQLangParser::ColorContext* IMQLangParser::ValueContext::color() {
  return getRuleContext<IMQLangParser::ColorContext>(0);
}


size_t IMQLangParser::ValueContext::getRuleIndex() const {
  return IMQLangParser::RuleValue;
}

void IMQLangParser::ValueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IMQLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterValue(this);
}

void IMQLangParser::ValueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IMQLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitValue(this);
}

IMQLangParser::ValueContext* IMQLangParser::value() {
  ValueContext *_localctx = _tracker.createInstance<ValueContext>(_ctx, getState());
  enterRule(_localctx, 40, IMQLangParser::RuleValue);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(330);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case IMQLangParser::B_TRUE:
      case IMQLangParser::B_FALSE:
      case IMQLangParser::FLOAT:
      case IMQLangParser::INTEGER: {
        enterOuterAlt(_localctx, 1);
        setState(324);
        dynamic_cast<ValueContext *>(_localctx)->const_valueContext = const_value();
        dynamic_cast<ValueContext *>(_localctx)->expr =  createNodeFromToken<ConstantExpr>((dynamic_cast<ValueContext *>(_localctx)->const_valueContext != nullptr ? (dynamic_cast<ValueContext *>(_localctx)->const_valueContext->start) : nullptr), dynamic_cast<ValueContext *>(_localctx)->const_valueContext->val);
        break;
      }

      case IMQLangParser::L_BRACE: {
        enterOuterAlt(_localctx, 2);
        setState(327);
        dynamic_cast<ValueContext *>(_localctx)->colorContext = color();
        dynamic_cast<ValueContext *>(_localctx)->expr =  dynamic_cast<ValueContext *>(_localctx)->colorContext->expr;
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Const_valueContext ------------------------------------------------------------------

IMQLangParser::Const_valueContext::Const_valueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IMQLangParser::Const_valueContext::INTEGER() {
  return getToken(IMQLangParser::INTEGER, 0);
}

tree::TerminalNode* IMQLangParser::Const_valueContext::FLOAT() {
  return getToken(IMQLangParser::FLOAT, 0);
}

IMQLangParser::BooleanContext* IMQLangParser::Const_valueContext::boolean() {
  return getRuleContext<IMQLangParser::BooleanContext>(0);
}


size_t IMQLangParser::Const_valueContext::getRuleIndex() const {
  return IMQLangParser::RuleConst_value;
}

void IMQLangParser::Const_valueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IMQLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConst_value(this);
}

void IMQLangParser::Const_valueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IMQLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConst_value(this);
}

IMQLangParser::Const_valueContext* IMQLangParser::const_value() {
  Const_valueContext *_localctx = _tracker.createInstance<Const_valueContext>(_ctx, getState());
  enterRule(_localctx, 42, IMQLangParser::RuleConst_value);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(339);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case IMQLangParser::INTEGER: {
        enterOuterAlt(_localctx, 1);
        setState(332);
        dynamic_cast<Const_valueContext *>(_localctx)->integerToken = match(IMQLangParser::INTEGER);
        dynamic_cast<Const_valueContext *>(_localctx)->val =  QValue::Integer(std::stoi((dynamic_cast<Const_valueContext *>(_localctx)->integerToken != nullptr ? dynamic_cast<Const_valueContext *>(_localctx)->integerToken->getText() : "")));
        break;
      }

      case IMQLangParser::FLOAT: {
        enterOuterAlt(_localctx, 2);
        setState(334);
        dynamic_cast<Const_valueContext *>(_localctx)->floatToken = match(IMQLangParser::FLOAT);
        dynamic_cast<Const_valueContext *>(_localctx)->val =  QValue::Float(std::stof((dynamic_cast<Const_valueContext *>(_localctx)->floatToken != nullptr ? dynamic_cast<Const_valueContext *>(_localctx)->floatToken->getText() : "")));
        break;
      }

      case IMQLangParser::B_TRUE:
      case IMQLangParser::B_FALSE: {
        enterOuterAlt(_localctx, 3);
        setState(336);
        dynamic_cast<Const_valueContext *>(_localctx)->booleanContext = boolean();
        dynamic_cast<Const_valueContext *>(_localctx)->val =  QValue::Bool(dynamic_cast<Const_valueContext *>(_localctx)->booleanContext->val);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BooleanContext ------------------------------------------------------------------

IMQLangParser::BooleanContext::BooleanContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IMQLangParser::BooleanContext::B_TRUE() {
  return getToken(IMQLangParser::B_TRUE, 0);
}

tree::TerminalNode* IMQLangParser::BooleanContext::B_FALSE() {
  return getToken(IMQLangParser::B_FALSE, 0);
}


size_t IMQLangParser::BooleanContext::getRuleIndex() const {
  return IMQLangParser::RuleBoolean;
}

void IMQLangParser::BooleanContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IMQLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBoolean(this);
}

void IMQLangParser::BooleanContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IMQLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBoolean(this);
}

IMQLangParser::BooleanContext* IMQLangParser::boolean() {
  BooleanContext *_localctx = _tracker.createInstance<BooleanContext>(_ctx, getState());
  enterRule(_localctx, 44, IMQLangParser::RuleBoolean);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(345);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case IMQLangParser::B_TRUE: {
        enterOuterAlt(_localctx, 1);
        setState(341);
        match(IMQLangParser::B_TRUE);
        dynamic_cast<BooleanContext *>(_localctx)->val =  true;
        break;
      }

      case IMQLangParser::B_FALSE: {
        enterOuterAlt(_localctx, 2);
        setState(343);
        match(IMQLangParser::B_FALSE);
        dynamic_cast<BooleanContext *>(_localctx)->val =  false;
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ColorContext ------------------------------------------------------------------

IMQLangParser::ColorContext::ColorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IMQLangParser::ColorContext::L_BRACE() {
  return getToken(IMQLangParser::L_BRACE, 0);
}

tree::TerminalNode* IMQLangParser::ColorContext::R_BRACE() {
  return getToken(IMQLangParser::R_BRACE, 0);
}

std::vector<tree::TerminalNode *> IMQLangParser::ColorContext::COMMA() {
  return getTokens(IMQLangParser::COMMA);
}

tree::TerminalNode* IMQLangParser::ColorContext::COMMA(size_t i) {
  return getToken(IMQLangParser::COMMA, i);
}

std::vector<IMQLangParser::ExpressionContext *> IMQLangParser::ColorContext::expression() {
  return getRuleContexts<IMQLangParser::ExpressionContext>();
}

IMQLangParser::ExpressionContext* IMQLangParser::ColorContext::expression(size_t i) {
  return getRuleContext<IMQLangParser::ExpressionContext>(i);
}


size_t IMQLangParser::ColorContext::getRuleIndex() const {
  return IMQLangParser::RuleColor;
}

void IMQLangParser::ColorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IMQLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterColor(this);
}

void IMQLangParser::ColorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IMQLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitColor(this);
}

IMQLangParser::ColorContext* IMQLangParser::color() {
  ColorContext *_localctx = _tracker.createInstance<ColorContext>(_ctx, getState());
  enterRule(_localctx, 46, IMQLangParser::RuleColor);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(347);
    dynamic_cast<ColorContext *>(_localctx)->l_braceToken = match(IMQLangParser::L_BRACE);
    setState(358);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx)) {
    case 1: {
      setState(348);
      dynamic_cast<ColorContext *>(_localctx)->r = expression();
      dynamic_cast<ColorContext *>(_localctx)->rExpr =  dynamic_cast<ColorContext *>(_localctx)->r->expr;
      break;
    }

    case 2: {
      setState(351);
      dynamic_cast<ColorContext *>(_localctx)->r = expression();
      setState(352);
      match(IMQLangParser::COMMA);
      setState(353);
      dynamic_cast<ColorContext *>(_localctx)->g = expression();
      setState(354);
      match(IMQLangParser::COMMA);
      setState(355);
      dynamic_cast<ColorContext *>(_localctx)->b = expression();

              dynamic_cast<ColorContext *>(_localctx)->rExpr =  dynamic_cast<ColorContext *>(_localctx)->r->expr;
              dynamic_cast<ColorContext *>(_localctx)->gExpr =  dynamic_cast<ColorContext *>(_localctx)->g->expr;
              dynamic_cast<ColorContext *>(_localctx)->bExpr =  dynamic_cast<ColorContext *>(_localctx)->b->expr;
          
      break;
    }

    }
    setState(364);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IMQLangParser::COMMA) {
      setState(360);
      match(IMQLangParser::COMMA);
      setState(361);
      dynamic_cast<ColorContext *>(_localctx)->a = expression();
      dynamic_cast<ColorContext *>(_localctx)->aExpr =  dynamic_cast<ColorContext *>(_localctx)->a->expr;
    }
    setState(366);
    match(IMQLangParser::R_BRACE);
    dynamic_cast<ColorContext *>(_localctx)->expr =  createNodeFromToken<ColorExpr>(dynamic_cast<ColorContext *>(_localctx)->l_braceToken, _localctx->rExpr, _localctx->gExpr, _localctx->bExpr, _localctx->aExpr);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VariableContext ------------------------------------------------------------------

IMQLangParser::VariableContext::VariableContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IMQLangParser::Resolved_variableContext* IMQLangParser::VariableContext::resolved_variable() {
  return getRuleContext<IMQLangParser::Resolved_variableContext>(0);
}

std::vector<tree::TerminalNode *> IMQLangParser::VariableContext::DOT() {
  return getTokens(IMQLangParser::DOT);
}

tree::TerminalNode* IMQLangParser::VariableContext::DOT(size_t i) {
  return getToken(IMQLangParser::DOT, i);
}

std::vector<IMQLangParser::Resolved_fieldContext *> IMQLangParser::VariableContext::resolved_field() {
  return getRuleContexts<IMQLangParser::Resolved_fieldContext>();
}

IMQLangParser::Resolved_fieldContext* IMQLangParser::VariableContext::resolved_field(size_t i) {
  return getRuleContext<IMQLangParser::Resolved_fieldContext>(i);
}


size_t IMQLangParser::VariableContext::getRuleIndex() const {
  return IMQLangParser::RuleVariable;
}

void IMQLangParser::VariableContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IMQLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVariable(this);
}

void IMQLangParser::VariableContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IMQLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVariable(this);
}

IMQLangParser::VariableContext* IMQLangParser::variable() {
  VariableContext *_localctx = _tracker.createInstance<VariableContext>(_ctx, getState());
  enterRule(_localctx, 48, IMQLangParser::RuleVariable);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(369);
    dynamic_cast<VariableContext *>(_localctx)->resolved_variableContext = resolved_variable();
    dynamic_cast<VariableContext *>(_localctx)->expr =  dynamic_cast<VariableContext *>(_localctx)->resolved_variableContext->expr;
    setState(377);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(371);
        match(IMQLangParser::DOT);
        setState(372);
        dynamic_cast<VariableContext *>(_localctx)->resolved_fieldContext = resolved_field(_localctx->expr);
        dynamic_cast<VariableContext *>(_localctx)->expr =  dynamic_cast<VariableContext *>(_localctx)->resolved_fieldContext->expr; 
      }
      setState(379);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Resolved_variableContext ------------------------------------------------------------------

IMQLangParser::Resolved_variableContext::Resolved_variableContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IMQLangParser::Resolved_variableContext::IDENT() {
  return getToken(IMQLangParser::IDENT, 0);
}

IMQLangParser::Func_parametersContext* IMQLangParser::Resolved_variableContext::func_parameters() {
  return getRuleContext<IMQLangParser::Func_parametersContext>(0);
}

IMQLangParser::Index_parametersContext* IMQLangParser::Resolved_variableContext::index_parameters() {
  return getRuleContext<IMQLangParser::Index_parametersContext>(0);
}


size_t IMQLangParser::Resolved_variableContext::getRuleIndex() const {
  return IMQLangParser::RuleResolved_variable;
}

void IMQLangParser::Resolved_variableContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IMQLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterResolved_variable(this);
}

void IMQLangParser::Resolved_variableContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IMQLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitResolved_variable(this);
}

IMQLangParser::Resolved_variableContext* IMQLangParser::resolved_variable() {
  Resolved_variableContext *_localctx = _tracker.createInstance<Resolved_variableContext>(_ctx, getState());
  enterRule(_localctx, 50, IMQLangParser::RuleResolved_variable);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(390);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 22, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(380);
      dynamic_cast<Resolved_variableContext *>(_localctx)->identToken = match(IMQLangParser::IDENT);
      dynamic_cast<Resolved_variableContext *>(_localctx)->expr =  createNodeFromToken<RetrieveVariableExpr>(dynamic_cast<Resolved_variableContext *>(_localctx)->identToken, (dynamic_cast<Resolved_variableContext *>(_localctx)->identToken != nullptr ? dynamic_cast<Resolved_variableContext *>(_localctx)->identToken->getText() : ""));
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(382);
      dynamic_cast<Resolved_variableContext *>(_localctx)->identToken = match(IMQLangParser::IDENT);
      setState(383);
      dynamic_cast<Resolved_variableContext *>(_localctx)->func_parametersContext = func_parameters();

                  dynamic_cast<Resolved_variableContext *>(_localctx)->expr =  createNodeFromToken<CallFunctionExpr>(
                      dynamic_cast<Resolved_variableContext *>(_localctx)->identToken,
                      createNodeFromToken<RetrieveVariableExpr>(dynamic_cast<Resolved_variableContext *>(_localctx)->identToken, (dynamic_cast<Resolved_variableContext *>(_localctx)->identToken != nullptr ? dynamic_cast<Resolved_variableContext *>(_localctx)->identToken->getText() : "")),
                      dynamic_cast<Resolved_variableContext *>(_localctx)->func_parametersContext->count,
                      dynamic_cast<Resolved_variableContext *>(_localctx)->func_parametersContext->args
                  );
              
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(386);
      dynamic_cast<Resolved_variableContext *>(_localctx)->identToken = match(IMQLangParser::IDENT);
      setState(387);
      dynamic_cast<Resolved_variableContext *>(_localctx)->index_parametersContext = index_parameters();

                  dynamic_cast<Resolved_variableContext *>(_localctx)->expr =  createNodeFromToken<RetrieveIndexExpr>(
                      dynamic_cast<Resolved_variableContext *>(_localctx)->identToken,
                      createNodeFromToken<RetrieveVariableExpr>(dynamic_cast<Resolved_variableContext *>(_localctx)->identToken, (dynamic_cast<Resolved_variableContext *>(_localctx)->identToken != nullptr ? dynamic_cast<Resolved_variableContext *>(_localctx)->identToken->getText() : "")),
                      dynamic_cast<Resolved_variableContext *>(_localctx)->index_parametersContext->expr
                  );
              
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Resolved_fieldContext ------------------------------------------------------------------

IMQLangParser::Resolved_fieldContext::Resolved_fieldContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IMQLangParser::Resolved_fieldContext::Resolved_fieldContext(ParserRuleContext *parent, size_t invokingState, VExpression* subexpr)
  : ParserRuleContext(parent, invokingState) {
  this->subexpr = subexpr;
}

tree::TerminalNode* IMQLangParser::Resolved_fieldContext::IDENT() {
  return getToken(IMQLangParser::IDENT, 0);
}

IMQLangParser::Func_parametersContext* IMQLangParser::Resolved_fieldContext::func_parameters() {
  return getRuleContext<IMQLangParser::Func_parametersContext>(0);
}

IMQLangParser::Index_parametersContext* IMQLangParser::Resolved_fieldContext::index_parameters() {
  return getRuleContext<IMQLangParser::Index_parametersContext>(0);
}


size_t IMQLangParser::Resolved_fieldContext::getRuleIndex() const {
  return IMQLangParser::RuleResolved_field;
}

void IMQLangParser::Resolved_fieldContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IMQLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterResolved_field(this);
}

void IMQLangParser::Resolved_fieldContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IMQLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitResolved_field(this);
}

IMQLangParser::Resolved_fieldContext* IMQLangParser::resolved_field(VExpression* subexpr) {
  Resolved_fieldContext *_localctx = _tracker.createInstance<Resolved_fieldContext>(_ctx, getState(), subexpr);
  enterRule(_localctx, 52, IMQLangParser::RuleResolved_field);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(402);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(392);
      dynamic_cast<Resolved_fieldContext *>(_localctx)->identToken = match(IMQLangParser::IDENT);
      dynamic_cast<Resolved_fieldContext *>(_localctx)->expr =  createNodeFromToken<RetrieveFieldExpr>(dynamic_cast<Resolved_fieldContext *>(_localctx)->identToken, _localctx->subexpr, (dynamic_cast<Resolved_fieldContext *>(_localctx)->identToken != nullptr ? dynamic_cast<Resolved_fieldContext *>(_localctx)->identToken->getText() : ""));
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(394);
      dynamic_cast<Resolved_fieldContext *>(_localctx)->identToken = match(IMQLangParser::IDENT);
      setState(395);
      dynamic_cast<Resolved_fieldContext *>(_localctx)->func_parametersContext = func_parameters();

                  dynamic_cast<Resolved_fieldContext *>(_localctx)->expr =  createNodeFromToken<CallFunctionExpr>(
                      dynamic_cast<Resolved_fieldContext *>(_localctx)->identToken,
                      createNodeFromToken<RetrieveFieldExpr>(dynamic_cast<Resolved_fieldContext *>(_localctx)->identToken, _localctx->subexpr, (dynamic_cast<Resolved_fieldContext *>(_localctx)->identToken != nullptr ? dynamic_cast<Resolved_fieldContext *>(_localctx)->identToken->getText() : "")),
                      dynamic_cast<Resolved_fieldContext *>(_localctx)->func_parametersContext->count,
                      dynamic_cast<Resolved_fieldContext *>(_localctx)->func_parametersContext->args
                  );
              
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(398);
      dynamic_cast<Resolved_fieldContext *>(_localctx)->identToken = match(IMQLangParser::IDENT);
      setState(399);
      dynamic_cast<Resolved_fieldContext *>(_localctx)->index_parametersContext = index_parameters();

                  dynamic_cast<Resolved_fieldContext *>(_localctx)->expr =  createNodeFromToken<RetrieveIndexExpr>(
                      dynamic_cast<Resolved_fieldContext *>(_localctx)->identToken,
                      createNodeFromToken<RetrieveFieldExpr>(dynamic_cast<Resolved_fieldContext *>(_localctx)->identToken, _localctx->subexpr, (dynamic_cast<Resolved_fieldContext *>(_localctx)->identToken != nullptr ? dynamic_cast<Resolved_fieldContext *>(_localctx)->identToken->getText() : "")),
                      dynamic_cast<Resolved_fieldContext *>(_localctx)->index_parametersContext->expr
                  );
              
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Func_parametersContext ------------------------------------------------------------------

IMQLangParser::Func_parametersContext::Func_parametersContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IMQLangParser::Func_parametersContext::L_PAREN() {
  return getToken(IMQLangParser::L_PAREN, 0);
}

tree::TerminalNode* IMQLangParser::Func_parametersContext::R_PAREN() {
  return getToken(IMQLangParser::R_PAREN, 0);
}

std::vector<IMQLangParser::ExpressionContext *> IMQLangParser::Func_parametersContext::expression() {
  return getRuleContexts<IMQLangParser::ExpressionContext>();
}

IMQLangParser::ExpressionContext* IMQLangParser::Func_parametersContext::expression(size_t i) {
  return getRuleContext<IMQLangParser::ExpressionContext>(i);
}

std::vector<tree::TerminalNode *> IMQLangParser::Func_parametersContext::COMMA() {
  return getTokens(IMQLangParser::COMMA);
}

tree::TerminalNode* IMQLangParser::Func_parametersContext::COMMA(size_t i) {
  return getToken(IMQLangParser::COMMA, i);
}


size_t IMQLangParser::Func_parametersContext::getRuleIndex() const {
  return IMQLangParser::RuleFunc_parameters;
}

void IMQLangParser::Func_parametersContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IMQLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunc_parameters(this);
}

void IMQLangParser::Func_parametersContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IMQLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunc_parameters(this);
}

IMQLangParser::Func_parametersContext* IMQLangParser::func_parameters() {
  Func_parametersContext *_localctx = _tracker.createInstance<Func_parametersContext>(_ctx, getState());
  enterRule(_localctx, 54, IMQLangParser::RuleFunc_parameters);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(404);
    match(IMQLangParser::L_PAREN);
    setState(416);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << IMQLangParser::L_PAREN)
      | (1ULL << IMQLangParser::L_BRACE)
      | (1ULL << IMQLangParser::NOT)
      | (1ULL << IMQLangParser::MINUS)
      | (1ULL << IMQLangParser::B_TRUE)
      | (1ULL << IMQLangParser::B_FALSE)
      | (1ULL << IMQLangParser::FLOAT)
      | (1ULL << IMQLangParser::INTEGER)
      | (1ULL << IMQLangParser::IDENT))) != 0)) {
      setState(405);
      dynamic_cast<Func_parametersContext *>(_localctx)->first = expression();
      _localctx->exprList.push_back(dynamic_cast<Func_parametersContext *>(_localctx)->first->expr);
      setState(413);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == IMQLangParser::COMMA) {
        setState(407);
        match(IMQLangParser::COMMA);
        setState(408);
        dynamic_cast<Func_parametersContext *>(_localctx)->n = expression();
        _localctx->exprList.push_back(dynamic_cast<Func_parametersContext *>(_localctx)->n->expr);
        setState(415);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(418);
    match(IMQLangParser::R_PAREN);

                dynamic_cast<Func_parametersContext *>(_localctx)->count =  _localctx->exprList.size();
                dynamic_cast<Func_parametersContext *>(_localctx)->args =  new VExpression*[_localctx->count];
                std::copy(_localctx->exprList.begin(), _localctx->exprList.end(), _localctx->args);
            
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Index_parametersContext ------------------------------------------------------------------

IMQLangParser::Index_parametersContext::Index_parametersContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IMQLangParser::Index_parametersContext::L_BRACKET() {
  return getToken(IMQLangParser::L_BRACKET, 0);
}

IMQLangParser::ExpressionContext* IMQLangParser::Index_parametersContext::expression() {
  return getRuleContext<IMQLangParser::ExpressionContext>(0);
}

tree::TerminalNode* IMQLangParser::Index_parametersContext::R_BRACKET() {
  return getToken(IMQLangParser::R_BRACKET, 0);
}


size_t IMQLangParser::Index_parametersContext::getRuleIndex() const {
  return IMQLangParser::RuleIndex_parameters;
}

void IMQLangParser::Index_parametersContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IMQLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIndex_parameters(this);
}

void IMQLangParser::Index_parametersContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IMQLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIndex_parameters(this);
}

IMQLangParser::Index_parametersContext* IMQLangParser::index_parameters() {
  Index_parametersContext *_localctx = _tracker.createInstance<Index_parametersContext>(_ctx, getState());
  enterRule(_localctx, 56, IMQLangParser::RuleIndex_parameters);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(421);
    match(IMQLangParser::L_BRACKET);
    setState(422);
    dynamic_cast<Index_parametersContext *>(_localctx)->expressionContext = expression();
    setState(423);
    match(IMQLangParser::R_BRACKET);
    dynamic_cast<Index_parametersContext *>(_localctx)->expr =  dynamic_cast<Index_parametersContext *>(_localctx)->expressionContext->expr;
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

// Static vars and initialization.
std::vector<dfa::DFA> IMQLangParser::_decisionToDFA;
atn::PredictionContextCache IMQLangParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN IMQLangParser::_atn;
std::vector<uint16_t> IMQLangParser::_serializedATN;

std::vector<std::string> IMQLangParser::_ruleNames = {
  "compileUnit", "statements", "statement", "define_input_stm", "define_output_stm", 
  "set_variable_stm", "set_field_stm", "delete_variable_stm", "select_stm", 
  "branch_stm", "for_loop_stm", "while_loop_stm", "expression", "orExpr", 
  "andExpr", "equalityExpr", "addExpr", "mulExpr", "notExpr", "atom", "value", 
  "const_value", "boolean", "color", "variable", "resolved_variable", "resolved_field", 
  "func_parameters", "index_parameters"
};

std::vector<std::string> IMQLangParser::_literalNames = {
  "", "';'", "'delete'", "'in'", "'out'", "'from'", "'if'", "'else'", "'for'", 
  "'while'", "'do'", "'('", "')'", "'['", "']'", "'{'", "'}'", "','", "':'", 
  "'.'", "'not'", "'and'", "'or'", "'='", "'!'", "'>'", "'<'", "'+'", "'-'", 
  "'*'", "'/'", "'%'", "'true'", "'false'"
};

std::vector<std::string> IMQLangParser::_symbolicNames = {
  "", "SEMICOLON", "DELETE", "INPUT", "OUTPUT", "FROM", "IF", "ELSE", "FOR", 
  "WHILE", "DO", "L_PAREN", "R_PAREN", "L_BRACKET", "R_BRACKET", "L_BRACE", 
  "R_BRACE", "COMMA", "COLON", "DOT", "NOT", "AND", "OR", "EQUAL", "BANG", 
  "GREATER", "LESS", "PLUS", "MINUS", "MULTIPLY", "DIVIDE", "MODULUS", "B_TRUE", 
  "B_FALSE", "FLOAT", "INTEGER", "IDENT", "WS", "COMMENT"
};

dfa::Vocabulary IMQLangParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> IMQLangParser::_tokenNames;

IMQLangParser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  _serializedATN = {
    0x3, 0x430, 0xd6d1, 0x8206, 0xad2d, 0x4417, 0xaef1, 0x8d80, 0xaadd, 
    0x3, 0x28, 0x1ad, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 
    0x9, 0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 
    0x4, 0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 
    0x9, 0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 0xe, 0x9, 0xe, 
    0x4, 0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x4, 0x11, 0x9, 0x11, 0x4, 
    0x12, 0x9, 0x12, 0x4, 0x13, 0x9, 0x13, 0x4, 0x14, 0x9, 0x14, 0x4, 0x15, 
    0x9, 0x15, 0x4, 0x16, 0x9, 0x16, 0x4, 0x17, 0x9, 0x17, 0x4, 0x18, 0x9, 
    0x18, 0x4, 0x19, 0x9, 0x19, 0x4, 0x1a, 0x9, 0x1a, 0x4, 0x1b, 0x9, 0x1b, 
    0x4, 0x1c, 0x9, 0x1c, 0x4, 0x1d, 0x9, 0x1d, 0x4, 0x1e, 0x9, 0x1e, 0x3, 
    0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x5, 0x2, 0x43, 
    0xa, 0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x6, 0x3, 0x48, 0xa, 0x3, 0xd, 
    0x3, 0xe, 0x3, 0x49, 0x3, 0x3, 0x3, 0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 
    0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 
    0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 
    0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 
    0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 
    0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 
    0x3, 0x4, 0x5, 0x4, 0x75, 0xa, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 
    0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 
    0x6, 0x3, 0x6, 0x5, 0x6, 0x83, 0xa, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x7, 
    0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 
    0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 
    0x3, 0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 
    0x3, 0xa, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x5, 0xb, 0xa2, 0xa, 
    0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 
    0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x5, 0xb, 0xae, 0xa, 0xb, 0x3, 0xb, 
    0x5, 0xb, 0xb1, 0xa, 0xb, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 
    0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x5, 0xc, 0xbc, 0xa, 0xc, 
    0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 
    0x3, 0xd, 0x3, 0xd, 0x5, 0xd, 0xc7, 0xa, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 
    0xd, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 
    0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x5, 0xf, 0xd7, 0xa, 0xf, 
    0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 
    0x10, 0x3, 0x10, 0x5, 0x10, 0xe1, 0xa, 0x10, 0x3, 0x11, 0x3, 0x11, 0x3, 
    0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 
    0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 
    0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 
    0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 
    0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 
    0x3, 0x11, 0x3, 0x11, 0x5, 0x11, 0x108, 0xa, 0x11, 0x3, 0x12, 0x3, 0x12, 
    0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 
    0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x5, 0x12, 0x117, 
    0xa, 0x12, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 
    0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 
    0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x5, 
    0x13, 0x12b, 0xa, 0x13, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 
    0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 
    0x14, 0x5, 0x14, 0x138, 0xa, 0x14, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 
    0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 
    0x15, 0x3, 0x15, 0x5, 0x15, 0x145, 0xa, 0x15, 0x3, 0x16, 0x3, 0x16, 
    0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 0x5, 0x16, 0x14d, 0xa, 0x16, 
    0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 
    0x17, 0x5, 0x17, 0x156, 0xa, 0x17, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 
    0x3, 0x18, 0x5, 0x18, 0x15c, 0xa, 0x18, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 
    0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 
    0x19, 0x3, 0x19, 0x5, 0x19, 0x169, 0xa, 0x19, 0x3, 0x19, 0x3, 0x19, 
    0x3, 0x19, 0x3, 0x19, 0x5, 0x19, 0x16f, 0xa, 0x19, 0x3, 0x19, 0x3, 0x19, 
    0x3, 0x19, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 
    0x1a, 0x7, 0x1a, 0x17a, 0xa, 0x1a, 0xc, 0x1a, 0xe, 0x1a, 0x17d, 0xb, 
    0x1a, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 
    0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x5, 0x1b, 0x189, 0xa, 0x1b, 
    0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 
    0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x5, 0x1c, 0x195, 0xa, 0x1c, 
    0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 
    0x1d, 0x7, 0x1d, 0x19e, 0xa, 0x1d, 0xc, 0x1d, 0xe, 0x1d, 0x1a1, 0xb, 
    0x1d, 0x5, 0x1d, 0x1a3, 0xa, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 
    0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 0x2, 
    0x2, 0x1f, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 
    0x18, 0x1a, 0x1c, 0x1e, 0x20, 0x22, 0x24, 0x26, 0x28, 0x2a, 0x2c, 0x2e, 
    0x30, 0x32, 0x34, 0x36, 0x38, 0x3a, 0x2, 0x2, 0x1c0, 0x2, 0x42, 0x3, 
    0x2, 0x2, 0x2, 0x4, 0x47, 0x3, 0x2, 0x2, 0x2, 0x6, 0x74, 0x3, 0x2, 0x2, 
    0x2, 0x8, 0x76, 0x3, 0x2, 0x2, 0x2, 0xa, 0x7c, 0x3, 0x2, 0x2, 0x2, 0xc, 
    0x86, 0x3, 0x2, 0x2, 0x2, 0xe, 0x8b, 0x3, 0x2, 0x2, 0x2, 0x10, 0x92, 
    0x3, 0x2, 0x2, 0x2, 0x12, 0x96, 0x3, 0x2, 0x2, 0x2, 0x14, 0x9d, 0x3, 
    0x2, 0x2, 0x2, 0x16, 0xb2, 0x3, 0x2, 0x2, 0x2, 0x18, 0xc0, 0x3, 0x2, 
    0x2, 0x2, 0x1a, 0xcb, 0x3, 0x2, 0x2, 0x2, 0x1c, 0xd6, 0x3, 0x2, 0x2, 
    0x2, 0x1e, 0xe0, 0x3, 0x2, 0x2, 0x2, 0x20, 0x107, 0x3, 0x2, 0x2, 0x2, 
    0x22, 0x116, 0x3, 0x2, 0x2, 0x2, 0x24, 0x12a, 0x3, 0x2, 0x2, 0x2, 0x26, 
    0x137, 0x3, 0x2, 0x2, 0x2, 0x28, 0x144, 0x3, 0x2, 0x2, 0x2, 0x2a, 0x14c, 
    0x3, 0x2, 0x2, 0x2, 0x2c, 0x155, 0x3, 0x2, 0x2, 0x2, 0x2e, 0x15b, 0x3, 
    0x2, 0x2, 0x2, 0x30, 0x15d, 0x3, 0x2, 0x2, 0x2, 0x32, 0x173, 0x3, 0x2, 
    0x2, 0x2, 0x34, 0x188, 0x3, 0x2, 0x2, 0x2, 0x36, 0x194, 0x3, 0x2, 0x2, 
    0x2, 0x38, 0x196, 0x3, 0x2, 0x2, 0x2, 0x3a, 0x1a7, 0x3, 0x2, 0x2, 0x2, 
    0x3c, 0x3d, 0x7, 0x2, 0x2, 0x3, 0x3d, 0x43, 0x8, 0x2, 0x1, 0x2, 0x3e, 
    0x3f, 0x5, 0x4, 0x3, 0x2, 0x3f, 0x40, 0x7, 0x2, 0x2, 0x3, 0x40, 0x41, 
    0x8, 0x2, 0x1, 0x2, 0x41, 0x43, 0x3, 0x2, 0x2, 0x2, 0x42, 0x3c, 0x3, 
    0x2, 0x2, 0x2, 0x42, 0x3e, 0x3, 0x2, 0x2, 0x2, 0x43, 0x3, 0x3, 0x2, 
    0x2, 0x2, 0x44, 0x45, 0x5, 0x6, 0x4, 0x2, 0x45, 0x46, 0x8, 0x3, 0x1, 
    0x2, 0x46, 0x48, 0x3, 0x2, 0x2, 0x2, 0x47, 0x44, 0x3, 0x2, 0x2, 0x2, 
    0x48, 0x49, 0x3, 0x2, 0x2, 0x2, 0x49, 0x47, 0x3, 0x2, 0x2, 0x2, 0x49, 
    0x4a, 0x3, 0x2, 0x2, 0x2, 0x4a, 0x4b, 0x3, 0x2, 0x2, 0x2, 0x4b, 0x4c, 
    0x8, 0x3, 0x1, 0x2, 0x4c, 0x5, 0x3, 0x2, 0x2, 0x2, 0x4d, 0x4e, 0x5, 
    0x8, 0x5, 0x2, 0x4e, 0x4f, 0x7, 0x3, 0x2, 0x2, 0x4f, 0x50, 0x8, 0x4, 
    0x1, 0x2, 0x50, 0x75, 0x3, 0x2, 0x2, 0x2, 0x51, 0x52, 0x5, 0xa, 0x6, 
    0x2, 0x52, 0x53, 0x7, 0x3, 0x2, 0x2, 0x53, 0x54, 0x8, 0x4, 0x1, 0x2, 
    0x54, 0x75, 0x3, 0x2, 0x2, 0x2, 0x55, 0x56, 0x5, 0xc, 0x7, 0x2, 0x56, 
    0x57, 0x7, 0x3, 0x2, 0x2, 0x57, 0x58, 0x8, 0x4, 0x1, 0x2, 0x58, 0x75, 
    0x3, 0x2, 0x2, 0x2, 0x59, 0x5a, 0x5, 0xe, 0x8, 0x2, 0x5a, 0x5b, 0x7, 
    0x3, 0x2, 0x2, 0x5b, 0x5c, 0x8, 0x4, 0x1, 0x2, 0x5c, 0x75, 0x3, 0x2, 
    0x2, 0x2, 0x5d, 0x5e, 0x5, 0x10, 0x9, 0x2, 0x5e, 0x5f, 0x7, 0x3, 0x2, 
    0x2, 0x5f, 0x60, 0x8, 0x4, 0x1, 0x2, 0x60, 0x75, 0x3, 0x2, 0x2, 0x2, 
    0x61, 0x62, 0x5, 0x12, 0xa, 0x2, 0x62, 0x63, 0x7, 0x3, 0x2, 0x2, 0x63, 
    0x64, 0x8, 0x4, 0x1, 0x2, 0x64, 0x75, 0x3, 0x2, 0x2, 0x2, 0x65, 0x66, 
    0x5, 0x14, 0xb, 0x2, 0x66, 0x67, 0x8, 0x4, 0x1, 0x2, 0x67, 0x75, 0x3, 
    0x2, 0x2, 0x2, 0x68, 0x69, 0x5, 0x16, 0xc, 0x2, 0x69, 0x6a, 0x8, 0x4, 
    0x1, 0x2, 0x6a, 0x75, 0x3, 0x2, 0x2, 0x2, 0x6b, 0x6c, 0x5, 0x18, 0xd, 
    0x2, 0x6c, 0x6d, 0x8, 0x4, 0x1, 0x2, 0x6d, 0x75, 0x3, 0x2, 0x2, 0x2, 
    0x6e, 0x6f, 0x5, 0x1a, 0xe, 0x2, 0x6f, 0x70, 0x7, 0x3, 0x2, 0x2, 0x70, 
    0x71, 0x8, 0x4, 0x1, 0x2, 0x71, 0x75, 0x3, 0x2, 0x2, 0x2, 0x72, 0x73, 
    0x7, 0x3, 0x2, 0x2, 0x73, 0x75, 0x8, 0x4, 0x1, 0x2, 0x74, 0x4d, 0x3, 
    0x2, 0x2, 0x2, 0x74, 0x51, 0x3, 0x2, 0x2, 0x2, 0x74, 0x55, 0x3, 0x2, 
    0x2, 0x2, 0x74, 0x59, 0x3, 0x2, 0x2, 0x2, 0x74, 0x5d, 0x3, 0x2, 0x2, 
    0x2, 0x74, 0x61, 0x3, 0x2, 0x2, 0x2, 0x74, 0x65, 0x3, 0x2, 0x2, 0x2, 
    0x74, 0x68, 0x3, 0x2, 0x2, 0x2, 0x74, 0x6b, 0x3, 0x2, 0x2, 0x2, 0x74, 
    0x6e, 0x3, 0x2, 0x2, 0x2, 0x74, 0x72, 0x3, 0x2, 0x2, 0x2, 0x75, 0x7, 
    0x3, 0x2, 0x2, 0x2, 0x76, 0x77, 0x7, 0x5, 0x2, 0x2, 0x77, 0x78, 0x7, 
    0x26, 0x2, 0x2, 0x78, 0x79, 0x7, 0x19, 0x2, 0x2, 0x79, 0x7a, 0x5, 0x1a, 
    0xe, 0x2, 0x7a, 0x7b, 0x8, 0x5, 0x1, 0x2, 0x7b, 0x9, 0x3, 0x2, 0x2, 
    0x2, 0x7c, 0x7d, 0x7, 0x6, 0x2, 0x2, 0x7d, 0x82, 0x7, 0x26, 0x2, 0x2, 
    0x7e, 0x7f, 0x7, 0x19, 0x2, 0x2, 0x7f, 0x80, 0x5, 0x1a, 0xe, 0x2, 0x80, 
    0x81, 0x8, 0x6, 0x1, 0x2, 0x81, 0x83, 0x3, 0x2, 0x2, 0x2, 0x82, 0x7e, 
    0x3, 0x2, 0x2, 0x2, 0x82, 0x83, 0x3, 0x2, 0x2, 0x2, 0x83, 0x84, 0x3, 
    0x2, 0x2, 0x2, 0x84, 0x85, 0x8, 0x6, 0x1, 0x2, 0x85, 0xb, 0x3, 0x2, 
    0x2, 0x2, 0x86, 0x87, 0x7, 0x26, 0x2, 0x2, 0x87, 0x88, 0x7, 0x19, 0x2, 
    0x2, 0x88, 0x89, 0x5, 0x1a, 0xe, 0x2, 0x89, 0x8a, 0x8, 0x7, 0x1, 0x2, 
    0x8a, 0xd, 0x3, 0x2, 0x2, 0x2, 0x8b, 0x8c, 0x5, 0x32, 0x1a, 0x2, 0x8c, 
    0x8d, 0x7, 0x15, 0x2, 0x2, 0x8d, 0x8e, 0x7, 0x26, 0x2, 0x2, 0x8e, 0x8f, 
    0x7, 0x19, 0x2, 0x2, 0x8f, 0x90, 0x5, 0x1a, 0xe, 0x2, 0x90, 0x91, 0x8, 
    0x8, 0x1, 0x2, 0x91, 0xf, 0x3, 0x2, 0x2, 0x2, 0x92, 0x93, 0x7, 0x4, 
    0x2, 0x2, 0x93, 0x94, 0x7, 0x26, 0x2, 0x2, 0x94, 0x95, 0x8, 0x9, 0x1, 
    0x2, 0x95, 0x11, 0x3, 0x2, 0x2, 0x2, 0x96, 0x97, 0x5, 0x1a, 0xe, 0x2, 
    0x97, 0x98, 0x7, 0x14, 0x2, 0x2, 0x98, 0x99, 0x5, 0x1a, 0xe, 0x2, 0x99, 
    0x9a, 0x7, 0x7, 0x2, 0x2, 0x9a, 0x9b, 0x5, 0x1a, 0xe, 0x2, 0x9b, 0x9c, 
    0x8, 0xa, 0x1, 0x2, 0x9c, 0x13, 0x3, 0x2, 0x2, 0x2, 0x9d, 0x9e, 0x7, 
    0x8, 0x2, 0x2, 0x9e, 0x9f, 0x5, 0x1a, 0xe, 0x2, 0x9f, 0xa1, 0x7, 0x11, 
    0x2, 0x2, 0xa0, 0xa2, 0x5, 0x4, 0x3, 0x2, 0xa1, 0xa0, 0x3, 0x2, 0x2, 
    0x2, 0xa1, 0xa2, 0x3, 0x2, 0x2, 0x2, 0xa2, 0xa3, 0x3, 0x2, 0x2, 0x2, 
    0xa3, 0xb0, 0x7, 0x12, 0x2, 0x2, 0xa4, 0xa5, 0x7, 0x9, 0x2, 0x2, 0xa5, 
    0xa6, 0x5, 0x14, 0xb, 0x2, 0xa6, 0xa7, 0x8, 0xb, 0x1, 0x2, 0xa7, 0xb1, 
    0x3, 0x2, 0x2, 0x2, 0xa8, 0xa9, 0x7, 0x9, 0x2, 0x2, 0xa9, 0xad, 0x7, 
    0x11, 0x2, 0x2, 0xaa, 0xab, 0x5, 0x4, 0x3, 0x2, 0xab, 0xac, 0x8, 0xb, 
    0x1, 0x2, 0xac, 0xae, 0x3, 0x2, 0x2, 0x2, 0xad, 0xaa, 0x3, 0x2, 0x2, 
    0x2, 0xad, 0xae, 0x3, 0x2, 0x2, 0x2, 0xae, 0xaf, 0x3, 0x2, 0x2, 0x2, 
    0xaf, 0xb1, 0x7, 0x12, 0x2, 0x2, 0xb0, 0xa4, 0x3, 0x2, 0x2, 0x2, 0xb0, 
    0xa8, 0x3, 0x2, 0x2, 0x2, 0xb0, 0xb1, 0x3, 0x2, 0x2, 0x2, 0xb1, 0x15, 
    0x3, 0x2, 0x2, 0x2, 0xb2, 0xb3, 0x7, 0xa, 0x2, 0x2, 0xb3, 0xb4, 0x5, 
    0x6, 0x4, 0x2, 0xb4, 0xb5, 0x5, 0x1a, 0xe, 0x2, 0xb5, 0xb6, 0x7, 0x3, 
    0x2, 0x2, 0xb6, 0xb7, 0x5, 0x6, 0x4, 0x2, 0xb7, 0xbb, 0x7, 0x11, 0x2, 
    0x2, 0xb8, 0xb9, 0x5, 0x4, 0x3, 0x2, 0xb9, 0xba, 0x8, 0xc, 0x1, 0x2, 
    0xba, 0xbc, 0x3, 0x2, 0x2, 0x2, 0xbb, 0xb8, 0x3, 0x2, 0x2, 0x2, 0xbb, 
    0xbc, 0x3, 0x2, 0x2, 0x2, 0xbc, 0xbd, 0x3, 0x2, 0x2, 0x2, 0xbd, 0xbe, 
    0x7, 0x12, 0x2, 0x2, 0xbe, 0xbf, 0x8, 0xc, 0x1, 0x2, 0xbf, 0x17, 0x3, 
    0x2, 0x2, 0x2, 0xc0, 0xc1, 0x7, 0xb, 0x2, 0x2, 0xc1, 0xc2, 0x5, 0x1a, 
    0xe, 0x2, 0xc2, 0xc6, 0x7, 0x11, 0x2, 0x2, 0xc3, 0xc4, 0x5, 0x4, 0x3, 
    0x2, 0xc4, 0xc5, 0x8, 0xd, 0x1, 0x2, 0xc5, 0xc7, 0x3, 0x2, 0x2, 0x2, 
    0xc6, 0xc3, 0x3, 0x2, 0x2, 0x2, 0xc6, 0xc7, 0x3, 0x2, 0x2, 0x2, 0xc7, 
    0xc8, 0x3, 0x2, 0x2, 0x2, 0xc8, 0xc9, 0x7, 0x12, 0x2, 0x2, 0xc9, 0xca, 
    0x8, 0xd, 0x1, 0x2, 0xca, 0x19, 0x3, 0x2, 0x2, 0x2, 0xcb, 0xcc, 0x5, 
    0x1c, 0xf, 0x2, 0xcc, 0xcd, 0x8, 0xe, 0x1, 0x2, 0xcd, 0x1b, 0x3, 0x2, 
    0x2, 0x2, 0xce, 0xcf, 0x5, 0x1e, 0x10, 0x2, 0xcf, 0xd0, 0x8, 0xf, 0x1, 
    0x2, 0xd0, 0xd7, 0x3, 0x2, 0x2, 0x2, 0xd1, 0xd2, 0x5, 0x1e, 0x10, 0x2, 
    0xd2, 0xd3, 0x7, 0x18, 0x2, 0x2, 0xd3, 0xd4, 0x5, 0x1c, 0xf, 0x2, 0xd4, 
    0xd5, 0x8, 0xf, 0x1, 0x2, 0xd5, 0xd7, 0x3, 0x2, 0x2, 0x2, 0xd6, 0xce, 
    0x3, 0x2, 0x2, 0x2, 0xd6, 0xd1, 0x3, 0x2, 0x2, 0x2, 0xd7, 0x1d, 0x3, 
    0x2, 0x2, 0x2, 0xd8, 0xd9, 0x5, 0x20, 0x11, 0x2, 0xd9, 0xda, 0x8, 0x10, 
    0x1, 0x2, 0xda, 0xe1, 0x3, 0x2, 0x2, 0x2, 0xdb, 0xdc, 0x5, 0x20, 0x11, 
    0x2, 0xdc, 0xdd, 0x7, 0x17, 0x2, 0x2, 0xdd, 0xde, 0x5, 0x1e, 0x10, 0x2, 
    0xde, 0xdf, 0x8, 0x10, 0x1, 0x2, 0xdf, 0xe1, 0x3, 0x2, 0x2, 0x2, 0xe0, 
    0xd8, 0x3, 0x2, 0x2, 0x2, 0xe0, 0xdb, 0x3, 0x2, 0x2, 0x2, 0xe1, 0x1f, 
    0x3, 0x2, 0x2, 0x2, 0xe2, 0xe3, 0x5, 0x22, 0x12, 0x2, 0xe3, 0xe4, 0x8, 
    0x11, 0x1, 0x2, 0xe4, 0x108, 0x3, 0x2, 0x2, 0x2, 0xe5, 0xe6, 0x5, 0x22, 
    0x12, 0x2, 0xe6, 0xe7, 0x7, 0x19, 0x2, 0x2, 0xe7, 0xe8, 0x7, 0x19, 0x2, 
    0x2, 0xe8, 0xe9, 0x5, 0x20, 0x11, 0x2, 0xe9, 0xea, 0x8, 0x11, 0x1, 0x2, 
    0xea, 0x108, 0x3, 0x2, 0x2, 0x2, 0xeb, 0xec, 0x5, 0x22, 0x12, 0x2, 0xec, 
    0xed, 0x7, 0x1a, 0x2, 0x2, 0xed, 0xee, 0x7, 0x19, 0x2, 0x2, 0xee, 0xef, 
    0x5, 0x20, 0x11, 0x2, 0xef, 0xf0, 0x8, 0x11, 0x1, 0x2, 0xf0, 0x108, 
    0x3, 0x2, 0x2, 0x2, 0xf1, 0xf2, 0x5, 0x22, 0x12, 0x2, 0xf2, 0xf3, 0x7, 
    0x1c, 0x2, 0x2, 0xf3, 0xf4, 0x5, 0x20, 0x11, 0x2, 0xf4, 0xf5, 0x8, 0x11, 
    0x1, 0x2, 0xf5, 0x108, 0x3, 0x2, 0x2, 0x2, 0xf6, 0xf7, 0x5, 0x22, 0x12, 
    0x2, 0xf7, 0xf8, 0x7, 0x1c, 0x2, 0x2, 0xf8, 0xf9, 0x7, 0x19, 0x2, 0x2, 
    0xf9, 0xfa, 0x5, 0x20, 0x11, 0x2, 0xfa, 0xfb, 0x8, 0x11, 0x1, 0x2, 0xfb, 
    0x108, 0x3, 0x2, 0x2, 0x2, 0xfc, 0xfd, 0x5, 0x22, 0x12, 0x2, 0xfd, 0xfe, 
    0x7, 0x1b, 0x2, 0x2, 0xfe, 0xff, 0x5, 0x20, 0x11, 0x2, 0xff, 0x100, 
    0x8, 0x11, 0x1, 0x2, 0x100, 0x108, 0x3, 0x2, 0x2, 0x2, 0x101, 0x102, 
    0x5, 0x22, 0x12, 0x2, 0x102, 0x103, 0x7, 0x1b, 0x2, 0x2, 0x103, 0x104, 
    0x7, 0x19, 0x2, 0x2, 0x104, 0x105, 0x5, 0x20, 0x11, 0x2, 0x105, 0x106, 
    0x8, 0x11, 0x1, 0x2, 0x106, 0x108, 0x3, 0x2, 0x2, 0x2, 0x107, 0xe2, 
    0x3, 0x2, 0x2, 0x2, 0x107, 0xe5, 0x3, 0x2, 0x2, 0x2, 0x107, 0xeb, 0x3, 
    0x2, 0x2, 0x2, 0x107, 0xf1, 0x3, 0x2, 0x2, 0x2, 0x107, 0xf6, 0x3, 0x2, 
    0x2, 0x2, 0x107, 0xfc, 0x3, 0x2, 0x2, 0x2, 0x107, 0x101, 0x3, 0x2, 0x2, 
    0x2, 0x108, 0x21, 0x3, 0x2, 0x2, 0x2, 0x109, 0x10a, 0x5, 0x24, 0x13, 
    0x2, 0x10a, 0x10b, 0x8, 0x12, 0x1, 0x2, 0x10b, 0x117, 0x3, 0x2, 0x2, 
    0x2, 0x10c, 0x10d, 0x5, 0x24, 0x13, 0x2, 0x10d, 0x10e, 0x7, 0x1d, 0x2, 
    0x2, 0x10e, 0x10f, 0x5, 0x22, 0x12, 0x2, 0x10f, 0x110, 0x8, 0x12, 0x1, 
    0x2, 0x110, 0x117, 0x3, 0x2, 0x2, 0x2, 0x111, 0x112, 0x5, 0x24, 0x13, 
    0x2, 0x112, 0x113, 0x7, 0x1e, 0x2, 0x2, 0x113, 0x114, 0x5, 0x22, 0x12, 
    0x2, 0x114, 0x115, 0x8, 0x12, 0x1, 0x2, 0x115, 0x117, 0x3, 0x2, 0x2, 
    0x2, 0x116, 0x109, 0x3, 0x2, 0x2, 0x2, 0x116, 0x10c, 0x3, 0x2, 0x2, 
    0x2, 0x116, 0x111, 0x3, 0x2, 0x2, 0x2, 0x117, 0x23, 0x3, 0x2, 0x2, 0x2, 
    0x118, 0x119, 0x5, 0x26, 0x14, 0x2, 0x119, 0x11a, 0x8, 0x13, 0x1, 0x2, 
    0x11a, 0x12b, 0x3, 0x2, 0x2, 0x2, 0x11b, 0x11c, 0x5, 0x26, 0x14, 0x2, 
    0x11c, 0x11d, 0x7, 0x1f, 0x2, 0x2, 0x11d, 0x11e, 0x5, 0x24, 0x13, 0x2, 
    0x11e, 0x11f, 0x8, 0x13, 0x1, 0x2, 0x11f, 0x12b, 0x3, 0x2, 0x2, 0x2, 
    0x120, 0x121, 0x5, 0x26, 0x14, 0x2, 0x121, 0x122, 0x7, 0x20, 0x2, 0x2, 
    0x122, 0x123, 0x5, 0x24, 0x13, 0x2, 0x123, 0x124, 0x8, 0x13, 0x1, 0x2, 
    0x124, 0x12b, 0x3, 0x2, 0x2, 0x2, 0x125, 0x126, 0x5, 0x26, 0x14, 0x2, 
    0x126, 0x127, 0x7, 0x21, 0x2, 0x2, 0x127, 0x128, 0x5, 0x24, 0x13, 0x2, 
    0x128, 0x129, 0x8, 0x13, 0x1, 0x2, 0x129, 0x12b, 0x3, 0x2, 0x2, 0x2, 
    0x12a, 0x118, 0x3, 0x2, 0x2, 0x2, 0x12a, 0x11b, 0x3, 0x2, 0x2, 0x2, 
    0x12a, 0x120, 0x3, 0x2, 0x2, 0x2, 0x12a, 0x125, 0x3, 0x2, 0x2, 0x2, 
    0x12b, 0x25, 0x3, 0x2, 0x2, 0x2, 0x12c, 0x12d, 0x7, 0x16, 0x2, 0x2, 
    0x12d, 0x12e, 0x5, 0x26, 0x14, 0x2, 0x12e, 0x12f, 0x8, 0x14, 0x1, 0x2, 
    0x12f, 0x138, 0x3, 0x2, 0x2, 0x2, 0x130, 0x131, 0x7, 0x1e, 0x2, 0x2, 
    0x131, 0x132, 0x5, 0x26, 0x14, 0x2, 0x132, 0x133, 0x8, 0x14, 0x1, 0x2, 
    0x133, 0x138, 0x3, 0x2, 0x2, 0x2, 0x134, 0x135, 0x5, 0x28, 0x15, 0x2, 
    0x135, 0x136, 0x8, 0x14, 0x1, 0x2, 0x136, 0x138, 0x3, 0x2, 0x2, 0x2, 
    0x137, 0x12c, 0x3, 0x2, 0x2, 0x2, 0x137, 0x130, 0x3, 0x2, 0x2, 0x2, 
    0x137, 0x134, 0x3, 0x2, 0x2, 0x2, 0x138, 0x27, 0x3, 0x2, 0x2, 0x2, 0x139, 
    0x13a, 0x5, 0x2a, 0x16, 0x2, 0x13a, 0x13b, 0x8, 0x15, 0x1, 0x2, 0x13b, 
    0x145, 0x3, 0x2, 0x2, 0x2, 0x13c, 0x13d, 0x5, 0x32, 0x1a, 0x2, 0x13d, 
    0x13e, 0x8, 0x15, 0x1, 0x2, 0x13e, 0x145, 0x3, 0x2, 0x2, 0x2, 0x13f, 
    0x140, 0x7, 0xd, 0x2, 0x2, 0x140, 0x141, 0x5, 0x1a, 0xe, 0x2, 0x141, 
    0x142, 0x7, 0xe, 0x2, 0x2, 0x142, 0x143, 0x8, 0x15, 0x1, 0x2, 0x143, 
    0x145, 0x3, 0x2, 0x2, 0x2, 0x144, 0x139, 0x3, 0x2, 0x2, 0x2, 0x144, 
    0x13c, 0x3, 0x2, 0x2, 0x2, 0x144, 0x13f, 0x3, 0x2, 0x2, 0x2, 0x145, 
    0x29, 0x3, 0x2, 0x2, 0x2, 0x146, 0x147, 0x5, 0x2c, 0x17, 0x2, 0x147, 
    0x148, 0x8, 0x16, 0x1, 0x2, 0x148, 0x14d, 0x3, 0x2, 0x2, 0x2, 0x149, 
    0x14a, 0x5, 0x30, 0x19, 0x2, 0x14a, 0x14b, 0x8, 0x16, 0x1, 0x2, 0x14b, 
    0x14d, 0x3, 0x2, 0x2, 0x2, 0x14c, 0x146, 0x3, 0x2, 0x2, 0x2, 0x14c, 
    0x149, 0x3, 0x2, 0x2, 0x2, 0x14d, 0x2b, 0x3, 0x2, 0x2, 0x2, 0x14e, 0x14f, 
    0x7, 0x25, 0x2, 0x2, 0x14f, 0x156, 0x8, 0x17, 0x1, 0x2, 0x150, 0x151, 
    0x7, 0x24, 0x2, 0x2, 0x151, 0x156, 0x8, 0x17, 0x1, 0x2, 0x152, 0x153, 
    0x5, 0x2e, 0x18, 0x2, 0x153, 0x154, 0x8, 0x17, 0x1, 0x2, 0x154, 0x156, 
    0x3, 0x2, 0x2, 0x2, 0x155, 0x14e, 0x3, 0x2, 0x2, 0x2, 0x155, 0x150, 
    0x3, 0x2, 0x2, 0x2, 0x155, 0x152, 0x3, 0x2, 0x2, 0x2, 0x156, 0x2d, 0x3, 
    0x2, 0x2, 0x2, 0x157, 0x158, 0x7, 0x22, 0x2, 0x2, 0x158, 0x15c, 0x8, 
    0x18, 0x1, 0x2, 0x159, 0x15a, 0x7, 0x23, 0x2, 0x2, 0x15a, 0x15c, 0x8, 
    0x18, 0x1, 0x2, 0x15b, 0x157, 0x3, 0x2, 0x2, 0x2, 0x15b, 0x159, 0x3, 
    0x2, 0x2, 0x2, 0x15c, 0x2f, 0x3, 0x2, 0x2, 0x2, 0x15d, 0x168, 0x7, 0x11, 
    0x2, 0x2, 0x15e, 0x15f, 0x5, 0x1a, 0xe, 0x2, 0x15f, 0x160, 0x8, 0x19, 
    0x1, 0x2, 0x160, 0x169, 0x3, 0x2, 0x2, 0x2, 0x161, 0x162, 0x5, 0x1a, 
    0xe, 0x2, 0x162, 0x163, 0x7, 0x13, 0x2, 0x2, 0x163, 0x164, 0x5, 0x1a, 
    0xe, 0x2, 0x164, 0x165, 0x7, 0x13, 0x2, 0x2, 0x165, 0x166, 0x5, 0x1a, 
    0xe, 0x2, 0x166, 0x167, 0x8, 0x19, 0x1, 0x2, 0x167, 0x169, 0x3, 0x2, 
    0x2, 0x2, 0x168, 0x15e, 0x3, 0x2, 0x2, 0x2, 0x168, 0x161, 0x3, 0x2, 
    0x2, 0x2, 0x169, 0x16e, 0x3, 0x2, 0x2, 0x2, 0x16a, 0x16b, 0x7, 0x13, 
    0x2, 0x2, 0x16b, 0x16c, 0x5, 0x1a, 0xe, 0x2, 0x16c, 0x16d, 0x8, 0x19, 
    0x1, 0x2, 0x16d, 0x16f, 0x3, 0x2, 0x2, 0x2, 0x16e, 0x16a, 0x3, 0x2, 
    0x2, 0x2, 0x16e, 0x16f, 0x3, 0x2, 0x2, 0x2, 0x16f, 0x170, 0x3, 0x2, 
    0x2, 0x2, 0x170, 0x171, 0x7, 0x12, 0x2, 0x2, 0x171, 0x172, 0x8, 0x19, 
    0x1, 0x2, 0x172, 0x31, 0x3, 0x2, 0x2, 0x2, 0x173, 0x174, 0x5, 0x34, 
    0x1b, 0x2, 0x174, 0x17b, 0x8, 0x1a, 0x1, 0x2, 0x175, 0x176, 0x7, 0x15, 
    0x2, 0x2, 0x176, 0x177, 0x5, 0x36, 0x1c, 0x2, 0x177, 0x178, 0x8, 0x1a, 
    0x1, 0x2, 0x178, 0x17a, 0x3, 0x2, 0x2, 0x2, 0x179, 0x175, 0x3, 0x2, 
    0x2, 0x2, 0x17a, 0x17d, 0x3, 0x2, 0x2, 0x2, 0x17b, 0x179, 0x3, 0x2, 
    0x2, 0x2, 0x17b, 0x17c, 0x3, 0x2, 0x2, 0x2, 0x17c, 0x33, 0x3, 0x2, 0x2, 
    0x2, 0x17d, 0x17b, 0x3, 0x2, 0x2, 0x2, 0x17e, 0x17f, 0x7, 0x26, 0x2, 
    0x2, 0x17f, 0x189, 0x8, 0x1b, 0x1, 0x2, 0x180, 0x181, 0x7, 0x26, 0x2, 
    0x2, 0x181, 0x182, 0x5, 0x38, 0x1d, 0x2, 0x182, 0x183, 0x8, 0x1b, 0x1, 
    0x2, 0x183, 0x189, 0x3, 0x2, 0x2, 0x2, 0x184, 0x185, 0x7, 0x26, 0x2, 
    0x2, 0x185, 0x186, 0x5, 0x3a, 0x1e, 0x2, 0x186, 0x187, 0x8, 0x1b, 0x1, 
    0x2, 0x187, 0x189, 0x3, 0x2, 0x2, 0x2, 0x188, 0x17e, 0x3, 0x2, 0x2, 
    0x2, 0x188, 0x180, 0x3, 0x2, 0x2, 0x2, 0x188, 0x184, 0x3, 0x2, 0x2, 
    0x2, 0x189, 0x35, 0x3, 0x2, 0x2, 0x2, 0x18a, 0x18b, 0x7, 0x26, 0x2, 
    0x2, 0x18b, 0x195, 0x8, 0x1c, 0x1, 0x2, 0x18c, 0x18d, 0x7, 0x26, 0x2, 
    0x2, 0x18d, 0x18e, 0x5, 0x38, 0x1d, 0x2, 0x18e, 0x18f, 0x8, 0x1c, 0x1, 
    0x2, 0x18f, 0x195, 0x3, 0x2, 0x2, 0x2, 0x190, 0x191, 0x7, 0x26, 0x2, 
    0x2, 0x191, 0x192, 0x5, 0x3a, 0x1e, 0x2, 0x192, 0x193, 0x8, 0x1c, 0x1, 
    0x2, 0x193, 0x195, 0x3, 0x2, 0x2, 0x2, 0x194, 0x18a, 0x3, 0x2, 0x2, 
    0x2, 0x194, 0x18c, 0x3, 0x2, 0x2, 0x2, 0x194, 0x190, 0x3, 0x2, 0x2, 
    0x2, 0x195, 0x37, 0x3, 0x2, 0x2, 0x2, 0x196, 0x1a2, 0x7, 0xd, 0x2, 0x2, 
    0x197, 0x198, 0x5, 0x1a, 0xe, 0x2, 0x198, 0x19f, 0x8, 0x1d, 0x1, 0x2, 
    0x199, 0x19a, 0x7, 0x13, 0x2, 0x2, 0x19a, 0x19b, 0x5, 0x1a, 0xe, 0x2, 
    0x19b, 0x19c, 0x8, 0x1d, 0x1, 0x2, 0x19c, 0x19e, 0x3, 0x2, 0x2, 0x2, 
    0x19d, 0x199, 0x3, 0x2, 0x2, 0x2, 0x19e, 0x1a1, 0x3, 0x2, 0x2, 0x2, 
    0x19f, 0x19d, 0x3, 0x2, 0x2, 0x2, 0x19f, 0x1a0, 0x3, 0x2, 0x2, 0x2, 
    0x1a0, 0x1a3, 0x3, 0x2, 0x2, 0x2, 0x1a1, 0x19f, 0x3, 0x2, 0x2, 0x2, 
    0x1a2, 0x197, 0x3, 0x2, 0x2, 0x2, 0x1a2, 0x1a3, 0x3, 0x2, 0x2, 0x2, 
    0x1a3, 0x1a4, 0x3, 0x2, 0x2, 0x2, 0x1a4, 0x1a5, 0x7, 0xe, 0x2, 0x2, 
    0x1a5, 0x1a6, 0x8, 0x1d, 0x1, 0x2, 0x1a6, 0x39, 0x3, 0x2, 0x2, 0x2, 
    0x1a7, 0x1a8, 0x7, 0xf, 0x2, 0x2, 0x1a8, 0x1a9, 0x5, 0x1a, 0xe, 0x2, 
    0x1a9, 0x1aa, 0x7, 0x10, 0x2, 0x2, 0x1aa, 0x1ab, 0x8, 0x1e, 0x1, 0x2, 
    0x1ab, 0x3b, 0x3, 0x2, 0x2, 0x2, 0x1c, 0x42, 0x49, 0x74, 0x82, 0xa1, 
    0xad, 0xb0, 0xbb, 0xc6, 0xd6, 0xe0, 0x107, 0x116, 0x12a, 0x137, 0x144, 
    0x14c, 0x155, 0x15b, 0x168, 0x16e, 0x17b, 0x188, 0x194, 0x19f, 0x1a2, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

IMQLangParser::Initializer IMQLangParser::_init;
