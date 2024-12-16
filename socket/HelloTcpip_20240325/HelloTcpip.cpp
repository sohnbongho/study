// HelloTcpip.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include <winsock2.h>
#pragma comment(lib, "ws2_32")

int _tmain(int argc, _TCHAR* argv[])
{
	//������ �ʱ�ȭ
	WSADATA wsa = { 0 };
	if (::WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		puts("ERROR: ������ �ʱ�ȭ �� �� �����ϴ�.");
		return 0;
	}

	//1. ���Ӵ�� ���� ����
	SOCKET hSocket = ::socket(AF_INET, SOCK_STREAM, 0);
	if (hSocket == INVALID_SOCKET)
	{
		puts("ERROR: ���� ��� ������ ������ �� �����ϴ�.");
		return 0;
	}

	//2. ��Ʈ ���ε�
	SOCKADDR_IN	svraddr = { 0 };
	svraddr.sin_family = AF_INET;
	svraddr.sin_port = htons(25000);
	svraddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	if (::bind(hSocket, (SOCKADDR*)&svraddr, sizeof(svraddr)) == SOCKET_ERROR)
	{
		puts("ERROR: ���Ͽ� IP�ּҿ� ��Ʈ�� ���ε� �� �� �����ϴ�.");
		return 0;
	}

	//3. ���Ӵ�� ���·� ��ȯ
	if (::listen(hSocket, SOMAXCONN) == SOCKET_ERROR)
	{
		puts("ERROR: ���� ���·� ��ȯ�� �� �����ϴ�.");
		return 0;
	}

	//4. Ŭ���̾�Ʈ ���� ó�� �� ����
	SOCKADDR_IN clientaddr = { 0 };
	int nAddrLen = sizeof(clientaddr);
	SOCKET hClient = 0;
	char szBuffer[128] = { 0 };
	int nReceive = 0;

	//4.1 Ŭ���̾�Ʈ ������ �޾Ƶ��̰� ���ο� ���� ����(����)
	while ((hClient = ::accept(hSocket,
		(SOCKADDR*)&clientaddr,
		&nAddrLen)) != INVALID_SOCKET)
	{
		puts("�� Ŭ���̾�Ʈ�� ����Ǿ����ϴ�."); fflush(stdout);
		//4.2 Ŭ���̾�Ʈ�κ��� ���ڿ��� ������.
		while ((nReceive = ::recv(hClient, szBuffer, sizeof(szBuffer), 0)) > 0)
		{
			//4.3 ������ ���ڿ��� �״�� ��������.
			::send(hClient, szBuffer, sizeof(szBuffer), 0);
			puts(szBuffer); fflush(stdout);
			memset(szBuffer, 0, sizeof(szBuffer));
		}

		//4.3 Ŭ���̾�Ʈ�� ������ ������.
		::shutdown(hClient, SD_BOTH);
		::closesocket(hClient);
		puts("Ŭ���̾�Ʈ ������ ������ϴ�."); fflush(stdout);
	}

	//5. ���� ���� �ݱ�
	::closesocket(hSocket);

	//������ ����
	::WSACleanup();
	return 0;
}
