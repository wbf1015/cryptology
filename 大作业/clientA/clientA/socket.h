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
//����Ϊȫ�ֱ���
//��ʼ��dll
WSADATA wsadata;
//������������Ҫ���׽����Լ��׽�����Ҫ�󶨵ĵ�ַ
SOCKADDR_IN oppo_addr;
SOCKADDR_IN my_addr;
SOCKET mySocket;
int olen = sizeof(oppo_addr);

void initalNeeded() {
	WSAStartup(MAKEWORD(2, 2), &wsadata);
    //ָ��clintA������
    my_addr.sin_family = AF_INET;//ʹ��IPV4
    my_addr.sin_port = htons(8888);//server�Ķ˿ں�
    my_addr.sin_addr.s_addr = htonl(2130706433);//����127.0.0.1
    //ָ��clientB������
    oppo_addr.sin_family = AF_INET;//ʹ��IPV4
    oppo_addr.sin_port = htons(8887);//server�Ķ˿ں�
    oppo_addr.sin_addr.s_addr = htonl(2130706433);//����127.0.0.1

    //�󶨷����
    mySocket = socket(AF_INET, SOCK_DGRAM, 0);
    bind(mySocket, (SOCKADDR*)&my_addr, sizeof(my_addr));
}

//����һ����ܶ���
DWORD WINAPI myreceive(LPVOID p) {
    char* Recvbuffer = new char[100000];
    while (true) {
        while (recvfrom(mySocket, Recvbuffer, 100000, 0, (sockaddr*)&oppo_addr, &olen) > 0) {
            string s;
            int i = 0;
            while (Recvbuffer[i] != 0) {
                s.append(string(1, Recvbuffer[i]));
            }
            cout << "[������Ϣ]" << s << endl;
        }
    }
}

//ֻ�Ǵ���һ�����
DWORD WINAPI mysend(LPVOID p) {
    char* sendbuffer = new char[100000];
    while (true) {
        cin.getline(sendbuffer, 100000);
        sendto(mySocket, sendbuffer, 100000, 0, (sockaddr*)&oppo_addr, olen);
    }
}
