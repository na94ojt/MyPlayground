#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <WinSock2.h>

using namespace cv;

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

	Mat newC;

	while (1)
	{
		if (-1 == recv(sock, (char*)&newC, sizeof(newC), 0))
		{
			return -1;
		}
		imshow("CCTV", newC);
	}

	return 0;
}