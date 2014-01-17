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
    char* sValue;                /* symbol table index */
    int type;
    int i;
};

%token MAIN
%token <iValue> INTEGER
%token <sValue> VARIABLE
%token WHILE IF PRINT
%token TRUE
%token FALSE
%nonassoc IFX
%nonassoc ELSE

%token <type> INT
%token <type> FLOAT
%token <type> BOOL
%token <type> STRING

%type <node> expr stmt

%left GE LE EQ NE '>' '<'
%left '+' '-'
%left '*' '/'
%nonassoc UMINUS

%start function
%%

function: MAIN scope         { printf("main\n"); }
        ;


scope:   '{' stmts '}'         { printf("scope\n"); }
        ;

stmts:   /* NULL */
        | stmts stmt        { printf("stmt\n"); }
        ;

stmt:   ';'                              { printf("semicolon\n"); }
        | declaration ';'                { printf("declaration\n"); }
        | expr ';'                       { evaluate($1); }
        | PRINT expr ';'                 { printf("%i",evaluate($2)); }
        | VARIABLE '=' expr ';'          { printf("assignment\n"); }
        | WHILE '(' expr ')' stmt        { printf("while"); }
        | IF '(' expr ')' stmt %prec IFX { printf("if"); }
        | IF '(' expr ')' stmt ELSE stmt { printf("if else"); }
        | scope                          { printf(";"); } 
        ;

declaration: INT { $<type>$ = 'i'; } expr ';'
/*
stmt_list:
          stmt                  { $$ = $1; }
        | stmt_list stmt        { $$ = opr(';', 2, $1, $2); }
        ;
*/
expr:
          INTEGER               { $$ = newNumberNode($1); }
        | VARIABLE              { printf("VARIABLE"); }
  /*      | '-' expr %prec UMINUS { $$ = opr(UMINUS, 1, $2); } */
        | expr '+' expr         { $$ = newSyntaxTreeNode('+',$1, $3); }
        | expr '-' expr         { printf("-"); }
        | expr '*' expr         { printf("*"); }
        | expr '/' expr         { printf("/"); }
     /*   | expr '<' expr         { $$ = opr('<', 2, $1, $3); }
        | expr '>' expr         { $$ = opr('>', 2, $1, $3); }
        | expr GE expr          { $$ = opr(GE, 2, $1, $3); }
        | expr LE expr          { $$ = opr(LE, 2, $1, $3); }
        | expr NE expr          { $$ = opr(NE, 2, $1, $3); }
        | expr EQ expr          { $$ = opr(EQ, 2, $1, $3); }
        | '(' expr ')'          { $$ = $2; } */
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
