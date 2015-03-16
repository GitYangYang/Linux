/*设计一个程序，要求创建消息队列，输入的文字添加到消息队列后，读取队列中的消息输出.*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

struct msgbuf
{
	long msg_type;
	char msg_text[512];
};
int main()
{
	int qid;
	key_t key;
	int len ;
	struct msgbuf msg;
	if((key=ftok(".",'a'))==-1)
	{
		perror("产生标准key 出错");
		exit(1);
	}
	if((qid=msgget(key,IPC_CREAT|0666))==-1)
	{
		perror("创建消息队列出错");
		exit(1);
	}
	printf("创建、打开的队列号是:%d\n",qid);
	puts("请输入队列消息:");
	if((fgets((&msg)->msg_text,512,stdin))==NULL)
	{
		puts("没有消息");
		exit(1);
	}
	msg.msg_type=getpid();
	len=strlen(msg.msg_text);
	if((msgsnd(qid,&msg,len,0))<0)
	{
		perror("添加消息出错");
		exit(1);
	}
	if((msgrcv(qid,&msg,512,0,0))<0)
	{
		perror("读取消息出错");
		exit(1);
	}
	printf("读取的消息是:%s\n",(&msg)->msg_text);
	if((msgctl(qid,IPC_RMID,NULL))<0)
	{
		perror("删除消息队列出错");
		exit(1);
	}
	exit(0);
}
