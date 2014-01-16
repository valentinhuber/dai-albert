/*
 * Dai Albert Compiler 1.0
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted.
 *
 */

%option noyywrap nodefault yylineno

%{
#include "symboltable.h"
#include "y.tab.h"
%}

%%



 /* single character ops */
"+" |
"-" |
"*" |
"/" |
"=" |
"," |
";" |
"(" |
")"     { return yytext[0]; }


"if"    { return IF; }
"then"  { return THEN; }
"else"  { return ELSE; }
"while" { return WHILE; }
"do"    { return DO; }
"let"   { return LET; }
"true"  { return TRUE; }
"false" { return FALSE; }

">"     { yylval.fn = 1; return CMP; }
"<"     { yylval.fn = 2; return CMP; }
"<>"    { yylval.fn = 3; return CMP; }
"=="    { yylval.fn = 4; return CMP; }
">="    { yylval.fn = 5; return CMP; }
"<="    { yylval.fn = 6; return CMP; }

"exit"  { return EXIT; }
"print" { return PRINT; }

[a-zA-Z][a-zA-Z0-9]*  { yylval.s = lookup(yytext); return VARIABLE; }

[0-9]+ | { yylval.d = atof(yytext); return NUMBER; }

"\n"      { return EOL; }
[ \t]   { /* ignore white space */ }
.	{ yyerror("Mystery character %c\n", *yytext); }
%%
