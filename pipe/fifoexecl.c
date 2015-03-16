//利用execl函数调用有名管道读写程序** *
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <errno.h>
#include<fcntl.h>
int main()
{
	unlink("myfifo");
	if((mkfifo("myfifo",0666)<0)&&(errno!=EEXIST)) //读写权限
		printf("cannot create fifoserver\n");
		printf("errono:%d \n",errno");
	}
	if(fork()==0)
		if(execl("fifowrite",NULL)<0)
			perror("Err on execl");
	if(fork()==0)
		if(execl("fiforead",NULL)<0)
			perror("Err on execl");
	 exit(0);
	 return(0);
}

