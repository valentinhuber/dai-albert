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
#include "y.tab.h"

/**
 * Creates a new Symbol table
 * @param parent
 * @return The current Symbol table
 */
table *makeTable(table *parent) {
    table *t = malloc(sizeof (struct table));
    t->parent = parent;
    t->child = NULL;
    t->name = NULL;
    t->first = malloc(sizeof (struct node));

    currentTable = t;

    return currentTable;
}

/**
 * Adds a Variable to the Symbol Table
 * @param t
 * @param n 
 * @param type
 */
void enter(table *t, node *n) {

    node *p;

    p = t->first;
    
    while (p != NULL && p->next != NULL) {
        p = p->next;
    }
    
    p->line = n->line;
    p->name = n->name;
    p->type = n->type;
    p->value = n->value; //maybe add n.value.type
    p->next = malloc(sizeof (node));

    currentTable = t;
}

/**
 * Sets the width of the Symbol table
 * @param t
 * @param width
 */
void addWidth(table *t, int width) {

}

/**
 * Adds a sub Symbol table to a Symbol table
 * @param t
 * @param name
 * @param newTable
 */
void enterProc(table *t, char *name, table *newTable) {
    t->child = newTable;
    t->child->name = name;
}

/**
 * Leaves a scope
 */
void leaveProc() {
    if (currentTable != NULL) {
        currentTable = currentTable->parent;
    }
}

/**
 * Searches for a node in the Symbol table and returns it if found
 * @param name
 * @param tbl
 * @return 
 */
