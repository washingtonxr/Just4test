#ifndef __MSG_H_
#define __MSG_H_
#include "common.h"

#ifdef L2_DUMP_L2L3MSG
pthread_mutex_t logMsgL2xL3_lock;
#endif

L2RingMsg *L2MsgqueRcv(L2MsgQue *pQue, UINT8 coreId);
INT32 L2MsgqueSnd(L2MsgQue *pQue, L2RingMsg *pMsg, UINT8 coreId);
#endif
/* End of this file. */