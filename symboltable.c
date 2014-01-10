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
    
    currentTable = t;
    
    return currentTable;
}
void enter(table *t, char *name, int type) {
    node *p;
    
    
    p = t->first;
    
    while(p != NULL && p->next != NULL) {
        p = p->next;
    }
    
    node *n;
    n = (node *)malloc(sizeof(node));
    
    
    n->name = name;
    n->type = type;
    n->next = NULL;
    
    p = n;
    
    currentTable = t;
}

void addWidth(table *t, int width) {

}

void enterProc(table *t, char *name, table *newTable) {
    t->child = newTable;
    t->child->name = name;
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
int main() {
    table *t;
    
    t = makeTable(NULL);
    enter(currentTable, "first node", 0);
    
    printf("%p node %p", currentTable, currentTable->first);
    printf("\n");
    
    table *newTable;
    printf("%p", newTable);
    newTable = makeTable(currentTable);
    enterProc(currentTable, "second table", newTable);
    
    printf("%p node %p child %p", currentTable, currentTable->first, currentTable->child);
    
    return (EXIT_SUCCESS);
}

