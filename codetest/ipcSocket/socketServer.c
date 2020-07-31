//s_unix.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <fcntl.h>

#if 0
#define UNIX_DOMAIN "./psctrl_l1c"//"/tmp/UNIX.domain"
#else
#define UNIX_DOMAIN "/tmp/psctrl_l1c"
#endif

int main(void)
{
    socklen_t clt_addr_len;
    int listen_fd = -1;
    int com_fd = -1;
    int ret;
    unsigned int i = 0;
    static char recv_buf[64]; 
    int len;
    struct sockaddr_un clt_addr;
    struct sockaddr_un srv_addr;
    int srv_fd_flags = 0;
    listen_fd = socket(PF_UNIX,SOCK_STREAM,0);
    if(listen_fd<0)
    {
        perror("cannot create communication socket");
        return 1;
    }  
    
    //set server addr_param
    /* set NON-BLOCK socket */
    srv_fd_flags = 0;
    srv_fd_flags = fcntl(listen_fd, F_GETFL, 0);
    srv_fd_flags |= SOCK_NONBLOCK;
    if (-1 == fcntl(listen_fd, F_SETFL, srv_fd_flags)) 
    {
        perror("fail to modify svr socket");
    }

    /* set srv addr */
    memset(&srv_addr, 0, sizeof(struct sockaddr_un));
    srv_addr.sun_family = AF_UNIX;
    strncpy(srv_addr.sun_path,UNIX_DOMAIN,sizeof(srv_addr.sun_path)-1);
    unlink(UNIX_DOMAIN);
    //bind sockfd & addr
    ret = bind(listen_fd,(struct sockaddr*)&srv_addr,sizeof(srv_addr));
    if(ret==-1)
    {
        perror("cannot bind server socket");
        close(listen_fd);
        unlink(UNIX_DOMAIN);
        return 1;
    }
    //listen sockfd 
    ret = listen(listen_fd,1);
    if(ret==-1)
    {
        perror("cannot listen the client connect request");
        close(listen_fd);
        unlink(UNIX_DOMAIN);
        return 1;
    }
#if 0
    //have connect request use accept
    len = sizeof(clt_addr);
    com_fd = accept(listen_fd,(struct sockaddr*)&clt_addr, &len);
    if(com_fd<0)
    {
        perror("cannot accept client connect request");
        close(listen_fd);
        unlink(UNIX_DOMAIN);
        return 1;
    }
    //read and printf sent client info
#endif

    i = 0;
    unsigned short rlen = 0;
    char rdata;
    while(1){
        com_fd = accept(listen_fd,(struct sockaddr*)&clt_addr, &len);
        if(com_fd < 0)
        {   
            perror("cannot accept client connect request");
        }else{
            printf("Client connected.\n");
            break;
        }
        printf("Still waiting.\n");
        sleep(1);
    }

        while(1){
            printf("com_fd = %d\n", com_fd);
            if(0 < com_fd ){
                //have connect request use accept
                printf("TanG counter = %d\n", i++);
                len = sizeof(clt_addr);
                int num; // = read(com_fd, recv_buf, 4);
                //printf("Message from client (%d)) :%s\n", num, recv_buf);
                num = read(com_fd, recv_buf, sizeof(recv_buf));
                if(num > 0 ){
                printf("Socket is not empty = %d\n", num);
                    while(num){
                        rlen = read(com_fd, &rdata, sizeof(unsigned char));
                        printf("%02x ", rdata);
                        num -= rlen;
                    }
                    printf("\n");

                    //recv_buf[0] = BUFSIZ;
                    //recv_buf[1] = 0x00;
                    recv_buf[2] = 63;
                    recv_buf[3] = 41;
                    ret = write(com_fd, recv_buf, sizeof(recv_buf));
                    printf("ret = %d\n", ret);
                }
            }else{
                //break;
            }
            sleep(1);
        }

    return 0;
}
