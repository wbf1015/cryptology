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
int main() {
	
}