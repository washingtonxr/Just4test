#include <stdio.h>
#include <stdlib.h>

int main()
{
	unsigned int *a = NULL;
	unsigned char b = 0;
	unsigned int i;
	char *a1;

	a1 = (char *)malloc(sizeof(char)*10);
	if(NULL == a1){
		printf("memory alloc for a failed.\n");
	}

	a = (unsigned int *)malloc(sizeof(unsigned int));
	if(NULL == a){
		printf("memory alloc for a failed.\n");
	}

	b = 100;
	*a = b;
	
	for( i = 0; i <10; i++){
		//a1[i] = i;
		*(a1 + i) = i;
	}
	
	for(i = 0; i < 10; i++)
		//printf("%d\n", *a1++);
		printf("%d\n", a1[i]);
	
	printf("%p %d %d %d\n", a, b, *a++, ++*a);
	printf("%p %ld %ld %ld\n", a, *(char *)a, *a++, ++*a);
	free(a);

}
