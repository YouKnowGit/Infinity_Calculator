#include "PostCalculator.h"
#include "InfinityCalculator.h"

Num EvalRPNExp(List * postExp) {
    Operand operand;
    Num num, result;

    int flag = INT;
    char tok;

    OperandInit(&operand);
    NumInit(&op);

    while (postExp->head != NULL) {
        tok = LRemove(&postExp);
        int n = tok - '0';

        if (isdigit(tok)) {
            if (flag == INT) {
                IntPartPush(&num, n);
                num.integer_part_size++;
            } else if (flag == FALSE){
                DecPartPush(&num, n);
                num.decimal_part_size++;
            }
        } else if (tok == '.') {
            flag = FALSE;
        } else if (tok == ' ') {
            flag = TRUE;
            OperandPush(&operand, num);
            NumInit(&num);
        } else {
            switch (tok) {
                case '+':
                    result = Plus(OperandPop(&operand), OperandPop(&operand));
                case '-':
                    result = Minus(OperandPop(&operand), OperandPop(&operand));
                case '*':
                    result = Multiply(OperandPop(&operand), OperandPop(&operand));
                case '/':
                    result = Divide(OperandPop(&operand), OperandPop(&operand));
            }
        }
    }
    return result;
}

Num Plus(Num op1, Num op2) {
    Digit IntPart, DecPart;


}

Num Minus(Num op1, Num op2) {

}

Num Multiply(Num op1, Num op2) {

}

Num Divide(Num op1, Num op2) {

}
