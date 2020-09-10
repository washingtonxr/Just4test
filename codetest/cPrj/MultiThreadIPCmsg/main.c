#include <stdio.h>
#include <stdlib.h> // exit()
#include <unistd.h> // fork(), sleep(), _exit(), pid_t
#include <mqueue.h>
#include "common.h"
#include "msg.h"

L2MsgQue *QueUpload;
L2MsgQue *QueDownload;
task_entry_t *tasks[WORKER_NUM];

static void helloworld(void)
{
    printf("Hello World\n");
}

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

static void *thread0(void *arg)
{
    task_entry_t *priv = NULL;
    priv = arg;
    L2RingMsg *msgIn = NULL;
    setCore((void *)&priv->core_id);
    UINT32 Cnt = 0;
    while(1){
        Cnt++;
        //printf("%s(%d):%d:Running!\n", __FUNCTION__, priv->core_id, __LINE__);

        /* Allocate a message. */
        msgIn = (L2RingMsg *)malloc(sizeof(L2RingMsg));
        if(NULL == msgIn){
            printf("Allocate memory for msg failed.\n");
            exit(1);
        }
        msgIn->pCnt = Cnt;
        msgIn->pFunc = helloworld;

        /* Sent msg. */
        if(L2_OK != L2MsgqueSnd(priv->que, msgIn, priv->core_id)){
            printf("%s:%d:Send msg failed.\n", __FUNCTION__, __LINE__);
        }
#if 1
        usleep(10);
#endif
    }
}

static void *thread1(void * arg)
{
    task_entry_t *priv = NULL;
    priv = arg;
    L2RingMsg *msgIn = NULL;
    setCore((void *)&priv->core_id);
    UINT32 Cnt = 0;
    while(1){
        Cnt++;
        //printf("%s(%d):%d:Running!\n", __FUNCTION__, priv->core_id, __LINE__);
        /* Allocate a message. */
        msgIn = (L2RingMsg *)malloc(sizeof(L2RingMsg));
        if(NULL == msgIn){
            printf("Allocate memory for msg failed.\n");
            exit(1);
        }
        msgIn->pCnt = Cnt;
        msgIn->pFunc = helloworld;

        /* Sent msg. */
        if(L2_OK != L2MsgqueSnd(priv->que, msgIn, priv->core_id)){
            printf("%s:%d:Send msg failed.\n", __FUNCTION__, __LINE__);
        }
#if 1
        usleep(10);
#endif
    }
    pthread_exit("Hello from thread!");
}

static void *thread2(void * arg)
{
    task_entry_t *priv = NULL;
    priv = arg;
    L2RingMsg *msgIn = NULL;
    setCore((void *)&priv->core_id);
    UINT32 Cnt = 0;
    while(1){
        Cnt++;
        //printf("%s(%d):%d:Running!\n", __FUNCTION__, priv->core_id, __LINE__);
        /* Allocate a message. */
        msgIn = (L2RingMsg *)malloc(sizeof(L2RingMsg));
        if(NULL == msgIn){
            printf("Allocate memory for msg failed.\n");
            exit(1);
        }
        msgIn->pCnt = Cnt;
        msgIn->pFunc = helloworld;

        /* Sent msg. */
        if(L2_OK != L2MsgqueSnd(priv->que, msgIn, priv->core_id)){
            printf("%s:%d:Send msg failed.\n", __FUNCTION__, __LINE__);
        }
#if 1
        usleep(10);
#endif
    }
    pthread_exit("Hello from thread!");
}

static void *thread3(void * arg)
{
    task_entry_t *priv = NULL;
    priv = arg;
    L2RingMsg *msgIn = NULL;
    setCore((void *)&priv->core_id);
    UINT32 Cnt = 0;
    while(1){
 #if 0
        Cnt++;
        printf("%s(%d):%d:Running!\n", __FUNCTION__, priv->core_id, __LINE__);

        /* Allocate a message. */
        msgIn = (L2RingMsg *)malloc(sizeof(L2RingMsg));
        if(NULL == msgIn){
            printf("Allocate memory for msg failed.\n");
            exit(1);
        }
        msgIn->pCnt = Cnt;
        msgIn->pFunc = helloworld;

        /* Sent msg. */
        if(L2_OK != L2MsgqueSnd(priv->que, msgIn)){
            printf("%s:%d:Send msg failed.\n", __FUNCTION__, __LINE__);
        }
#else
        sleep(1);
#endif
    }
}

