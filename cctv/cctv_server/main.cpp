#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <WinSock2.h>
#include <process.h>

#pragma comment(lib, "ws2_32.lib")

using namespace cv;

#define MAXCLNT 10

SOCKET g_clnt_sock[MAXCLNT];

unsigned WINAPI cctvsender(void* arg)
{
	IplImage* image = 0;
	CvCapture* capture = cvCaptureFromCAM(0);
	char* SendImageData;

	while (1)
	{
		cvGrabFrame(capture);
		image = cvRetrieveFrame(capture);

		for (int i = 0; i < MAXCLNT; i++)
		{
			if (0 != g_clnt_sock[i])
			{
				if (-1 == send(g_clnt_sock[i], (char*)image->imageData, image->imageSize, 0))
				{
					g_clnt_sock[i] = 0;
				}
			}
		}

		if (0 <= cvWaitKey(10))
		{
			break;
		}

	}

	cvReleaseImage(&image);
	cvReleaseCapture(&capture);
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