#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static void testx(void)
{
	int i,j;
	for(i=0;i<1000000;i++){
		j=i;
	}
}


static void test2(unsigned int arg)
{
	unsigned int i = 0;
	for(i=0; i<arg; i++){
		testx();
	}
}

static void test1(unsigned int arg)
{
	unsigned int i = 0;
	for(i=0; i<arg; i++){
		testx();
	}
}

int main(int argc, char** argv)
{
	unsigned int Cnt;
	while(1)
	{
		if(Cnt++ >= 10){
			exit(1);
		}
		test1(100);
		test2(1000);    
	}
	return 0;
}

