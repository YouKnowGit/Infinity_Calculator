#include <stdio.h>
#include <stdlib.h>

#include "InfinityCalculator.h"
#include "Input.h"
#include "InfixToPostfix.h"
#include "PostCalculator.h"


int main(void)
{
	char *p;
	List pos_fix;
    Num result;

    NumInit(&result);
    ListInit(&pos_fix);

	p = Input();
	printf("%s\n", p);

    InfToPos(&pos_fix, p);
    LRead(&pos_fix);
    result = EvalRPNExp(&pos_fix);

}