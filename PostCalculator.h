#ifndef __POST_CALCULATOR_H__
#define __POST_CALCULATOR_H__

#include "InfixToPostfix.h"

#define INT     0
#define DEC     1

Num EvalRPNExp(List * postExp);

Num Plus(Num op1, Num op2);

Num Minus(Num op1, Num op2);

Num Multiply(Num op1, Num op2);

Num Divide(Num op1, Num op2);

#endif