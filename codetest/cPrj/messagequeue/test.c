#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>

#define MAX_MSGLEN 4;
#define PATH "./imapmsg"

typedef struct student
{
	int age;
	char name[10];
}*st;

typedef struct
{
	long mtype;
	st val;
}mymsg;

int main()
{
	int res,msgid;
	char *path = PATH;
	key_t key = ftok(path,742);
	msgid =  msgget(key,0666|IPC_CREAT);
	if(msgid>=0){
		printf("消息队列初始化成功:%d.\n",msgid);
	}else{
		printf("消息队列初始化shibai\n");
	}
	
	mymsg smsg;
	smsg.mtype = 10;
	//strcpy(smsg.val,"ABCd");
	//struct student stu={30,"qq"};
	struct student stu;
	stu.age=30;
	strcpy(stu.name,"qq");
	
	printf("%d,%s\n",stu.age,stu.name);
	//memcpy(smsg.val,&stu,sizeof(st));
	smsg.val = &stu;
	
	res = msgsnd(msgid,(void *)&(smsg),sizeof(smsg),0);
	if(-1 == res)
	{
		printf("发送失败\n");
		
	}
	else
	{
		printf("发送成功\n");
		printf("%02x\n",(smsg.val));
		printf("%d\n",(smsg.val)->age);
		printf("%s\n",(smsg.val)->name);
		
	}
	
	mymsg rmsg;
	res = msgrcv(msgid,(void *)&(rmsg),sizeof(mymsg),0,0);
	if(-1 == res)
	{
		printf("jieshou失败\n");
	}
	else
	{
		printf("jieshou成功:%d\n%s\n",((struct student*)rmsg.val)->age,((struct student*)rmsg.val)->name);
	}	
	
	printf("stu.age%d\n",stu.age);
	
	res=msgctl(msgid,IPC_RMID,NULL);
	if(-1 != res)
	{
		printf("删除消息队列成功:%d.\n");
	
	}

}
//Reference from : https://bbs.csdn.net/topics/370243296