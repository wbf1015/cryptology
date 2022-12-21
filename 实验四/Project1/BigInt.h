#pragma once
#include<iostream>
#include<vector>
#include<ctime>
#include <windows.h>
using namespace std;
char Int2Hex(int i1, int i2, int i3, int i4) {
	if (i1 == 0 && i2 == 0 && i3 == 0 && i4 == 0) { return '0'; }
	if (i1 == 0 && i2 == 0 && i3 == 0 && i4 == 1) { return '1'; }
	if (i1 == 0 && i2 == 0 && i3 == 1 && i4 == 0) { return '2'; }
	if (i1 == 0 && i2 == 0 && i3 == 1 && i4 == 1) { return '3'; }
	if (i1 == 0 && i2 == 1 && i3 == 0 && i4 == 0) { return '4'; }
	if (i1 == 0 && i2 == 1 && i3 == 0 && i4 == 1) { return '5'; }
	if (i1 == 0 && i2 == 1 && i3 == 1 && i4 == 0) { return '6'; }
	if (i1 == 0 && i2 == 1 && i3 == 1 && i4 == 1) { return '7'; }
	if (i1 == 1 && i2 == 0 && i3 == 0 && i4 == 0) { return '8'; }
	if (i1 == 1 && i2 == 0 && i3 == 0 && i4 == 1) { return '9'; }
	if (i1 == 1 && i2 == 0 && i3 == 1 && i4 == 0) { return 'A'; }
	if (i1 == 1 && i2 == 0 && i3 == 1 && i4 == 1) { return 'B'; }
	if (i1 == 1 && i2 == 1 && i3 == 0 && i4 == 0) { return 'C'; }
	if (i1 == 1 && i2 == 1 && i3 == 0 && i4 == 1) { return 'D'; }
	if (i1 == 1 && i2 == 1 && i3 == 1 && i4 == 0) { return 'E'; }
	if (i1 == 1 && i2 == 1 && i3 == 1 && i4 == 1) { return 'F'; }
}
class BigInt {
public:
	//类内属性
	vector<int>num;//用来存储真正的数,在这里我们默认0是最高位
	bool isSpecial = false;//再做运算时用来判定运算是否合法

	//重载运算符
	friend BigInt operator+(const BigInt& a, const BigInt& b);
	friend BigInt operator-(const BigInt& a, const BigInt& b);
	friend BigInt operator*(const BigInt& a, const BigInt& b);
	friend BigInt operator/(const BigInt& a, const BigInt& b);
	friend BigInt operator%(const BigInt& a, const BigInt& b);
	friend bool operator==(const BigInt& a, const BigInt& b);
	friend bool operator>=(const BigInt& a, const BigInt& b);
	friend bool operator<(const BigInt& a, const BigInt& b) {
		bool ret = a >= b;
		return !ret;
	}


	//其他功能性函数
	BigInt();
	BigInt(int size);
	BigInt(int size, vector<int>& v);
	BigInt(const BigInt& bi);
	bool isLegal();//判断vector中的数是否合法
	bool strictLegal();//判断长度、数字是否合法
	void generateNum(int size);//随机生成一个数
	void generateOdd(int size);
	void randGenerate(BigInt& n);
};

//重载输出运算符
ostream& operator<<(ostream& out, BigInt& a) {
	if (a.num.size() == 0) {
		out << "0";
		return out;
	}
	BigInt t(a);
	//因为要加零的话其实要在前面补零，所以先reverse一下
	reverse(t.num.begin(), t.num.end());
	//让他们对4对齐
	int diff = t.num.size() % 4;
	if (diff != 0) {
		for (int i = 1; i <= 4 - diff; i++) {
			t.num.push_back(0);
		}
	}
	reverse(t.num.begin(), t.num.end());
	//挨个转换为16进制
	vector<char>vc;
	for (int i = 0; i < t.num.size(); i += 4) {
		vc.push_back(Int2Hex(t.num[i], t.num[i + 1], t.num[i + 2], t.num[i + 3]));
	}
	//输出，并进行格式控制
	for (int i = 0; i < vc.size(); i++) {
		out << vc[i];
		if (i + 1 % 4 == 0) { out << " "; }
	}
	return out;
}

vector<int> AddZero(int num, const vector<int>& v) {
	vector<int>vv(v);
	for (int i = 1; i <= num; i++) {
		vv.push_back(0);
	}
	return vv;
}

