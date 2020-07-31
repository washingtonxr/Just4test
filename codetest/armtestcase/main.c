/*mutex.c*/
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

int gnum = 0;

pthread_mutex_t mutex;
pthread_mutex_t mutex2;
pthread_mutex_t mutex1;

static void pthread_func_1 (void);
static void pthread_func_2 (void);

int main (void)
{
	pthread_t pt_1 = 0;
	pthread_t pt_2 = 0;
	int ret = 0;

	printf("Hello thread mutex.\n");

	pthread_mutex_init (&mutex, NULL);
	printf("&mutex = %p - %08x\n", &mutex, mutex);

	pthread_mutex_init (&mutex1, NULL);
	printf("&mutex = %p - %08x\n", &mutex1, mutex1);

	pthread_mutex_init (&mutex2, NULL);
	printf("&mutex = %p - %08x\n", &mutex2, mutex2);

	ret = pthread_create( &pt_1, NULL, (void *)pthread_func_1, NULL);
	if (ret != 0)
	{
		perror ("pthread_1_create");
	}
	printf("Create 1 successfully.\n");

	ret = pthread_create( &pt_2, NULL, (void *)pthread_func_2, NULL);
	if (ret != 0)
	{
		perror ("pthread_2_create");
	}
	printf("Create 2 successfully.\n");

	pthread_join (pt_1, NULL);
	printf("Create thread 1 successfully.\n");
	pthread_join (pt_2, NULL);
	printf("Create thread 2 successfully.\n");

	printf ("main programme exit!/n");
	return 0;
}

static void pthread_func_1 (void)
{
	int i = 0;
	for( i = 0; i < 5; i++ ){
		printf ("This is pthread_1!\n");
		pthread_mutex_lock(&mutex);
		printf("&mutex = %p - %08x\n", &mutex, mutex);
		sleep (1);
		gnum++;
		printf ("Thread_1 add one to num:%d\n",gnum);
		pthread_mutex_unlock(&mutex);
	}
	pthread_exit ( NULL );
}

static void pthread_func_2 (void)
{
	int i = 0;
	for( i = 0; i < 5; i++ )  {
		printf ("This is pthread_2!\n");
		pthread_mutex_lock(&mutex);
		printf("&mutex = %p - %08x\n", &mutex, mutex);
		sleep (1);
		gnum++;
		printf ("Thread_2 add one to num:%d\n",gnum);
		pthread_mutex_unlock(&mutex);
	}
	pthread_exit ( NULL );
}


/* End of this file. */