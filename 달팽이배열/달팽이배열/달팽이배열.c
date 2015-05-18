#include<stdio.h>
#include<stdlib.h>

int main()
{
	int ** arr;
	int max,x,y,len,num=1;

	printf("Insert number :");
	scanf("%d",&max);

	arr=(int **)malloc(sizeof(int)*max);

	for(y=0;y<max;y++)
	{
		arr[y]=(int *)malloc(sizeof(int)*max);
	}

	y=0;
	x=0;

	for(len=0;len<max*2-1;len++)
	{
		switch(len%4)
		{
		case 0:
			for(;x<max-len/4-1;x++)
			{
				arr[y][x]=num;
				num++;
			}
			break;
		case 1:
			for(;y<max-len/4-1;y++)
			{
				arr[y][x]=num;
				num++;
			}
			break;
		case 2:
			for(;x>=len/4+1;x--)
			{
				arr[y][x]=num;
				num++;
			}
			break;
		case 3:
			for(;y>len/4+1;y--)
			{
				arr[y][x]=num;
				num++;
			}
			break;
		default:
			printf("이거 왜이래");
		}
	}
	
	if(max%2 == 0)
	{
		arr[max/2][max/2-1]=max*max;
	}
	else
	{
		arr[max/2][max/2]=max*max;
	}

	for(y=0;y<max;y++)
	{
		for(x=0;x<max;x++)
		{
			printf("%5d",arr[y][x]);
		}
		printf("\n");
	}

	system("PAUSE");
	return 0;
}