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
void CalMD5() {
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

	string ret = HashMD5(m);
	cout << "最后的结果为：" << ret << endl;
	cout << "16进制表示为" << Bin2Hex(ret) << endl;

	cout << "本次转换结束，感谢使用" << endl;
}
double avalanchetest() {
	cout << "下面进行雪崩效应检测" << endl;
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
	cout << "是否进行雪崩效应检测？" << endl;
	cout << "1:是" << endl;
	cout << "2:否" << endl;
	int choose; cin >> choose;
	if (choose == 1) {
		cout << "雪崩效应检测方式是，规定base为64个0组成的文本字符" << endl;
		cout << "程序会逐个改变每个比特，最终输出平均的比特位改变" << endl;
		double i = avalanchetest();
		cout << "最终平均每改变一个比特位，最后结果会改变" << i << "个比特" << endl;
	}
	while (true) {

	}
}