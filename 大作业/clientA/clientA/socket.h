#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string>
#include<WinSock2.h>
#include<WS2tcpip.h>
#include<thread>
#include<map>
using namespace std;
#pragma comment(lib,"ws2_32.lib")
//以下为全局变量
//初始化dll
WSADATA wsadata;
//声明服务器需要的套接字以及套接字需要绑定的地址
SOCKADDR_IN oppo_addr;
SOCKADDR_IN my_addr;
SOCKET mySocket;
int olen = sizeof(oppo_addr);

void initalNeeded() {
	WSAStartup(MAKEWORD(2, 2), &wsadata);
    //指定clintA的性质
    my_addr.sin_family = AF_INET;//使用IPV4
    my_addr.sin_port = htons(8888);//server的端口号
    my_addr.sin_addr.s_addr = htonl(2130706433);//主机127.0.0.1
    //指定clientB的性质
    oppo_addr.sin_family = AF_INET;//使用IPV4
    oppo_addr.sin_port = htons(8887);//server的端口号
    oppo_addr.sin_addr.s_addr = htonl(2130706433);//主机127.0.0.1

    //绑定服务端
    mySocket = socket(AF_INET, SOCK_DGRAM, 0);
    bind(mySocket, (SOCKADDR*)&my_addr, sizeof(my_addr));
}

DWORD WINAPI myreceive(LPVOID p) {
    char* Recvbuffer = new char[100000];
    while (true) {
        while (recvfrom(mySocket, Recvbuffer, 100000, 0, (sockaddr*)&oppo_addr, &olen) > 0) {
            string s;
            int i = 0;
            while (Recvbuffer[i] != 0) {
                s.append(string(1, Recvbuffer[i]));
            }
            cout << "[接受消息]" << s << endl;
        }
    }
}

DWORD WINAPI mysend(LPVOID p) {
    char* sendbuffer = new char[100000];
    while (true) {
        cin.getline(sendbuffer, 100000);
        sendto(mySocket, sendbuffer, 100000, 0, (sockaddr*)&oppo_addr, olen);
    }
}
