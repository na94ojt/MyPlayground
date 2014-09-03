#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <WinSock2.h>

using namespace cv;

#pragma comment(lib, "ws2_32.lib")

typedef struct
{
	CvSize size;
	int imageSize;
}RECVDATA;

int main()
{
	WSADATA wsa;
	if (0 != WSAStartup(MAKEWORD(2, 2), &wsa))
	{
		return -1;
	}
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (-1 == sock)
	{
		return -1;
	}

	SOCKADDR_IN sock_addr;
	sock_addr.sin_family = AF_INET;
	sock_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	sock_addr.sin_port = htons(9999);

	if (-1 == connect(sock, (SOCKADDR*)&sock_addr, sizeof(sock_addr)))
	{
		return -1;
	}

	char* RecvImageData;
	IplImage* image = cvCreateImageHeader({ 640, 480 }, IPL_DEPTH_8U, 3);
	RECVDATA recvdata;

	while (1)
	{
		if (-1 == recv(sock, (char*)&recvdata, sizeof(recvdata), 0))
		{
			printf("1\n");
			return -1;
		}

		image->imageSize = recvdata.imageSize;

		RecvImageData = (char*)malloc(image->imageSize);

		if (-1 == recv(sock, (char*)RecvImageData, image->imageSize, 0))
		{
			printf("2\n");
			return -1;
		}

		image->imageData = RecvImageData;

		cvShowImage("CCTV", image);
		
		if (0 <= cvWaitKey(10))
		{
			break;
		}
	}

	return 0;
}