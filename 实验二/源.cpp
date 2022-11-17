#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

char message[65];//用来存储明文分组

string h2b(char c) {
    if (c >= 65 && c <= 90) {
        c += 32;
    }
    switch (c)
    {
    case '0':
        return "0000";
        break;
    case '1':
        return "0001";
        break;
    case '2':
        return "0010";
        break;
    case '3':
        return "0011";
        break;
    case '4':
        return "0100";
        break;
    case '5':
        return "0101";
        break;
    case '6':
        return "0110";
        break;
    case '7':
        return "0111";
        break;
    case '8':
        return "1000";
        break;
    case '9':
        return "1001";
        break;
    case 'a':
        return "1010";
        break;
    case 'b':
        return "1011";
        break;
    case 'c':
        return "1100";
        break;
    case 'd':
        return "1101";
        break;
    case 'e':
        return "1110";
        break;
    case 'f':
        return "1111";
        break;
    default:
        return "error";
        break;
    }

}
void printcstar(char* c,int start,int end) {
    for (int i = start; i <end; i++) {
        cout << c[i];
    }
    cout << endl;
}
int loadmessage() {
    memset(message, 0, 65);
	string path;
	cout << "请输入要读取的文件路径" << endl;
	cin >> path;
    ifstream infile;
    infile.open(path, ios::in);
    if (!infile.is_open()) {
        cout << "读取文件失败" << endl;
        return -1;
    }
    char buff[1000];
    char tempbuff[1000];
    while (infile.getline(tempbuff, 1000)) {
        cout << "正在读取...."<<endl;
        for (int i = 0; i<1000; i++) {
            if (tempbuff[i] != '\0') {
                buff[i] = tempbuff[i];
                continue;
            }
            else {
                buff[i] = '\0';
                break;
            }

        }
    }
    int count = 0;
    int i = 0;
    while (count < 8 && buff[i] != '\0') {
        if (i >= 1 && buff[i - 1] == '0' && buff[i] == 'x') {
            cout << buff[i+1] << buff[i + 2] << endl;
            string front = h2b(buff[i + 1]);
            if (front == "error") { return -1; }
            string back = h2b(buff[i + 2]);
            if (back == "error") { return -1; }
            front = front.append(back);
            cout << front << endl;
            strcpy(message + (count * 8+1), front.data());
            i += 2;
            count++;
            continue;
        }
        else {
            i += 1;
            continue;
        }
    }
}




int main() {
    loadmessage();
    printcstar(message,1,65);
}