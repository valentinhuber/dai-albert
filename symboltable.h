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


typedef enum { typeCon, typeId, typeOpr } nodeEnum;

/* constants */
typedef struct {
    int value;                  /* value of constant */
} conNodeType;

/* identifiers */
typedef struct {
    int i;                      /* subscript to sym array */
} idNodeType;

/* operators */
typedef struct {
    int oper;                   /* operator */
    int nops;                   /* number of operands */
    struct nodeTypeTag **op;	/* operands */
} oprNodeType;

typedef struct nodeTypeTag {
    nodeEnum type;              /* type of node */

    union {
        conNodeType con;        /* constants */
        idNodeType id;          /* identifiers */
        oprNodeType opr;        /* operators */
    };
} nodeType;

extern int sym[26];




/*
 * Holbegs a symbol table
 */
table *makeTable(table *parent);
void enter(table *t, char *name, int type);
void addWidth(table *t, int width);
void enterProc(table *t, char *name, table *newTable);
node* findNode(char *name, table *t);
#endif	/* SYMBOLTABLE_H */

