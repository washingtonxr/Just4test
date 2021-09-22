#ifndef __COMMON_H__
#define __COMMON_H__
#define __USE_GNU
#include <sched.h>      /* For multicore. */
#include <pthread.h>    /* For multiprocess. */
#include <stdio.h>
#include <stdbool.h>    /* For bool type. */
#include <malloc.h>
#include <time.h>
//
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>

#define USE_SPL
#define L2_DUMP_L2L3MSG
#define WORKER_NUM 7
/* 对基础数据类型作重定义，如果平台已经有了，这块定义不生效 */
#ifndef CHAR
        typedef char                  CHAR;
#endif
#ifndef INT8
        typedef char                  INT8;
#endif
#ifndef UINT8
        typedef unsigned char         UINT8;
#endif
#ifndef BOOL8
        typedef unsigned char         BOOL8;
#endif
#ifndef UCHAR
        typedef unsigned char         UCHAR;
#endif
#ifndef INT16
    typedef short                     INT16;
#endif
#ifndef UINT16
    typedef unsigned short            UINT16;
#endif
#ifndef WORD
    typedef short            WORD;
#endif
#ifndef INT32
    typedef int                       INT32;
#endif
#ifndef UINT32
    typedef unsigned int              UINT32;
#endif
#ifndef INT64
    typedef long long                     INT64;
#endif
#ifndef UINT64
    typedef unsigned long long            UINT64;
#endif
#ifndef NULL
    #define NULL                      ((void *)0)
#endif

/* common define for err/ok in l2 */
#define L2_OK                   0   /* not any exception */
#define L2_NOK                  1   /* unknow err */
#define L2_ERR                  1   /* unknow err */
#define L2_ERR_RES              2   /* resource lack,such as mem */
#define L2_ERR_CFG              4   /* err config from l3 */
#define L2_ERR_DATA             8   /* err data from cn/l1/... */

#define L2_FALSE             0
#define L2_TRUE              1

/* uni-direct list item */
typedef struct L2UDLITEM
{
    void *pNxt;
}L2UdlItem;

typedef struct L2BDLITEM
{
    void *pNxt;
    void *pPrv;
}L2BdlItem;

typedef struct _SyS_Thread_T{
    char *name;
    void *(* fun)(void * arg);
    unsigned char core_id;
}sys_thread_t;

typedef struct L2POINTERLIST
{
    void *pBgn;
    void *pEnd;
}L2PointerList;

typedef struct L2MSGQUE{
    L2PointerList tQue;
#ifndef USE_SPL
    pthread_mutex_t tMtx;
#else
    pthread_spinlock_t tSpl;
#endif
    bool   Empty;
}L2MsgQue;

typedef struct _TASK_ENTRY_T{
    unsigned char core_id;
    unsigned int cnt;   
    L2MsgQue *que;
}task_entry_t;

typedef void (* L2MSGFUNC)(void);

typedef struct L2RINGMSG{
    /* fifo uni-direct list */
    void                *pNxt;
    void                *pMsg;          /* mem point for msg */
    /* inter msg can be parsed by self */
    /* intra msg need call func by icell, iue and isess params to be parsed */
    L2MSGFUNC           pFunc;          /* receiver call the func to continue process */
    UINT32              pCnt;
    struct timespec     pPushTime1;
    struct timespec     pPushTime2;
    struct timespec     pPullTime1;
    struct timespec     pPullTime2;
}L2RingMsg;

INT32 L2UdlPush(void *pHandle, void *pItem);
void *L2UdlPull(void *pHandle);

#endif
/* End of this file. */