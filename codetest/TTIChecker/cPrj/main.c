#include "main.h"
static char logMsgFile[] = "l1cGetInd.log"; /* Location of message write into.    */
#define LINELEN 256

int main(unsigned int argc, char **argv)
{
    char buffer[LINELEN];
    char buf[1];
    unsigned int i = 0;
    int logfd;
    unsigned int dlen = 0;
    unsigned int dind = 0;
    
    logfd = open(logMsgFile, O_RDONLY);
    if(0 == logfd){
        printf("File open failed.\n");
    }
    printf("fd = %d\n", logfd);

    while(1){
        memset(buffer, 0, sizeof(buffer));
        dind = 0;

        while(1){
            dlen = read(logfd, buf, 1);
            dind += dlen;
            printf("%c", buf[0]);
        }

        printf("%d:\n", dind);
        if(dlen <= 0){
            break;
        }
    }

    printf("Done\n");
    close(logfd);
    return 0;
}


