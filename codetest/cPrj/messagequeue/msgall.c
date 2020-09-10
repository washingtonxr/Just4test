#include "common.h"

void displayInfo(COMMON_MSG_T *msg_pdu)
{
    unsigned char i;
    /* Print for all element. */
    //printf("sizeof long = %d\n", sizeof(long));
    //printf("unsigned char = %d\n", sizeof(unsigned char));
    printf("%p:msg_pdu.type = %ld\n", &(msg_pdu)->type, (long)(msg_pdu)->type);
    printf("%p:msg_pdu.group = %d\n", &(msg_pdu)->group, (unsigned char)(msg_pdu)->group);
    printf("%p:msg_pdu.dlen = %d\n", &(msg_pdu)->dlen, (unsigned int)(msg_pdu)->dlen);

    for(i = 0; i < PayloadSize; i++){
        printf("%p:msg_pdu.Payload[%d] = %d\n", \
                msg_pdu->payload + i, i, *((char *)msg_pdu->payload + i));
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
    
    COMMON_MSG_T *msg_pdu;
    
    key = ftok(PathName, ProjectID);		/* Generate message queue key. */
    if(0 > key){
        reportAndExit("Couldn't get key...\n");
    }

    qid = msgget(key, 0666 | IPC_CREAT);	/* Use key to get gueue id. */
    if(0 > qid){
        reportAndExit("Couldn't get queue id...\n");
    }

    for(i = 0; i < GroupNumber; i++){
        msg_pdu = (COMMON_MSG_T *)malloc(sizeof(COMMON_MSG_T));
        if(msg_pdu == NULL){
            reportAndExit("malloc fail for msg_pdu.\n");
        }
        memset(msg_pdu, 0, sizeof(COMMON_MSG_T));

        msg_pdu->payload = (char *)malloc(PayloadSize*sizeof(char));
        if(0 > msg_pdu->payload){
            reportAndExit("Allocate memory for payload failed.\n");
        }

        memset(msg_pdu->payload, 0, PayloadSize);

        for(j = 0; j < PayloadSize; j++){
            *(msg_pdu->payload + j) = j + i;
        }

        msg_pdu->type = 1 + i;
        msg_pdu->group = GT0;
        msg_pdu->dlen = PayloadSize;

        displayInfo(msg_pdu);

        if(msgsnd(qid, (void *)msg_pdu, sizeof(COMMON_MSG_T), IPC_NOWAIT) < 0)  /* don't block */
        {
            printf("Send failed\n");
        }
        free(msg_pdu);
    }

    
    printf("We send done.\n");

    COMMON_MSG_T *recv_msg_pdu;
    {        
        for(i = 0; i < GroupNumber; i++){
            printf("counter = %d ==========>>> \n", i);

            recv_msg_pdu = (COMMON_MSG_T *)malloc(sizeof(COMMON_MSG_T));
            if(recv_msg_pdu == NULL){
                reportAndExit("malloc fail for recv_msg_pdu.\n");
            }
            printf("recv_msg_pdu address:%p\n", recv_msg_pdu);
            memset(recv_msg_pdu, 0, sizeof(COMMON_MSG_T));

            recv_msg_pdu->payload = (char *)malloc(sizeof(char)*PayloadSize);
            if(recv_msg_pdu->payload == NULL){
                reportAndExit("malloc fail for recv_msg_pdu->payload.\n");
            }
            printf("recv_msg_pdu->payload address:%p\n", recv_msg_pdu->payload);
            memset(recv_msg_pdu->payload, 0, sizeof(char)*PayloadSize);

            printf("\n");

            if(msgrcv(qid, (void *)recv_msg_pdu, sizeof(COMMON_MSG_T), i+1, MSG_NOERROR | IPC_NOWAIT) < 0){
                goto err;
            }

            displayInfo(recv_msg_pdu);

            free(recv_msg_pdu->payload);
            free(recv_msg_pdu);
            printf("done");
        }

        /** remove the queue **/
        if (msgctl(qid, IPC_RMID, NULL) < 0)  /* NULL = 'no flags' */
            reportAndExit("trouble removing queue...");
    }

	printf("Hello recv.\n");

    return 0;
err:
    reportAndExit("receive error...\n");
    free(recv_msg_pdu->payload);
    free(recv_msg_pdu);
    return 0;
}


/* End of this file. */