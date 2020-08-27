#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <sys/un.h>


/* Socket name for PSCTRL. */
#define UNIX_DOMAIN "/tmp/psctrl_l1c"

/* fd for psctl socket. */
int g_psctl_server_fd = -1;
int g_psctl_client_fd = -1;

#define UINT8 unsigned char
/* 
 * Note: This structure is a duplicate of _SOCK_MSG_HEADER_DPDK_T
 * from this file:
 * 5gnb_code\01.app\common\sock_lib\inc\sock_msg.h
 */
typedef struct _PSCTL_SOCK_MSG_HEADER_T{
	/* Need to remove fd's length, so read data length eq. sizeof(PSCTL_SOCK_MSG_HEADER_T) - sizeof(INT32). */
#if 0
    INT32 sock_fd;        /**< the socket fd received to/from */
#endif
    UINT8 msg_len_low;    /**< low 8bits of length of msg data */
    UINT8 msg_len_high;   /**< high 8bits of length of msg data */
    UINT8 msg_group;      /**< config msg group */
    UINT8 msg_id;         /**< config msg id */
}PSCTL_SOCK_MSG_HEADER_T;

typedef struct _PsCtl_Socket_Msg_T{
	PSCTL_SOCK_MSG_HEADER_T header;
	void *payload;
}PsCtl_Socket_Msg_T;


int main (void)
{
    unsigned int cnt = 0;
    int srv_fd_flags = 0;
#if 0
    /* init server socket */
    g_psctl_server_fd = socket(PF_UNIX, SOCK_STREAM, 0);
    if (g_psctl_server_fd < 0) 
    {
        L2_UXM_E("fail to create psctl server socket");
        return L2_ERR_RES;
    }

    /* set NON-BLOCK socket */
    srv_fd_flags = fcntl(g_psctl_server_fd, F_GETFL, 0);
    srv_fd_flags |= O_NONBLOCK;
    if (-1 == fcntl(g_psctl_server_fd, F_SETFL, srv_fd_flags)) 
    {
        L2_UXM_E("fail to modify psctl server socket");
        return L2_ERR_RES;
    }
    /* set srv addr */
    memset(&srv_addr, 0, sizeof(struct sockaddr_un));
    srv_addr.sun_family = AF_UNIX;
    strncpy(srv_addr.sun_path, CFG_PSCTRL_L1C_SOCK_NAME, sizeof(srv_addr.sun_path) - 1);
    unlink(CFG_PSCTRL_L1C_SOCK_NAME);

    /* bind srv addr */
    if (-1 == bind(g_psctl_server_fd, (struct sockaddr *)&srv_addr, sizeof(srv_addr))) 
    {
        L2_UXM_E("fail to bind svr socket");
        close(g_psctl_server_fd);
        unlink(CFG_PSCTRL_L1C_SOCK_NAME);
        return L2_ERR_RES;
    }

    /* listen srv fd */
    if (-1 == listen(g_psctl_server_fd, 1)) 
    {
        L2_UXM_E("fail to listen svr socket");
        close(g_psctl_server_fd);
        unlink(CFG_PSCTRL_L1C_SOCK_NAME);
        return L2_ERR_RES;
    }
#else
    struct sockaddr_un serverAddr;
    /* init server socket */
    g_psctl_server_fd = socket(PF_UNIX, SOCK_STREAM, 0);
    if (g_psctl_server_fd < 0) 
    {
        printf("fail to create psctl server socket");
    }

    /*
    * Connect to server.
    */
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sun_family = AF_LOCAL;/* AF_UNIX */
    strncpy(serverAddr.sun_path, UNIX_DOMAIN, sizeof(serverAddr.sun_path));

    if (connect(g_psctl_server_fd, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) != 0)
    {
        printf("SOCKMSG :  inter-process socket (%d) connect() failed in sockmsg_tcp_client_start_service\n",g_psctl_server_fd);
        close(g_psctl_server_fd);
        g_psctl_server_fd = -1;
    }

#endif
    while (1)
    {
        PsCtl_Socket_Msg_T shotmsg;
        unsigned char pl[10];
        unsigned char i = 0;
        unsigned short dwByteSend = 0;
        unsigned short dwByteExLen = 0;

        for(i =0; i < 10; i++){
            pl[i] = 10 + i;
        }
        memset(&shotmsg, 0, sizeof(PsCtl_Socket_Msg_T));
        shotmsg.header.msg_group = 12;
        shotmsg.header.msg_id = 13;
        shotmsg.header.msg_len_high = 01;
        shotmsg.header.msg_len_low = 02;
        shotmsg.payload = pl;
        dwByteExLen = sizeof(PsCtl_Socket_Msg_T) + 10;
        dwByteSend = write(g_psctl_server_fd, (void *)&shotmsg, dwByteExLen);
        if(dwByteSend != dwByteExLen){
            printf("Error: dwByteSend = %d, dwByteExLen = %d\n", dwByteSend, dwByteExLen);
        }

        printf("Hello world(%d).\n", cnt++);/* code */

        sleep(1);
    }
}

/* End of this file. */