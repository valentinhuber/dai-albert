/*
 * Dai Albert Compiler 1.0
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted.
 *
 */

%{
#include <stdio.h>
%}

/* Declare Tokens */
%token DIGIT LOWERCASELETTER UPPERCASELETTER OTHER STOP 
%token ALBERT
%token CP OP ASSIGN

%%
start :
    | start something
    ;

something : DIGIT {printf("DIGIT\n");}
    | LOWERCASELETTER {printf("LOWERCASELETTER\n");}
    | UPPERCASELETTER {printf("UPPERCASELETTER\n");}
    | OTHER {printf("OTHER\n");}
    | ALBERT {printf("Dai Albert!!");}
    | STOP {exit(0);}
    ;
%%

main()
{
    // Intro
    printf("Type something followed by Return. Type 'q' to end.\n");
    printf("\n");
    // Start the parser
    return(yyparse());
}

yyerror(s)
char *s;
{
    printf("yacc error: %s\n", s);
}

yywrap()
{
    return(0);
}

