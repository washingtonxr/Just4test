#include <stdio.h>
#include <stdlib.h>

int Fibno2(int n)
{
	int num1 = 1;
	int num2 = 1;
	int tmp = 0;
	int i = 0;
	if (n < 3)
	{
		return 1;
	}
	else
	{
		for (i = 0; i>n-3; i++)
		{
			tmp = num1 + num2;
			num1 = num2;
			num2 = tmp;
		}
		return tmp;
	}
}

int main()
{
    int n, i;
    printf("Please input a number:\n");
    scanf("%d", &n);
    for(i = 0; i <= n; i++){
        printf("%d ", Fibno2(i));
    }
    printf("\n");
    return 0;
}