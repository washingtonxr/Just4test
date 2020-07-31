#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "msgquefile"
#include <unistd.h>

#define ProjectID	123
#define PathName	"msgquefile"
#define PayloadSize	4	/* Bytes. */
#define GroupNumber	4



typedef struct _COMMON_MSG_T{
	long type;
	unsigned char group;
	unsigned int dlen;
	char *payload;
}COMMON_MSG_T;

typedef enum _COMMON_GROUP_T{
	GT0 = 0,
	GT1,
	GT2,
	GT3,
	GT4,
	GT5,
	GT6,
	GT7
}COMMON_GROUP_T;


void reportAndExit(const char* msg);

#endif
/* End of this file. */