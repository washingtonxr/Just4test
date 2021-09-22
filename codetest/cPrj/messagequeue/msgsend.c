#include "common.h"

void displayInfo(COMMON_MSG_T *msg_pdu)
{
    unsigned char i, j;
    /* Print for all element. */
    for(i = 0; i < GroupNumber; i++){
        printf("%p:msg_pdu[%d].type = %ld\n", &(msg_pdu+i)->type, i, (msg_pdu+i)->type);
        printf("%p:msg_pdu[%d].group = %d\n", &(msg_pdu+i)->group, i, (msg_pdu+i)->group);
        printf("%p:msg_pdu[%d].dlen = %d\n", &(msg_pdu+i)->dlen, i, (msg_pdu+i)->dlen);

        for(j = 0; j < PayloadSize; j++){
            printf("%p:msg_pdu[%d].Payload[%d] = %d\n", \
                    (msg_pdu+i)->payload + j, i, j, *((msg_pdu+i)->payload + j));
        }
        printf("\n");
    }
}

int main(int argc, char **argv)
{
    key_t key;
    int qid;
    char *payload;
    unsigned char group_num;
    unsigned char i, j;
    unsigned char counter;
    
    COMMON_MSG_T msg_pdu[GroupNumber];
    
    memset(msg_pdu, 0, sizeof(COMMON_MSG_T)*GroupNumber);
    
    key = ftok(PathName, ProjectID);		/* Generate message queue key. */
    if(0 > key){
        reportAndExit("Couldn't get key...\n");
    }

    qid = msgget(key, 0666 | IPC_CREAT);	/* Use key to get gueue id. */
    if(0 > qid){
        reportAndExit("Couldn't get queue id...\n");
    }

    memset(msg_pdu, 0, sizeof(COMMON_MSG_T));
#if 0
    *msg_pdu = (COMMON_MSG_T *)malloc(GroupNumber*sizeof(COMMON_MSG_T));
    if(0 > *msg_pdu){
        reportAndExit("Allocate memory for msg_pdu failed\n");
    }
#endif

    for(i = 0; i < GroupNumber; i++){
        msg_pdu[i].payload = (char *)malloc(PayloadSize*sizeof(char));
        if(0 > msg_pdu[i].payload){
            reportAndExit("Allocate memory for payload failed.\n");
        }
        
        memset(msg_pdu[i].payload, 0, PayloadSize);
        
        for(j = 0; j < PayloadSize; j++){
            *(msg_pdu[i].payload + j) = j + i;
        }
    }
    
    //displayInfo(msg_pdu);
    
    for(i = 0; i < GroupNumber; i++){
        msg_pdu[i].type = 1 + i;
        msg_pdu[i].group = GT0;
        msg_pdu[i].dlen = PayloadSize;
        if(msgsnd(qid, (void *)&msg_pdu[i], sizeof(COMMON_MSG_T), IPC_NOWAIT)>0){
            printf("Send failed.\n");
        } /* don't block */
    }
    
    displayInfo((COMMON_MSG_T *)msg_pdu);

    printf("We done.\n");

    return 0;
}


/* End of this file. */