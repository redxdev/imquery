grammar IMQLang;

@parser::header {
    #include "expressions.h"
    #include "mathexpr.h"
    #include "scriptfunction.h"
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
    :   define_input_stm SEMICOLON      {$stm = $define_input_stm.stm;}
    |   define_output_stm SEMICOLON     {$stm = $define_output_stm.stm;}
    |   set_variable_stm SEMICOLON      {$stm = $set_variable_stm.stm;}
    |   set_field_stm SEMICOLON         {$stm = $set_field_stm.stm;}
    |   delete_variable_stm SEMICOLON   {$stm = $delete_variable_stm.stm;}
    |   select_stm SEMICOLON            {$stm = $select_stm.stm;}
    |   break_stm SEMICOLON             {$stm = $break_stm.stm;}
    |   return_stm SEMICOLON            {$stm = $return_stm.stm;}
    |   branch_stm                      {$stm = $branch_stm.stm;} // no semicolon, uses block syntax
    |   for_loop_stm                    {$stm = $for_loop_stm.stm;} // ^^
    |   while_loop_stm                  {$stm = $while_loop_stm.stm;} // ^^
    |   define_function_stm             {$stm = $define_function_stm.stm;} // ^^
    |   expression SEMICOLON            {$stm = createNodeFromToken<VExpressionAsStatement>($expression.start, $expression.expr);}
    |   SEMICOLON                       {$stm = nullptr;} //{$stm = createNodeFromToken<NoOpStm>($SEMICOLON);}
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
    locals [VExpression* whereExpr = nullptr, VExpression* elseExpr = nullptr]
    :   dest=expression COLON calc=expression FROM src=expression
    (
        WHERE where=expression {$whereExpr = $where.expr;}
        (
            ELSE el=expression {$elseExpr = $el.expr;}
        )?
    )?
        {$stm = createNodeFromToken<SelectStm>($dest.start, $dest.expr, $src.expr, $calc.expr, $whereExpr, $elseExpr);}
    ;

branch_stm returns [VStatement* stm]
    locals [VBlock* trueBlock = nullptr, VStatement* falseBlock = nullptr]
    :   IF check=expression L_BRACE
        (statements {$trueBlock = createNodeFromToken<VBlock>($statements.start, $statements.count, $statements.stmArr);})?
        R_BRACE
    (
        ELSE
        (
            elif=branch_stm     {$falseBlock = $elif.stm;}
        |   L_BRACE
            (el=statements {$falseBlock = createNodeFromToken<VBlock>($el.start, $el.count, $el.stmArr);})?
            R_BRACE
        )
    )?
        {$stm = createNodeFromToken<BranchStm>($IF, $check.expr, $trueBlock, $falseBlock);}
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

break_stm returns [VStatement* stm]
    :   BREAK {$stm = createNodeFromToken<BreakStm>($BREAK);}
    ;

return_stm returns [VStatement* stm]
    locals [VExpression* retExpr = nullptr]
    :   RETURN
    (
        expression {$retExpr = $expression.expr;}
    )?
        {$stm = createNodeFromToken<ReturnStm>($RETURN, $retExpr);}
    ;

define_function_stm returns [VStatement* stm]
    locals [VBlock* block = nullptr]
    :   FUNCTION IDENT func_parameters_def L_BRACE
        (statements {$block = createNodeFromToken<VBlock>($statements.start, $statements.count, $statements.stmArr);})?
        R_BRACE
        {
            $stm = createNodeFromToken<SetVariableStm>(
                $FUNCTION,
                $IDENT.text,
                createNodeFromToken<DefineFunctionExpr>($FUNCTION, $IDENT.text, $block, $func_parameters_def.argNames)
            );
        }
    ;

expression returns [VExpression* expr]
    :   ternaryExpr {$expr = $ternaryExpr.expr;}
    ;

ternaryExpr returns [VExpression* expr]
    :   orExpr                                          {$expr = $orExpr.expr;}
        (
            QUESTION t=expression COLON f=expression    {$expr = createNodeFromToken<TernaryExpr>($orExpr.start, $expr, $t.expr, $f.expr);}
        )?
    ;

orExpr returns [VExpression* expr]
    :   andExpr             {$expr = $andExpr.expr;}
    (
        OR orExpr           {$expr = createNodeFromToken<OrExpr>($andExpr.start, $andExpr.expr, $orExpr.expr);}
    )?
    ;

andExpr returns [VExpression* expr]
    :   equalityExpr                {$expr = $equalityExpr.expr;}
    (
        AND andExpr                 {$expr = createNodeFromToken<AndExpr>($equalityExpr.start, $equalityExpr.expr, $andExpr.expr);}
    )?
    ;

equalityExpr returns [VExpression* expr]
    :   addExpr                             {$expr = $addExpr.expr;}
    (
        EQUAL EQUAL equalityExpr            {$expr = createNodeFromToken<EqualExpr>($addExpr.start, $addExpr.expr, $equalityExpr.expr);}
    |   BANG EQUAL equalityExpr             {$expr = createNodeFromToken<NotEqualExpr>($addExpr.start, $addExpr.expr, $equalityExpr.expr);}
    |   LESS
        (
            EQUAL equalityExpr              {$expr = createNodeFromToken<LessEqExpr>($addExpr.start, $addExpr.expr, $equalityExpr.expr);}
        |   equalityExpr                    {$expr = createNodeFromToken<LessExpr>($addExpr.start, $addExpr.expr, $equalityExpr.expr);}
        )
    |   GREATER
        (
            EQUAL equalityExpr              {$expr = createNodeFromToken<GreaterEqExpr>($addExpr.start, $addExpr.expr, $equalityExpr.expr);}
        |   equalityExpr                    {$expr = createNodeFromToken<GreaterExpr>($addExpr.start, $addExpr.expr, $equalityExpr.expr);}
        )
    )?
    ;

addExpr returns [VExpression* expr]
    :   mulExpr                 {$expr = $mulExpr.expr;}
    (
        PLUS addExpr            {$expr = createNodeFromToken<AddExpr>($mulExpr.start, $mulExpr.expr, $addExpr.expr);}
    |   MINUS addExpr           {$expr = createNodeFromToken<SubExpr>($mulExpr.start, $mulExpr.expr, $addExpr.expr);}
    )?
    ;

mulExpr returns [VExpression* expr]
    :   notExpr                     {$expr = $notExpr.expr;}
    (
        MULTIPLY mulExpr            {$expr = createNodeFromToken<MulExpr>($notExpr.start, $notExpr.expr, $mulExpr.expr);}
    |   DIVIDE mulExpr              {$expr = createNodeFromToken<DivExpr>($notExpr.start, $notExpr.expr, $mulExpr.expr);}
    |   MODULUS mulExpr             {$expr = createNodeFromToken<ModExpr>($notExpr.start, $notExpr.expr, $mulExpr.expr);}
    )?
    ;

notExpr returns [VExpression* expr]
    :   NOT notExpr     {$expr = createNodeFromToken<NotExpr>($NOT, $notExpr.expr);}
    |   MINUS notExpr   {$expr = createNodeFromToken<NegateExpr>($MINUS, $notExpr.expr);}
    |   fieldExpr       {$expr = $fieldExpr.expr;}
    ;

fieldExpr returns [VExpression* expr]
    :   callExpr            {$expr = $callExpr.expr;}
    (
        DOT field[$expr]    {$expr = $field.expr;}
    )*
    ;

callExpr returns [VExpression* expr]
    :   atom                {$expr = $atom.expr;}
    (
        func_parameters     {$expr = createNodeFromToken<CallFunctionExpr>($atom.start, $atom.expr, $func_parameters.count, $func_parameters.args);}
    |   index_parameters    {$expr = createNodeFromToken<RetrieveIndexExpr>($atom.start, $atom.expr, $index_parameters.expr);}
    )?
    ;

atom returns [VExpression* expr]
    :   value                       {$expr = $value.expr;}
    |   variable                    {$expr = $variable.expr;}
    |   L_PAREN expression R_PAREN  {$expr = $expression.expr;}
    ;

value returns [VExpression* expr]
    :   const_value     {$expr = createNodeFromToken<ConstantExpr>($const_value.start, $const_value.val);}
    |   color           {$expr = $color.expr;}
    |   function_expr   {$expr = $function_expr.expr;}
    ;

const_value returns [QValue val]
    :   INTEGER     {$val = QValue::Integer(std::stoi($INTEGER.text));}
    |   FLOAT       {$val = QValue::Float(std::stof($FLOAT.text));}
    |   NIL         {$val = QValue::Nil();}
    |   boolean     {$val = QValue::Bool($boolean.val);}
    ;

boolean returns [bool val]
    :   B_TRUE {$val = true;}
    |   B_FALSE {$val = false;}
    ;

color returns [VExpression* expr]
    locals [VExpression* rExpr = nullptr, VExpression* gExpr = nullptr, VExpression* bExpr = nullptr, VExpression* aExpr = nullptr]
    :   L_BRACE
        r=expression                            {$rExpr = $r.expr;}
    (
        COMMA g=expression COMMA b=expression   {$gExpr = $g.expr; $bExpr = $b.expr;}
    )?
    (
        COMMA a=expression {$aExpr = $a.expr;}
    )?
        R_BRACE {$expr = createNodeFromToken<ColorExpr>($L_BRACE, $rExpr, $gExpr, $bExpr, $aExpr);}
    ;

function_expr returns [VExpression* expr]
    locals [VBlock* block = nullptr]
    :   func_parameters_def ARROW
    (
        L_BRACE
        (statements {$block = createNodeFromToken<VBlock>($statements.start, $statements.count, $statements.stmArr);})?
        R_BRACE
    |   expression
        {
            $block = createNodeFromToken<VBlock>(
                $expression.start,
                1,
                new VStatement*[1] {
                    createNodeFromToken<ReturnStm>(
                        $expression.start,
                        $expression.expr
                    )
                }
            );
        }
    )
        {$expr = createNodeFromToken<DefineFunctionExpr>($func_parameters_def.start, $block, $func_parameters_def.argNames);}
    ;

variable returns [VExpression* expr]
    :   IDENT {$expr = createNodeFromToken<RetrieveVariableExpr>($IDENT, $IDENT.text);}
    ;

field [VExpression* subexpr] returns [VExpression* expr]
    :   IDENT               {$expr = createNodeFromToken<RetrieveFieldExpr>($IDENT, $subexpr, $IDENT.text);}
    (
        func_parameters     {$expr = createNodeFromToken<CallFunctionExpr>($IDENT, $expr, $func_parameters.count, $func_parameters.args);}
    |   index_parameters    {$expr = createNodeFromToken<RetrieveIndexExpr>($IDENT, $expr, $index_parameters.expr);}
    )?
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

func_parameters_def returns [std::vector<std::string> argNames]
    :   L_PAREN
    (   first=IDENT         {$argNames.push_back($first.text);}
        (
            COMMA n=IDENT   {$argNames.push_back($n.text);}
        )*
    )?   R_PAREN
    ;

////
// Lexer
////

SEMICOLON
    :   ';'
    ;

FUNCTION
    :   'func'
    ;

DELETE
    :   'delete'
    ;

BREAK
    :   'break'
    ;

RETURN
    :   'return'
    ;

INPUT
    :   'in'
    ;

WHERE
    :   'where'
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

ARROW
    :   '=>'
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

QUESTION
    :   '?'
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

NIL
    :   'nil'
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