grammar IMQLang;

options {
    language=Cpp;
}

@parser::header {
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
}

////
// Parser
////

compileUnit returns [VBlock* block]
    :   EOF {$block = nullptr;}
    |   statements EOF {$block = createNodeFromToken<VBlock>($statements.start, $statements.count, $statements.stmArr);}
    ;

statements returns [int32_t count, VStatement** stmArr]
    locals [std::vector<VStatement*> stmList]
    :
    (
        statement {$stmList.push_back($statement.stm);}
    )+
        {
            $count = $stmList.size();
            $stmArr = new VStatement*[$stmList.size()];
            std::copy($stmList.begin(), $stmList.end(), $stmArr);
        }
    ;

statement returns [VStatement* stm]
    :   define_input_stm SEMICOLON {$stm = $define_input_stm.stm;}
    |   define_output_stm SEMICOLON {$stm = $define_output_stm.stm;}
    |   set_variable_stm SEMICOLON {$stm = $set_variable_stm.stm;}
    |   set_field_stm SEMICOLON {$stm = $set_field_stm.stm;}
    |   delete_variable_stm SEMICOLON {$stm = $delete_variable_stm.stm;}
    |   select_stm SEMICOLON {$stm = $select_stm.stm;}
    |   branch_stm {$stm = $branch_stm.stm;} // no semicolon, uses block syntax
    |   for_loop_stm {$stm = $for_loop_stm.stm;} // ^^
    |   while_loop_stm {$stm = $while_loop_stm.stm;} // ^^
    |   expression SEMICOLON {$stm = createNodeFromToken<VExpressionAsStatement>($expression.start, $expression.expr);}
    |   SEMICOLON {$stm = nullptr;}
    ;

define_input_stm returns [VStatement* stm]
    :   INPUT IDENT EQUAL expression {$stm = createNodeFromToken<DefineInputStm>($INPUT, $IDENT.text, $expression.expr);}
    ;

define_output_stm returns [VStatement* stm]
    locals [VExpression* valueExpr = nullptr]
    :   OUTPUT IDENT
        (EQUAL expression {$valueExpr = $expression.expr;})?
        {$stm = createNodeFromToken<DefineOutputStm>($OUTPUT, $IDENT.text, $valueExpr);}
    ;

set_variable_stm returns [VStatement* stm]
    :   IDENT EQUAL expression {$stm = createNodeFromToken<SetVariableStm>($IDENT, $IDENT.text, $expression.expr);}
    ;

set_field_stm returns [VStatement* stm]
    :   variable DOT IDENT EQUAL expression {$stm = createNodeFromToken<SetFieldStm>($variable.start, $variable.expr, $IDENT.text, $expression.expr);}
    ;

delete_variable_stm returns [VStatement* stm]
    :   DELETE IDENT {$stm = createNodeFromToken<DeleteVariableStm>($DELETE, $IDENT.text);}
    ;

select_stm returns [VStatement* stm]
    :   dest=expression COLON calc=expression FROM src=expression {$stm = createNodeFromToken<SelectStm>($dest.start, $dest.expr, $src.expr, $calc.expr);}
    ;

branch_stm returns [VStatement* stm]
    locals [VBlock* trueBlock = nullptr, VStatement* falseBlock = nullptr]
    :   IF expression L_BRACE statements? R_BRACE
    (
        ELSE elif=branch_stm                {$falseBlock = $branch_stm.stm;}
    |   ELSE L_BRACE
        (statements {$falseBlock = createNodeFromToken<VBlock>($statements.start, $statements.count, $statements.stmArr);})?
        R_BRACE
    )?
    ;

for_loop_stm returns [VStatement* stm]
    locals [VBlock* block = nullptr]
    :   FOR init=statement expression SEMICOLON incr=statement L_BRACE
        (statements {$block = createNodeFromToken<VBlock>($statements.start, $statements.count, $statements.stmArr);})?
        R_BRACE
        {
            $stm = createNodeFromToken<ForLoopStm>($FOR, $init.stm, $expression.expr, $incr.stm, $block);
        }
    ;

while_loop_stm returns [VStatement* stm]
    locals [VBlock* block = nullptr]
    :   WHILE expression L_BRACE
        (statements {$block = createNodeFromToken<VBlock>($statements.start, $statements.count, $statements.stmArr);})?
        R_BRACE
        {
            $stm = createNodeFromToken<WhileLoopStm>($WHILE, $expression.expr, $block);
        }
    ;

