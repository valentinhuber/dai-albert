yacc -vd token.y
flex token.l
gcc -c y.tab.c lex.yy.c
gcc y.tab.o lex.yy.o
./a.out < testFile.txt
