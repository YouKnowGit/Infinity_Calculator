#include <stdio.h>
#include <stdlib.h>

#include "InfinityCalculator.h"
#include "Input.h"
#include "InfixToPostfix.h"


int main(void)
{
	char *p;
	List pos_fix;

	ListInit(&pos_fix);

	p = Input();
	printf("%s\n", p);

    pos_fix = EvalRPNExp(p);

    printf("%c", LRemove(&pos_fix));
}