expression returns [VExpression* expr]
    :   orExpr  {$expr = $orExpr.expr;}
    ;

orExpr returns [VExpression* expr]
    :   andExpr             {$expr = $andExpr.expr;}
    |   andExpr OR orExpr   {$expr = createNodeFromToken<OrExpr>($andExpr.start, $andExpr.expr, $orExpr.expr);}
    ;

andExpr returns [VExpression* expr]
    :   equalityExpr                {$expr = $equalityExpr.expr;}
    |   equalityExpr AND andExpr    {$expr = createNodeFromToken<AndExpr>($equalityExpr.start, $equalityExpr.expr, $andExpr.expr);}
    ;

equalityExpr returns [VExpression* expr]
    :   addExpr                             {$expr = $addExpr.expr;}
    |   addExpr EQUAL EQUAL equalityExpr    {$expr = createNodeFromToken<EqualExpr>($addExpr.start, $addExpr.expr, $equalityExpr.expr);}
    |   addExpr BANG EQUAL equalityExpr     {$expr = createNodeFromToken<NotEqualExpr>($addExpr.start, $addExpr.expr, $equalityExpr.expr);}
    |   addExpr LESS equalityExpr           {$expr = createNodeFromToken<LessExpr>($addExpr.start, $addExpr.expr, $equalityExpr.expr);}
    |   addExpr LESS EQUAL equalityExpr     {$expr = createNodeFromToken<LessEqExpr>($addExpr.start, $addExpr.expr, $equalityExpr.expr);}
    |   addExpr GREATER equalityExpr        {$expr = createNodeFromToken<GreaterExpr>($addExpr.start, $addExpr.expr, $equalityExpr.expr);}
    |   addExpr GREATER EQUAL equalityExpr  {$expr = createNodeFromToken<GreaterEqExpr>($addExpr.start, $addExpr.expr, $equalityExpr.expr);}
    ;

addExpr returns [VExpression* expr]
    :   mulExpr                 {$expr = $mulExpr.expr;}
    |   mulExpr PLUS addExpr    {$expr = createNodeFromToken<AddExpr>($mulExpr.start, $mulExpr.expr, $addExpr.expr);}
    |   mulExpr MINUS addExpr   {$expr = createNodeFromToken<SubExpr>($mulExpr.start, $mulExpr.expr, $addExpr.expr);}
    ;

mulExpr returns [VExpression* expr]
    :   notExpr                     {$expr = $notExpr.expr;}
    |   notExpr MULTIPLY mulExpr    {$expr = createNodeFromToken<MulExpr>($notExpr.start, $notExpr.expr, $mulExpr.expr);}
    |   notExpr DIVIDE mulExpr      {$expr = createNodeFromToken<DivExpr>($notExpr.start, $notExpr.expr, $mulExpr.expr);}
    |   notExpr MODULUS mulExpr     {$expr = createNodeFromToken<ModExpr>($notExpr.start, $notExpr.expr, $mulExpr.expr);}
    ;

notExpr returns [VExpression* expr]
    :   NOT notExpr     {$expr = createNodeFromToken<NotExpr>($NOT, $notExpr.expr);}
    |   MINUS notExpr   {$expr = createNodeFromToken<NegateExpr>($MINUS, $notExpr.expr);}
    |   atom            {$expr = $atom.expr;}
    ;

atom returns [VExpression* expr]
    :   value                       {$expr = $value.expr;}
    |   variable                    {$expr = $variable.expr;}
    |   L_PAREN expression R_PAREN  {$expr = $expression.expr;}
    ;

value returns [VExpression* expr]
    :   const_value {$expr = createNodeFromToken<ConstantExpr>($const_value.start, $const_value.val);}
    |   color       {$expr = $color.expr;}
    ;

const_value returns [QValue val]
    :   INTEGER     {$val = QValue::Integer(std::stoi($INTEGER.text));}
    |   FLOAT       {$val = QValue::Float(std::stof($FLOAT.text));}
    |   boolean     {$val = QValue::Bool($boolean.val);}
    ;

boolean returns [bool val]
    :   B_TRUE {$val = true;}
    |   B_FALSE {$val = false;}
    ;

color returns [VExpression* expr]
    locals [VExpression* rExpr = nullptr, VExpression* gExpr = nullptr, VExpression* bExpr = nullptr, VExpression* aExpr = nullptr]
    :   L_BRACE
    (
        r=expression {$rExpr = $r.expr;} // single element applied to rgb
    |   r=expression COMMA g=expression COMMA b=expression // all elements
    {
        $rExpr = $r.expr;
        $gExpr = $g.expr;
        $bExpr = $b.expr;
    }
    )
    (
        COMMA a=expression {$aExpr = $a.expr;} // alpha element
    )?
        R_BRACE {$expr = createNodeFromToken<ColorExpr>($L_BRACE, $rExpr, $gExpr, $bExpr, $aExpr);}
    ;

