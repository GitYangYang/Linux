//thread1.c *
#include <stdio.h>
#include <pthread.h>

int temp;
pthread_t id1,id2;
void thread1(void)
{
	int i=0;
	pthread_t myid;
	myid=pthread_self();
	printf("This is a pthread1. myID=%d myID=%d\n",myid,id1);
	for(i=0;i<10;i++)
	{
		temp=i;
		printf("This is a pthread1. temp=%d\n",temp);
		sleep(1);
		if(i==8)
			pthread_exit(0);
	}
}

void thread2(void)
{
	int i;
	pthread_t myid;
	myid=pthread_self();
	printf("This is a pthread2. myID=%d myID=%d\n",myid,id2);
	for(i=0;i<10;i++){
		printf("This is a pthread2. temp=%d\n",temp);
		sleep(1);
	}
	pthread_exit(0);
}
int main(void)
{

	int i,ret;
	ret=pthread_create(&id1,NULL,(void *) thread1,NULL);
	if(ret!=0)
	{
		printf ("Create pthread error!\n");
		exit (1);
	}
	ret=pthread_create(&id2,NULL,(void *) thread2,NULL);
	if(ret!=0)
	{
		printf ("Create pthread error!\n");
		exit (1);
	}
	pthread_join(id1,NULL);
	pthread_join(id2,NULL);
	printf("temp=%d\n",temp);
	exit (0);
}

