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

DWORD WINAPI client(LPVOID lpParam) {
	WSADATA wsaData;
	SOCKET clntSock;
	SOCKADDR_IN servAddr;
	char addr[20] = "127.0.0.1";
	char buf[BUFF_SIZE];

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		printf("WSAStartup() error.\n");

	clntSock = socket(PF_INET, SOCK_STREAM, 0);
	if (clntSock == INVALID_SOCKET)
		printf("socket() error.\n");

	printf("input server address : ");
	scanf("%s", addr);

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr(addr);
	servAddr.sin_port = SERVER_PORT;

	if (connect(clntSock, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR) {
		printf("connect() error.\n");
		return;
	}

	while (1) {
		memset(buf, 0, BUFF_SIZE);
		printf("Input msg : ");
		//scanf("%s", buf);
		fgets(buf, BUFF_SIZE - 1, stdin);
		buf[strlen(buf) - 1] = '\0';
		send(clntSock, buf, strlen(buf) + 1, 0);

		if (strcmp(buf, "/quit") == 0){
			printf("/quit command is inputted.\n");
			break;
		}
	}

	closesocket(clntSock);
	WSACleanup();

	return 0;
}

int main(void) {
	DWORD clntThId = 1;
	DWORD clntThParam = 1;

	HANDLE clntTh = CreateThread(NULL, 0, client, &clntThParam, 0, &clntThId);

	if (clntTh == NULL)
		printf("client thread creation failed.\n");
	else
		printf("client thread ID : %d\n", clntThId);
	

	while (1) {}

	return 0;
}















