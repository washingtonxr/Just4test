build:all
all:common.o msg.o
	gcc -o main main.c common.o msg.o -lpthread -g

common.o:
	gcc -c common.c common.h

msg.o:
	gcc -c msg.c msg.c

.PHONY:clean
clean:
	rm -rf main msg.o common.o common.h.gch
