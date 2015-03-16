//fiforead.c **
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
int main()
{
	char buffer[80];
	int fd;
	fd= open("myfifo",O_RDONLY);
	read(fd,buffer,80);
	printf("%s\n",buffer);
	close(fd);
	exit(0);
}
