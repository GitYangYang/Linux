#include<stdlib.h>
#include"stdio.h"
int main()
{
	int i,u;
	srand((unsigned)time(0));//int or unsigned
	for(i=0;i<10;i++)
	{
		u=(int)(20.0*rand()/(RAND_MAX+1.0))-10;
		printf("%6d\n",u);
	}
}