BigInt OpBIgInt(const BigInt& bi) {
	BigInt t(bi);
	for (int i = 0; i < t.num.size(); i++) {
		if (t.num[i] == 0) { t.num[i] = 1; }
		else { t.num[i] = 0; }
	}
	return t;
}

BigInt::BigInt() {
	//相当于默认初始化为0
	num.push_back(0);
}

BigInt::BigInt(int size) {
	//自动生成
	for (int i = 1; i <=size; i++) {
		num.push_back(0);
	}
}

BigInt::BigInt(int size, vector<int>& v) {
	for (int i = 0; i < size; i++) {
		num.push_back(v[i]);
	}
}

BigInt::BigInt(const BigInt& bi) {
	for (int i = 0; i < bi.num.size(); i++) {
		num.push_back(bi.num[i]);
	}
}

bool BigInt::isLegal() {
	for (int i = 0; i < num.size();i++) {
		if (num[i] != 0 && num[i] != 1)return false;
	}
	return true;
 }

bool BigInt::strictLegal() {
	if (num[0] == 0 && isLegal())return true;
	return false;
}

void BigInt::generateNum(int size) {
	srand((int)time(NULL));
	for (int i = 0; i < size; i++) {
		num[i] = rand() % 2;
	}
	//这样才能确保他的位数
	num[0] = 1;
}

void BigInt::generateOdd(int size) {
	generateNum(size);
	if (num[size - 1] == 0) {
		num[size - 1] = 1;
	}
}

BigInt operator+(const BigInt& a, const BigInt& b) {
	BigInt t(max(a.num.size(), b.num.size()) + 1);//在这里先多开一位
	int jw = 0;//进位
	for (int i = 1; i <= t.num.size(); i++) {
		int bit = 0;
		if (a.num.size()>=i && b.num.size()>=i) {
			//如果现在a有数b也有数
			int k = b.num.size() - i;
			if (a.num[a.num.size() - i] == 1 && b.num[b.num.size() - i] == 1 && jw == 1) { jw = 1; bit = 1; t.num[t.num.size() - i] = bit; continue; }
			if (a.num[a.num.size() - i] == 1 && b.num[b.num.size() - i] == 1 && jw == 0) { jw = 1; bit = 0; t.num[t.num.size() - i] = bit; continue; }
			if (a.num[a.num.size() - i] == 1 && b.num[b.num.size() - i] == 0 && jw == 1) { jw = 1; bit = 0; t.num[t.num.size() - i] = bit; continue; }
			if (a.num[a.num.size() - i] == 1 && b.num[b.num.size() - i] == 0 && jw == 0) { jw = 0; bit = 1; t.num[t.num.size() - i] = bit; continue; }
			if (a.num[a.num.size() - i] == 0 && b.num[b.num.size() - i] == 1 && jw == 1) { jw = 1; bit = 0; t.num[t.num.size() - i] = bit; continue; }
			if (a.num[a.num.size() - i] == 0 && b.num[b.num.size() - i] == 1 && jw == 0) { jw = 0; bit = 1; t.num[t.num.size() - i] = bit; continue; }
			if (a.num[a.num.size() - i] == 0 && b.num[b.num.size() - i] == 0 && jw == 1) { jw = 0; bit = 1; t.num[t.num.size() - i] = bit; continue; }
			if (a.num[a.num.size() - i] == 0 && b.num[b.num.size() - i] == 0 && jw == 0) { jw = 0; bit = 0; t.num[t.num.size() - i] = bit; continue; }
		}
		else {
			if (a.num.size()<i && b.num.size()>=i) {
				//如果a没有数了
				if (b.num[b.num.size() - i] == 1 && jw == 1) { jw = 1; bit = 0; t.num[t.num.size() - i] = bit; continue; }
				if (b.num[b.num.size() - i] == 1 && jw == 0) { jw = 0; bit = 1; t.num[t.num.size() - i] = bit; continue; }
				if (b.num[b.num.size() - i] == 0 && jw == 1) { jw = 0; bit = 1; t.num[t.num.size() - i] = bit; continue; }
				if (b.num[b.num.size() - i] == 0 && jw == 0) { jw = 0; bit = 0; t.num[t.num.size() - i] = bit; continue; }
			}
			if (b.num.size()<i && a.num.size()>=i) {
				//如果b没有数了
				if (a.num[a.num.size() - i] == 1 && jw == 1) { jw = 1; bit = 0; t.num[t.num.size() - i] = bit; continue; }
				if (a.num[a.num.size() - i] == 1 && jw == 0) { jw = 0; bit = 1; t.num[t.num.size() - i] = bit; continue; }
				if (a.num[a.num.size() - i] == 0 && jw == 1) { jw = 0; bit = 1; t.num[t.num.size() - i] = bit; continue; }
				if (a.num[a.num.size() - i] == 0 && jw == 0) { jw = 0; bit = 0; t.num[t.num.size() - i] = bit; continue; }
			}
			//如果到了这里说明是到了第一位了
			t.num[t.num.size() - i] = jw;
			continue;
		}
	}
	//消除空首零
	if (t.num[0] == 0) {
		reverse(t.num.begin(), t.num.end());
		t.num.pop_back();
		reverse(t.num.begin(), t.num.end());
	}
	return t;
}

