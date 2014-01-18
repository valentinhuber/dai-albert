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
    char* variableNode;                /* name of variable in symbol table */
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

%type <node> expr stmt scope stmts function

%left GE LE EQ NE '>' '<'
%left '+' '-'
%left '*' '/'
%nonassoc UMINUS

%start program
%%

program: 
        init function            { exit(0); }

init: /* NULL */ { makeTable(NULL); }; 
    ;

function: 
        MAIN scope         {   } //printf("main\n");    freeNode($2);
        |
        ;


scope:   '{' stmts '}'         {  }
        ;

stmts:   
        | stmts stmt        { evaluate($2); } //freeNode($2);
        ;

stmt:   ';'                              { printf("semicolon\n"); }
        | declaration ';'                { printf("declaration\n"); }
     /*   | expr ';'                       { printf("des isch um schuscht"); } */
        | PRINT expr ';'                 { $$ = newOperationNode('p', 1, $2);}
        | VARIABLE '=' expr ';'          { $$ = newOperationNode('=', 2, newVariableNode($1,0), $3); }
      /*  | WHILE '(' expr ')' stmt        { printf("while"); }
        | IF '(' expr ')' stmt %prec IFX { printf("if"); }
        | IF '(' expr ')' stmt ELSE stmt { printf("if else"); } */
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
        | VARIABLE              { $$ = newVariableNode($1,0); }
  /*      | '-' expr %prec UMINUS { $$ = opr(UMINUS, 1, $2); } */
        | expr '+' expr         { $$ = newOperationNode('+', 2 ,$1, $3); }
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
