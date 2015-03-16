//fifowrite.c **
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
int main()
{
	char buffer[80];
	int fd;
	char s[ ] = "hello!\n";
	fd = open ("myfifo",O_WRONLY);
	write(fd,s,sizeof(s));
	close(fd);
	exit(0);
}

