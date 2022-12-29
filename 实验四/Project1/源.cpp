#include<iostream>
#include<cmath>
#include"BigInt.h"
using namespace std;
void testPow() {
	BigInt bignum(1024);
	bignum.generateNum(1024);
	for (int i = 0; i <= 10; i++) {
		BigInt bi(3);
		bi.generateNum(3);
		Sleep(1000);
		BigInt bi2(3);
		bi2.generateNum(3);
		BigInt bi3 = MyquickPow(bi,bi2,bignum);
		cout << bi << " ^ " << bi2 << " = " << bi3 << endl;
		Sleep(1000);
		cout << bi3.num.size()<<endl;
		
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
		cout << b<<endl;
		bool judge;
		judge=Miller_Rabin(b, 5);
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
void RSA(int i,BigInt m) {
	vector<int>vi; vi.push_back(1);
	BigInt ONE(1, vi);
	BigInt B = generatePrime(i);
	BigInt B_1 = B - ONE;
	BigInt B2 = generatePrime(i+1);
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
int main() {
	/*BigInt m(10);
	m.generateNum(10);
	RSA(16, m);*/
	//testMR();
	myRSA();
	while (true) {

	}
	
}