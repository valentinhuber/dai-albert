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
struct string {
    char *name;
    int value;
};

/**
 * Nodes for the Abstract Syntax Tree
 */
// Generic Node
struct syntaxTreeNode {
    int nodetype;
    struct syntaxTreeNode *left;
    struct syntaxTreeNode *right;
};
// Node for Flow Constructs (IF ELSE WHILE...)
struct flowNode {
    int nodetype;
    struct flowNode *condition;
    struct flowNode *thenList;
    struct flowNode *elseList;
};
// Node for Numbers(Constants)
struct numberNode {
    int nodeType;
    int number;
};

struct variableNode {
    int nodetype;
    struct string *s;
};

struct assignmentNode {
    int nodeType;
    struct string *s;
    struct syntaxTreeNode *v;
};
/**
 * Functions to build AST
 *  
 */
struct syntaxTreeNode *newSyntaxTreeNode(int nodetype, struct syntaxTreeNode *left, struct syntaxTreeNode *right);
struct syntaxTreeNode *newFlowNode(int nodetype,struct flowNode *condition, struct flowNode *thenList, struct flowNode *elseList );
struct syntaxTreeNode *newNumberNode(int number);
struct syntaxTreeNode *newVariableNode(struct string str);
struct syntaxTreeNode *newAssignmentNode(struct string *s, struct synatxTreeNode *v);
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

