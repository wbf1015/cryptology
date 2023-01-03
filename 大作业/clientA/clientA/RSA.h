#pragma once
#include<iostream>
#include<cmath>
#include"BigInt.h"
using namespace std;
//拥有自己的公钥和私钥
string public_key_A_e = "54263422DFBAF";
string public_key_A_n = "C43A65A1709716BF546EA372F31D599271";
string private_key_A_d = "82F2440BD23BC259A9703055207884719F";
//拥有对方的公钥
string public_key_B_e="789642123F";
string public_key_B_n="84EC656BD4E444F7B2BC70F783D52119C9";
void testPow() {
	BigInt bignum(1024);
	bignum.generateNum(1024);
	for (int i = 0; i <= 10; i++) {
		BigInt bi(3);
		bi.generateNum(3);
		Sleep(1000);
		BigInt bi2(3);
		bi2.generateNum(3);
		BigInt bi3 = MyquickPow(bi, bi2, bignum);
		cout << bi << " ^ " << bi2 << " = " << bi3 << endl;
		Sleep(1000);
		cout << bi3.num.size() << endl;

	}
}
void testMod() {
	for (int i = 0; i <= 10; i++) {
		BigInt bi(4);
		bi.generateNum(4);
		Sleep(1000);
		BigInt bi2(1);
		bi2.generateNum(1);
		BigInt bi3 = bi % bi2;
		cout << bi << " % " << bi2 << " = " << bi3 << endl;
		Sleep(1000);
		cout << bi3.num.size() << endl;
	}
}
void testMR() {
	vector<BigInt>v;
	vector<int>vi2; vi2.push_back(1); vi2.push_back(0);
	BigInt TWO(2, vi2);
	BigInt b(512);
	for (int i = 0; i <= 10; i++) {

		if (i == 0) {
			b.generateOdd(512);
		}
		else {
			b = b + TWO;
		}
		cout << b << endl;
		bool judge;
		judge = Miller_Rabin(b, 5);
		if (judge) {
			v.push_back(b);
		}
	}
	cout << "识别出的有效素数为:" << endl;
	for (int i = 0; i < v.size(); i++) {
		cout << v[i] << endl;
	}
}
void testgcd() {
	for (int i = 0; i <= 10; i++) {
		BigInt bi1(8);
		bi1.generateNum(8);
		Sleep(1000);
		BigInt bi2(4);
		bi2.generateNum(4);
		BigInt bi3 = Euqlid(bi1, bi2);
		cout << "gcd(" << bi1 << "," << bi2 << ")=" << bi3 << endl;
		Sleep(1000);
	}
}
void testexgcd() {
	vector<int>vi1; vi1.push_back(1);
	BigInt ONE(1, vi1);
	for (int i = 0; i <= 10; i++) {
		BigInt bi1(5);
		bi1.generateNum(5);
		Sleep(1000);
		BigInt bi2(3);
		bi2.generateNum(3);
		BigInt x;
		BigInt y;
		BigInt check = Euqlid(bi1, bi2);
		if (check != ONE) {
			cout << bi1 << "和" << bi2 << "不互素" << endl;
			continue;
		}
		BigInt bi3 = extendEuqlid(bi1, bi2, x, y);
		cout << "exgcd(" << bi1 << "," << bi2 << ")=" << x << " " << y << endl;
		Sleep(1000);
	}
}
void testMyexgcd() {
	vector<int>vi1; vi1.push_back(1);
	BigInt ONE(1, vi1);
	for (int i = 0; i <= 10; i++) {
		BigInt bi1(512);
		bi1.generateNum(512);
		Sleep(1000);
		BigInt bi2(128);
		bi2.generateNum(128);
		BigInt x;
		BigInt y;
		BigInt check = Euqlid(bi1, bi2);
		if (check != ONE) {
			cout << bi1 << "和" << bi2 << "不互素" << endl;
			continue;
		}
		BigInt bi3 = MyextendEuqlid(bi1, bi2);
		cout << bi1 << "*" << bi3 << "= 1 (mod" << bi2 << ")" << endl;
		Sleep(1000);
	}
}
void RSA(int i, BigInt m) {
	vector<int>vi; vi.push_back(1);
	BigInt ONE(1, vi);
	BigInt B = generatePrime(i);
	BigInt B_1 = B - ONE;
	BigInt B2 = generatePrime(i + 1);
	BigInt B2_1 = B2 - ONE;
	BigInt n = B * B2;
	BigInt fn = B_1 * B2_1;
	BigInt e = generategcd_1(fn);
	BigInt d = MyextendEuqlid(e, fn);
	if (m.num.size() >= n.num.size()) {
		cout << "错误的明文分组" << endl;
		return;
	}
	BigInt c = MyquickPow(m, e, n);
	BigInt m2 = MyquickPow(c, d, n);
	cout << "m=" << m << endl;
	cout << "c=" << c << endl;
	cout << "m2=" << m2 << endl;
}
void myRSA() {
	cout << "请选择使用的大素数的比特数" << endl;
	cout << "建议选择的位数：16、32、64、128、256、512" << endl;
	int n; cin >> n;
	if (n != 256 && n != 512) {
		if (n > 128) {
			cout << "选择的位数较大，请选择推荐的位数256或者512" << endl;
			return;
		}
		string s;
		cout << "请输入想要加密的文本文档" << endl;
		cin >> s;
		s = string2Bin(s);
		cout << s << endl;
		cout << "现在对输入文件的二进制形式进行分组" << endl;
		vector<string>vs;
		for (int i = 0; i <= s.size() / n; i++) {
			if (i * n >= s.size()) { break; }
			string ss = s.substr(i * n, n);
			vs.push_back(ss);
		}
		vector<BigInt>vbi;//最终需要加密的在这
		for (int i = 0; i < vs.size(); i++) {
			vs[i] = cleanZero(vs[i]);
			BigInt tbi = string2BigInt2(vs[i]);
			vbi.push_back(tbi);
		}
		vector<int>vi; vi.push_back(1);
		BigInt ONE(1, vi);
		BigInt B = generatePrime(n);
		BigInt B_1 = B - ONE;
		Sleep(1000);
		BigInt B2 = generatePrime(n);
		BigInt B2_1 = B2 - ONE;
		BigInt n = B * B2;
		BigInt fn = B_1 * B2_1;
		BigInt e = generategcd_1(fn);
		BigInt d = MyextendEuqlid(e, fn);
		cout << "选定的两个大素数分别是" << endl;
		cout << B << endl;
		cout << B2 << endl;
		cout << "作为公钥为" << endl;
		cout << "e=" << e << "n=" << n << endl;
		cout << "作为私钥的d为" << endl;
		cout << "d=" << d << "n=" << n << endl;
		for (int i = 0; i < vbi.size(); i++) {
			BigInt c = MyquickPow(vbi[i], e, n);
			BigInt m2 = MyquickPow(c, d, n);
			cout << "---------------------------------------------" << endl;
			cout << "待加密的内容为" << vbi[i] << endl;
			cout << "加密后的内容为" << c << endl;
			cout << "解密后的内容为" << m2 << endl;
		}
	}
	if (n == 512) {
		InitialPrime512();
		string s;
		cout << "请输入想要加密的文本文档" << endl;
		cin >> s;
		s = string2Bin(s);
		cout << "现在对输入文件的二进制形式进行分组" << endl;
		vector<string>vs;
		for (int i = 0; i <= s.size() / n; i++) {
			if (i * n >= s.size()) { break; }
			string ss = s.substr(i * n, n);
			vs.push_back(ss);
		}
		vector<BigInt>vbi;//最终需要加密的在这
		for (int i = 0; i < vs.size(); i++) {
			BigInt tbi = string2BigInt2(vs[i]);
			vbi.push_back(tbi);
		}
		vector<int>vi; vi.push_back(1);
		BigInt ONE(1, vi);
		srand((unsigned)time(NULL));
		BigInt B = Prime512[rand() % (Prime512.size())];
		BigInt B_1 = B - ONE;
		Sleep(5000);
		cout << "already busy produce Prime512" << endl;
	L:
		BigInt B2 = Prime512[rand() % (Prime512.size())];
		if (B2 == B) { goto L; }
		BigInt B2_1 = B2 - ONE;
		BigInt n = B * B2;
		BigInt fn = B_1 * B2_1;
		BigInt e = generategcd_1(fn);
		BigInt d = MyextendEuqlid(e, fn);
		cout << "选定的两个大素数分别是" << endl;
		cout << B << endl;
		cout << B2 << endl;
		cout << "作为公钥的e为" << endl;
		cout << e << endl;
		cout << "作为私钥的d为" << endl;
		cout << d << endl;
		for (int i = 0; i < vbi.size(); i++) {
			BigInt c = MyquickPow(vbi[i], e, n);
			BigInt m2 = MyquickPow(c, d, n);
			cout << "---------------------------------------------" << endl;
			cout << "待加密的内容为" << vbi[i] << endl;
			cout << "加密后的内容为" << c << endl;
			cout << "解密后的内容为" << m2 << endl;
		}
	}
	if (n == 256) {
		IntialPrime256();
		string s;
		cout << "请输入想要加密的文本文档" << endl;
		cin >> s;
		s = string2Bin(s);
		cout << "现在对输入文件的二进制形式进行分组" << endl;
		vector<string>vs;
		for (int i = 0; i <= s.size() / n; i++) {
			if (i * n >= s.size()) { break; }
			string ss = s.substr(i * n, n);
			vs.push_back(ss);
		}
		vector<BigInt>vbi;//最终需要加密的在这
		for (int i = 0; i < vs.size(); i++) {
			BigInt tbi = string2BigInt2(vs[i]);
			vbi.push_back(tbi);
		}
		vector<int>vi; vi.push_back(1);
		BigInt ONE(1, vi);
		srand((unsigned)time(NULL));
		BigInt B = Prime256[rand() % (Prime256.size())];
		BigInt B_1 = B - ONE;
		Sleep(5000);
		cout << "already busy produce Prime256" << endl;
	L2:
		BigInt B2 = Prime256[rand() % (Prime256.size())];
		if (B2 == B) { goto L2; }
		BigInt B2_1 = B2 - ONE;
		BigInt n = B * B2;
		BigInt fn = B_1 * B2_1;
		BigInt e = generategcd_1(fn);
		BigInt d = MyextendEuqlid(e, fn);
		cout << "选定的两个大素数分别是" << endl;
		cout << B << endl;
		cout << B2 << endl;
		cout << "作为公钥的e为" << endl;
		cout << e << endl;
		cout << "作为私钥的d为" << endl;
		cout << d << endl;
		for (int i = 0; i < vbi.size(); i++) {
			BigInt c = MyquickPow(vbi[i], e, n);
			BigInt m2 = MyquickPow(c, d, n);
			cout << "---------------------------------------------" << endl;
			cout << "待加密的内容为" << vbi[i] << endl;
			cout << "加密后的内容为" << c << endl;
			cout << "解密后的内容为" << m2 << endl;
		}
	}
}
int Char2Dec(char a, char b) {
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
string Hex2Char(string s) {
	if (s.size() % 2 == 1) {
		cout << "16进制翻译错误" << endl;
		return "";
	}
	string ret;
	for (int i = 0; i < s.size(); i = i + 2) {
		int temp = Char2Dec(s[i], s[i + 1]);
		//cout << temp << endl;
		ret.push_back((char)temp);
	}
	return ret;
}

//用A的私钥加密
string encrypt_A_private(string s) {
	// 传进16进制数，所以最多16位
	if (s.size() > 16) {
		cout << "错误的加密信息，请检查后重传" << endl;
		string ss;
		return ss;
	}
	string ss = string2Bin(s);
	ss = cleanZero(ss);//去掉前导零
	BigInt b = string2BigInt2(ss);

	BigInt b_d = string2BigInt(private_key_A_d);

	BigInt b_n = string2BigInt(public_key_A_n);

	BigInt res = MyquickPow(b, b_d, b_n);
	string ret = BigInt2Hex(res);
	return ret;
}

//用A的私钥解密
string decrypt_A_private(string s) {
	//直接从16进制转换为BigInt
	BigInt b = string2BigInt(s);

	BigInt b_d = string2BigInt(private_key_A_d);

	BigInt b_n = string2BigInt(public_key_A_n);

	BigInt res = MyquickPow(b, b_d, b_n);
	//cout << res << endl;
	string ret = BigInt2Hex(res);
	//cout << ret << endl;
	ret = Hex2Char(ret);
	return ret;
}


//用对方的公钥加密
string encrypt_B_public(string s) {
	if (s.size() > 16) {
		cout << "错误的加密信息，请检查后重传" << endl;
		string ss;
		return ss;
	}
	string ss = string2Bin(s);
	ss = cleanZero(ss);//去掉前导零
	BigInt b = string2BigInt2(ss);

	//cout << b << endl;

	BigInt b_d = string2BigInt(public_key_B_e);

	BigInt b_n = string2BigInt(public_key_B_n);

	BigInt res = MyquickPow(b, b_d, b_n);

	//cout << res << endl;
	string ret = BigInt2Hex(res);
	return ret;
}