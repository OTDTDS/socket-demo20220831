//
// Created by JinxBIGBIG on 2022/8/3.
//client-客户端
#include <stdio.h>
#include <string.h>

/* inet_ntop() */
#include <WS2tcpip.h>
#include "client_UDP.h"


/*链接静态库*/
#pragma comment(lib,"ws2_32.lib")

int main()
{
	int32_t bitrate_cb;
	//adapt_model_input_t input;
	/*初始化套接字库*/
	WSADATA wdata;
	WORD wVersion;

	wVersion = MAKEWORD(2, 2);
	int err = WSAStartup(wVersion, &wdata);
	if (err != 0)
	{
		return err;
	}

	if (HIBYTE(wdata.wVersion) != 2 || LOBYTE(wdata.wVersion) != 2)
	{
		return -1;
	}

	/*初始化地址结构体 addrServ，其实也是服务器地址*/
	struct sockaddr_in addrServ;
	int len = sizeof(addrServ);
	//inet_pton(AF_INET, "127.0.0.1", &addrServ.sin_addr);
	addrServ.sin_addr.S_un.S_addr = inet_addr("192.168.31.57");
	addrServ.sin_family = AF_INET;//使用IPV4地址
	addrServ.sin_port = htons(9992);//端口



	/*申请监听套接字*/
	SOCKET sockClient = socket(AF_INET, SOCK_DGRAM, 0);



	char sendBuf[128];
	while (1)
	{

		memset(sendBuf, 0, sizeof(sendBuf));

		printf(sizeof(sendBuf));
		cout << "Please input word:";

		cin.getline(sendBuf, 64);
		/*返回发送回来的长度*/
		sendto(sockClient, sendBuf, sizeof(sendBuf), 0, (struct sockaddr*)&addrServ, len);

		/*接收返回回来的数据*/

		char recvBuf[128];
		memset(recvBuf, 0, 128);
		int recvlen = recvfrom(sockClient, recvBuf, 128, 0, (struct sockaddr*)&addrServ, &len);

		printf("Client receive:%s\n", recvBuf);//打印传输回来的



	}

	/*关闭套接字和套接字库*/
	closesocket(sockClient);
	WSACleanup();

	getchar();

	return 0;
}
