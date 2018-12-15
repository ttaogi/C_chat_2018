#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<WinSock2.h>
#include<Windows.h>
#pragma warning(disable: 4996) 
#pragma comment(lib, "Ws2_32.lib")

#define SERVER_PORT 48700
#define CLIENT_PORT 46800
#define LISTEN_NUM 5
#define BUFF_SIZE 4096

DWORD WINAPI server(LPVOID lpParam) {
	WSADATA wsaData;
	SOCKET servSock, clntSock;
	SOCKADDR_IN servAddr, clntAddr;
	char buf[BUFF_SIZE];
	int len;

	int szClntAddr;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		printf("WSAStartup() error.\n");

	servSock = socket(PF_INET, SOCK_STREAM, 0);
	if (servSock == INVALID_SOCKET)
		printf("socket() error.\n");

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = SERVER_PORT;

	if (bind(servSock, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
		printf("bind() error.\n");

	if (listen(servSock, LISTEN_NUM) == SOCKET_ERROR)
		printf("listen() error.\n");

	szClntAddr = sizeof(clntAddr);
	clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &szClntAddr);

	while (1) {

		len = recv(clntSock, buf, BUFF_SIZE - 1, 0);

		if(len != -1)
			printf("%s\n", buf);

		if (strcmp(buf, "/quit") == 0) {
			printf("terminate chatting.\n");
			break;
		}
	}

	closesocket(servSock);
	closesocket(clntSock);
	WSACleanup();

	return 0;
}

int main(void) {
	DWORD servThId = 1;
	DWORD servThParam = 1;

	HANDLE servTh = CreateThread(NULL, 0, server, &servThParam, 0, &servThId);

	if (servTh == NULL)
		printf("server thread creation failed.\n");
	else
		printf("server thread ID : %d\n", servThId);

	while (1) {}

	return 0;
}






























