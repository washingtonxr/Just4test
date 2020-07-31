#include <stdio.h>
#include <stdlib.h>

//递归之Fibonacci数列
unsigned int Fibonacci(unsigned int t)
{
    if(t == 0 || t == 1)
        return 1;
    else
        return Fibonacci(t - 1) + Fibonacci(t - 2);
}
 
int main()
{
    unsigned int n, i;
    printf("Please input a number:\n");
    scanf("%d", &n);
    for(i = 0; i <= n; i++){
        printf("%d ", Fibonacci(i));
    }
    printf("\n");
    return 0;
}