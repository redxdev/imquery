
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
#include "IMQLangListener.h"


namespace imq {

/**
 * This class provides an empty implementation of IMQLangListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class IMQLangBaseListener : public IMQLangListener {
public:

  virtual void enterCompileUnit(IMQLangParser::CompileUnitContext * /*ctx*/) override { }
  virtual void exitCompileUnit(IMQLangParser::CompileUnitContext * /*ctx*/) override { }

  virtual void enterStatements(IMQLangParser::StatementsContext * /*ctx*/) override { }
  virtual void exitStatements(IMQLangParser::StatementsContext * /*ctx*/) override { }

  virtual void enterStatement(IMQLangParser::StatementContext * /*ctx*/) override { }
  virtual void exitStatement(IMQLangParser::StatementContext * /*ctx*/) override { }

  virtual void enterDefine_input_stm(IMQLangParser::Define_input_stmContext * /*ctx*/) override { }
  virtual void exitDefine_input_stm(IMQLangParser::Define_input_stmContext * /*ctx*/) override { }

  virtual void enterDefine_output_stm(IMQLangParser::Define_output_stmContext * /*ctx*/) override { }
  virtual void exitDefine_output_stm(IMQLangParser::Define_output_stmContext * /*ctx*/) override { }

  virtual void enterSet_variable_stm(IMQLangParser::Set_variable_stmContext * /*ctx*/) override { }
  virtual void exitSet_variable_stm(IMQLangParser::Set_variable_stmContext * /*ctx*/) override { }

  virtual void enterSet_field_stm(IMQLangParser::Set_field_stmContext * /*ctx*/) override { }
  virtual void exitSet_field_stm(IMQLangParser::Set_field_stmContext * /*ctx*/) override { }

  virtual void enterDelete_variable_stm(IMQLangParser::Delete_variable_stmContext * /*ctx*/) override { }
  virtual void exitDelete_variable_stm(IMQLangParser::Delete_variable_stmContext * /*ctx*/) override { }

  virtual void enterSelect_stm(IMQLangParser::Select_stmContext * /*ctx*/) override { }
  virtual void exitSelect_stm(IMQLangParser::Select_stmContext * /*ctx*/) override { }

  virtual void enterBranch_stm(IMQLangParser::Branch_stmContext * /*ctx*/) override { }
  virtual void exitBranch_stm(IMQLangParser::Branch_stmContext * /*ctx*/) override { }

  virtual void enterFor_loop_stm(IMQLangParser::For_loop_stmContext * /*ctx*/) override { }
  virtual void exitFor_loop_stm(IMQLangParser::For_loop_stmContext * /*ctx*/) override { }

  virtual void enterWhile_loop_stm(IMQLangParser::While_loop_stmContext * /*ctx*/) override { }
  virtual void exitWhile_loop_stm(IMQLangParser::While_loop_stmContext * /*ctx*/) override { }

  virtual void enterExpression(IMQLangParser::ExpressionContext * /*ctx*/) override { }
  virtual void exitExpression(IMQLangParser::ExpressionContext * /*ctx*/) override { }

  virtual void enterOrExpr(IMQLangParser::OrExprContext * /*ctx*/) override { }
  virtual void exitOrExpr(IMQLangParser::OrExprContext * /*ctx*/) override { }

  virtual void enterAndExpr(IMQLangParser::AndExprContext * /*ctx*/) override { }
  virtual void exitAndExpr(IMQLangParser::AndExprContext * /*ctx*/) override { }

  virtual void enterEqualityExpr(IMQLangParser::EqualityExprContext * /*ctx*/) override { }
  virtual void exitEqualityExpr(IMQLangParser::EqualityExprContext * /*ctx*/) override { }

  virtual void enterAddExpr(IMQLangParser::AddExprContext * /*ctx*/) override { }
  virtual void exitAddExpr(IMQLangParser::AddExprContext * /*ctx*/) override { }

  virtual void enterMulExpr(IMQLangParser::MulExprContext * /*ctx*/) override { }
  virtual void exitMulExpr(IMQLangParser::MulExprContext * /*ctx*/) override { }

  virtual void enterNotExpr(IMQLangParser::NotExprContext * /*ctx*/) override { }
  virtual void exitNotExpr(IMQLangParser::NotExprContext * /*ctx*/) override { }

  virtual void enterAtom(IMQLangParser::AtomContext * /*ctx*/) override { }
  virtual void exitAtom(IMQLangParser::AtomContext * /*ctx*/) override { }

  virtual void enterValue(IMQLangParser::ValueContext * /*ctx*/) override { }
  virtual void exitValue(IMQLangParser::ValueContext * /*ctx*/) override { }

  virtual void enterConst_value(IMQLangParser::Const_valueContext * /*ctx*/) override { }
  virtual void exitConst_value(IMQLangParser::Const_valueContext * /*ctx*/) override { }

  virtual void enterBoolean(IMQLangParser::BooleanContext * /*ctx*/) override { }
  virtual void exitBoolean(IMQLangParser::BooleanContext * /*ctx*/) override { }

  virtual void enterColor(IMQLangParser::ColorContext * /*ctx*/) override { }
  virtual void exitColor(IMQLangParser::ColorContext * /*ctx*/) override { }

  virtual void enterVariable(IMQLangParser::VariableContext * /*ctx*/) override { }
  virtual void exitVariable(IMQLangParser::VariableContext * /*ctx*/) override { }

  virtual void enterResolved_variable(IMQLangParser::Resolved_variableContext * /*ctx*/) override { }
  virtual void exitResolved_variable(IMQLangParser::Resolved_variableContext * /*ctx*/) override { }

  virtual void enterResolved_field(IMQLangParser::Resolved_fieldContext * /*ctx*/) override { }
  virtual void exitResolved_field(IMQLangParser::Resolved_fieldContext * /*ctx*/) override { }

  virtual void enterFunc_parameters(IMQLangParser::Func_parametersContext * /*ctx*/) override { }
  virtual void exitFunc_parameters(IMQLangParser::Func_parametersContext * /*ctx*/) override { }

  virtual void enterIndex_parameters(IMQLangParser::Index_parametersContext * /*ctx*/) override { }
  virtual void exitIndex_parameters(IMQLangParser::Index_parametersContext * /*ctx*/) override { }


  virtual void enterEveryRule(ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(tree::ErrorNode * /*node*/) override { }

};

}  // namespace imq
