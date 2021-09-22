#include "msg.h"

#ifdef L2_DUMP_L2L3MSG
pthread_mutex_t logMsgL2xL3_lock;
static INT8 logMsgFile[] = "/var/log/l2-l3Msg.log";
#endif

INT32 L2MsgqueSnd(L2MsgQue *pQue, L2RingMsg *pMsg, UINT8 coreId)
{
    if (NULL == pQue)
    {
        printf("Que isn't inited!\n");
        return L2_NOK;
    }
    
    if (NULL == pMsg)
    {
        printf("msg is null!\n");
        return L2_NOK;
    }
    clock_gettime(CLOCK_REALTIME, &pMsg->pPushTime1);

#ifndef USE_SPL
    pthread_mutex_lock(&(pQue->tMtx));
#else
    pthread_spin_lock(&(pQue->tSpl));
#endif
    L2UdlPush((void *) &(pQue->tQue), (void *) pMsg);
    pQue->Empty = L2_FALSE;
#ifndef USE_SPL
    pthread_mutex_unlock(&(pQue->tMtx));
#else
    pthread_spin_unlock(&(pQue->tSpl));
#endif
    clock_gettime(CLOCK_REALTIME, &pMsg->pPushTime2);
#if 0
    printf("T(%d)\t%ld\t%ld\t%ld\t%p\t%p\n", coreId,
            (pMsg->pPushTime1.tv_sec*1000000000 + pMsg->pPushTime1.tv_nsec),
            (pMsg->pPushTime2.tv_sec*1000000000 + pMsg->pPushTime2.tv_nsec),
            (pMsg->pPushTime2.tv_sec*1000000000 + pMsg->pPushTime2.tv_nsec) - 
                (pMsg->pPushTime1.tv_sec*1000000000 + pMsg->pPushTime1.tv_nsec),
            &(pQue->tQue), pMsg);
#endif
#ifdef L2_DUMP_L2L3MSG
    UINT32 i = 0;
    char logBuf[1024];
    UINT32 logOffSet = 0;
    int logfd = 0; 
    struct timeval us;
    gettimeofday(&us,NULL);
    memset(logBuf, 0, sizeof(logBuf));
    sprintf(logBuf, "%ld:Core(%d) send msg(%p) to list(%p).\n", (us.tv_sec*1000000 + us.tv_usec), coreId, pMsg, pQue);
    pthread_mutex_lock(&logMsgL2xL3_lock);
    logfd = open(logMsgFile, O_RDWR | O_APPEND | O_CREAT);
    if(logfd == -1) {
        printf("error is %s\n", strerror(errno));
    }
    write(logfd, logBuf, strlen(logBuf));
    close(logfd);
    pthread_mutex_unlock(&logMsgL2xL3_lock);
    //printf("Core(%d) send msg(%p) to list(%p).\n", coreId, pMsg, pQue);
#endif
    return L2_OK;
}

L2RingMsg *L2MsgqueRcv(L2MsgQue *pQue, UINT8 coreId)
{
    if (NULL == pQue)
    {
        printf("Que isn't inited!\n");
        return NULL;
    }
    
    if(L2_TRUE == pQue->Empty)
        return NULL;
    
    struct timespec tv;
    clock_gettime(CLOCK_REALTIME, &tv);
#ifndef USE_SPL
    pthread_mutex_lock(&(pQue->tMtx));
#else
    pthread_spin_lock(&(pQue->tSpl));
#endif
    L2RingMsg *p = (L2RingMsg *) L2UdlPull((void *) &(pQue->tQue));
    if(NULL == p){
        pQue->Empty = L2_TRUE;
#ifndef USE_SPL
        pthread_mutex_unlock(&(pQue->tMtx));
#else
        pthread_spin_unlock(&(pQue->tSpl));
#endif
        return NULL;
    }
#ifndef USE_SPL
    pthread_mutex_unlock(&(pQue->tMtx));
#else
    pthread_spin_unlock(&(pQue->tSpl));
#endif
    clock_gettime(CLOCK_REALTIME, &p->pPullTime2);
    p->pPullTime1 = tv;
#if 0
    printf("R(%d)\t%ld\t%ld\t%ld\t%p\t%p\n", coreId,
            (p->pPullTime1.tv_sec*1000000000 + p->pPullTime1.tv_nsec),
            (p->pPullTime2.tv_sec*1000000000 + p->pPullTime2.tv_nsec),
            (p->pPullTime2.tv_sec*1000000000 + p->pPullTime2.tv_nsec) - 
                (p->pPullTime1.tv_sec*1000000000 + p->pPullTime1.tv_nsec),
            &(pQue->tQue), p);
#endif
#ifdef L2_DUMP_L2L3MSG
    UINT32 i = 0;
    char logBuf[1024];
    UINT32 logOffSet = 0;
    int logfd = 0; 
    struct timeval us;
    gettimeofday(&us,NULL);
    memset(logBuf, 0, sizeof(logBuf));
    sprintf(logBuf, "%ld:Core(%d) receive msg(%p) from list(%p).\n", (us.tv_sec*1000000 + us.tv_usec), coreId, p, pQue);
    pthread_mutex_lock(&logMsgL2xL3_lock);
    logfd = open(logMsgFile, O_RDWR | O_APPEND | O_CREAT);
    if(logfd == -1) {
        printf("error is %s\n", strerror(errno));
    }
    write(logfd, logBuf, strlen(logBuf));
    close(logfd);
    pthread_mutex_unlock(&logMsgL2xL3_lock);
    //printf("Core(%d) receive msg(%p) to list(%p).\n", coreId, p, pQue);
#endif
    return p;
}

/* End of this file. */