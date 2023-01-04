#pragma once
#include<fstream>  //ifstream
#include<iostream>
#include<string>     //包含getline()
//#include<cmath>
using namespace std;
string readFile() {
	cout << "请输入要读入的文件" << endl;
	cout << "要输入的文件内容请不要包含中文及中文符号" << endl;
	string path;
	cin >> path;
	ifstream infile(path, ios::in);
	if (!infile) {//文件没打开
		cerr<<"出错啦~这个文件出错啦！";
	}
	string ret;
	string s;//我创建的变量，存储数据用的
	while (infile >> s) {//输入文件流
		cout << s;
		ret.append(s);
		ret.push_back('\n');
	}
	return ret;
}