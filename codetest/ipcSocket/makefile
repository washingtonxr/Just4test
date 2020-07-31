CC = aarch64-linux-gnu-gcc
#CC = gcc
build:socketClient socketServer

socketClient:
	$(CC) -o socketClient socketClient.c -g -lpthread
socketServer:
	$(CC) -o socketServer socketServer.c -g
.PHONY:clean
clean:
	rm -rf socketClient socketServer
