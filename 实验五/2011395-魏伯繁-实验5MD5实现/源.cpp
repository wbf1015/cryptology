#include"MD5.h"
using namespace std;
void testreadcmd() {
	vector<char>vc;
	readcmd(vc);
	printVectorChar(vc);
}
void testfill() {
	vector<char>vc;
	readcmd(vc);
	cout << "������ļ�Ϊ��" << endl;
	printVectorChar(vc);
	vector<char>vc2(vc);

	fill(vc);
	cout << "����Ĵ�СΪ:";
	cout << vc.size()<<endl;
	cout << "���������Ϊ��" << endl;
	printVectorChar(vc);

	fillLength(vc,vc2);
	cout << "��������Ĵ�СΪ��" << endl;
	cout << vc.size()<<endl;
	cout << "�������������Ϊ��" << endl;
	printVectorChar(vc);
}
void testmyMD5() {
	vector<char>vc;
	readcmd(vc);
	cout << "������ļ�Ϊ��" << endl;
	printVectorChar(vc);
	vector<char>vc2(vc);

	fill(vc);
	cout << "����Ĵ�СΪ:";
	cout << vc.size() << endl;
	cout << "���������Ϊ��" << endl;
	printVectorChar(vc);

	fillLength(vc, vc2);
	cout << "��������Ĵ�СΪ��" << endl;
	cout << vc.size() << endl;
	cout << "�������������Ϊ��" << endl;
	printVectorChar(vc);

	myMD5 m(vc);
	cout << "����myMD5��Ľ��Ϊ��" << endl;
	cout << m;
}
void testAddString() {
	string a = Hex2Bin("11223344");
	string b = Hex2Bin("ACDBEFA1");
	string c = stringADD(a, b);
	cout << a << endl;
	cout << b << endl;
	cout << c << endl;
}
void testCLS() {
	string s = "10010001001110110110010100110110";
	cout << CLS(s, 31);
}
void testHash() {
	vector<char>vc;
	readcmd(vc);
	cout << "������ļ�Ϊ��" << endl;
	printVectorChar(vc);
	vector<char>vc2(vc);

	fill(vc);
	cout << "����Ĵ�СΪ:";
	cout << vc.size() << endl;
	cout << "���������Ϊ��" << endl;
	printVectorChar(vc);

	fillLength(vc, vc2);
	cout << "��������Ĵ�СΪ��" << endl;
	cout << vc.size() << endl;
	cout << "�������������Ϊ��" << endl;
	printVectorChar(vc);

	myMD5 m(vc);
	cout << "����myMD5��Ľ��Ϊ��" << endl;
	cout << m;

	string ret=HashMD5(m);
	cout << "���Ľ��Ϊ��" << ret << endl;
	cout << "16���Ʊ�ʾΪ" << Bin2Hex(ret) << endl;
}
void CalMD5() {
	vector<char>vc;
	readcmd(vc);
	cout << "������ļ�Ϊ��" << endl;
	printVectorChar(vc);
	vector<char>vc2(vc);

	fill(vc);
	cout << "����Ĵ�СΪ:";
	cout << vc.size() << endl;
	cout << "���������Ϊ��" << endl;
	printVectorChar(vc);

	fillLength(vc, vc2);
	cout << "��������Ĵ�СΪ��" << endl;
	cout << vc.size() << endl;
	cout << "�������������Ϊ��" << endl;
	printVectorChar(vc);

	myMD5 m(vc);
	cout << "����myMD5��Ľ��Ϊ��" << endl;
	cout << m;

	string ret = HashMD5(m);
	cout << "���Ľ��Ϊ��" << ret << endl;
	cout << "16���Ʊ�ʾΪ" << Bin2Hex(ret) << endl;

	cout << "����ת����������лʹ��" << endl;
}
double avalanchetest() {
	cout << "�������ѩ��ЧӦ���" << endl;
	vector<char>vc;
	for (int i = 0; i < 64; i++) {
		vc.push_back('0');
	}
	vector<char>vc2(vc);
	fill(vc);
	fillLength(vc, vc2);
	myMD5 m(vc);
	string base = HashMD5(m);
	double finali=0;
	for (int i = 0; i < 64; i++) {
		vc.clear();
		for (int j = 0; j < 64; j++) {
			if (j == i) { vc.push_back('1'); }
			else { vc.push_back('0'); }
		}
		vector<char>vc3(vc);
		fill(vc);
		fillLength(vc, vc3);
		myMD5 mm(vc);
		string ss = HashMD5(mm);
		finali += stringDiff(base, ss);
	}
	return finali / 64.0;
}
int main() {
	CalMD5();
	cout << "�Ƿ����ѩ��ЧӦ��⣿" << endl;
	cout << "1:��" << endl;
	cout << "2:��" << endl;
	int choose; cin >> choose;
	if (choose == 1) {
		cout << "ѩ��ЧӦ��ⷽʽ�ǣ��涨baseΪ64��0��ɵ��ı��ַ�" << endl;
		cout << "���������ı�ÿ�����أ��������ƽ���ı���λ�ı�" << endl;
		double i = avalanchetest();
		cout << "����ƽ��ÿ�ı�һ������λ���������ı�" << i << "������" << endl;
	}
	while (true) {

	}
}