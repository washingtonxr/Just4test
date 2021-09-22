#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void main()
{
	unsigned char i = 0;
	signed char v1 = 0;
	unsigned char v2 = 0;
	unsigned int UV1 = 0;
	unsigned int UV2 = 0;
	unsigned int UV3 = 0;
	while(1){
		for(i = 0; i < 0xff; i++)
		{
			printf("INT8 = %d, UINT8 = %d\n", v1++, v2++);
		}

		UV1 = 1200;
		UV2 = 1000;
		UV3 = UV1/UV2;
		printf("UV3 = %d\n", UV3);
		exit(0);
	}
}
