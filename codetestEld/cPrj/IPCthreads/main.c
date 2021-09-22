#include <stdio.h>
#include <unistd.h>


int thread_master(int arg)
{
    unsigned int cnt = 0;
    int pid, ppid;
    pid = getpid();
    ppid = getppid();

    printf("pid: %d\n", pid);
    printf("ppid: %d\n", ppid);
    while(1){
        printf("this is %d - (%d).\n", arg, cnt++);
        sleep(1);
    }
}

int thread_primary(int arg)
{
    unsigned int cnt = 0;
    int pid, ppid;
    pid = getpid();
    ppid = getppid();

    printf("pid: %d\n", pid);
    printf("ppid: %d\n", ppid);
    while(1){
        printf("this is %d - (%d).\n", arg, cnt++);
        sleep(1);
    }
}

#define THREAD_NUM 4
int main()
{
    pid_t pid;
    unsigned char i;

    for(i = 0; i< THREAD_NUM; i++){
        pid = fork();
        if (pid == -1) {
            perror("fork error");
            return -1;
        }

        printf("pid = %d\n", pid);

        if (pid == 0) {
            printf("Parent thread!\n");
            //thread_master(pid);
        } else {
            printf("Child thread!\n");
            thread_primary(pid);
        }
    }

    
    return 0;
}

