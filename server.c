/* 服务端程序 */
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<arpa/inet.h>  /*htons*/
#include<errno.h>
#define PORT 9999
#define MAX_THREAD_NUM 5
#define BUFFER_SIZE 512
int main(int argc,char **argv){
    int sockfd,client_fd,sin_size;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    char buffer[BUFFER_SIZE];
    /* 创建socket */
    if((sockfd = socket(AF_INET,SOCK_STREAM,0))==-1){
	fprintf(stderr,"Socket Error:%s\n\a",strerror(errno));
	exit(1);
    }
    /*init socket structure */
    bzero(&server_addr,sizeof(struct sockaddr_in));
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(PORT);
    server_addr.sin_addr.s_addr=INADDR_ANY;

    /* 绑定端口 */
    if(bind(sockfd,(struct sockaddr*)(&server_addr),sizeof(struct sockaddr))==-1){
	fprintf(stderr,"Bind error:%s\n\a",strerror(errno));
	exit(1);
    }
    /* 监听 */
    if(listen(sockfd,5)==-1){
	fprintf(stderr,"Listen error:%s\n\a",strerror(errno));
	exit(1);
    }
    sin_size=sizeof(struct sockaddr_in);
    while(1){
	if((client_fd=accept(sockfd,(struct sockaddr *)&client_addr,&sin_size))==-1){
	    fprintf(stderr,"Accept error:%s\a\n",strerror(errno));
	    continue;
	}
	fprintf(stderr,"Get a connection from %s\n\a",inet_ntoa(client_addr.sin_addr));
	if(send(client_fd,"Already connected!\n\a",BUFFER_SIZE,0)==-1){
	    fprintf(stderr,"Send error:%s\a\n",strerror(errno));
	}
	close(client_fd);
    }
    close(sockfd);
    exit(0);
}
