#include "main.h"

int main(unsigned int argc, char **argv)
{
	int a = -90;
	int b = 255;
	int a1 = 0;
	int b1 = 0;

	a1 = a >> 1;
	b1 = b >> 5;

	printf("a = %d, b = %d\n", a, b);
	printf("a1 = %d, b1 = %d\n", a1, b1);


	return 0;
}
