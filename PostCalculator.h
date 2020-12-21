#ifndef __POST_CALCULATOR_H__
#define __POST_CALCULATOR_H__

#include "InfinityCalculator.h"

Num EvalRPNExp(List * postExp);

Num* PlusOp(Num * op1, Num * op2);

Num* MinusOp(Num op1, Num op2);

Num* MultiplyOp(Num op1, Num op2);

Num* DivideOp(Num op1, Num op2);

#endif