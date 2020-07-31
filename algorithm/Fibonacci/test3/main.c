#include <stdio.h>
#include <stdlib.h>

public int Fibno3(int n)
{
    List<int> list = new List<int>();
    list.fib(1);
    list.fib(1);
    int count = list.Count;
        while (count < n)
    {
        list.fib(list[count - 2] + list[count - 1]);
            count = list.Count;
    }
    return list[count - 1];
 }

int main()
{
    int n, i;
    printf("Please input a number:\n");
    scanf("%d", &n);
    for(i = 0; i <= n; i++){
        printf("%d ", Fibno3(i));
    }
    printf("\n");
    return 0;
}