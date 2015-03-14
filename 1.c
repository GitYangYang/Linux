/* Yet still have many problems */

/* child write random number to pipe and parent read. */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>
#include<sys/types.h>
#include<sys/wait.h>
int main()
{
	pid_t cpid;
	int i,j,pipe_fd[2];
	int status,r_num;
	int  buf_r[20];
	memset(buf_r,0,sizeof(buf_r));
	if(pipe(pipe_fd)<0)
		perror("pipe error!\n");
	cpid=fork();
	if(cpid == -1)
		perror("fork error!");
	else if(cpid == 0) /* Code executed by child */
	{
	/* child write to pipe */
		close(pipe_fd[0]);
		srand((int)time(0));
		for(i=0;i<20;i++)
		{
			j=1+(int)(20.0*rand()/(RAND_MAX+1.0));
			if(write(pipe_fd[1],&j,1)!=-1)
				printf("Write %d to pipe\n",j);
		}
		close(pipe_fd[1]);
		exit(0);
	}
	else/* Code executed by parent */
	{
	/* parent read from pipe */
		do
		{
			waitpid(cpid,&status,WNOHANG);
			close(pipe_fd[1]);
			if(r_num=read(pipe_fd[0],buf_r,20)>0)
			{
				printf("Read success!\n");
				for(i=0;i<20;i++)
				{
					printf("%d ",buf_r[i]);
				}
			}
		/*	close(pipe_fd[0]);
			waitpid(cpid,NULL,0);
			exit(0);
		*/
		}while(!WIFEXITED(status));
		close(pipe_fd[0]);
		exit(0);
	}
}