const sys_thread_t app_init_tab[] = {
    {"thread0", thread0, 0},
    {"thread1", thread1, 1},
    {"thread2", thread2, 2},
    {"thread3", thread3, 3},
    {"thread4", thread3, 4},
    {"thread4", thread3, 5},
    {"thread4", thread3, 6}
};

static int regResources(void)
{
    /* Register resources. */
    QueUpload = (L2MsgQue *)malloc(sizeof(L2MsgQue));
    if(NULL == QueUpload){
        printf("Failed to malloc memory for QueUpload.\n");
        exit(1);
    }

    QueDownload = (L2MsgQue *)malloc(sizeof(L2MsgQue));
    if(NULL == QueDownload){
        printf("Failed to malloc memory for QueDownload.\n");
        exit(1);
    }

    /* Register entry for tasks. */
    unsigned char i;
    for(i = 0; i < WORKER_NUM; i++){
        tasks[i] = (task_entry_t *)malloc(sizeof(task_entry_t));
        if(NULL == tasks[i]){
            printf("Failed to malloc memory for tasks[%d].\n", i);
            return -1;
        }
        tasks[i]->que = (L2MsgQue *)malloc(sizeof(L2MsgQue));
        if(NULL == tasks[i]){
            printf("Failed to malloc memory for tasks[%d]->L2MsgQue.\n", i);
            return -1;
        }
#ifndef USE_SPL
        pthread_mutex_init(&tasks[i]->que->tMtx, NULL);
#else
        pthread_spin_init(&tasks[i]->que->tSpl, 0);
#endif
        tasks[i]->core_id = app_init_tab[i].core_id;
    }

    return 0;
}

static void checkMsg(void)
{
    task_entry_t *priv = NULL;
    unsigned char i = 0;
    L2RingMsg *msgOut = NULL;

    /* Check msg from tasks. */
    for(i = 0; i < WORKER_NUM; i++){
        priv = tasks[i];
        msgOut = L2MsgqueRcv(priv->que, i);
        if(NULL != msgOut){
            //msgOut->pFunc();
            printf("MsgTakesTime(%d-%d):%p\t%p\t%ld\n", i ,
                    msgOut->pCnt,
                    priv->que,
                    msgOut,
                    ((msgOut->pPullTime2.tv_sec*1000000000 + msgOut->pPullTime2.tv_nsec) -
                    (msgOut->pPushTime1.tv_sec*1000000000 + msgOut->pPushTime1.tv_nsec)));
            free(msgOut->pMsg);
            free(msgOut);
        }
    }

}

int main(void)
{
    pthread_t id[WORKER_NUM];
    void * thread_retval;
    unsigned char i = 0;
    unsigned int Cnt = 0;
#ifdef L2_DUMP_L2L3MSG
    if(0!=pthread_mutex_init(&logMsgL2xL3_lock, NULL))
    {
        printf("fail to create mutex!\n");
    }
#endif
    if(0 > regResources()){
        printf("Allocate resources for thread failed!\n");
        exit(1);
    }

    for(i = 0; i < WORKER_NUM; i++){
        if (pthread_create(&id[i], 
            0, 
            app_init_tab[i].fun , 
            (void *)tasks[i]
            ) != 0) 
        {
            printf("Create thread failed!\n");
            exit(1);
        }
    }

    while(1){
#if 0
        if(Cnt++ >= 100000){
            exit(1);
        }
#endif
        checkMsg();
    }

    for(i = 0; i < WORKER_NUM; i++){
        pthread_join(id[i], &thread_retval);
        printf("%s\n", (char *)thread_retval);
    }
    return 0;
}