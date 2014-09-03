#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <WinSock2.h>
#include <process.h>

#pragma comment(lib, "ws2_32.lib")

using namespace cv;

#define MAXCLNT 10

typedef struct
{
	CvSize size;
	int imageSize;
}SENDDATA;

SOCKET g_clnt_sock[MAXCLNT];

unsigned WINAPI cctvsender(void* arg)
{
	IplImage* image = 0;
	CvCapture* capture = cvCaptureFromCAM(0);
	SENDDATA senddata;
	char* SendImageData;

	while (1)
	{
		cvGrabFrame(capture);
		image = cvRetrieveFrame(capture);
		
		SendImageData = (char*)malloc(image->imageSize);

		senddata.size.height = image->height;
		senddata.size.width = image->width;
		senddata.imageSize = image->imageSize;
		memcpy(SendImageData, image->imageData, image->imageSize);

		


		for (int i = 0; i < MAXCLNT; i++)
		{
			if (0 != g_clnt_sock[i])
			{
				if (-1 == send(g_clnt_sock[i], (char*)&senddata, sizeof(senddata), 0))
				{
					g_clnt_sock[i] = 0;
				}
				if (-1 == send(g_clnt_sock[i], (char*)SendImageData, image->imageSize, 0))
				{
					g_clnt_sock[i] = 0;
				}
			}
		}

		free(SendImageData);
		cvShowImage("CCTV", image);
		if (0 <= cvWaitKey(10))
		{
			break;
		}

	}

	return 0;
}

int main()
{
	WSADATA wsa;

	if (0 != WSAStartup(MAKEWORD(2, 2), &wsa))
	{
		return -1;
	}
	
	SOCKET serv_sock, clnt_sock;
	SOCKADDR_IN serv_addr, clnt_addr;
	int addrlen = sizeof(clnt_addr);

	serv_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (-1 == serv_sock)
	{
		return -1;
	}
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(9999);

	if (-1 == bind(serv_sock, (SOCKADDR*)&serv_addr, sizeof(serv_addr)))
	{
		return -1;
	}

	if (-1 == listen(serv_sock, SOMAXCONN))
	{
		return -1;
	}

	ZeroMemory(g_clnt_sock, sizeof(g_clnt_sock));

	_beginthreadex(NULL, 0, cctvsender, NULL, 0, NULL);
	while (1)
	{
		clnt_sock = accept(serv_sock, (SOCKADDR*)&clnt_addr, &addrlen);
		if (-1 == clnt_sock)
		{
			printf("Invalid Client\n");
		}
		else
		{
			for (int i = 0; i < MAXCLNT; i++)
			{
				if (0 == g_clnt_sock[i])
				{
					g_clnt_sock[i] = clnt_sock;
					break;
				}
			}
			
		}
	}

	return 0;
}