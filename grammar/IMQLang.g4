grammar IMQLang;

////
// Parser
////

compileUnit
    :   EOF
    |   statements EOF
    ;

statements
    :
    (
        statement
    )+
    ;

statement
    :   define_input_stm SEMICOLON
    |   define_output_stm SEMICOLON
    |   set_variable_stm SEMICOLON
    |   set_field_stm SEMICOLON
    |   delete_variable_stm SEMICOLON
    |   select_stm SEMICOLON
    |   branch_stm // no semicolon, uses block syntax
    |   expression SEMICOLON
    ;

define_input_stm
    :   INPUT IDENT (EQUAL expression)?
    ;

define_output_stm
    :   OUTPUT IDENT (EQUAL expression)?
    ;

set_variable_stm
    :   IDENT EQUAL expression
    ;

set_field_stm
    :   variable DOT IDENT EQUAL expression
    ;

delete_variable_stm
    :   DELETE IDENT
    ;

select_stm
    :   expression COLON expression FROM expression
    ;

branch_stm
    :   IF expression L_BRACE statements? R_BRACE
    (
        ELSE L_BRACE statements? R_BRACE
    )?
    ;

expression
    :   orExpr
    ;

orExpr
    :   andExpr
    |   andExpr OR orExpr
    ;

andExpr
    :   equalityExpr
    |   equalityExpr AND andExpr
    ;

equalityExpr
    :   addExpr
    |   addExpr EQUAL EQUAL equalityExpr
    |   addExpr BANG EQUAL equalityExpr
    |   addExpr LESS equalityExpr
    |   addExpr LESS EQUAL equalityExpr
    |   addExpr GREATER equalityExpr
    |   addExpr GREATER EQUAL equalityExpr
    ;

addExpr
    :   mulExpr
    |   mulExpr PLUS addExpr
    |   mulExpr MINUS addExpr
    ;

mulExpr
    :   notExpr
    |   notExpr MULTIPLY mulExpr
    |   notExpr DIVIDE mulExpr
    |   notExpr MODULUS mulExpr
    ;

notExpr
    :   NOT atom
    |   atom
    ;

atom
    :   value
    |   variable
    |   L_PAREN expression R_PAREN
    ;

value
    :   INTEGER
    |   FLOAT
    |   boolean
    |   color
    ;

boolean
    :   B_TRUE
    |   B_FALSE
    ;

color
    :   L_BRACE
    (
        expression // single element applied to rgb
    |   expression COMMA expression COMMA expression // all elements
    )
    (
        COMMA expression // alpha element
    )?
        R_BRACE
    ;

variable
    :   resolved_value (DOT resolved_value)*
    ;

resolved_value
    :   IDENT
    |   IDENT func_parameters
    |   IDENT index_parameters
    ;

func_parameters
    :   L_PAREN (expression (COMMA expression)*)? R_PAREN
    ;

index_parameters
    :   L_BRACKET (expression (COMMA expression)*)? R_BRACKET
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