BigInt operator-(const BigInt& a, const BigInt& b) {
	BigInt bi(b);
	if (a >= b) {
		if (a.num.size() > b.num.size()) {
			reverse(bi.num.begin(), bi.num.end());
			for (int i = 1; i <= a.num.size() - b.num.size(); i++) {
				bi.num.push_back(0);
			}
			reverse(bi.num.begin(), bi.num.end());
		}
		//完成反码相加
		BigInt Rb = OpBIgInt(bi);
		bi = a + Rb;
		//完成+1
		vector<int>vi; vi.push_back(1);
		BigInt t(1, vi);
		bi = bi + t;
		//这个时候还需要判断，如果得到的结果的size变大了肯定是错误的
		if (bi.num.size() > a.num.size()) {
			reverse(bi.num.begin(), bi.num.end());
			bi.num.pop_back();
			reverse(bi.num.begin(), bi.num.end());
		}
		//去掉无用的前导零
		vector<int>vii;
		int start = false;
		for (int i = 0; i < bi.num.size(); i++) {
			if (bi.num[i] == 1) { start = true; vii.push_back(bi.num[i]); }
			else {
				if (start) { vii.push_back(bi.num[i]); }
			}
		}
		int s = vii.size();
		if (vii.empty()) { vii.push_back(0); }
		BigInt ret(s, vii);
		return ret;
	}
	else {
		cout << "非法的减法" << endl;
		//待增加标志
		bi.num.clear();
		return bi;
	}
}

BigInt operator*(const BigInt& a, const BigInt& b) {
	BigInt Myb(b);
	reverse(Myb.num.begin(), Myb.num.end());
	BigInt ret;//默认初始化为0
	for (int i = 0; i < Myb.num.size(); i++) {
		if (Myb.num[i] == 1) {//为1才有意义
			//添加零
			vector<int>v = AddZero(i, a.num);
			//拿着向量新初始化一个BigInt
			BigInt b(v.size(), v);
			//加到ret上
			ret = ret + b;
		}
	}
	return ret;
}

BigInt operator/(const BigInt& a, const BigInt& b) {
	if (a < b) {
		cout << "非法的乘法，被除数小于除数" << endl;
		BigInt bi;
		return bi;
	}
	BigInt Mya(a);
	vector<int>vi;//存储结果的地方
	for (int i = 0; i < a.num.size(); i++) {
		BigInt myb = b;
		for (int j = 1; j <= ((a.num.size() - 1) - i); j++) {
			myb.num.push_back(0);
		}
		//cout << i << " ";
		//cout << Mya<<" "<< myb << endl;
		if (Mya >= myb) {
			vi.push_back(1);
			Mya = Mya - myb;
			continue;
		}
		if (Mya < myb) {
			vi.push_back(0);
			continue;
		}
		//cout << Mya << " " << myb << " " << vi[i]<<endl;
	}
	//cout << endl;
	//去除前导零
	reverse(vi.begin(), vi.end());
	for (int i = vi.size() - 1; i >= 0; i--) {
		if (vi[vi.size() - 1] == 0) { vi.pop_back(); }
		else { break; }
	}
	reverse(vi.begin(), vi.end());
	BigInt ret(vi.size(), vi);
	return ret;
}

