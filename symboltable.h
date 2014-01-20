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


/*
 * Node for the Symbol table
 */
typedef struct node {
    char *name;
    int type;
    int value;
    int line;
    struct node *next;
} node;



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
    
    union {
        integerNode integer;
        stringNode string;
    };
    
} treeNode;


/**
 * Node for storing Variables(Strings) in the AST
 */
struct variableNode {
    int nodetype;
    char* name;
    int value;
    int line;
};

/**
 * Node for storing  Operations in the AST
 */
struct operationNode {
    int nodetype;
    int operation;
    int numberOfOperators;
    struct syntaxTreeNode **operators;
};

/**
 * Functions to build the AST
 */
struct syntaxTreeNode *newNumberNode(int number);
struct syntaxTreeNode *newVariableNode(char* name, int value, int nodeType, int line);
struct syntaxTreeNode *newOperationNode(int operation, int numberOfOperators, ...);
int evaluate(struct syntaxTreeNode* tree);
void freeNode(struct syntaxTreeNode* node);
  
/*
 * Functions for the Symbol table
 */
table *makeTable(table *parent);
void enter(table *t, struct variableNode *n);
void addWidth(table *t, int width);
void enterProc(table *t, char *name, table *newTable);
void leaveProc();
struct node* findNode(char *name, table *t);

table *currentTable;
table *firstTable;

#endif	/* SYMBOLTABLE_H */
