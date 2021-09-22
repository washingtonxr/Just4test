#include "main.h"
#include "test1.h"


int main(int argc, unsigned char **argv)
{
	unsigned int i;

	for(i = 0; i < SET_NUM; i++)
	{
		printf("Counter = %d\n", i);
		delayX(10);

	}
	return 0;
}
