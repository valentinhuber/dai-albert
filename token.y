%{
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdarg.h>
#include "symboltable.h"

/* prototypes */
int yylex(void);
void yyerror(char *s);
%}

%union {
    struct syntaxTreeNode *node;
    int iValue;                 /* integer value */
    char* variableNode;         /* name of variable in symbol table */
    int type;
};

%token MAIN
%token <iValue> INTEGER
%token <variableNode> VARIABLE
%token WHILE IF PRINT
%token TRUE
%token FALSE
%nonassoc IFX
%nonassoc ELSE

%token <type> INT
%token <type> FLOAT
%token <type> BOOL
%token <type> STRING

%type <node> expr stmt scope stmts function init

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

stmts:   
         stmt                   { $$ = $1; } //freeNode($2);
        | stmts stmt            { $$ = newOperationNode('l', 2, $1, $2); }
        ;

stmt:    PRINT expr ';'                  { $$ = newOperationNode(PRINT, 1, $2);}
        | VARIABLE '=' expr ';'          { $$ = newOperationNode('=', 2, newVariableNode($1,0), $3);}
                                         
        | WHILE '(' expr ')' stmt        { $$ = newOperationNode(WHILE, 2, $3, $5); }
        | IF '(' expr ')' stmt %prec IFX { $$ = newOperationNode(IF, 2, $3, $5); }
        | IF '(' expr ')' stmt ELSE stmt { $$ = newOperationNode(ELSE, 3, $3, $5, $7); }
        | '{' stmts '}'                  { $$ = $2; } 
    /*  | declaration ';'                { printf("declaration\n"); } */
        ;

/* declaration: INT { $<type>$ = 'i'; } expr ';' */


expr:
          INTEGER               { $$ = newNumberNode($1); }
        | VARIABLE              { $$ = newVariableNode($1,0); }
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

void yyerror(char *s) {
    fprintf(stdout, "%s\n", s);
}


extern int yy_flex_debug;
int main(void) {
    printf("\n");
    return(yyparse());
}
