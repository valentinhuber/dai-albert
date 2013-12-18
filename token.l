/*
 * Dai Albert Compiler 1.0
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted.
 *
 * * Albers Mama isch sou fett...Putana Dai Albert
 *
 */

%{
#include "y.tab.h"
%}
%%
"q"   return STOP;
"a"   return ALBERT;
"("   return OP;
")"   return CP;
"="   return ASSIGN;
"=="  return EQUALS;
[0-9] return DIGIT;
[a-z] return LOWERCASELETTER;
[A-Z] return UPPERCASELETTER;
.     return OTHER;
%%
