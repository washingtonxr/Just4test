#include "test1.h"
#include "common.h"

int delayX(unsigned int arg)
{
	unsigned int i;
	unsigned int j;
	
	for(i = 0; i < DELAY_TIME*arg; i++)
		j = i;

	return 0;
}

