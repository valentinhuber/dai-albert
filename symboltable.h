/* 
 * File:   symboltable.h
 * Author: hons
 *
 * Created on 10. Januar 2014, 13:20
 */

#ifndef SYMBOLTABLE_H
#define	SYMBOLTABLE_H

/*
 * Symbol table which contains the previous symbol table
 *  
 */
typedef struct table {
    struct table *parent;
    struct table *child;
    char *name;
    int width;
    struct node *first;
} table;


/*
 * A bissl a node
 */
typedef struct node {
    char *name;
    int type;
    int line;
    struct node *next;
} node;

/**
 * Node for the Symboltable
 */

/**
 * Nodes for the Abstract Syntax Tree
 */
// Generic Node
typedef struct syntaxTreeNode {
    int nodetype;
    struct syntaxTreeNode *left;
    struct syntaxTreeNode *right;
} treeNode;
// Node for Numbers(Constants)
struct numberNode {
    int nodeType;
    int number;
};

struct variableNode {
    int nodetype;
    char* name;
    int value;
};

struct operationNode {
    int nodetype;
    int operation;
    int numberOfOperators;
    struct syntaxTreeNode **operators;
};
/**
 * Functions to build AST
 *  
 */
struct syntaxTreeNode *newSyntaxTreeNode(int nodetype, struct syntaxTreeNode *left, struct syntaxTreeNode *right);
struct syntaxTreeNode *newNumberNode(int number);
struct syntaxTreeNode *newVariableNode(char* name, int value);
struct syntaxTreeNode *newOperationNode(int operation, int numberOfOperators, ...);
int evaluate(struct syntaxTreeNode* tree);




/*
 * Holbegs a symbol table
 */
table *makeTable(table *parent);
void enter(table *t, char *name, int type);
void addWidth(table *t, int width);
void enterProc(table *t, char *name, table *newTable);
node* findNode(char *name, table *t);
#endif	/* SYMBOLTABLE_H */