node* findNode(char *name, table *tbl) {
    table *t = tbl;
    node *p = NULL;
    char *r = name;

    if (t == NULL) {
        p->name = malloc(sizeof(char *));
        return p;
    }

    p = t->first;

    while (1) {
        if (p == NULL) {
            if (t->parent != NULL) {
                t = t->parent;
                return findNode(name, t);
            } else {
                return p;
            }
        }

        if (p->name == NULL) {
            return p;
        }

        if (strcmp(p->name, r) == 0) {
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

/**
 * Creates a number node in the AST
 * @param number
 * @return 
 */
treeNode *newNumberNode(int number) {
    treeNode *node = malloc(sizeof (treeNode));
    
    node->nodeType = 'i';
    node->integer.number = number;

    return node;
}

/**
 * Creates a number node in the AST
 * @param number
 * @return 
 */
treeNode *newStringNode(char *s) {
    treeNode *node = malloc(sizeof (treeNode));

    node->nodeType = 's';
    node->string.str = strdup(s);

    return node;
}

/**
 * Creates a variable node in the AST
 * @param name
 * @param value
 * @return 
 */
treeNode *newVariableNode(char* name, int nodeType, int line) {
    
    node *n = malloc(sizeof (struct node));

    n->name = strdup(name);
    n->value = malloc(sizeof (treeNode));
    
    switch (nodeType) {
        case 'i': 
            n->value->name = strdup(name);
            n->value->nodeType = nodeType;
            n->value->integer.number = 0;
            break;
        case 's': 
            n->value->name = strdup(name);
            n->value->nodeType = nodeType;
            n->value->string.str = malloc(sizeof (stringNode));
            n->value->string.str = "";
            break;
    }
    
    n->type = nodeType;
    n->line = line;
    
    return ((treeNode *)n); //->nodeType = nodeType
}

/**
 * Creates a operation node in the AST
 * @param operation
 * @param numberOfOperators
 * @param ...
 * @return 
 */
treeNode *newOperationNode(int operation, int numberOfOperators, ...) {
    int i;
    va_list operatorList;

    struct operationNode *node = malloc(sizeof (struct operationNode));
    node->operators = malloc(numberOfOperators * sizeof (treeNode));
    node->nodetype = 'o';
    node->operation = operation;
    node->numberOfOperators = numberOfOperators;

    va_start(operatorList, numberOfOperators);
    for (i = 0; i < numberOfOperators; i++) {
        node->operators[i] = va_arg(operatorList, treeNode*);
    }
    va_end(operatorList);
    return (treeNode *) node;
}

/**
 * Evaluates the AST recursively and returns the value of the
 * evaluated statement
 * @param tree
 * @return 
 */
treeNode *evaluate(treeNode* tree) {

    struct operationNode *n = malloc(sizeof (struct operationNode));
    treeNode *t = malloc(sizeof (treeNode));


    if (!tree || !tree->nodeType) return t;

    switch (tree->nodeType) {

        case 'i': t->integer.number = tree->integer.number; t->nodeType = 'i';
            return t;
            break;
        case 's': t->string.str = tree->string.str; t->nodeType = 's';
            return t;
            break;
      //  case 'v':  return evaluate(((node *)tree)->value); break;
        case 'o':
            n = ((struct operationNode*) tree);
            switch (n->operation) {

                    /* arithmetic operations */
                case '+': t->integer.number = evaluate(n->operators[0])->integer.number + evaluate(n->operators[1])->integer.number;
                    return t;
                    break;
                case '-': t->integer.number = evaluate(n->operators[0])->integer.number - evaluate(n->operators[1])->integer.number;
                    return t;
                    break;
                case '*': t->integer.number = evaluate(n->operators[0])->integer.number * evaluate(n->operators[1])->integer.number;
                    return t;
                    break;
                case '/': t->integer.number = evaluate(n->operators[0])->integer.number / evaluate(n->operators[1])->integer.number;
                    return t;
                    break;

                case '<': t->integer.number = evaluate(n->operators[0])->integer.number < evaluate(n->operators[1])->integer.number;
                    return t;
                    break;
                case '>': t->integer.number = evaluate(n->operators[0])->integer.number > evaluate(n->operators[1])->integer.number;
                    return t;
                    break;

                case GE: t->integer.number = evaluate(n->operators[0])->integer.number >= evaluate(n->operators[1])->integer.number;
                    return t;
                    break;
                case LE: t->integer.number = evaluate(n->operators[0])->integer.number <= evaluate(n->operators[1])->integer.number;
                    return t;
                    break;
                case NE: t->integer.number = evaluate(n->operators[0])->integer.number != evaluate(n->operators[1])->integer.number;
                    return t;
                    break;
                case EQ: t->integer.number = evaluate(n->operators[0])->integer.number == evaluate(n->operators[1])->integer.number;
                    return t;
                    break;

                    /* IF */
                case IF: enterProc(currentTable, "if", makeTable(currentTable));
                    if (evaluate(n->operators[0]))
                        evaluate(n->operators[1]);

                    leaveProc();
                    return t;
                    break;

                    /* IF ELSE */
                case ELSE:
                    enterProc(currentTable, "ifelse", makeTable(currentTable));
                    if (evaluate(n->operators[0]))
                        evaluate(n->operators[1]);
                    else
                        evaluate(n->operators[2]);

                    leaveProc();
                    return t;
                    break;
                    /* WHILE */
                case WHILE:
                    enterProc(currentTable, "while", makeTable(currentTable));
                    while (evaluate(n->operators[0])) evaluate(n->operators[1]);
                    return t;
                    break;

                    /* list oft statements */
                case 'l': evaluate(n->operators[0]);
                    return evaluate(n->operators[1]);
                    break;

                    /* PRINT */
                case PRINT: {
                    if(n->operators[0]->nodeType != 'i') {
                        node *result = findNode(((node*) n->operators[0])->name, currentTable);
                        if(result->name != NULL) {
                            switch(result->type) {
                                case 'i': printf("%i\n",result->value->integer.number); break;
                                case 's': printf("%s\n",result->value->string.str); break;
                            }
                        }
                    } else {
                        printf("%i\n",evaluate(n->operators[0])->integer.number);
                    }
                    return t;
                    break;
                }
                    /* ASSIGNMENT */
                case '=': {
                    node *result = findNode(((node*) n->operators[0])->name, currentTable);
                    if (result->name != NULL && result->type == ((treeNode*)evaluate(n->operators[1]))->nodeType) {
                       if(result->type == ((treeNode*)evaluate(n->operators[1]))->nodeType)
                                result->value = evaluate(n->operators[1]);      // VALUE ASSIGNMENT
                        else if (result->name != NULL && ((node*) n->operators[1])->name != NULL) {
                                node *assignment = findNode(((node*) n->operators[1])->name, currentTable);
                                if(assignment->name != NULL && result->type == assignment->type)
                                        result->value = assignment->value;          //VARIABLE ASSIGNEMNT
                                else 
                                        yyerror("dai albert error");
                        }else 
                            yyerror("dai albert error");
                    } else {
                        if (result->name == NULL){
                                treeNode *test = evaluate(n->operators[1]);
                                ((node*)n->operators[0])->value = test;
                                enter(currentTable, (node *) n->operators[0]);
                        } else 
                            yyerror("variable of type  already declared as");
                    }
                    return t;
                    break;
                }
            }
            break;
    }
}


/**
 * Frees the AST recursively
 * @param node
 */
void freeNode(struct syntaxTreeNode* node) {
    int i;
    struct operationNode *n = malloc(sizeof (struct operationNode));
    if (node->nodeType = 'o') {
        n = ((struct operationNode*) node);
        for (i = 0; i < n->numberOfOperators; i++) {
            freeNode(n->operators[i]);
        }
        free(n->operators);
    }
    free(n);
    free(node);
}

/**
 * Error function using variable argument list
 * @param s
 * @param ...
 */
void yyerror(char *str, ...) {
    va_list listPointer;
    va_start(listPointer, str);

    fprintf(stderr, "Error in line %d: ", yylineno);
    vfprintf(stderr, str, listPointer);
    fprintf(stderr, "\n");
}
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