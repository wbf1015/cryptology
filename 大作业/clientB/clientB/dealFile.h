#pragma once
#include<fstream>  //ifstream
#include<iostream>
#include<string>     //包含getline()
//#include<cmath>
using namespace std;
string Dec2Hex(int n) {
	string s;
	string t = "0123456789ABCDEF";
	int x;
	while (n != 0) {
		x = n % 16;
		// 将 n % 16 转换为字符逆序存入 s 
		s = t[x] + s;
		n = n / 16;
	}

	if (s == "") {
		cout << "错误的十进制转16进制输入" << endl;
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
		cout << "16进制翻译错误" << endl;
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
string readFile() {
	cout << "请输入要读入的文件" << endl;
	cout << "要输入的文件内容请不要包含中文及中文符号" << endl;
	string path;
	cin >> path;
	ifstream infile(path, ios::in);
	if (!infile) {//文件没打开
		cerr << "出错啦~这个文件出错啦！";
	}
	string ret;
	string s;//我创建的变量，存储数据用的
	while (infile >> s) {//输入文件流
		//cout << s;
		ret.append(s);
		ret.push_back('\n');
	}

	ret = Text2Hex(ret);
	return ret;
}
void WriteFile(string s) {
	ofstream OutFile("Message_from_client_A.txt"); //利用构造函数创建txt文本，并且打开该文本
	s = Hex2Char2(s);
	OutFile << s; //把字符串内容"This is a Test!"，写入Test.txt文件
	OutFile.close(); //关闭Test.txt文件
}