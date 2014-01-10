/* 
 * File:   symboltable.c
 * Author: hons
 *
 * Created on 10. Januar 2014, 13:20
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symboltable.h"

table *currentTable;
table *firstTable;

/*
 * 
 */
table *makeTable(table *parent) {
    table *t;
    t = (table *) malloc(sizeof(table *));
    t->parent = parent;
    t->child = NULL;
    t->name = NULL;
    t->first = NULL;
}
void enter(table *t, char *name, int type, int offset) {

}

void addWidth(table *t, int width) {

}

void enterProc(table *t, char *name, table *newTable) {

}

/**
 * Get the width of all symbol tables (stacksize)
 * @param t
 * @return 
 */
int getWidth(table *t) {
    int width = 0;
    while (t->child != NULL) {
        width += t->width;
        t = t->child;
    } 
    return width;
}

/*
 * 
 */
int main(int argc, char** argv) {

    return (EXIT_SUCCESS);
}

