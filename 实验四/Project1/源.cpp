#include<iostream>
#include<cmath>
#include"BigInt.h"
#include <windows.h>
using namespace std;
int main() {
	for (int i = 0; i <= 10; i++) {
		BigInt bi(4);
		bi.generateNum(4);
		Sleep(1000);
		BigInt bi2(2);
		bi2.generateNum(1);
		if (bi >= bi2) {
			BigInt bi3 = bi % bi2;
			cout << bi << " % " << bi2 << " = " << bi3 << endl;
			Sleep(1000);
			cout << bi3.num.size()<<endl;
		}
		else {
			i -= 1;
			continue;
		}
	}
}