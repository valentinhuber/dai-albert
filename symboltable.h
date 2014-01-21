/* 
 * File:   symboltable.h
 * Author: hons
 *
 * Created on 10. Januar 2014, 13:20
 */

#ifndef SYMBOLTABLE_H
#define	SYMBOLTABLE_H

extern int yylineno;
void yyerror(char *s, ...);

/*
 * Symbol table
 */
typedef struct table {
    struct table *parent;
    struct table *child;
    char *name;
    int width;
    struct node *first;
} table;






/**
 * Node for storing Numbers in the AST
 */
typedef struct {
    int number;
} integerNode;

typedef struct {
    char *str;
} stringNode;

/**
 * Generic Node for the Abstract Syntax Tree
 */
typedef struct syntaxTreeNode {
    int nodeType;
    int line; 
    char* name;
    
    union {
        integerNode integer;
        stringNode string;
    };
} treeNode;

/**
 * Node for storing  Operations in the AST
 */
struct operationNode {
    int nodetype;
    int operation;
    int numberOfOperators;
    struct syntaxTreeNode **operators;
};

/*
 * Node for the Symbol table
 */
typedef struct node {
    char *name;
    int type;
    treeNode *value;
    int line;
    struct node *next;
} node;

/**
 * Functions to build the AST
 */
treeNode *newNumberNode(int number);
treeNode *newVariableNode(char* name, int nodeType, int line);
treeNode *newOperationNode(int operation, int numberOfOperators, ...);
treeNode *evaluate(treeNode* tree);
void freeNode(struct syntaxTreeNode* node);
  

/*
 * Functions for the Symbol table
 */
table *makeTable(table *parent);
void enter(table *t, node *n);
void addWidth(table *t, int width);
void enterProc(table *t, char *name, table *newTable);
void leaveProc();
struct node* findNode(char *name, table *t);

table *currentTable;
table *firstTable;

#endif	/* SYMBOLTABLE_H */
