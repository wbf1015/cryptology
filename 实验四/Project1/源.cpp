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
	BigInt b(64);
	for (int i = 0; i <= 100; i++) {

		if (i == 0) {
			b.generateOdd(64);
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

int main() {
	testMyexgcd();




	
}