#pragma once
#include<iostream>
#include<vector>
#include<ctime>
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include<map>
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
	//��������
	vector<int>num;//�����洢��������,����������Ĭ��0�����λ
	bool minus = false;//���Ӹ�����ʾ

	//���������
	friend BigInt operator+(const BigInt& a, const BigInt& b);
	friend BigInt operator-(const BigInt& a, const BigInt& b);
	friend BigInt operator*(const BigInt& a, const BigInt& b);
	friend BigInt operator/(const BigInt& a, const BigInt& b);
	friend BigInt operator%(const BigInt& a, const BigInt& b);
	//��Щ�Ƚ�Ŀǰֻ�Ƚ�num�����Ƚ�����λ
	friend bool operator==(const BigInt& a, const BigInt& b);
	friend bool operator!=(const BigInt& a, const BigInt& b) { return !(a == b); }
	friend bool operator>=(const BigInt& a, const BigInt& b);
	friend bool operator<(const BigInt& a, const BigInt& b) {
		bool ret = a >= b;
		return !ret;
	}



	//���������Ժ���
	BigInt();
	BigInt(int size, bool minus = false);
	BigInt(int size, vector<int>& v, bool minus = false);
	BigInt(const BigInt& bi);
	bool isLegal();//�ж�vector�е����Ƿ�Ϸ�
	bool strictLegal();//�жϳ��ȡ������Ƿ�Ϸ�
	void generateNum(int size);//�������һ����
	void generateOdd(int size);
	void randGenerate(BigInt& n);
	void equal(BigInt& b);
};

string BigInt2Hex(BigInt& a) {
	string s;
	if (a.num.size() == 0) {
		return s;
	}
	BigInt t(a);
	//��ΪҪ����Ļ���ʵҪ��ǰ�油�㣬������reverseһ��
	reverse(t.num.begin(), t.num.end());
	//�����Ƕ�4����
	int diff = t.num.size() % 4;
	if (diff != 0) {
		for (int i = 1; i <= 4 - diff; i++) {
			t.num.push_back(0);
		}
	}
	reverse(t.num.begin(), t.num.end());
	//����ת��Ϊ16����
	for (int i = 0; i < t.num.size(); i += 4) {
		char c = (Int2Hex(t.num[i], t.num[i + 1], t.num[i + 2], t.num[i + 3]));
		s.append(string(1, c));
	}
	return s;
}


//������������
ostream& operator<<(ostream& out, BigInt& a) {
	if (a.num.size() == 0) {
		out << "0";
		return out;
	}
	BigInt t(a);
	//��ΪҪ����Ļ���ʵҪ��ǰ�油�㣬������reverseһ��
	reverse(t.num.begin(), t.num.end());
	//�����Ƕ�4����
	int diff = t.num.size() % 4;
	if (diff != 0) {
		for (int i = 1; i <= 4 - diff; i++) {
			t.num.push_back(0);
		}
	}
	reverse(t.num.begin(), t.num.end());
	//����ת��Ϊ16����
	vector<char>vc;
	for (int i = 0; i < t.num.size(); i += 4) {
		vc.push_back(Int2Hex(t.num[i], t.num[i + 1], t.num[i + 2], t.num[i + 3]));
	}
	if (a.minus) { cout << "-"; }//���Ӹ�����ʾ
	//����������и�ʽ����
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
	//�൱��Ĭ�ϳ�ʼ��Ϊ0
	num.push_back(0);
}

BigInt::BigInt(int size, bool minus) {
	//�Զ�����
	for (int i = 1; i <= size; i++) {
		num.push_back(0);
	}
	this->minus = minus;
}

BigInt::BigInt(int size, vector<int>& v, bool minus) {
	for (int i = 0; i < size; i++) {
		num.push_back(v[i]);
	}
	this->minus = minus;
}

BigInt::BigInt(const BigInt& bi) {
	this->minus = bi.minus;//���Ӹ���
	num.clear();
	for (int i = 0; i < bi.num.size(); i++) {
		num.push_back(bi.num[i]);
	}
}

