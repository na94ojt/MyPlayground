#include <stdio.h>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

int main()
{
	WSADATA wsa;
	if (0 != WSAStartup(MAKEWORD(2, 2), &wsa))
	{
		return -1;
	}

	SOCKET serv_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (-1 == serv_sock)
	{
		return -1;
	}

	SOCKADDR_IN serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(9000);

	if (-1 == bind(serv_sock, (SOCKADDR*)&serv_addr, sizeof(serv_addr)))
	{
		return -1;
	}

	if (-1 == listen(serv_sock, SOMAXCONN))
	{
		return -1;
	}

	SOCKET clnt_sock;
	SOCKADDR_IN clnt_addr;
	int addrlen = sizeof(clnt_addr);

	clnt_sock = accept(serv_sock, (SOCKADDR*)&clnt_addr, &addrlen);
	if (-1 == clnt_sock)
	{
		return -1;
	}


	return 0;
}