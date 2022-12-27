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
	cout << "读入的文件为：" << endl;
	printVectorChar(vc);
	vector<char>vc2(vc);

	fill(vc);
	cout << "填充后的大小为:";
	cout << vc.size()<<endl;
	cout << "填充后的内容为：" << endl;
	printVectorChar(vc);

	fillLength(vc,vc2);
	cout << "最终填充后的大小为：" << endl;
	cout << vc.size()<<endl;
	cout << "最终填充后的内容为：" << endl;
	printVectorChar(vc);
}
void testmyMD5() {
	vector<char>vc;
	readcmd(vc);
	cout << "读入的文件为：" << endl;
	printVectorChar(vc);
	vector<char>vc2(vc);

	fill(vc);
	cout << "填充后的大小为:";
	cout << vc.size() << endl;
	cout << "填充后的内容为：" << endl;
	printVectorChar(vc);

	fillLength(vc, vc2);
	cout << "最终填充后的大小为：" << endl;
	cout << vc.size() << endl;
	cout << "最终填充后的内容为：" << endl;
	printVectorChar(vc);

	myMD5 m(vc);
	cout << "进入myMD5后的结果为：" << endl;
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
	cout << "读入的文件为：" << endl;
	printVectorChar(vc);
	vector<char>vc2(vc);

	fill(vc);
	cout << "填充后的大小为:";
	cout << vc.size() << endl;
	cout << "填充后的内容为：" << endl;
	printVectorChar(vc);

	fillLength(vc, vc2);
	cout << "最终填充后的大小为：" << endl;
	cout << vc.size() << endl;
	cout << "最终填充后的内容为：" << endl;
	printVectorChar(vc);

	myMD5 m(vc);
	cout << "进入myMD5后的结果为：" << endl;
	cout << m;

	string ret=HashMD5(m);
	cout << "最后的结果为：" << ret << endl;
	cout << "16进制表示为" << Bin2Hex(ret) << endl;
}
int main() {
	testHash();
}