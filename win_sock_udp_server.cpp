/*This program create communications between server and client based on udp protocols*/
/*server.cpp*/
#include<WinSock2.h>
#include<stdio.h>

#pragma comment(lib,"ws2_32.lib")

/*UDP Server*/
void main()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested=MAKEWORD(2,2);

	err=WSAStartup(wVersionRequested,&wsaData);
	if(err!=0)
		return ;

	if(LOBYTE(wsaData.wVersion)!=2||
		HIBYTE(wsaData.wVersion)!=2)
	{
		WSACleanup();
		return ;
	}
	SOCKET sockSrv=socket(AF_INET,SOCK_DGRAM,0);
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr=htonl(INADDR_ANY);
	addrSrv.sin_family=AF_INET;
	addrSrv.sin_port=htons(6000);

	bind(sockSrv,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));

	char recvBuf[100];
	char sendBuf[100];
	char tempBuf[200];

	SOCKADDR_IN addrClient;
	int len=sizeof(SOCKADDR);

	while(1)
	{
		recvfrom(sockSrv,recvBuf,100,0,(SOCKADDR*)&addrClient,&len);
		if('q'==recvBuf[0])
		{
			sendto(sockSrv,"q",strlen("q")+1,0,(SOCKADDR*)&addrClient,len);
			printf("chat end\n");
			break;
		}
		sprintf(tempBuf,"%s say: %s",inet_ntoa(addrClient.sin_addr),recvBuf);
		printf("%s\n",tempBuf);
		printf("Please input data:\n");
		gets(sendBuf);
		sendto(sockSrv,sendBuf,strlen(sendBuf)+1,0,(SOCKADDR*)&addrClient,len);
	}
	closesocket(sockSrv);
	WSACleanup();
}
