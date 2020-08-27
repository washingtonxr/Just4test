#include <stdio.h>
#include <stdlib.h> // exit()
#include <unistd.h> // fork(), sleep(), _exit(), pid_t
#define __USE_GNU
#include <sched.h>
#include <pthread.h>

typedef struct _SyS_Thread_T{
    char *name;
    void *(* fun)(void * arg);
    unsigned char core_id;
}sys_thread_t;

static void showPid(void)
{
    int pid, ppid;
    pid = getpid();
    ppid = getppid();

    printf("pid: %d\n", pid);
    printf("ppid: %d\n", ppid);
}

static void setCore(void *arg)
{
    unsigned char core_id = *(unsigned char *)arg;
    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(core_id, &mask);

    if(-1 == pthread_setaffinity_np(pthread_self(), sizeof(mask), &mask))
    {
        printf("pthread_setaffinity_np %d err!", core_id);
        return;
    }
    printf("This task is set to core %d\n", core_id);
    return; 
}

static void *thread1(void * arg)
{
    setCore(arg);
    while(1){
        printf("Thread start running!\n");
        sleep(1);
    }
    pthread_exit("Hello from thread!");
}

static void *thread2(void * arg)
{
    setCore(arg);
    while(1){
        printf("Thread start running!\n");
        sleep(1);
    }
    pthread_exit("Hello from thread!");
}

static void *thread3(void * arg)
{
    setCore(arg);
    while(1){
        printf("Thread start running!\n");
        sleep(1);
    }
    pthread_exit("Hello from thread!");
}

static void *thread4(void * arg)
{
    setCore(arg);
    while(1){
        printf("Thread start running!\n");
        sleep(1);
    }
    pthread_exit("Hello from thread!");
}

const sys_thread_t app_init_tab[] = {
    {"thread1", thread1, 1},
    {"thread2", thread2, 2},
    {"thread3", thread3, 3},
    {"thread4", thread4, 4},
    {"thread4", thread4, 5},
    {"thread4", thread4, 6},
    {"thread4", thread4, 7}
};

#define WORKER_NUM 7
int main(void)
{
    pthread_t id[WORKER_NUM];
    void * thread_retval;
    unsigned char i = 0;
    unsigned int cnt;

    for(i = 0; i < WORKER_NUM; i++){
        if (pthread_create(&id[i], 
            0, 
            app_init_tab[i].fun , 
            (void *)&app_init_tab[i].core_id
            ) != 0) 
        {
            printf("Create thread failed!\n");
            exit(1);
        }
    }
    while(1){
        printf("This is master core(%d).\n", cnt++);
        sleep(5);
    }
    for(i = 0; i < WORKER_NUM; i++){
        pthread_join(id[i], &thread_retval);
        printf("%s\n", (char *)thread_retval);
    }
    return 0;
}