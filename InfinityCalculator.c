#include "InfinityCalculator.h"

#define TRUE        1
#define FALSE       0

void DigitInit(Digit * pdigit){
    pdigit->digit = 0
    pdigit->next = NULL;
}

void NumInit(Num * pnum) {
    pnum->integer_part_size = 0;
    pnum->decimal_part_size = 0;
    pnum->integer_part = NULL;
    pnum->decimal_part = NULL;
}


int IntPartIsEmpty(Num * pnum) {
    if (pnum->integer_part == NULL) {
        return TRUE;
    } else {
        return FALSE;
    }
}

int DecPartIsEmpty(Num * pnum) {
    if (pnum->decimal_part == NULL) {
        return TRUE;
    } else {
        return FALSE;
    }
}

void IntPartPush(Num * pnum, int data) {
    Digit * newDigit = (Digit *)malloc(sizeof(Digit));

    newDigit->digit = data;
    newDigit->next = pnum->integer_part;

    pnum->integer_part = newDigit;
}

void DecPartPush(Num * pnum, int data) {
    Digit * newDigit = (Digit *)malloc(sizeof(Digit));

    newDigit->digit = data;
    newDigit->next = pnum->decimal_part;

    pnum->decimal_part = newDigit;
}

int IntPartPop(Num * pnum) {
    int rdata;
    Digit * rnode;

    if (IntPartIsEmpty(pnum)) {
        printf("stack memory error");
        exit(-1);
    }

    rdata = pnum->integer_part->digit;
    rnode = pnum->integer_part;

    pnum->integer_part = pnum->integer_part->next;
    free(rnode);

    return rdata;
}

int DecPartPop(Num * pnum) {
    int rdata;
    Digit * rnode;

    if (DecPartIsEmpty(pnum)) {
        printf("stack memory error");
        exit(-1);
    }

    rdata = pnum->decimal_part->digit;
    rnode = pnum->decimal_part;

    pnum->decimal_part = pnum->decimal_part->next;
    free(rnode);

    return rdata;
}

int IntPartPeek(Num * pnum) {
    if (IntPartIsEmpty(pnum)) {
        printf("stack memory error");
        exit(-1);
    }

    return pnum->integer_part->digit;
}

int DecPartPeek(Num * pnum) {
    if (DecPartIsEmpty(pnum)) {
        printf("stack memory error");
        exit(-1);
    }

    return pnum->decimal_part->digit;
}


void ListInit(List * plist) {
    plist->head = NULL;
    plist->tail = NULL;
}

void LInsert(List * plist, Data data) {
    Node * newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    if (plist->head == NULL) {
        plist->head = newNode;
    }
    else {
        plist->tail->next = newNode;
    }
    plist->tail = newNode;
}

Data LRemove(List* plist) {
    Data rdata;
    Node* rnode;

    if (plist->head == NULL) {
        printf("list memory error");
        exit(-1);
    }

    rdata = plist->head->data;
    rnode = plist->head;

    plist->head = plist->head->next;
    free(rnode);

    return rdata;
}

/* 연산자 스택 */

void OperatorInit(Operator * pOp) {
    pOp->head = NULL;
}

int OperatorIsEmpty(Operator * pOp) {
    if (pOp->head == NULL) {
        return TRUE;
    } else {
        return FALSE;
    }
}

void OperatorPush(Operator * pOp, char data) {
    Node * newNode = (Node *)malloc(sizeof(Node));

    newNode->data = data;
    newNode->next = pOp->head;

    pOp->head = newNode;
}

Data OperatorPop(Operator * pOp) {
    char rdata;
    Node * rnode;

    if (OperatorIsEmpty(pOp)) {
        printf("stack memory error");
        exit(-1);
    }

    rdata = pOp->head->data;
    rnode = pOp->head;

    pOp->head = pOp->head->next;
    free(rnode);

    return rdata;
}

Data OperatorPeek(Operator * pOp) {
    if (OperatorIsEmpty(pOp)) {
        printf("stack memory error");
        exit(-1);
    }
    return pOp->head->data;
}

/* 피연산자 스택 */
void OperandInit(Operand * pOp) {
    pOp->head = NULL;
}

int OperandIsEmpty(Operand * pOp) {
    if (pOp->head == NULL)
        return TRUE;
    else
        return FALSE;
}

void OperandPush(Operand * pOp, Num data) {
    Block * newBlock = (Block*)malloc(sizeof(Block));

    newBlock->operand = data;
    newBlock->next = pOp->head;

    pOp->head = newBlock;
}

Num OperandPop(Operand * pOp) {
    Num rdata;
    Block * rblock;

    if (OperandIsEmpty(pOp)) {
        printf("stack memory error");
        exit(-1);
    }

    rdata = pOp->head->operand;
    rblock = pOp->head;

    pOp->head = pOp->head->next;
    free(rblock);

    return rdata;
}

Num OperandPeek(Operand * pOp) {
    if (OperandIsEmpty(pOp)) {
        printf("stack memory error");
        exit(-1);
    }

    return pOp->head->operand;
}
