%{
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdarg.h>
#include "symboltable.h"

/* prototypes */
int yylex(void);
%}

%union {
    treeNode *node;
    int iValue;                 /* integer value */
    char* sValue;
    char* variableNode;         /* name of variable in symbol table */
    int type;
};

%token MAIN
%token <iValue> INTEGER
%token <sValue> STRING_LITERAL
%token <variableNode> VARIABLE
%token WHILE IF PRINT
%token TRUE
%token FALSE
%nonassoc IFX
%nonassoc ELSE

%token <node> INT
%token <node> FLOAT
%token <node> BOOL
%token <node> STRING
%type <node> expr stmt scope stmts function init assignment declaration


%left GE LE EQ NE '>' '<'
%left '+' '-'
%left '*' '/'
%nonassoc UMINUS

%start program
%%

program: 
        init function            { exit(0); }

init: /* NULL */                 { makeTable(NULL); }; 
    ;

function: 
        MAIN scope               {   } //printf("main\n");    freeNode($2);
        ;


scope:   '{' stmts '}'           { evaluate($2); }
        ;

stmts:  stmt                   { $$ = $1; } //freeNode($2);
        | stmts stmt            { $$ = newOperationNode('l', 2, $1, $2); }
        ;

stmt:    PRINT expr ';'                  { $$ = newOperationNode(PRINT, 1, $2);}
        | VARIABLE '=' expr ';'          { $$ = newOperationNode('=', 2, newVariableNode($1, 0, yylineno), $3);}
                                         
        | WHILE '(' expr ')' stmt        { $$ = newOperationNode(WHILE, 2, $3, $5); }
        | IF '(' expr ')' stmt %prec IFX { $$ = newOperationNode(IF, 2, $3, $5); }
        | IF '(' expr ')' stmt ELSE stmt { $$ = newOperationNode(ELSE, 3, $3, $5, $7); }
        | '{' stmts '}'                  { $$ = $2; } 
        | declaration ';'                { $$ = $1; } 
        ;

declaration: INT { $<type>$ = 'i'; } assignment              { $$ = $3; }
        | STRING { $<type>$ = 's'; } assignment              { $$ = $3; }
        ;

assignment: VARIABLE                        { $$ = newOperationNode('=', 1, newVariableNode($1, $<type>0, yylineno)); }
            | VARIABLE '=' expr             { $$ = newOperationNode('=', 2, newVariableNode($1, $<type>0, yylineno), $3);}
            ;

expr:    INTEGER                { $$ = newNumberNode($1); }
        | STRING_LITERAL        { $$ = newStringNode($1); }
        | VARIABLE              { $$ = newVariableNode($1,$<type>0, yylineno); }
        | expr '+' expr         { $$ = newOperationNode('+', 2 ,$1, $3); }
        | expr '-' expr         { $$ = newOperationNode('-', 2 ,$1, $3); }
        | expr '*' expr         { $$ = newOperationNode('*', 2 ,$1, $3); }
        | expr '/' expr         { $$ = newOperationNode('/', 2 ,$1, $3); }
        | expr '<' expr         { $$ = newOperationNode('<', 2 ,$1, $3); }
        | expr '>' expr         { $$ = newOperationNode('>', 2 ,$1, $3); }
        | expr GE expr          { $$ = newOperationNode(GE, 2 ,$1, $3); }
        | expr LE expr          { $$ = newOperationNode(LE, 2 ,$1, $3); }
        | expr NE expr          { $$ = newOperationNode(NE, 2 ,$1, $3); }
        | expr EQ expr          { $$ = newOperationNode(EQ, 2 ,$1, $3); }
        | '(' expr ')'          { $$ = $2; }
        ;
%%

extern int yy_flex_debug;
int main(void) {
    return(yyparse());
}