#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#define TASK_NUM 128
#define TASK_MSG_LEN 64

void *start_routine(void *arg) {
    unsigned int cnt = 0;
    char tmsg[TASK_MSG_LEN];

    sprintf(tmsg, "thread(%d): - ", *(unsigned int *)arg);
	while (1) {
		write(1, tmsg, strlen(tmsg));
        printf("%d\n", cnt++);
		usleep(100);
	}
}

int main(unsigned int argc, unsigned char **argv) {
    unsigned int cnt = 0;
    unsigned char t = 0;
	pthread_t tid[TASK_NUM];

    for(t = 0; t < TASK_NUM; t++){
	    pthread_create(&tid[t], NULL, start_routine, (void *)&t);
    }

	const char *msg = "main: i am main - ";
	while (1) {
		write(1, msg, strlen(msg));
        printf("%d\n", cnt++);
		usleep(100);
	}

	return 0;
}