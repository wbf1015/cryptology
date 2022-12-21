#include<iostream>
#include<cmath>
#include"BigInt.h"
using namespace std;
int main() {
	/*BigInt bignum(1024);
	bignum.generateNum(1024);
	for (int i = 0; i <= 10; i++) {
		BigInt bi(3);
		bi.generateNum(3);
		Sleep(1000);
		BigInt bi2(3);
		bi2.generateNum(3);
		BigInt bi3 = pow(bi,bi2,bignum);
		cout << bi << " ^ " << bi2 << " = " << bi3 << endl;
		Sleep(1000);
		cout << bi3.num.size()<<endl;
		
	}*/
	for (int i = 0; i <= 10; i++) {
		BigInt b(10);
		b.generateOdd(10);
		cout << b << endl;
		Sleep(1000);
		Miller_Rabin(b, 5);
	}
	
}