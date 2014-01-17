yacc -vd token.y
flex token.l
gcc -c y.tab.c lex.yy.c symboltable.c
gcc y.tab.o lex.yy.o symboltable.o
./a.out < testFile.txt
