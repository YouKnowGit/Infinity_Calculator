#include "InfinityCalculator.h"
#include "PostCalculator.h"

Num EvalRPNExp(List * postExp) {
    printf("\n");
    Operand operand;
    Num num, result;
    int flag = INT;
    char tok;

    OperandInit(&operand);
    NumInit(&num);

    while (1) {
        if (postExp->head->next != NULL)
            break;

        tok = LRemove(&postExp);
        int n = tok - '0';

        if (isdigit(tok)) {
            if (flag == INT) {
                IntPartPush(&num, n);
                num.integer_part_size++;
            } else if (flag == DEC){
                DecPartPush(&num, n);
                num.decimal_part_size++;
            }
        } else if (tok == '.') {
            flag = DEC;
        } else if (tok == ' ') {
            flag = INT;
            if (OperandIsEmpty(&operand)) {         // Operand 스택이 비워져있다면
                OperandPush(&operand, num);
                NumInit(&num);
            } else {                                // Operand 스택이 비워져있지 않다면
                OperandInit(&operand);
            }
        } else {
            printf("%d", OperandPop(&operand).integer_part_size);
            printf("%d", OperandPop(&operand).decimal_part_size);
            switch (tok) {
                case '+':
                    result = Plus(OperandPop(&operand), OperandPop(&operand));
//                case '-':
//                    result = Minus(OperandPop(&operand), OperandPop(&operand));
//                case '*':
//                    result = Multiply(OperandPop(&operand), OperandPop(&operand));
//                case '/':
//                    result = Divide(OperandPop(&operand), OperandPop(&operand));
//            }
        }
    }

    return result;
}

Num Plus(Num *op1, Num *op2) {
    Num result;     // 계산 결과 저장 구조체

    NumInit(&result);

    // 정수 부분, 소수 부분의 차이, tok = TRUE면 정수 첫 번재 자리에서 +1
    int decimal_gap = op1->decimal_part_size - op2->decimal_part_size;
    int integer_gap = op1->integer_part_size - op2->integer_part_size;
    int tok = FALSE;

    if (decimal_gap > 0) {
        // 소수 부분 길이의 차이만큼 긴 소수의 숫자 Push
        for (int i = 0; i < decimal_gap; ++i) {
            DecPartPush(&result, op1->decimal_part->digit);
            op1->decimal_part = op1->decimal_part->next;
        }
        // 두 소수 부분의 합을 Push, 10 이상이면 -10을 하고 다음 자릿 수의 합에 +1
        int sum = op1->decimal_part->digit + op2->decimal_part->digit;
        while (op1->decimal_part->next != NULL) {
            op1->decimal_part = op1->decimal_part->next;
            op2->decimal_part = op2->decimal_part->next;
            if (sum >= 10) {
                if (op1->decimal_part->next == NULL)
                    tok = TRUE;
                sum -= 10;
                DecPartPush(&result, sum);
                sum = op1->decimal_part->digit + op2->decimal_part->digit + 1;
            } else {
                DecPartPush(&result, sum);
                sum = op1->decimal_part->digit + op2->decimal_part->digit;
            }
        }
    } else {
        // 소수 부분의 차이만큼 긴 소수의 숫자 Push
        for (int i = 0; i < (-1) * decimal_gap; ++i) {
            DecPartPush(&result, op2->decimal_part->digit);
            op2->decimal_part = op2->decimal_part->next;
        }
        // 두 소수 부분의 합을 Push, 10 이상이면 -10을 하고 다음 자릿 수의 합에 +1
        int sum = op1->decimal_part->digit + op2->decimal_part->digit;
        while (op2->decimal_part->next != NULL) {
            op1->decimal_part = op1->decimal_part->next;
            op2->decimal_part = op2->decimal_part->next;
            if (sum >= 10) {
                sum -= 10;
                DecPartPush(&result, sum);
                sum = op1->decimal_part->digit + op2->decimal_part->digit + 1;
            } else {
                DecPartPush(&result, sum);
                sum = op1->decimal_part->digit + op2->decimal_part->digit;
            }
        }
    }

    if (integer_gap > 0) {
        // 정수 부분의 합을 Push, 10 이상이면 -10을 하고 다음 자릿 수의 합에 +1
        int sum = op1->integer_part->digit + op2->integer_part->digit;
        // tok가 TRUE면 첫 번째 자릿 수에서 +1
        if (tok == TRUE)
            sum++;
        while (op1->integer_part->next != NULL) {
            op1->integer_part = op1->integer_part->next;
            op2->integer_part = op2->integer_part->next;
            if (sum >= 10) {
                sum -= 10;
                IntPartPush(&result, sum);
                sum = op1->integer_part->digit + op2->integer_part->digit + 1;
            } else {
                IntPartPush(&result, sum);
                sum = op1->integer_part->digit + op2->integer_part->digit;
            }
        }
        // 정수 부분 길이의 차이만큼 긴 정수의 숫자 Push
        for (int i = 0; i < integer_gap; ++i) {
            DecPartPush(&result, op1->integer_part->digit);
            op1->integer_part = op1->integer_part->next;
        }
    } else {
        // 정수 부분의 합을 Push, 10 이상이면 -10을 하고 다음 자릿 수의 합에 +1
        int sum = op1->integer_part->digit + op2->integer_part->digit;
        // tok가 TRUE면 첫 번째 자릿 수에서 +1
        if (tok == TRUE)
            sum++;
        while (op1->integer_part->next != NULL) {
            op1->integer_part = op1->integer_part->next;
            op2->integer_part = op2->integer_part->next;
            if (sum >= 10) {
                sum -= 10;
                IntPartPush(&result, sum);
                sum = op1->integer_part->digit + op2->integer_part->digit + 1;
            } else {
                IntPartPush(&result, sum);
                sum = op1->integer_part->digit + op2->integer_part->digit;
            }
        }
        // 정수 부분 길이의 차이만큼 긴 정수의 숫자 Push
        for (int i = 0; i < (-1) * integer_gap; ++i) {
            DecPartPush(&result, op1->integer_part->digit);
            op1->integer_part = op1->integer_part->next;
        }
    }

    return result;

}


Num Minus(Num op1, Num op2) {
    Num result;
    NumInit(&result);


}

Num Multiply(Num op1, Num op2) {

}

Num Divide(Num op1, Num op2) {

}

/*
Num whoLonglen(Num op1, Num op2) {
    int size1 = op1.integer_part_size;
    int size2 = op2.integer_part_size;

    if (size1 > size2)
        return 1;
    else if (size1 < size2)
        return -1;
    else {
        for (i = 0; i < size1; i++) {
            if (op1->) return true;
            else if (a[i] < b[i]) return false;
        }
        equal_check = false;
        return false;
    }
}
*/
