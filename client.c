/* 通用客户端程序 */
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<arpa/inet.h>
#include<netdb.h>  /* gethostbyname() */
#include<errno.h>
#define PORT 9999
#define BUFFER_SIZE 512
int main(int argc,char **argv){
    int sockfd,recvbytes;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    struct hostent *host;
    if(argc!=2){
	fprintf(stderr,"Usage:%s portnumber\a\n",argv[0]);
	exit(1);
    }

/* get host info */
if((host=gethostbyname(argv[1]))==NULL){
    fprintf(stderr,"Cann't get host information!Error:%s\a\n",strerror(errno));
    exit(1);
}

/* create socket */
if((sockfd = socket(AF_INET,SOCK_STREAM,0))==-1){
    fprintf(stderr,"Socket Error :%s\n\a",strerror(errno));
    exit(1);
}

/* Inite sockaddr structure */
bzero(&server_addr,sizeof(struct sockaddr_in));
server_addr.sin_family=AF_INET;
server_addr.sin_addr=*((struct in_addr *)host->h_addr);
server_addr.sin_port=htons(PORT);

/* connect socker */
if(connect(sockfd,(struct sockaddr*)(&server_addr),sizeof(struct sockaddr))==-1){
    fprintf(stderr,"Conncet error:%s\n\a",strerror(errno));
    exit(1);
}
bzero(buffer,BUFFER_SIZE);
if((recvbytes=recv(sockfd,buffer,BUFFER_SIZE,0))==-1){
    fprintf(stderr,"Recv error:%s\a\n",strerror(errno));
    exit(1);
}else{
    fprintf(stderr,"Receive respond:%s\a\n",buffer);
    close(sockfd);
}
}
