#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
static int g_i = 0;
static pthread_mutex_t g_lock1;
int *dataArry;

static void memtest2(void)
{
	char dataArry2[50];
	memset(dataArry2, 0, sizeof(dataArry2));
	strncpy(&dataArry2[0], &dataArry2[10], 30);
}
#if 0
static void memtest1(void)
{
	//dataArry[200] = 0;
}

static void memtest0(void)
{
	dataArry = malloc(100*sizeof(int));
	if(NULL == dataArry){
		printf("Error: No memory for dataArry.\n");
	}
	dataArry[22] = 0;
	free(dataArry);
}

static void stupid(unsigned int arg)
{
    unsigned char i,j;
    for(i=0; i< arg; i++)
    {
        j=i;
    }
}

static int num=1;
static void *fun(void * arg)
{
	int i;
	for(i=0; i<num; ++i)
	{
		pthread_mutex_lock(&g_lock1);
		printf("pthread[%d]:i=%d\n",getpid(), --g_i);
		pthread_mutex_unlock(&g_lock1);
        stupid(10);
		//memtest0();
		//memtest1();
		memtest2();
		//sleep(1);
	}
}

int main()
{
	pthread_t t;

	pthread_mutex_init(&g_lock1, NULL);

	if (pthread_create(&t, NULL, fun, NULL)==-1)
	{
		printf("pthread creat error\n");
	}

	int i;
	for(i=0; i<num; ++i)
	{
		pthread_mutex_lock(&g_lock1);
		printf("main[%d]:i=%d\n",getpid(), ++g_i);
        pthread_mutex_unlock(&g_lock1);
		
		//sleep(1);
	}
	for(i=0; i<num; ++i)
	{
		if (pthread_join(t, NULL) == -1)
		{
			printf("pthread_join error\n");
		}
	}
	pthread_mutex_destroy(&g_lock1);
	return 0;
}
#else
void main()
{
	memtest2();
}
#endif

