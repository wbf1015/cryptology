#pragma once
#include<fstream>  //ifstream
#include<iostream>
#include<string>     //����getline()
//#include<cmath>
using namespace std;
string Dec2Hex(int n) {
    string s;
    string t = "0123456789ABCDEF";
    int x;
    while (n != 0) {
        x = n % 16;
        // �� n % 16 ת��Ϊ�ַ�������� s 
        s = t[x] + s;
        n = n / 16;
    }

    if (s == "") {
        cout << "�����ʮ����ת16��������" << endl;
        return s;
    }
    else {
        if (s.size() == 1) {
            s.push_back('0');
            reverse(s.begin(), s.end());
        }
        return s;
    }
}
string Text2Hex(string s) {
    string ret;
    for (int i = 0; i < s.size(); i++) {
        int t = s[i];
        string ss = Dec2Hex(t);
        ret.append(ss);
    }
    return ret;
}
int Char2Dec2(char a, char b) {
	int ret = 0;
	if (a == '0') { ret += 0 * 16; }
	if (a == '1') { ret += 1 * 16; }
	if (a == '2') { ret += 2 * 16; }
	if (a == '3') { ret += 3 * 16; }
	if (a == '4') { ret += 4 * 16; }
	if (a == '5') { ret += 5 * 16; }
	if (a == '6') { ret += 6 * 16; }
	if (a == '7') { ret += 7 * 16; }
	if (a == '8') { ret += 8 * 16; }
	if (b == '0') { ret += 0; }
	if (b == '1') { ret += 1; }
	if (b == '2') { ret += 2; }
	if (b == '3') { ret += 3; }
	if (b == '4') { ret += 4; }
	if (b == '5') { ret += 5; }
	if (b == '6') { ret += 6; }
	if (b == '7') { ret += 7; }
	if (b == '8') { ret += 8; }
	if (b == '9') { ret += 9; }
	if (b == 'a' || b == 'A') { ret += 10; }
	if (b == 'b' || b == 'B') { ret += 11; }
	if (b == 'c' || b == 'C') { ret += 12; }
	if (b == 'd' || b == 'D') { ret += 13; }
	if (b == 'e' || b == 'E') { ret += 14; }
	if (b == 'f' || b == 'F') { ret += 15; }
	return ret;
}
string Hex2Char2(string s) {
	if (s.size() % 2 == 1) {
		cout << "16���Ʒ������" << endl;
		return "";
	}
	string ret;
	for (int i = 0; i < s.size(); i = i + 2) {
		int temp = Char2Dec2(s[i], s[i + 1]);
		//cout << temp << endl;
		ret.push_back((char)temp);
	}
	return ret;
}
string myGetTime() {
	SYSTEMTIME t;
	GetLocalTime(&t);
	string ret;
	string s;
	s = "                                      ********������ϢΪ";
	ret.append(s);
	ret.append(std::to_string(t.wYear)); ret.append("��");
	ret.append(std::to_string(t.wMonth)); ret.append("��");
	ret.append(std::to_string(t.wDay)); ret.append("��");
	ret.append(std::to_string(t.wHour)); ret.append("ʱ");
	ret.append(std::to_string(t.wMinute)); ret.append("��");
	ret.append(std::to_string(t.wSecond)); ret.append("��");
	ret.append("���ܵ�����Ϣ********\n");
	return ret;
}
string readFile() {
	cout << "                       ***********************************************************************" << endl;
	cout << "                       *           ������Ҫ������ļ�·������������λ��test.txt              *" << endl;
	cout << "                       *              �뱣֤Ҫ������ļ�����С��8000���ַ�                   *" << endl;
	cout << "                       *   ��Ҫ������ļ������Լ��ļ�·���벻Ҫ�������ģ��⽫�ᵼ�¶���ʧ��  *" << endl;
	cout << "                       ***********************************************************************" << endl;
	string path;
	cin >> path;
	ifstream infile(path, ios::in);
	if (!infile) {//�ļ�û��
		cerr<<"[TIPS] ���ļ������ڣ������¼��·��"<<endl;
	}
	string ret;
	string s;//�Ҵ����ı������洢�����õ�
	while (infile >> s) {//�����ļ���
		//cout << s;
		ret.append(s);
		ret.push_back('\n');
	}
	cout << "[TIPS] �ļ�" << path << "�ɹ���ȡ" << endl;
	cout << "[TIPS] �ļ���СΪ" << s.size() << "bytes" << endl;
    ret =  Text2Hex(ret);
	return ret;
}
void WriteFile(string s) {
	ofstream OutFile("Message_from_client_B.txt",ios::app); //���ù��캯������txt�ı������Ҵ򿪸��ı�
	s = Hex2Char2(s);
	OutFile << myGetTime();
	OutFile <<s; //���ַ�������"This is a Test!"��д��Test.txt�ļ�
	OutFile.close(); //�ر�Test.txt�ļ�
	cout << "[TIPS] �ļ�" << "Message_from_client_B.txt" << "�ɹ���ȡ" << endl;
	cout << "[TIPS] �ļ���СΪ" << s.size() << "bytes" << endl;
	cout << "                       ***********************************************************************" << endl;
	cout << "                       *                  �ļ���д��Message_from_client_B.txt                *" << endl;
	cout << "                       *     ���ļ��д������룬���ܶԷ��������ļ��������ģ���ͶԷ���ϵȷ��  *" << endl;
	cout << "                       ***********************************************************************" << endl;
}