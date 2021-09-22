#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>

void readFile() {
        char s[] = "main.c";
        //只读打开文件
        int fd = open(s, O_RDONLY);

        if(fd == -1) {
                printf("error is %s\n", strerror(errno));
                return;
        }

        printf("sucess fd = %d\n", fd);
        char buf[100];
        memset(buf, 0, sizeof(buf));
        //read返回0表示文件读取完毕
        while(read(fd, buf, sizeof(buf) - 1) > 0) {
                printf("%s\n", buf);
                memset(buf, 0, sizeof(buf));
        }

        printf("%s\n", buf);
        //别忘记关闭
        close(fd);
}

void writeFile() {
        char s[] = "abc.txt";
        //读写并追加方式
        int fd = open(s, O_RDWR | O_APPEND | O_CREAT);
        if(fd == -1) {
                //发生错误会把错误信息设置到errno中
                //通过strerror函数获取错误内容
                printf("error is %s\n", strerror(errno));
                return;
        }

        printf("sucess fd = %d\n", fd);
        char buf[1024];
        memset(buf, 0, sizeof(buf));
        int i = 10;
        while(i-- > 0){
                strcpy(buf, "hello world linux write file \n");
		printf("sizeof buf = %d\n", strlen(buf));
                write(fd, buf, strlen(buf));
                memset(buf, 0, sizeof(buf));
        }

        close(fd);

}


int main(int arg, char *args[]) {
        readFile();
        writeFile();
        return 0;
}
