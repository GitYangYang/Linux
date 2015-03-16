#include"stdio.h"
#include<stdlib.h>
int main()
{
	int i,j;
	srand((int)time(0));
	for(i=0;i<10;i++)
	{
		j=rand()%21-10;
		printf("%d\n",j);
	}
	return 0;
}
