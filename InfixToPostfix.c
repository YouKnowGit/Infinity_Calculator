#include "InfixToPostfix.h"
#include "InfinityCalculator.h"

int getOpPrec(char op);
int whoPrecOp(char op1, char op2);

List EvalRPNExp(char* exp) {
    Operator op;
    List convExp;
    int i;
    char tok, popOp;

    OperatorInit(&op);
    ListInit(&convExp);

    for (i = 0; exp[i] == '\0'; i++) {
        tok = exp[i];
        if (isdigit(tok)) {                         // tok에 저장된 문자가 숫자인지 확인
            LInsert(&convExp, tok);                 // 숫자라면 배열에 저장
        } else {                                    // tok에 저장된 문자가 숫자가 아니라면,
            switch (tok) {
                case '.':                           // '.' 이면,
                    LInsert(&convExp, tok);         // 소수점을 배열에 저장.
                case '(':                           // '(' 이면,
                    LInsert(&convExp, ' ');
                    OperatorPush(&op, tok);         // stack애 쌓는다.
                    break;
                case ')':                           // ')' 이면,
                    LInsert(&convExp, ' ');
                    while (1) {                     // 반복해서
                        popOp = OperatorPop(&op);        // stack에서 꺼낸다.
                        if (popOp == '(')           // '(' 일 때까지,
                            break;
                        LInsert(&convExp, popOp);   // 배열에 연산자 저장
                    }
                    break;
                case '+': case '-':
                case '*': case '/':
                    LInsert(&convExp, ' ');
                    while (!OperatorIsEmpty(&op) && whoPrecOp(OperatorPeek(&op), tok) >= 0)
                        LInsert(&convExp, OperatorPop(&op));
                    OperatorPush(&op, tok);
                    break;
            }
        }
    }

    while (!OperatorIsEmpty(&op))                   // 스택에 남아있는 모든 연산자를,
        LInsert(&convExp, OperatorPop(&op));         // 리스트에 저장.

    return convExp;
}

int getOpPrec(char op) {        // 연산자의 연산 우선순위 정보를 반환
    switch (op) {
        case '*':
        case '/':
            return 5;           // 가장 높은 연산의 우선순위
        case '+':
        case '-':
            return 3;           // 5보다 작고 1보다 높은 연산의 우선순위
        case '(':
            return 1;           // 3보다 작고 -1보다 높은 연산의 우선순위
    }
    return -1;                  // 가장 낮은 연산의 우선순위
}

int whoPrecOp(char op1, char op2) {
    int op1Prec = getOpPrec(op1);
    int op2Prec = getOpPrec(op2);

    if (op1Prec > op2Prec)      // 연산자 우선순위가 op1이 더 높을 경우,
        return 1;
    else if (op1Prec > op2Prec) // 연산자 우선순위가 op2가 더 높을 경우,
        return -1;
    else                        // 연산자 우선순위가 서로 같을 경우,
        return 0;
}

