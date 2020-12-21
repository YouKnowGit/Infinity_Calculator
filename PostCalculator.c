#include "InfinityCalculator.h"
#include "PostCalculator.h"

#define INT     0
#define DEC     1

Num EvalRPNExp(List * postExp) {
    Operand operand;
    Num num, result;
    int flag = INT;
    char tok;

    OperandInit(&operand);
    NumInit(&num);

    while (postExp->head != NULL) {
        tok = LRemove(postExp);
        int n = tok - '0';

        if (isdigit(tok)) {
            if (flag == INT) {
                IntPartPush(&num, n);
                num.integer_part_size++;
            } else {
                DecPartPush(&num, n);
                num.decimal_part_size++;
            }
        }
        else if (tok == '.') {
            flag = DEC;
        }
        else if (tok == ' ') {
            flag = INT;
            if (OperandIsEmpty(&operand)) {         // Operand 스택이 비워져있다면
                OperandPush(&operand, &num);
                NumInit(&num);
            } else {                                // Operand 스택이 비워져있지 않다면
                OperandInit(&operand);
            }
        }
        else {
            printf("%d", IntPartPop(&num));
            printf("%d", IntPartPop(&num));
            printf("%d", IntPartPop(&num));
            printf("%d", num.integer_part_size);
            printf("%d", num.decimal_part_size);
            switch (tok) {
                case '+':
//                    result = PlusOp(OperandPop(&operand), OperandPop(&operand));
                    break;
                case '-':
                    // result = MinusOp(OperandPop(&operand), OperandPop(&operand));
                    break;
                case '*':
                    // result = MultiplyOp(OperandPop(&operand), OperandPop(&operand));
                    break;
                case '/':
                    // result = DivideOp(OperandPop(&operand), OperandPop(&operand));
                    break;
            }
            OperandPush(&operand, &result);
        }
    }
    return result;
}



/*
Num* MinusOp(Num* op1, Num* op2) {
    Num result;
    NumInit(&result);


}

Num* MultiplyOp(Num* op1, Num* op2) {

}

Num* DivideOp(Num* op1, Num* op2) {

}
*/
