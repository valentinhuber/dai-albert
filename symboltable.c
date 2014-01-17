/* 
 * File:   symboltable.c
 * Author: hons
 *
 * Created on 10. Januar 2014, 13:20
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "symboltable.h"

table *currentTable;
table *firstTable;

/*
 * 
 */
table *makeTable(table *parent) {
    table *t = malloc(sizeof(struct table));
    t->parent = parent;
    t->child = NULL;
    t->name = NULL;
    t->first = malloc(sizeof(struct node));
    
    currentTable = t;
    
    return currentTable;
}
void enter(table *t, char *name, int type) {
    node *p;
    
    p = t->first;
    
    while(p != NULL && p->next != NULL) {
        p = p->next;
    }
    
    p->name = strdup(name);
    p->type = type;
    p->next = malloc(sizeof(struct node));
    
    currentTable = t;
}

void addWidth(table *t, int width) {

}

void enterProc(table *t, char *name, table *newTable) {
    t->child = newTable;
    t->child->name = name;
}

node* findNode(char *name, table *tbl){
    table *t = tbl;
    node *p = NULL;
    char *r = name;
    
    if( t == NULL) return p;
    
    p = t->first;
    
    while(1) {
        if (p == NULL){
            if (t->parent != NULL){
                t = t->parent;
                return findNode(name, t);
            } else {
                return p;
            }
        } 
        
        if (p->name == r){
            return p;
        }
        
        p = p->next;
        
        
    }
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

struct syntaxTreeNode *newSyntaxTreeNode(int nodetype, struct syntaxTreeNode *left, struct syntaxTreeNode *right) {
    struct syntaxTreeNode *node = malloc(sizeof(struct syntaxTreeNode));
    node->nodetype = nodetype;
    node->left = left;
    node->right = right;
    
    return node;
}

struct syntaxTreeNode *newNumberNode(int number) {
    struct numberNode *node = malloc(sizeof(struct numberNode));
    
    node->nodeType = 'i';
    node->number = number;
    
    return (struct syntaxTreeNode *) node;
}

struct syntaxTreeNode *newVariableNode(char* name, int value) {
     struct variableNode *node = malloc(sizeof(struct variableNode));
 
     node->nodetype = 's';
     node->name = name;
     node->value = value;
     
     return (struct syntaxTreeNode *) node;
}

struct syntaxTreeNode *newOperationNode(int operation, int numberOfOperators, ...) {
    int i;
    va_list operatorList;
    
    struct operationNode *node = malloc(sizeof(struct operationNode));
    node->operators = malloc(numberOfOperators * sizeof(treeNode));
    node->nodetype = 'o';
    node->operation = operation;
    node->numberOfOperators = numberOfOperators;
    
    va_start(operatorList, numberOfOperators);
    for(i = 0; i < numberOfOperators; i++) {
        node->operators[i] = va_arg(operatorList, treeNode*);
    }
    va_end(operatorList);
    return (struct syntaxTreeNode *) node;
}

int evaluate(struct syntaxTreeNode* tree) {
    
    struct operationNode *n = malloc(sizeof(struct operationNode));
    
    switch(tree->nodetype) {
        
        case 'i': return ((struct numberNode *)tree)->number; break;
        case 's': return ((struct variableNode*)tree)->value; break;
        case 'o': 
            n = ((struct operationNode*)tree);
            switch(n->operation) {
                /* expr */
                case '+': return evaluate(n->operators[0]) + evaluate(n->operators[1]); break;
                /* PRINT */
                case 'p': printf("%i",evaluate(n->operators[0])); break;

                /*
                case '=': returnValue = ((struct assignmentNode *)tree)->s->value =
                        evaluate(((struct assignmentNode *)tree)->v); break;
                 */
            }
            break;
    }
}



/*
 * 
 */
/*
int main() {
    table *t;
    
    t = makeTable(NULL);
    enter(currentTable, "first node", 0);
    
    printf("%p node %p name %s", currentTable, currentTable->first, currentTable->first->name);
    printf("\n");
    
    table *newTable;
    printf("%p", newTable);
    newTable = makeTable(currentTable);
    enterProc(currentTable, "second table", newTable);
    
    printf("%p node %p child %p", currentTable, currentTable->first, currentTable->child);
    
    node *success = findNode("first node", currentTable);
    printf("node found: %p",success);
    
    return (EXIT_SUCCESS);
}
*/
