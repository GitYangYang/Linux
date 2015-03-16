//中断例子
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void fun();
void fun2();
int main()
{
	pid_t result;
	int ret;
	result =fork(); //fork
	if(result<0)
	{
		perror("fail to creat child !\n");
		exit(1);
	}
	else if(result==0) //child process
	{
		int ret;
		sleep(2);
		printf("\nChild :\n");
		int p_pid,p_ppid;
		p_pid =getpid();
		p_ppid =getppid();
		printf("my pid: %d\n",p_pid);
		printf("my father ppid: %d\n",p_ppid);
		printf("I am OK !\n\n");
		ret =kill(p_ppid,SIGUSR1);
		while(ret == -1)
		{
			ret =kill(p_ppid,SIGUSR1);
		}
		exit(1);
	}
	else  //parent process
	{
		int t;
		printf("Father :\n");
		printf("Are you ready? \n");
		(void) signal(SIGUSR1,fun);
		(void) signal(SIGINT,fun2);//中断Ctrl+C
		t=0;
		while(1)
		{
			sleep(1);
			printf("wait...%d seconds\n",++t);
		}
		exit(0);
	}
}

void fun()
{
	printf("I have received !\n");
}
void fun2()
{
	printf("\nyou have enter Ctrl+C!\n");
	raise(SIGKILL);
}

