build:doconfig all
doconfig:
	$(shell mkdir -p ./build)
	$(shell touch ./build/msgquefile)

all:msgsend msgrecv msgall
	$(shell mv msgsend msgrecv msgall build)

msgsend:
	gcc -o msgsend msgsend.c common.h common.c -lm -g

msgrecv:
	gcc -o msgrecv msgrecv.c common.h common.c -lm -g

msgall:
	gcc -o msgall msgall.c common.h common.c -lm -g

.PHONY:clean
clean:
	rm -rf build
