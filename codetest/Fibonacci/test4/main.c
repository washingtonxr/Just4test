#include <stdio.h>
#include <stdlib.h>

public int Fibno4(int n)
{
	Queue<int> queue = new Queue<int>();
	queue.Enqueue(1);
	queue.Enqueue(1);
	for (int i = 0; i <= n - 2; i++)
	{
		queue.Enqueue(queue.AsQueryable().First() + queue.AsQueryable().Last());
		queue.Dequeue();
	}
	 return queue.Peek();
}

int main()
{
    int n, i;
    printf("Please input a number:\n");
    scanf("%d", &n);
    for(i = 0; i <= n; i++){
        printf("%d ", Fibno4(i));
    }
    printf("\n");
    return 0;
}