#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
/* Servert.c */
#include<sys/socket.h>
#include<string.h>
#include<arpa/inet.h>
#include<errno.h>
#define THREAD_QUERY 20
#define BUFFER_SIZE 1024 
#define PORT 9999
#define THREAD_MAX_NUM 2 
int thread_num=THREAD_MAX_NUM;
void talk_to_client(void *data){
    int new_server_socket=*(int*)data;
    char buffer[BUFFER_SIZE];
    bzero(buffer,BUFFER_SIZE);
    int recvbytes;
    strcpy(buffer,"Welcom!");
    strcat(buffer,"\n");
    send(new_server_socket,buffer,BUFFER_SIZE,0);
    while(1){
	bzero(buffer,BUFFER_SIZE);
	if((recvbytes=recv(new_server_socket,buffer,BUFFER_SIZE,0))>0){
	    fprintf(stderr,"Client:%s\a\n",buffer);
	    if(strncmp("bye",buffer,3)==0){
		send(new_server_socket,"bye",BUFFER_SIZE,0);
		break;
	    }
	    send(new_server_socket,buffer,BUFFER_SIZE,0);
        }else
		continue;
    }
    bzero(buffer,BUFFER_SIZE);
    close(new_server_socket);
    thread_num++;
    pthread_exit(NULL);
}

int main(int argc,char **argv){
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    bzero(&server_addr,sizeof(struct sockaddr));
    server_addr.sin_family=AF_INET;
    server_addr.sin_addr.s_addr=htons(INADDR_ANY);
    server_addr.sin_port=htons(PORT);

/* create socket */
    int server_socket;
    if((server_socket=socket(AF_INET,SOCK_STREAM,0))==-1){
        fprintf(stderr,"Socket error:%s\a\n",strerror(errno));
        exit(1);
    }
/* bind socket */
if(bind(server_socket,(struct sockaddr*)&server_addr,sizeof(struct sockaddr))==-1){
    fprintf(stderr,"Bind error:%s\a\n",strerror(errno));
    exit(1);
}
/* lisent socket */
if(listen(server_socket,THREAD_QUERY)==-1){
    fprintf(stderr,"Listen error:%s\a\n",strerror(errno));
    exit(1);
}
pthread_t *thread;
int sin_size=sizeof(struct sockaddr_in);
while(1){
    int content_socket=accept(server_socket,(struct sockaddr*)&client_addr,&sin_size);
    if(content_socket==-1){
        fprintf(stderr,"Accept error:%s\a\n",strerror(errno));
        continue;
}

    if(thread_num){
        pthread_t child_thread;

        if(pthread_create(&child_thread,NULL,talk_to_client,(void*)&content_socket)){
             fprintf(stderr,"Thread create error:%s\a\n",strerror(errno));
             continue;
        }
        thread_num--;
    }else{
	send(content_socket,"\003达到最大连接数，稍后再试！\a\n",BUFFER_SIZE,0);
    }
}
    close(server_socket);
    return 0;
}