variable returns [VExpression* expr]
    :   resolved_variable   {$expr = $resolved_variable.expr;}
    (
        DOT resolved_field[$expr]  {$expr = $resolved_field.expr;}
    )*
    ;

resolved_variable returns [VExpression* expr]
    :   IDENT                   {$expr = createNodeFromToken<RetrieveVariableExpr>($IDENT, $IDENT.text);}
    |   IDENT func_parameters
        {
            $expr = createNodeFromToken<CallFunctionExpr>(
                $IDENT,
                createNodeFromToken<RetrieveVariableExpr>($IDENT, $IDENT.text),
                $func_parameters.count,
                $func_parameters.args
            );
        }
    |   IDENT index_parameters
        {
            $expr = createNodeFromToken<RetrieveIndexExpr>(
                $IDENT,
                createNodeFromToken<RetrieveVariableExpr>($IDENT, $IDENT.text),
                $index_parameters.expr
            );
        }
    ;

resolved_field [VExpression* subexpr] returns [VExpression* expr]
    :   IDENT                   {$expr = createNodeFromToken<RetrieveFieldExpr>($IDENT, $subexpr, $IDENT.text);}
    |   IDENT func_parameters
        {
            $expr = createNodeFromToken<CallFunctionExpr>(
                $IDENT,
                createNodeFromToken<RetrieveFieldExpr>($IDENT, $subexpr, $IDENT.text),
                $func_parameters.count,
                $func_parameters.args
            );
        }
    |   IDENT index_parameters
        {
            $expr = createNodeFromToken<RetrieveIndexExpr>(
                $IDENT,
                createNodeFromToken<RetrieveFieldExpr>($IDENT, $subexpr, $IDENT.text),
                $index_parameters.expr
            );
        }
    ;

func_parameters returns [int32_t count, VExpression** args]
    locals [std::vector<VExpression*> exprList]
    :   L_PAREN
    (   first=expression        {$exprList.push_back($first.expr);}
        (
            COMMA n=expression  {$exprList.push_back($n.expr);}
        )*
    )?  R_PAREN
        {
            $count = $exprList.size();
            $args = new VExpression*[$count];
            std::copy($exprList.begin(), $exprList.end(), $args);
        }
    ;

index_parameters returns [VExpression* expr]
    :   L_BRACKET expression R_BRACKET {$expr = $expression.expr;}
    ;

////
// Lexer
////

SEMICOLON
    :   ';'
    ;

DELETE
    :   'delete'
    ;

INPUT
    :   'in'
    ;

OUTPUT
    :   'out'
    ;

FROM
    :   'from'
    ;

IF
    :   'if'
    ;

ELSE
    :   'else'
    ;

FOR
    :   'for'
    ;

WHILE
    :   'while'
    ;

DO
    :   'do'
    ;

L_PAREN
    :   '('
    ;

R_PAREN
    :   ')'
    ;

L_BRACKET
    :   '['
    ;

R_BRACKET
    :   ']'
    ;

L_BRACE
    :   '{'
    ;

R_BRACE
    :   '}'
    ;

COMMA
    :   ','
    ;

COLON
    :   ':'
    ;

DOT
    :   '.'
    ;

NOT
    :   'not'
    ;

AND
    :   'and'
    ;

OR
    :   'or'
    ;

EQUAL
    :   '='
    ;

BANG
    :   '!'
    ;

GREATER
    :   '>'
    ;

LESS
    :   '<'
    ;

PLUS
    :   '+'
    ;

MINUS
    :   '-'
    ;

MULTIPLY
    :   '*'
    ;

DIVIDE
    :   '/'
    ;

MODULUS
    :   '%'
    ;

B_TRUE
    :   'true'
    ;

B_FALSE
    :   'false'
    ;

FLOAT
    :   '-'? [0-9]+ '.' [0-9]*
    ;

INTEGER
    :   '-'? [0-9]+
    ;

IDENT
    :   [a-zA-Z_] [0-9a-zA-Z_]*
    ;

WS
    :   [ \n\t\r] -> channel(HIDDEN)
    ;

COMMENT
    :   '#' ~[\r\n]* -> channel(HIDDEN)
    ;