%option noyywrap nodefault yylineno

%{
#include <stdlib.h>
#include <string.h>
#include "symboltable.h"
#include "y.tab.h"
%}

%%

0                   { yylval.iValue = atoi(yytext); return INTEGER; }

[1-9][0-9]*         { yylval.iValue = atoi(yytext); return INTEGER; }

\"(\\.|[^\\"])*\"   { yylval.sValue = strdup(yytext); return STRING_LITERAL; }

[-()<>=+*/;{}.]     { return *yytext; }

">="                return GE;
"<="                return LE;
"=="                return EQ;
"!="                return NE;
"while"             return WHILE;
"if"                return IF;
"else"              return ELSE;
"print"             return PRINT;
"main"              return MAIN;

"int"               return INT;
"bool"              return BOOL;
"float"             return FLOAT;
"string"            return STRING; 
"true"              return TRUE;
"false"             return FALSE;

[a-z][A-z0-9]*      { yylval.variableNode = strdup(yytext); return VARIABLE; }

[ \t]               ;   /* ignore whitespace */

[\n]                ;   /* ignore newline */

"//".*"\n"          ;   /* ignore single line comments */
"/*"(.|"\n")*"*/\n" ;   /* ignore multi line comments */

.                   { yyerror("Unknown character %c\n", *yytext); }
%%