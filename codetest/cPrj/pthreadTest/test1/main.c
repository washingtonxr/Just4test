#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
static pthread_cond_t cond;
static pthread_mutex_t mutex1;
static pthread_mutex_t mutex2;

#define TIMESTAMP       1000000

void showtime(struct timespec pPushTime1, struct timespec pPushTime2)
{
        long int detalTime = 0;
        detalTime = (pPushTime2.tv_sec*1000000000 + pPushTime2.tv_nsec) - 
                        (pPushTime1.tv_sec*1000000000 + pPushTime1.tv_nsec);
        printf("T-1\t%ld\t%ld\t%ld\t%d\n",
                (pPushTime1.tv_sec*1000000000 + pPushTime1.tv_nsec),
                (pPushTime2.tv_sec*1000000000 + pPushTime2.tv_nsec),
                detalTime,
                (int)(abs(detalTime - TIMESTAMP)*100/TIMESTAMP));
}

void *thread1_entry(void *arg)
{
        struct timespec pPushTime1, pPushTime2;
        while(1)
        {
                pthread_mutex_lock(&mutex1);
                //printf("cond wait cond1\n");
                clock_gettime(CLOCK_REALTIME, &pPushTime1);
                pthread_cond_wait(&cond, &mutex1);
                clock_gettime(CLOCK_REALTIME, &pPushTime2);
                showtime(pPushTime1, pPushTime2);
                //printf("recv cond1\n");
                pthread_mutex_unlock(&mutex1);
                usleep(1);
        }
}

void *thread2_entry(void *arg)
{
        struct timespec pPushTime1, pPushTime2;
        long int detalTime = 0;
        while(1)
        {
                pthread_mutex_lock(&mutex1);
                //printf("cond wait cond2\n");
                clock_gettime(CLOCK_REALTIME, &pPushTime1);
                pthread_cond_wait(&cond, &mutex1);
                clock_gettime(CLOCK_REALTIME, &pPushTime2);
                showtime(pPushTime1, pPushTime2);
                //printf("recv cond2\n");
                pthread_mutex_unlock(&mutex1);
                usleep(1);
        }

}

void *thread3_entry(void *arg)
{
        struct timespec pPushTime1, pPushTime2;
        long int detalTime = 0;
        while(1)
        {
                pthread_mutex_lock(&mutex1);
                //printf("cond wait cond3\n");
                clock_gettime(CLOCK_REALTIME, &pPushTime1);
                pthread_cond_wait(&cond, &mutex1);
                clock_gettime(CLOCK_REALTIME, &pPushTime2);
                showtime(pPushTime1, pPushTime2);
                //printf("recv cond3\n");
                pthread_mutex_unlock(&mutex1);
                usleep(1);
        }

}

void *thread4_entry(void *arg)
{
        struct timespec pPushTime1, pPushTime2;
        long int detalTime = 0;
        while(1)
        {
                pthread_mutex_lock(&mutex1);
                //printf("cond wait cond4\n");
                clock_gettime(CLOCK_REALTIME, &pPushTime1);
                pthread_cond_wait(&cond, &mutex1);
                clock_gettime(CLOCK_REALTIME, &pPushTime2);
                showtime(pPushTime1, pPushTime2);
                //printf("recv cond4\n");
                pthread_mutex_unlock(&mutex1);
                usleep(1);
        }

}

void *thread5_entry(void *arg)
{
        struct timespec pPushTime1, pPushTime2;
        long int detalTime = 0;
        while(1)
        {
                pthread_mutex_lock(&mutex1);
                //printf("cond wait cond5\t");
                clock_gettime(CLOCK_REALTIME, &pPushTime1);
                pthread_cond_wait(&cond, &mutex1);
                clock_gettime(CLOCK_REALTIME, &pPushTime2);
                showtime(pPushTime1, pPushTime2);
                //printf("recv cond5\n");
                pthread_mutex_unlock(&mutex1);
                usleep(1);
        }

}

void *thread6_entry(void *arg)
{
        int ret;
        while(1)
        {
                pthread_mutex_lock(&mutex1);
                pthread_mutex_lock(&mutex2);
                ret = pthread_cond_broadcast(&cond);
                if(ret < 0)
                {
                        printf("pthread_cond_broadcast error\n");
                }
                pthread_mutex_unlock(&mutex2);
                pthread_mutex_unlock(&mutex1);
#if 1
                usleep(1);
#else
                sleep(1);
#endif
        }
}
int main(void)
{
        int ret =0;
        pthread_t tid1, tid2, tid3, tid4, tid5, tid6;
        ret = pthread_cond_init(&cond, NULL);
        if(ret < 0)
        {
                printf("pthread_cond_init error\n");
        }
        ret = pthread_mutex_init(&mutex1, NULL);
        if(ret < 0)
        {
                printf("pthread_mutex_init error\n");
        }

        ret = pthread_mutex_init(&mutex2,NULL);
        if(ret < 0)
        {
                printf("pthread_mutex_init error\n");
        }

        ret=  pthread_create(&tid1, NULL, thread1_entry, NULL);
        if(ret < 0)
        {
                printf("pthread_create thread1 error\n");
        }

        ret = pthread_create(&tid2, NULL, thread2_entry, NULL);
        if(ret < 0)
        {
                printf("pthread_create thread2 error\n");
        }

        ret = pthread_create(&tid3, NULL, thread3_entry, NULL);
        if(ret < 0)
        {
                printf("pthread_create thread3 error\n");
        }

        ret = pthread_create(&tid4, NULL, thread4_entry, NULL);
        if(ret < 0)
        {
                printf("pthread_create thread4 error\n");
        }

        ret = pthread_create(&tid5, NULL, thread5_entry, NULL);
        if(ret < 0)
        {
                printf("pthread_create thread5 error\n");
        }
#if 1
        sleep(2);
        ret = pthread_create(&tid6, NULL, thread6_entry, NULL);
        if(ret < 0)
        {
                printf("pthread_create thread6 error\n");
        }
#endif


#if 0
        pthread_mutex_lock(&mutex1);
        pthread_mutex_lock(&mutex2);
        ret = pthread_cond_broadcast(&cond);
        if(ret < 0)
        {
                printf("pthread_cond_broadcast error\n");
        }
        pthread_mutex_unlock(&mutex1);
        pthread_mutex_unlock(&mutex2);
#endif
        while(1)
        {
                sleep(10000);
        }
        return 0;
}

