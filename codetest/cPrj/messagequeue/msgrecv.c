#include "common.h"

void display(COMMON_MSG_T *msg_pdu)
{
    unsigned char j;
    
    /* Print for all element. */
    printf("%p:msg_pdu->type = %ld\n", &msg_pdu->type, msg_pdu->type);
    printf("%p:msg_pdu->group = %d\n", &msg_pdu->group, msg_pdu->group);
    printf("%p:msg_pdu->dlen = %d\n", &msg_pdu->dlen, msg_pdu->dlen);
#if 1
    for(j = 0; j < PayloadSize; j++){
        printf("%p:msg_pdu.payload[%d] = %d\n", \
                msg_pdu->payload + j, j, (char)*msg_pdu->payload + j);
    }
#endif
    printf("\n");    
}

int main(int argc, char **argv)
{
    COMMON_MSG_T *msg_pdu;
    unsigned char i;
    key_t key;
    int qid;
    //unsigned char counter = 0;
    
    key = ftok(PathName, ProjectID); /* key to identify the queue */
    if (key < 0)
        reportAndExit("key not gotten...");
    
    qid = msgget(key, 0666 | IPC_CREAT); /* access if created already */
    if (qid < 0)
        reportAndExit("no access to queue...");

    //while(1)
    {
        for(i = 0; i < GroupNumber; i++){
            printf("counter = %d ==========>\n", i);
            msg_pdu = (COMMON_MSG_T *)malloc(sizeof(COMMON_MSG_T));
            if(msg_pdu == NULL){
                reportAndExit("malloc fail for msg_pdu.\n");
            }
            memset(msg_pdu, 0, sizeof(COMMON_MSG_T));

            msg_pdu->payload = (char *)malloc(sizeof(char)*PayloadSize);
            if(msg_pdu->payload == NULL){
                reportAndExit("malloc fail for msg_pdu->payload.\n");
            }
            memset(msg_pdu->payload, 0, sizeof(char)*PayloadSize);
#if 1
            if(msgrcv(qid, (void *)msg_pdu, sizeof(COMMON_MSG_T), i+1, MSG_NOERROR | IPC_NOWAIT) < 0){
                goto err;
            }
#endif
            display(msg_pdu);
            printf("done");
            free(msg_pdu->payload);
            free(msg_pdu);
        }
        /** remove the queue **/
        if (msgctl(qid, IPC_RMID, NULL) < 0)  /* NULL = 'no flags' */
            reportAndExit("trouble removing queue...");
    }

	printf("Hello recv.\n");

	return 0;
err:
    reportAndExit("receive error...\n");
    free(msg_pdu->payload);
    free(msg_pdu);
    return 0;
}

/* End of this file. */