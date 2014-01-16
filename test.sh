bison -y -d token.y
flex token.l
gcc -c y.tab.c lex.yy.c
./a.out < testFile.txt