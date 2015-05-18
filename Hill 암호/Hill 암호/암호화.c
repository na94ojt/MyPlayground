#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
	char table[27]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	int *** temp1;
	int *** temp2;
	int key[2][2]={
		{0,1},
		{3,2}
	};
	char unpassword[100];
	char password[100];
	int x,y,z,i,j=0,len;

	for(i=0;i<100;i++)
	{
		unpassword[i]='A';
		password[i]='A';
	}

	printf("암호화하고 싶은 문장을 입력하세요.(영어대문자만) :");
	scanf("%s",unpassword);

	len=strlen(unpassword);

	temp1=(int ***)malloc(sizeof(int)*(len/4+((len%4) ? 1:0)));

	for(y=0;y<(len/4+((len%4) ? 1:0));y++)
	{
		temp1[y]=(int **)malloc(sizeof(int)*2);
		
		for(x=0;x<2;x++)
		{
			temp1[y][x]=(int *)malloc(sizeof(int)*2);
		}
	}

	temp2=(int ***)malloc(sizeof(int)*(len/4+((len%4) ? 1:0)));
	
	for(y=0;y<(len/4+((len%4) ? 1:0));y++)
	{
		temp2[y]=(int **)malloc(sizeof(int)*2);
		
		for(x=0;x<2;x++)
		{
			temp2[y][x]=(int *)malloc(sizeof(int)*2);
		}
	}

	for(z=0;z<len/4+((len%4) ? 1:0);z++)
	{
		for(y=0;y<2;y++)
		{
			for(x=0;x<2;x++)
			{
				temp1[z][y][x]=0;
				temp2[z][y][x]=0;
			}
		}
	}

////////////////////////////////////////////////////////////////////////////////////////////////

	for(z=0;z<len/4+((len%4) ? 1:0);z++)
	{
		for(y=0;y<2;y++)
		{
			for(x=0;x<2;x++)
			{
				for(i=0;i<26;i++)
				{
					if(table[i] == unpassword[j])
					{
						temp1[z][y][x]=i;
						j++;
						break;
					}
				}
			}
		}
	}

///////////////////////////////////////////////////////////////////////////////////////////

	for(z=0;z<len/4+((len%4) ? 1:0);z++)
	{
		temp2[z][0][0]=temp1[z][0][0]*key[0][0]+temp1[z][0][1]*key[1][0];
		temp2[z][0][1]=temp1[z][0][0]*key[0][1]+temp1[z][0][1]*key[1][1];
		temp2[z][1][0]=temp1[z][1][0]*key[0][0]+temp1[z][1][1]*key[1][0];
		temp2[z][1][1]=temp1[z][1][0]*key[0][1]+temp1[z][1][1]*key[1][1];
	}

	j=0;

	for(z=0;z<len/4+((len%4) ? 1:0);z++)
	{
		for(y=0;y<2;y++)
		{
			for(x=0;x<2;x++)
			{
				for(i=0;i<1000;i++)
				{
					if(i == temp2[z][y][x])
					{
						password[j]=table[i%26];
						j++;
						break;
					}
				}
			}
		}
	}

	printf("암호문 :");

	for(i=0;i<(len/4+((len%4) ? 1:0))*4;i++)
	{
		printf("%c",password[i]);
	}

	printf("\n");

	for(z=0;z<len/4+((len%4) ? 1:0);z++)
	{
		for(y=0;y<2;y++)
		{
			for(x=0;x<2;x++)
			{
				printf("%d ",temp1[z][y][x]);
			}

			printf("\n");
		}

		printf("\n");
	}

	printf("\n");

	for(z=0;z<len/4+((len%4) ? 1:0);z++)
	{
		for(y=0;y<2;y++)
		{
			for(x=0;x<2;x++)
			{
				printf("%d ",temp2[z][y][x]);
			}

			printf("\n");
		}

		printf("\n");
	}

	return 0;
}
