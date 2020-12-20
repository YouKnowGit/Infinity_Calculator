#ifndef __INF_CALC_H__
#define __INF_CALC_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct _digit {
    int digit;
    struct _digit * next;
} Digit, pDigit;

typedef struct _number {
    int integer_part_size;
    int decimal_part_size;
    Digit * integer_part;
    Digit * decimal_part;
} Num, *pNum;

typedef char Data;

typedef struct _node {
    Data data;
    struct _node * next;
} Node;

typedef struct _block {
    Num operand;
    struct _block * next;
} Block;

typedef struct _list {
    Node * head;
    Node * tail;
} List, *pList;

typedef struct _operator {
    Node * head;
} Operator;

typedef struct _operand {
    Block * head;
} Operand;

void DigitInit(Digit * pdigit);

void NumInit(Num * pnum);
int IntPartIsEmpty(Num * pnum);
int DecPartIsEmpty(Num * pnum);
void IntPartPush(Num * pnum, int data);
void DecPartPush(Num * pnum, int data);
int IntPartPop(Num * pnum);
int DecPartPop(Num * pnum);
int IntPartPeek(Num * pnum);
int DecPartPeek(Num * pnum);

void ListInit (List * plist);
void LInsert (List * plist, Data data);
Data LRemove (List * plist);

void OperatorInit (Operator * pOp);
int OperatorIsEmpty(Operator * pOp);
void OperatorPush (Operator * pOp, Data data);
Data OperatorPop (Operator * pOp);
Data OperatorPeek (Operator * pOp);

void OperandInit (Operand * pOp);
int OperandIsEmpty(Operand * pOp);
void OperandPush (Operand * pOp, Num data);
Num OperandPop (Operand * pOp);
Num OperandPeek (Operand * pOp);

#endif