bool BigInt::isLegal() {
	for (int i = 0; i < num.size(); i++) {
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
	//��������ȷ������λ��
	num[0] = 1;
}

void BigInt::generateOdd(int size) {
	generateNum(size);
	if (num[size - 1] == 0) {
		num[size - 1] = 1;
	}
}

BigInt operator+(const BigInt& a, const BigInt& b) {
	//���Ǹ��� (-a)+(-b)=-(a+b)
	if (a.minus && b.minus) {
		BigInt Mya(a); Mya.minus = false;
		BigInt Myb(b); Myb.minus = false;
		BigInt ret = Mya + Myb;
		ret.minus = true;
		return ret;
	}
	//a�Ǹ�����b������ (-a)+b=b-a
	if (a.minus && !b.minus) {
		BigInt Mya(a); Mya.minus = false;
		BigInt Myb(b); Myb.minus = false;
		BigInt ret;
		//��ΪMyb��Mya�������������Լ��������Զ��ж��������
		ret = Myb - Mya;
		return ret;
	}
	//a�����ģ�b�Ǹ��� a+(-b)=(-b)+a
	if (!a.minus && b.minus) {
		//ֱ��ת�Ƹ����棬������ȥ����
		BigInt ret = b + a;
		return ret;
	}
	//������������
	BigInt t(max(a.num.size(), b.num.size()) + 1);//�������ȶ࿪һλ
	int jw = 0;//��λ
	for (int i = 1; i <= t.num.size(); i++) {
		int bit = 0;
		if (a.num.size() >= i && b.num.size() >= i) {
			//�������a����bҲ����
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
			if (a.num.size() < i && b.num.size() >= i) {
				//���aû������
				if (b.num[b.num.size() - i] == 1 && jw == 1) { jw = 1; bit = 0; t.num[t.num.size() - i] = bit; continue; }
				if (b.num[b.num.size() - i] == 1 && jw == 0) { jw = 0; bit = 1; t.num[t.num.size() - i] = bit; continue; }
				if (b.num[b.num.size() - i] == 0 && jw == 1) { jw = 0; bit = 1; t.num[t.num.size() - i] = bit; continue; }
				if (b.num[b.num.size() - i] == 0 && jw == 0) { jw = 0; bit = 0; t.num[t.num.size() - i] = bit; continue; }
			}
			if (b.num.size() < i && a.num.size() >= i) {
				//���bû������
				if (a.num[a.num.size() - i] == 1 && jw == 1) { jw = 1; bit = 0; t.num[t.num.size() - i] = bit; continue; }
				if (a.num[a.num.size() - i] == 1 && jw == 0) { jw = 0; bit = 1; t.num[t.num.size() - i] = bit; continue; }
				if (a.num[a.num.size() - i] == 0 && jw == 1) { jw = 0; bit = 1; t.num[t.num.size() - i] = bit; continue; }
				if (a.num[a.num.size() - i] == 0 && jw == 0) { jw = 0; bit = 0; t.num[t.num.size() - i] = bit; continue; }
			}
			//�����������˵���ǵ��˵�һλ��
			t.num[t.num.size() - i] = jw;
			continue;
		}
	}
	//����������
	if (t.num[0] == 0) {
		reverse(t.num.begin(), t.num.end());
		t.num.pop_back();
		reverse(t.num.begin(), t.num.end());
	}
	return t;
}

BigInt operator-(const BigInt& a, const BigInt& b) {
	//�������Ǹ���  (-a)-(-b)=b-a
	if (a.minus && b.minus) {
		BigInt Mya(a); Mya.minus = false;
		BigInt Myb(b); Myb.minus = false;
		//ͬ��MYb��Mya�������ģ����������Զ�ʶ���������
		BigInt ret = Myb - Mya;
		return ret;
	}
	//a�����ģ�b�Ǹ���  a-(-b)=a+b
	if (!a.minus && b.minus) {
		BigInt Mya(a); Mya.minus = false;
		BigInt Myb(b); Myb.minus = false;
		BigInt ret = Mya + Myb;
		return ret;
	}
	//a�Ǹ��ģ�b������  -a-b=-(a+b)
	if (a.minus && !b.minus) {
		BigInt Mya(a); Mya.minus = false;
		BigInt Myb(b); Myb.minus = false;
		BigInt ret = Mya + Myb;
		ret.minus = true;
		return ret;
	}
	//�������ĵ����
	BigInt bi(b);
	if (a >= b) {
		if (a.num.size() > b.num.size()) {
			reverse(bi.num.begin(), bi.num.end());
			for (int i = 1; i <= a.num.size() - b.num.size(); i++) {
				bi.num.push_back(0);
			}
			reverse(bi.num.begin(), bi.num.end());
		}
		//��ɷ������
		BigInt Rb = OpBIgInt(bi);
		bi = a + Rb;
		//���+1
		vector<int>vi; vi.push_back(1);
		BigInt t(1, vi);
		bi = bi + t;
		//���ʱ����Ҫ�жϣ�����õ��Ľ����size����˿϶��Ǵ����
		if (bi.num.size() > a.num.size()) {
			reverse(bi.num.begin(), bi.num.end());
			bi.num.pop_back();
			reverse(bi.num.begin(), bi.num.end());
		}
		//ȥ�����õ�ǰ����
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
		ret.minus = false;
		return ret;
	}
	else {
		BigInt ret = b - a;
		ret.minus = true;
		return ret;
	}
}

BigInt operator*(const BigInt& a, const BigInt& b) {
	BigInt Myb(b);
	reverse(Myb.num.begin(), Myb.num.end());
	BigInt ret;//Ĭ�ϳ�ʼ��Ϊ0
	for (int i = 0; i < Myb.num.size(); i++) {
		if (Myb.num[i] == 1) {//Ϊ1��������
			//�����
			vector<int>v = AddZero(i, a.num);
			//���������³�ʼ��һ��BigInt
			BigInt b(v.size(), v);
			//�ӵ�ret��
			ret = ret + b;
		}
	}
	if ((a.minus && b.minus) || (!a.minus && !b.minus)) { ret.minus = false; }
	else { ret.minus = true; }
	return ret;
}

BigInt operator/(const BigInt& a, const BigInt& b) {
	if (a < b) {
		//cout << "�Ƿ��ĳ�����������С�ڳ���" << endl;
		BigInt bi;
		return bi;
	}
	BigInt Mya(a);
	vector<int>vi;//�洢����ĵط�
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
	//ȥ��ǰ����
	reverse(vi.begin(), vi.end());
	for (int i = vi.size() - 1; i >= 0; i--) {
		if (vi[vi.size() - 1] == 0) { vi.pop_back(); }
		else { break; }
	}
	reverse(vi.begin(), vi.end());
	BigInt ret(vi.size(), vi);
	if ((a.minus && b.minus) || (!a.minus && !b.minus)) { ret.minus = false; }
	else { ret.minus = true; }
	return ret;
}

BigInt operator%(const BigInt& a, const BigInt& b) {
	if (a < b) {
		return a;
	}
	BigInt Mya(a);
	vector<int>vi;//�洢����ĵط�
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
	//����������Ϊa��b�����ϸ�Ϸ���
	if (a.num.size() > b.num.size()) { return true; }
	if (a.num.size() < b.num.size()) { return false; }
	for (int i = 0; i < a.num.size(); i++) {
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

void BigInt::randGenerate(BigInt& n) {
	//��Χ��2��n-2
	vector<int>vi; vi.push_back(1); vi.push_back(0);
	BigInt TWO(2, vi);
	BigInt end = n - TWO;
	//size�����n��size��
	int size;
	while (true) {
		size = rand() % (n.num.size() + 1);
		if (size > 0 && size != 1) { break; }
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

void BigInt::equal(BigInt& b) {
	this->minus = b.minus;
	this->num.clear();
	for (int i = 0; i < b.num.size(); i++) {
		this->num.push_back(b.num[i]);
	}
}

BigInt pow(BigInt& a, BigInt& b, BigInt& m) {
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
//�����洢�Ѿ�����õĽ�
//һ��Ҫע�⣬���ⲿ����quickPow֮ǰһ��Ҫ���storeһ��
BigInt quickPow(BigInt& a, BigInt& b, BigInt& m) {
	//cout << "b=" << b << endl;
	//����ʵ��Ҫ���ľ�ֻ�ǵ���
	vector<int>vi2; vi2.push_back(1); vi2.push_back(0);
	BigInt TWO(2, vi2);
	vector<int>vi1; vi1.push_back(1);
	BigInt ONE(1, vi1);
	//�����2�η�ֱ�Ӽ���
	if (b == TWO) {
		BigInt ret;
		ret = pow(a, b, m);
		return ret;
	}
	//һ�η�ֱ�ӷ���
	if (b == ONE) {
		return a;
	}
	//ż���η�
	if (b.num[b.num.size() - 1] == 0) {
		BigInt ret;
		BigInt t = b / TWO;
		BigInt Mya = (a * a) % m;
		ret = quickPow(Mya, t, m);//ת������a^2��b/2�η�
		return ret;

	}
	//�����η�
	else {
		BigInt ret;
		BigInt t = b / TWO;
		BigInt Mya = (a * a) % m;
		ret = quickPow(Mya, t, m);//ת������a^2��b/2�η�
		ret = (ret * a) % m;//��Ϊ���������Ի�Ҫ�ٳ�һ��a
		return ret;
	}
}
BigInt MyquickPow(BigInt& a, BigInt& b, BigInt& m) {
	return quickPow(a, b, m);
}

bool Miller_Rabin(BigInt b, int k) {
	if (b.num[b.num.size() - 1] == 0) { return false; }
	int s = 0;//����2���������ݵı�ʾ
	BigInt myb(b);
	BigInt t;//����һ����
	BigInt r;//ÿһ�ֵ�����Ҫ�õ���
	//����һ������2��BigInt��
	vector<int>vi; vi.push_back(1); vi.push_back(0);
	BigInt TWO(2, vi);
	vector<int>vi2; vi2.push_back(1);
	BigInt ONE(1, vi2);
	myb = myb - ONE;
	//������Ҫȷ��s��t
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
		//cout << "bb=" << bb << endl;
		for (int i = 0; i < s; i++) {
			if (i == 0) {
				r = MyquickPow(bb, t, b);
				if (r == ONE) { break; }
				BigInt check = b - ONE;
				if (r == check) { break; }
				if (s == 1) { cout << "fail to pass Miller_Rabin" << endl; return false; }
				continue;
			}
			else {
				r = MyquickPow(r, TWO, b);
				BigInt check = b - ONE;
				if (r == check) { break; }
				if (i == s - 1) { cout << "fail to pass Miller_Rabin" << endl; return false; }
				continue;
			}
		}
	}
	cout << "pass Miller_Rabin successfully" << endl;
	return true;
}

//ll exgcd(ll a, ll b, ll& x, ll& y) {
//	if (b == 0) {
//		x = 1;
//		y = 0;
//		return a;
//	}
//	ll r = exgcd(b, a % b, x, y);
//	ll temp = x;//x,y���ϻ��� 
//	x = y;
//	y = (temp - (a / b) * y);
//	return r;//r Ϊ���Լ�� 
//}

BigInt extendEuqlid(BigInt a, BigInt b, BigInt& x, BigInt& y) {
	vector<int>vi1; vi1.push_back(1);
	BigInt ONE(1, vi1);
	vector<int>vi0; vi0.push_back(0);
	BigInt ZERO(1, vi0);
	if (b.num.size() == 0) {
		x = ONE;
		y = ZERO;
		return a;
	}
	BigInt r = extendEuqlid(b, a % b, x, y);
	BigInt temp = x;
	x = y;
	y = (temp - (a / b) * y);
	return r;
}

//inline int gcd(int a, int b) {
//	int r;
//	while (b > 0) {
//		r = a % b;
//		a = b;
//		b = r;
//	}
//	return a;
//}

BigInt Euqlid(BigInt a, BigInt b) {
	BigInt r;
	while (b.num.size() > 0) {
		r = a % b;
		a = b;
		b = r;
	}
	return a;
}

//���a���㣺ax=1��mod b��Ҳ����a����b�ĳ˷���Ԫ
BigInt MyextendEuqlid(BigInt a, BigInt b) {
	BigInt x;
	BigInt y;
	extendEuqlid(a, b, x, y);
	//x�����Ľ��
	while (x.minus == true) {
		x = x + b;
	}
	return x;
}

BigInt generatePrime(int i) {
	BigInt b(i);
	b.generateOdd(i);
	vector<int>vi;
	vi.push_back(1); vi.push_back(0);
	BigInt TWO(2, vi);
	while (true) {
		if (Miller_Rabin(b, 5)) { return b; }
		else {
			b = b + TWO;
		}
	}
}
BigInt generategcd_1(BigInt& bi) {
	BigInt b(bi.num.size() / 2);
	b.generateOdd(bi.num.size() / 2);
	vector<int>vi2; vi2.push_back(1);
	BigInt ONE(1, vi2);
	while (true) {
		if (b >= bi) {
			cout << "���㻥��ֵʧ��" << endl;
			return ONE;
		}
		if (Euqlid(b, bi) == ONE) {
			return b;
		}
		else {
			b = b + ONE;
		}
	}
}

BigInt string2BigInt(string s) {
	vector<int>vi;
	for (int i = 0; i < s.size(); i++) {
		if (i == 0) {
			if (s[i] == '0') {  continue; }
			if (s[i] == '1') { vi.push_back(1); continue; }
			if (s[i] == '2') { vi.push_back(1); vi.push_back(0); continue; }
			if (s[i] == '3') { vi.push_back(1); vi.push_back(1); continue; }
			if (s[i] == '4') { vi.push_back(1); vi.push_back(0); vi.push_back(0); continue; }
			if (s[i] == '5') { vi.push_back(1); vi.push_back(0); vi.push_back(1); continue; }
			if (s[i] == '6') { vi.push_back(1); vi.push_back(1); vi.push_back(0); continue; }
			if (s[i] == '7') { vi.push_back(1); vi.push_back(1); vi.push_back(1); continue; }
			if (s[i] == '8') { vi.push_back(1); vi.push_back(0); vi.push_back(0); vi.push_back(0); continue; }
			if (s[i] == '9') { vi.push_back(1); vi.push_back(0); vi.push_back(0); vi.push_back(1); continue; }
			if (s[i] == 'A' || s[i] == 'a') { vi.push_back(1); vi.push_back(0); vi.push_back(1); vi.push_back(0); continue; }
			if (s[i] == 'B' || s[i] == 'b') { vi.push_back(1); vi.push_back(0); vi.push_back(1); vi.push_back(1); continue; }
			if (s[i] == 'C' || s[i] == 'c') { vi.push_back(1); vi.push_back(1); vi.push_back(0); vi.push_back(0); continue; }
			if (s[i] == 'D' || s[i] == 'd') { vi.push_back(1); vi.push_back(1); vi.push_back(0); vi.push_back(1); continue; }
			if (s[i] == 'E' || s[i] == 'e') { vi.push_back(1); vi.push_back(1); vi.push_back(1); vi.push_back(0); continue; }
			if (s[i] == 'F' || s[i] == 'f') { vi.push_back(1); vi.push_back(1); vi.push_back(1); vi.push_back(1); continue; }
		}
		if (s[i] == '0') { vi.push_back(0); vi.push_back(0); vi.push_back(0); vi.push_back(0); continue; }
		if (s[i] == '1') { vi.push_back(0); vi.push_back(0); vi.push_back(0); vi.push_back(1); continue; }
		if (s[i] == '2') { vi.push_back(0); vi.push_back(0); vi.push_back(1); vi.push_back(0); continue; }
		if (s[i] == '3') { vi.push_back(0); vi.push_back(0); vi.push_back(1); vi.push_back(1); continue; }
		if (s[i] == '4') { vi.push_back(0); vi.push_back(1); vi.push_back(0); vi.push_back(0); continue; }
		if (s[i] == '5') { vi.push_back(0); vi.push_back(1); vi.push_back(0); vi.push_back(1); continue; }
		if (s[i] == '6') { vi.push_back(0); vi.push_back(1); vi.push_back(1); vi.push_back(0); continue; }
		if (s[i] == '7') { vi.push_back(0); vi.push_back(1); vi.push_back(1); vi.push_back(1); continue; }
		if (s[i] == '8') { vi.push_back(1); vi.push_back(0); vi.push_back(0); vi.push_back(0); continue; }
		if (s[i] == '9') { vi.push_back(1); vi.push_back(0); vi.push_back(0); vi.push_back(1); continue; }
		if (s[i] == 'A' || s[i] == 'a') { vi.push_back(1); vi.push_back(0); vi.push_back(1); vi.push_back(0); continue; }
		if (s[i] == 'B' || s[i] == 'b') { vi.push_back(1); vi.push_back(0); vi.push_back(1); vi.push_back(1); continue; }
		if (s[i] == 'C' || s[i] == 'c') { vi.push_back(1); vi.push_back(1); vi.push_back(0); vi.push_back(0); continue; }
		if (s[i] == 'D' || s[i] == 'd') { vi.push_back(1); vi.push_back(1); vi.push_back(0); vi.push_back(1); continue; }
		if (s[i] == 'E' || s[i] == 'e') { vi.push_back(1); vi.push_back(1); vi.push_back(1); vi.push_back(0); continue; }
		if (s[i] == 'F' || s[i] == 'f') { vi.push_back(1); vi.push_back(1); vi.push_back(1); vi.push_back(1); continue; }
	}
	BigInt b(vi.size(), vi);
	return b;
}
BigInt string2BigInt2(string s) {
	vector<int>vi;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == '0') { vi.push_back(0); }
		else { vi.push_back(1); }
	}
	BigInt bi(vi.size(), vi);
	return bi;
}
string Dec2Bin(int i) {
	vector<int>vi;
	unsigned long long int myi = i;
	while (myi != 0) {
		vi.push_back(myi % 2);
		myi = myi / 2;
	}
	while (vi.size() < 8) {
		vi.push_back(0);
	}
	reverse(vi.begin(), vi.end());
	string s;
	for (int i = 0; i < vi.size(); i++) {
		if (vi[i] == 0) { s.append(string(1, '0')); }
		else { s.append(string(1, '1')); }
	}

	return s;
}
string string2Bin(string s) {
	string ret;
	for (int i = 0; i < s.size(); i++) {
		int k = s[i];
		string temp = Dec2Bin(k);
		//cout << k << " " << temp << endl;
		ret.append(temp);
	}
	return ret;
}
string cleanZero(string s) {
	string ss = s;
	reverse(ss.begin(), ss.end());
	while (ss[ss.size() - 1] == '0') {
		ss.pop_back();
	}
	reverse(ss.begin(), ss.end());
	return ss;
}
vector<BigInt>Prime512;
void InitialPrime512() {
	string s1 = "B49700D49696726058F2506BAF6860981E4F097B89CF5540FB07A3CDEB9BDCC3";
	string s2 = "DE9AE262BBFA557E9EF55E9D165B43E6F859803F4AC929FAE9680325BA295513";
	string s3 = "A14A46D62943712797385A7259AD68FAE4110C83DBFD75AFAED7AC3B52F4308B";
	string s4 = "A7BBD5BD2F177E7BAEB89DB47196F7640C8ED51F62ED6961BF5726877FF06A53";
	string s5 = "B87E37FE315B0F4CC722BB0F815A184EA27FAB85119BFDD8A45DD98643926D1B";
	string s6 = "8233A8BA28A6F782A7A70AFD7AE05808AE0F812515DBD75CEE2EB0967E7FA063";
	Prime512.push_back(string2BigInt(s1));
	Prime512.push_back(string2BigInt(s2));
	Prime512.push_back(string2BigInt(s3));
	Prime512.push_back(string2BigInt(s4));
	Prime512.push_back(string2BigInt(s5));
	Prime512.push_back(string2BigInt(s6));
}
vector<BigInt>Prime256;
void IntialPrime256() {
	string s1 = "DB92BF308AF4895A7EF3E3FCD7290853";
	string s2 = "F4D7A6FF616582E7A18FDA48A5B6A303";
	string s3 = "AD49678F3DBA34AA8789350E9FA3FE5B";
	string s4 = "D711D47AEF9F9471FF9C7DFCD1DCC18B";
	string s5 = "C502F81D0180027EE578EC5AF5C67EE3";
	string s6 = "C2C899D5EA7E21517C42C9AB5104BA83";
	Prime256.push_back(string2BigInt(s1));
	Prime256.push_back(string2BigInt(s2));
	Prime256.push_back(string2BigInt(s3));
	Prime256.push_back(string2BigInt(s4));
	Prime256.push_back(string2BigInt(s5));
	Prime256.push_back(string2BigInt(s6));
}
