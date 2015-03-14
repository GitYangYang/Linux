#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
int main()
{
	int fd;
	fd=creat("/home/yangyang/linux/4-5file",S_IRUSR);/*所有者具有只读权限*/
	system("ls /home/yangyang/linux/4-5file -l");/*调用system函数执行命令ls显示此文件到信息*/
	return 0;
}
