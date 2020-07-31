#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <mcheck.h>
#include "main.h"

#define PAYLOAD_LEN 128

int main(unsigned int argc, unsigned char **argv)
{
    unsigned int ret, i;
    iMsg_Package_T *iMsg = NULL;

    //setenv("MALLOC_TRACE", "output", 1);
    //mtrace();

    /* Memmory allocate for header. */
    printf("sizeof(iMsg_Package_T) = %d\n", sizeof(iMsg_Package_T));
    printf("sizeof(iMsg_Header_T) = %d\n", sizeof(iMsg_Header_T));
    printf("sizeof(iMsg_Package_T2) = %d\n", sizeof(iMsg_Package_T2));
    printf("sizeof(unsigned char) = %d\n", sizeof(unsigned char));
    printf("sizeof(unsigned char *) = %d\n", sizeof(unsigned char *));
    printf("sizeof(unsigned int) = %d\n", sizeof(unsigned int));
    printf("sizeof(unsigned int *) = %d\n", sizeof(unsigned int *));

    iMsg = (iMsg_Package_T *)malloc(sizeof(iMsg_Package_T));
    if(NULL == iMsg){
        printf("Malloc failed for imsg.\n");
        exit(0);
    }
    /* Memmory allocate for payload. */
    iMsg->payload = (unsigned char *)malloc(PAYLOAD_LEN*sizeof(unsigned char));
    if(NULL == iMsg->payload){
        printf("Malloc failed for iMsg->payload.\n");
        free(iMsg);
        exit(0);
    }

    iMsg->header.fd = 0x01;
    iMsg->header.group = 0x02;
    iMsg->header.id = 0x03;
    iMsg->header.len_low = PAYLOAD_LEN;
    iMsg->header.len_high = 0;

    for(i = 0; i < PAYLOAD_LEN; i++){
        *(unsigned char *)(iMsg->payload + i) = i;
    }

    printf("Image data :\n");
    printf("fd : 0x%02x\n", iMsg->header.fd);
    printf("group : 0x%02x\n", iMsg->header.group);  
    printf("id : 0x%02x\n", iMsg->header.id);
    printf("len_low : 0x%02x\n", iMsg->header.len_low); 
    printf("len_high :0x %02x\n", iMsg->header.len_high);
    printf("Image payload data :\n");

    printf("addr iMsg:%p\n", iMsg);
    printf("addr iMsg+1:%p\n", (iMsg_Package_T *)(iMsg+1));
    printf("addr iMsg+1:%p\n", (iMsg+1));
    printf("addr iMsg+1:%p\n", ((void *)iMsg+1));
    printf("addr payload:%p\n", iMsg->payload);

    for(i = 0; i < PAYLOAD_LEN; i++){
        //printf("%p: 0x%02x\n", iMsg->payload + i, \
                *(unsigned char *)(iMsg->payload + i));
        printf("%02x ", *(unsigned char *)(iMsg->payload + i));
    }
    printf("\nImage data end.\n");

    free(iMsg->payload);
    free(iMsg);

    return 0;
}