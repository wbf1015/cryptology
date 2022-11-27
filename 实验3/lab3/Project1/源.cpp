#include<iostream>
#include<cmath>
#include<vector>
#include<string>
using namespace std;
string mx = "100011011";
//二进制自增
string StringInc(string a) {
	char jw = '0';
	int la = a.length();
	for (int i = la - 1; i >= 0; i--) {
		if (i == la - 1) {
			if (a[i] == '0') { a[i] = '1'; }
			else { a[i] = '0'; jw = '1'; }
			continue;
		}
		else {
			if (a[i] == '0' && jw == '0') { a[i] = '0'; jw = '0';}
			if (a[i] == '0' && jw == '1') { a[i] = '1'; jw = '0'; }
			if (a[i] == '1' && jw == '0') { a[i] = '1'; jw = '0'; }
			if (a[i] == '1' && jw == '1') { a[i] = '0'; jw = '1'; }
		}
	}
	if (jw == '1') {
		string s = "1" + a;
		return s;
	}
	return a;
}
//从string提取对应的int
int String2Intb(string s) {
	int r = 0;
	if (s.length() == 8) {
		for (int i = 0; i < 8; i++) {
			int temp;
			if (s[i] == '0') { temp = 0; }
			else { temp = 1; }
			r += temp * pow(2, 7 - i);
		}
	}
	return r;
}
char CharAddb(char a, char b) {
	if (a == '0' && b == '0') { return '0'; }
	if (a == '0' && b == '1') { return '1'; }
	if (a == '1' && b == '0') { return '1'; }
	if (a == '1' && b == '1') { return '0'; }
}
//做伽罗瓦域上的加法
string StringAddb(string a, string b) {
	int la = a.length();//拿到a的长度
	int lb = b.length();//拿到b的长度
	int l;
	vector<char>ls;//代表长的string的vector
	vector<char>ss;//代表段的string的vector
	vector<char>rs;//结果字符串
	if (la >= lb) {//a是更长的
		for (int i = la - 1; i >= 0; i--) {
			ls.push_back(a[i]);
		}
		for (int i = lb - 1; i >= 0; i--) {
			ss.push_back(b[i]);
		}
		l = la;
	}
	else {
		for (int i = la - 1; i >= 0; i--) {
			ss.push_back(a[i]);
		}
		for (int i = lb - 1; i >= 0; i--) {
			ls.push_back(b[i]);
		}
		l = lb;
	}
	for (int i = 0; i <= ls.size()-1; i++) {
		if (i <= ss.size() - 1) {
			if (ls[i] == ss[i]) { rs.push_back('0'); }
			else { rs.push_back('1'); }
		}
		else {
			rs.push_back(ls[i]);
			}
	}
	string s="";
	int lr = rs.size();
	for (int i = lr - 1; i >= 0; i--) {
		string temp(1, rs[i]);
		s.append(temp);
	}
	return s;
}
//相当于做取模运算
string StringModb(string a) {
	string temp = a;
	int la = temp.length();
	for (int i = 0; i <= la - 9; i++) {
		if (temp[i] == '1') {
			for (int j = 0; j <= 8; j++) {
				temp[i + j] = CharAddb(temp[i + j], mx[j]);
			}
		}
	}
	string rs = "";
	for (int i = la - 1 - 7; i <= la-1; i++) {
		string t(1, temp[i]);
		rs.append(t);
	}
	return rs;
}
//伽罗瓦域上的乘法运算
string mulGF(string a, string b) {
	if (a == "00000000" || b == "00000000") {
		return "00000000";
	}
	string temp = a;
	int lb = b.length();
	string front="";
	string back="";
	for (int i = lb - 1; i >= 0; i--) {
		if (b[i] == '1') {
			if (front == "") {
				string t = a;
				for (int j = 1; j <= (lb - 1) - i; j++) {
					t.append("0");
				}
				front = t;
				continue;
			}
			else {
				string t = a;
				for (int j = 1; j <= (lb - 1) - i; j++) {
					t.append("0");
				}
				back = t;
				//cout << front << "  " << back << endl;
				front = StringAddb(front, back);
				//cout << front << endl;
				continue;
			}
		}
	}
	//cout << front << endl;
	temp = StringModb(front);
	return temp;
}
string reverseGF(string a) {
	string s = "00000000";
	for (int i = 1; i <= 256; i++) {;
		if (mulGF(a, s) == "00000001") {
			return s;
		}
		else {
			s = StringInc(s);
		}
	}
	return s;
}

int main() {
	string s1 = "00011011";
	string s2 = "00101101";
	//cout << mulGF(s1, s2)<<endl;
	string s3 = "01010111";
	cout << reverseGF(s3);
}