BigInt operator%(const BigInt& a, const BigInt& b) {
	if (a < b) {
		return a;
	}
	BigInt Mya(a);
	vector<int>vi;//存储结果的地方
	for (int i = 0; i < a.num.size(); i++) {
		BigInt myb = b;
		for (int j = 1; j <= ((a.num.size() - 1) - i); j++) {
			myb.num.push_back(0);
		}
		//cout << i << " ";
		//cout << Mya<<" "<< myb << endl;
		if (Mya >= myb) {
			vi.push_back(1);
			Mya = Mya - myb;
			continue;
		}
		if (Mya < myb) {
			vi.push_back(0);
			continue;
		}
		//cout << Mya << " " << myb << " " << vi[i]<<endl;
	}
	return Mya;
}

bool operator>=(const BigInt& a, const BigInt& b) {
	//假设我们认为a和b都是严格合法的
	if (a.num.size() > b.num.size()) { return true; }
	if (a.num.size() < b.num.size()) { return false; }
	for (int i = 0; i < a.num.size();i++) {
		if (a.num[i] > b.num[i]) { return true; }
		if (a.num[i] < b.num[i]) { return false; }
	}
	return true;
}

bool operator==(const BigInt& a, const BigInt& b) {
	if (a.num.size() != b.num.size()) { return false; }
	else {
		for (int i = 0; i < a.num.size(); i++) {
			if (a.num[i] != b.num[i]) { return false; }
		}
	}
	return true;
}

void BigInt::randGenerate(BigInt& n){
	//范围是2到n-2
	vector<int>vi; vi.push_back(1); vi.push_back(0);
	BigInt TWO(2, vi);
	BigInt end = n - TWO;
	//size不会比n的size大
	int size;
	while (true) {
		size = rand() % (n.num.size()+1);
		if (size > 0&&size!=1) { break; }
	}
L:
	BigInt ret(size);
	ret.generateNum(size);
	if (end < ret) { goto L; }
	num.clear();
	for (int i = 0; i < size; i++) {
		num.push_back(ret.num[i]);
	}
}

BigInt pow(BigInt& a, BigInt& b,BigInt& m) {
	vector<int>vi;
	vi.push_back(1);
	BigInt ONE(1, vi);
	BigInt Myb(b);
	BigInt Mya(a);
	Myb = Myb - ONE;
	if (Myb.num.size() == 0) { Mya = Mya % m; return Mya; }
	while (true) {
		if (Myb.num.size() != 0) {
			Mya = Mya * a;
			Mya = Mya % m;
			Myb = Myb - ONE;
		}
		else {
			break;
		}
	}
	return Mya;
}



bool Miller_Rabin(BigInt b,int k) {
	if (b.num[b.num.size() - 1] == 0) { return false; }
	int s=0;//这是2的整数次幂的表示
	BigInt myb(b);
	BigInt t;//另外一部分
	BigInt r;//每一轮迭代都要用到的
	//构造一个代表2的BigInt数
	vector<int>vi; vi.push_back(1); vi.push_back(0);
	BigInt TWO(2, vi);
	vector<int>vi2; vi2.push_back(1);
	BigInt ONE(1, vi2);
	myb = myb - ONE;
	//首先需要确定s和t
	while (true) {
		BigInt bi;
		bi = myb % TWO;
		if (bi.num.size() == 0) {
			s++;
			myb = myb / TWO;
			continue;
		}
		else {
			t = myb;
			break;
		}
	}
	//cout << "s= " << s << "  " << "t= " << t << endl;
	for (int j = 1; j <= k; j++) {
		BigInt bb;
		Sleep(1000);
		bb.randGenerate(b);
		cout << "bb= " << bb << endl;
		for (int i = 0; i < s; i++) {
			if (i == 0) {
				r = pow(bb, t, b);
				if (r == ONE) { break; }
				BigInt check = b - ONE;
				if (r == check) { break; }
				if(s==1){ cout << "fail to pass Miller_Rabin" << endl; return false; }
				continue;
			}
			else {
				r = pow(r, TWO, b);
				BigInt check = b - ONE;
				if (r == check) { break; }
				if (i == s - 1) { cout << "fail to pass Miller_Rabin"<<endl; return false; }
				continue;
			}
		}
	}
	cout << "pass Miller_Rabin successfully" << endl;
	return true;
}