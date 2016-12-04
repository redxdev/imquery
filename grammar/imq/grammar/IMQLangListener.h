
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
#include "IMQLangParser.h"


namespace imq {

/**
 * This interface defines an abstract listener for a parse tree produced by IMQLangParser.
 */
class IMQLangListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterCompileUnit(IMQLangParser::CompileUnitContext *ctx) = 0;
  virtual void exitCompileUnit(IMQLangParser::CompileUnitContext *ctx) = 0;

  virtual void enterStatements(IMQLangParser::StatementsContext *ctx) = 0;
  virtual void exitStatements(IMQLangParser::StatementsContext *ctx) = 0;

  virtual void enterStatement(IMQLangParser::StatementContext *ctx) = 0;
  virtual void exitStatement(IMQLangParser::StatementContext *ctx) = 0;

  virtual void enterDefine_input_stm(IMQLangParser::Define_input_stmContext *ctx) = 0;
  virtual void exitDefine_input_stm(IMQLangParser::Define_input_stmContext *ctx) = 0;

  virtual void enterDefine_output_stm(IMQLangParser::Define_output_stmContext *ctx) = 0;
  virtual void exitDefine_output_stm(IMQLangParser::Define_output_stmContext *ctx) = 0;

  virtual void enterSet_variable_stm(IMQLangParser::Set_variable_stmContext *ctx) = 0;
  virtual void exitSet_variable_stm(IMQLangParser::Set_variable_stmContext *ctx) = 0;

  virtual void enterSet_field_stm(IMQLangParser::Set_field_stmContext *ctx) = 0;
  virtual void exitSet_field_stm(IMQLangParser::Set_field_stmContext *ctx) = 0;

  virtual void enterDelete_variable_stm(IMQLangParser::Delete_variable_stmContext *ctx) = 0;
  virtual void exitDelete_variable_stm(IMQLangParser::Delete_variable_stmContext *ctx) = 0;

  virtual void enterSelect_stm(IMQLangParser::Select_stmContext *ctx) = 0;
  virtual void exitSelect_stm(IMQLangParser::Select_stmContext *ctx) = 0;

  virtual void enterBranch_stm(IMQLangParser::Branch_stmContext *ctx) = 0;
  virtual void exitBranch_stm(IMQLangParser::Branch_stmContext *ctx) = 0;

  virtual void enterFor_loop_stm(IMQLangParser::For_loop_stmContext *ctx) = 0;
  virtual void exitFor_loop_stm(IMQLangParser::For_loop_stmContext *ctx) = 0;

  virtual void enterWhile_loop_stm(IMQLangParser::While_loop_stmContext *ctx) = 0;
  virtual void exitWhile_loop_stm(IMQLangParser::While_loop_stmContext *ctx) = 0;

  virtual void enterExpression(IMQLangParser::ExpressionContext *ctx) = 0;
  virtual void exitExpression(IMQLangParser::ExpressionContext *ctx) = 0;

  virtual void enterOrExpr(IMQLangParser::OrExprContext *ctx) = 0;
  virtual void exitOrExpr(IMQLangParser::OrExprContext *ctx) = 0;

  virtual void enterAndExpr(IMQLangParser::AndExprContext *ctx) = 0;
  virtual void exitAndExpr(IMQLangParser::AndExprContext *ctx) = 0;

  virtual void enterEqualityExpr(IMQLangParser::EqualityExprContext *ctx) = 0;
  virtual void exitEqualityExpr(IMQLangParser::EqualityExprContext *ctx) = 0;

  virtual void enterAddExpr(IMQLangParser::AddExprContext *ctx) = 0;
  virtual void exitAddExpr(IMQLangParser::AddExprContext *ctx) = 0;

  virtual void enterMulExpr(IMQLangParser::MulExprContext *ctx) = 0;
  virtual void exitMulExpr(IMQLangParser::MulExprContext *ctx) = 0;

  virtual void enterNotExpr(IMQLangParser::NotExprContext *ctx) = 0;
  virtual void exitNotExpr(IMQLangParser::NotExprContext *ctx) = 0;

  virtual void enterAtom(IMQLangParser::AtomContext *ctx) = 0;
  virtual void exitAtom(IMQLangParser::AtomContext *ctx) = 0;

  virtual void enterValue(IMQLangParser::ValueContext *ctx) = 0;
  virtual void exitValue(IMQLangParser::ValueContext *ctx) = 0;

  virtual void enterConst_value(IMQLangParser::Const_valueContext *ctx) = 0;
  virtual void exitConst_value(IMQLangParser::Const_valueContext *ctx) = 0;

  virtual void enterBoolean(IMQLangParser::BooleanContext *ctx) = 0;
  virtual void exitBoolean(IMQLangParser::BooleanContext *ctx) = 0;

  virtual void enterColor(IMQLangParser::ColorContext *ctx) = 0;
  virtual void exitColor(IMQLangParser::ColorContext *ctx) = 0;

  virtual void enterVariable(IMQLangParser::VariableContext *ctx) = 0;
  virtual void exitVariable(IMQLangParser::VariableContext *ctx) = 0;

  virtual void enterResolved_variable(IMQLangParser::Resolved_variableContext *ctx) = 0;
  virtual void exitResolved_variable(IMQLangParser::Resolved_variableContext *ctx) = 0;

  virtual void enterResolved_field(IMQLangParser::Resolved_fieldContext *ctx) = 0;
  virtual void exitResolved_field(IMQLangParser::Resolved_fieldContext *ctx) = 0;

  virtual void enterFunc_parameters(IMQLangParser::Func_parametersContext *ctx) = 0;
  virtual void exitFunc_parameters(IMQLangParser::Func_parametersContext *ctx) = 0;

  virtual void enterIndex_parameters(IMQLangParser::Index_parametersContext *ctx) = 0;
  virtual void exitIndex_parameters(IMQLangParser::Index_parametersContext *ctx) = 0;


};

}  // namespace imq
