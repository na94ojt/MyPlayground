#include <stdio.h>
#include <tchar.h>
#include "wcomm.h"
#include <Windows.h>

int main()
{
	char flag[10] = "true";
	char signal[10];
	int file_quantity = 0;
	WComm w;
	w.startServer(9494);
	
	char fileslist[50][50] = {0, };


	WIN32_FIND_DATA search_data;

	memset(&search_data, 0, sizeof(WIN32_FIND_DATA));

	char current_directory[100];
	char update_directory[100];

	GetCurrentDirectory(100,current_directory);

	sprintf(update_directory,"%s\\updates\\*",current_directory);

	HANDLE hfiles = FindFirstFile(update_directory,&search_data);

	while(hfiles != INVALID_HANDLE_VALUE)
	{
		strcpy(fileslist[file_quantity++],search_data.cFileName);
		printf("%s is uploaded\n",search_data.cFileName);
		if(FindNextFile(hfiles, &search_data) == FALSE)
			break;
	}
	
	
	while (1)
	{
		w.waitForClient();
		printf("Client Connected............\n");

		for (int i = 2; i<file_quantity; i++)
		{
			char fpath[50];
			w.sendData(flag);
			if (fileslist[i] == 0)
			{
				break;
			}
			sprintf(fpath,"updates\\%s",fileslist[i]);
			w.recvData(signal,4);
			w.fileSend(fpath);
			printf("%s is Sent..............\n",fileslist[i]);
			w.recvData(signal,4);
		}
		strcpy(flag,"false");
		w.sendData(flag);
	}
	
	w.closeConnection();
	return 0;
}