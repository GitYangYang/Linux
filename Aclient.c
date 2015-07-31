/* Client.c */
#include <stdio.h>  /* fscanf fprintf */
#include <stdlib.h> /* exit */
#include <pthread.h> /* Fun:pthread_create */
#include <string.h> /* Fun:bzero strncmp */
#include <sys/types.h>  /* socket */
#include <sys/socket.h>   /* send recv socket inet_addr */
#include <netinet/in.h> /* inet_addr */
#include <arpa/inet.h>  /* inet_addr */
#include <errno.h>
#define BUFFER_SIZE 1024
void start_routine(void *arg){
	int threadfd = *((int *)arg);
	char buff[BUFFER_SIZE];
	while(1){
		bzero(buff,BUFFER_SIZE);
		fscanf(stderr,"%s",buff);
		send(threadfd,buff,BUFFER_SIZE,0);
		if(strncmp("bye",buff,3)==0){
			exit(0);
		}
	}
}
int main(int argc, char const *argv[])
{
	int connect_fd;
	char buffer[BUFFER_SIZE];
    pthread_t thread;
    struct sockaddr_in srv_addr;
    
    //address and port
    if (argc!=3)
    	{
    		fprintf(stderr, "Usage:%s server_ip_address port\n",argv[0] );
    		exit(1);
    	}	
    
    /* create socket */
    if((connect_fd=socket(AF_INET,SOCK_STREAM,0))==-1){
    	fprintf(stderr, "Cannot create communication socket:%s\n", strerror(errno));
    	exit(1);
    }

    /* server endpoint information */
    bzero(&srv_addr,sizeof(struct sockaddr_in));
    srv_addr.sin_family=AF_INET;
    srv_addr.sin_addr.s_addr=inet_addr(argv[1]);
    srv_addr.sin_port=htons(atoi(argv[2]));

    /* connect the server */
    if(connect(connect_fd,(struct sockaddr*)&srv_addr,sizeof(srv_addr))==-1){
    	fprintf(stderr, "Connect error:%s\n", strerror(errno));
    	close(connect_fd);
    	exit(1);
    }

    /* send message thread */
    pthread_create(&thread,NULL,(void*)(&start_routine),(void*)&connect_fd);
    /* receive message thread */

    /* Loop */
    while(1){
    	bzero(buffer,BUFFER_SIZE);
    	if(recv(connect_fd,buffer,BUFFER_SIZE,0)>0){
    		fprintf(stderr, "%s\n", buffer);
    	}
    	if(strncmp("OK!",buffer,3)==0){
    		close(connect_fd);
    		break;
    	}
    }
	return 0;
}
