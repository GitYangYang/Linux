/*This is the 2nd program.
程序A，每隔1s向命名管道中写入20以内的随机数，写10次；
程序B，从命名管道中读取数据；
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main()
{
	char buf;
	mkfifo("fifo1",S_IWUSR|S_IRUSR|S_IRGRP|S_IROTH);
	fd=open("fifo1",O_WRONLY);/*WRITE ONLY*/
	if(fd==-1)
	{
		perror("mkfifo error");
		exit(0);
	}
	srand((int)time(0));
	for(i=0;i<10;i++)
	{
		buf=(int)rand()%21;
		if(write(fd,buf,1)==-1)
		{
			perror("write error");
			exit(0);
		}
		sleep(1);
	}
}
