#include <stdio.h>
#include "wcomm.h"

int main(int argc, char * argv[])
{
	if (argc != 2)
	{
		printf("Usage : %s <IP>\n",argv[0]);
		return -1;
	}

	WComm w;
	char flag[20] = {0, };
	char fileslist[50][50];
	int file_quantity = 0;

	char ip[20];
	strcpy(ip,argv[1]);
	int port = 9494;

	w.connectServer(argv[1],port);
	w.recvData(flag,20);

	while (!strncmp("true",flag,4))
	{
		w.sendData("OK");
		w.fileReceive(fileslist[file_quantity++]);
		printf("%s is Recieved...............\n",fileslist[file_quantity-1]);
		w.sendData("OK");
		w.recvData(flag,4);
	}
	w.closeConnection();
	return 0;
}