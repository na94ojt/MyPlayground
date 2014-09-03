#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

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

	IplImage* image = cvCreateImageHeader({ 640, 480 }, IPL_DEPTH_8U, 3);\
	image->imageSize = 921600;
	char RecvImageData[921600];
	image->imageData = RecvImageData;

	while (1)
	{
		if (-1 == recv(sock, (char*)RecvImageData, image->imageSize, 0))
		{
			printf("2\n");
			return -1;
		}

		cvShowImage("CCTV", image);
		
		if (0 <= cvWaitKey(10))
		{
			break;
		}
	}

	cvDestroyWindow("CCTV");
	cvReleaseImage(&image);

	return 0;
}