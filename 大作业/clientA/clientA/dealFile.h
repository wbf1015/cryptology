#pragma once
#include<fstream>  //ifstream
#include<iostream>
#include<string>     //����getline()
//#include<cmath>
using namespace std;
string readFile() {
	cout << "������Ҫ������ļ�" << endl;
	cout << "Ҫ������ļ������벻Ҫ�������ļ����ķ���" << endl;
	string path;
	cin >> path;
	ifstream infile(path, ios::in);
	if (!infile) {//�ļ�û��
		cerr<<"������~����ļ���������";
	}
	string ret;
	string s;//�Ҵ����ı������洢�����õ�
	while (infile >> s) {//�����ļ���
		cout << s;
		ret.append(s);
		ret.push_back('\n');
	}
	return ret;
}