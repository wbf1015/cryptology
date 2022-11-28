#include<iostream>
#include<cmath>
#include<vector>
#include<string>
using namespace std;
int textSize;//明文长度
int keySize;//密钥长度
char* text;//明文内容
char* key;//密钥内容
char* out;//结果
int Myround;//迭代的轮数
int shift[4]{ 0 };//移位时的位数
string mx = "100011011";
class TestData1 {
public:
	int textSize = 128;
	int keySize = 128;
	string text = "0001, 0001, 01a1, 98af, da78, 1734, 8615, 3566";
	string key = "0001, 2001, 7101, 98ae, da79, 1714, 6015, 3594";
	string out = "6cdd, 596b, 8f56, 42cb, d23b, 4798, 1a65, 422a";
}td1;
class TestData2 {
public:
	int textSize = 128;
	int keySize = 128;
	string text = "3243, f6a8, 885a, 308d, 3131, 98a2, e037, 0734";
	string key = "2b7e, 1516, 28ae, d2a6, abf7, 1588, 09cf, 4f3c";
	string out = "3925, 841d, 02dc, 09fb, dc11, 8597, 196a, 0b32";
}td2;
char matrix1[9][9]{
	{},
	{'0','1','0','0','0','1','1','1','1'},
	{'0','1','1','0','0','0','1','1','1'},
	{'0','1','1','1','0','0','0','1','1'},
	{'0','1','1','1','1','0','0','0','1'},
	{'0','1','1','1','1','1','0','0','0'},
	{'0','0','1','1','1','1','1','0','0'},
	{'0','0','0','1','1','1','1','1','0'},
	{'0','0','0','0','1','1','1','1','1'},
};
char matrix2[9]{'0','1','1','0','0','0','1','1','0'};
string matrix3[5][5]{
	{"","","","",""},
	{"","00000010","00000011","00000001","00000001"},
	{"","00000001","00000010","00000011","00000001"},
	{"","00000001","00000001","00000010","00000011"},
	{"","00000011","00000001","00000001","00000010"},
};
//根据明文长度以及密文长度设置迭代轮数以及位移量
void SetValue(){
	//先设置迭代轮数
	if (textSize == 128 && keySize == 128) { Myround = 10; }
	if (textSize == 192 && keySize == 128) { Myround = 12; }
	if (textSize == 256 && keySize == 128) { Myround = 14; }
	if (textSize == 128 && keySize == 192) { Myround = 12; }
	if (textSize == 192 && keySize == 192) { Myround = 12; }
	if (textSize == 256 && keySize == 192) { Myround = 12; }
	if (textSize == 128 && keySize == 256) { Myround = 14; }
	if (textSize == 192 && keySize == 256) { Myround = 14; }
	if (textSize == 256 && keySize == 256) { Myround = 14; }
	//再设置引动的位移量
	if (textSize == 128) { shift[1] = 1; shift[2] = 2; shift[3] = 3; }
	if (textSize == 192) { shift[1] = 1; shift[2] = 2; shift[3] = 3; }
	if (textSize == 256) { shift[1] = 1; shift[2] = 3; shift[3] = 4; }
}
//打印char*
void printCStar(char* c, int start, int end) {
	for (int i = start; i < end; i++) {
		cout << c[i];
	}cout << endl;
}
//16进制转换为2进制
string Hex2Binary(char c) {
	if (c == '0') { return "0000"; }
	if (c == '1') { return "0001"; }
	if (c == '2') { return "0010"; }
	if (c == '3') { return "0011"; }
	if (c == '4') { return "0100"; }
	if (c == '5') { return "0101"; }
	if (c == '6') { return "0110"; }
	if (c == '7') { return "0111"; }
	if (c == '8') { return "1000"; }
	if (c == '9') { return "1001"; }
	if (c == 'a') { return "1010"; }
	if (c == 'b') { return "1011"; }
	if (c == 'c') { return "1100"; }
	if (c == 'd') { return "1101"; }
	if (c == 'e') { return "1110"; }
	if (c == 'f') { return "1111"; }
}
//二进制自增
string StringInc(string a) {
	char jw = '0';
	int la = a.length();
	for (int i = la - 1; i >= 0; i--) {
		if (i == la - 1) {
			if (a[i] == '0') { a[i] = '1'; }
			else { a[i] = '0'; jw = '1'; }
			continue;
		}
		else {
			if (a[i] == '0' && jw == '0') { a[i] = '0'; jw = '0';}
			if (a[i] == '0' && jw == '1') { a[i] = '1'; jw = '0'; }
			if (a[i] == '1' && jw == '0') { a[i] = '1'; jw = '0'; }
			if (a[i] == '1' && jw == '1') { a[i] = '0'; jw = '1'; }
		}
	}
	if (jw == '1') {
		string s = "1" + a;
		return s;
	}
	return a;
}
//从string提取对应的int
int String2Intb(string s) {
	int r = 0;
	if (s.length() == 8) {
		for (int i = 0; i < 8; i++) {
			int temp;
			if (s[i] == '0') { temp = 0; }
			else { temp = 1; }
			r += temp * pow(2, 7 - i);
		}
	}
	return r;
}
char CharAddb(char a, char b) {
	if (a == '0' && b == '0') { return '0'; }
	if (a == '0' && b == '1') { return '1'; }
	if (a == '1' && b == '0') { return '1'; }
	if (a == '1' && b == '1') { return '0'; }
}
//没有进位的加法
string StringAddb2(string a, string b) {
	string r = "00000000";
	for (int i = 0; i < 8; i++) {
		r[i] = CharAddb(a[i], b[i]);
	}
	return r;
}
//做伽罗瓦域上的加法(有加法)
string StringAddb(string a, string b) {
	int la = a.length();//拿到a的长度
	int lb = b.length();//拿到b的长度
	int l;
	vector<char>ls;//代表长的string的vector
	vector<char>ss;//代表段的string的vector
	vector<char>rs;//结果字符串
	if (la >= lb) {//a是更长的
		for (int i = la - 1; i >= 0; i--) {
			ls.push_back(a[i]);
		}
		for (int i = lb - 1; i >= 0; i--) {
			ss.push_back(b[i]);
		}
		l = la;
	}
	else {
		for (int i = la - 1; i >= 0; i--) {
			ss.push_back(a[i]);
		}
		for (int i = lb - 1; i >= 0; i--) {
			ls.push_back(b[i]);
		}
		l = lb;
	}
	for (int i = 0; i <= ls.size()-1; i++) {
		if (i <= ss.size() - 1) {
			if (ls[i] == ss[i]) { rs.push_back('0'); }
			else { rs.push_back('1'); }
		}
		else {
			rs.push_back(ls[i]);
			}
	}
	string s="";
	int lr = rs.size();
	for (int i = lr - 1; i >= 0; i--) {
		string temp(1, rs[i]);
		s.append(temp);
	}
	return s;
}
//相当于做取模运算
string StringModb(string a) {
	string temp = a;
	int la = temp.length();
	for (int i = 0; i <= la - 9; i++) {
		if (temp[i] == '1') {
			for (int j = 0; j <= 8; j++) {
				temp[i + j] = CharAddb(temp[i + j], mx[j]);
			}
		}
	}
	string rs = "";
	for (int i = la - 1 - 7; i <= la-1; i++) {
		string t(1, temp[i]);
		rs.append(t);
	}
	return rs;
}
//伽罗瓦域上的乘法运算
string mulGF(string a, string b) {
	if (a == "00000000" || b == "00000000") {
		return "00000000";
	}
	string temp = a;
	int lb = b.length();
	string front="";
	string back="";
	for (int i = lb - 1; i >= 0; i--) {
		if (b[i] == '1') {
			if (front == "") {
				string t = a;
				for (int j = 1; j <= (lb - 1) - i; j++) {
					t.append("0");
				}
				front = t;
				continue;
			}
			else {
				string t = a;
				for (int j = 1; j <= (lb - 1) - i; j++) {
					t.append("0");
				}
				back = t;
				//cout << front << "  " << back << endl;
				front = StringAddb(front, back);
				//cout << front << endl;
				continue;
			}
		}
	}
	//cout << front << endl;
	temp = StringModb(front);
	return temp;
}
string reverseGF(string a) {
	if (a == "00000000") { return "00000000"; }//0映射到自己
	string s = "00000000";
	for (int i = 1; i <= 256; i++) {;
		if (mulGF(a, s) == "00000001") {
			return s;
		}
		else {
			s = StringInc(s);
		}
	}
	return s;
}
//需要用测试用例2直接把TestData1改成TestData2就行
void gettext(TestData1 td) {
	textSize = td.textSize;
	int textlength = td.textSize;
	text = new char[textlength+1];
	out = new char[textlength + 1];
	string s = td.text;
	int count = 1;
	for (int i = 0; i < s.length(); i++) {
		if ((s[i] >= 48 && s[i] <= 57) || (s[i] >= 97 && s[i] <= 102)) {
			string t = Hex2Binary(s[i]);
			for (int j = 0; j < 4; j++) {
				text[count++] = t[j];
			}
		}
	}
}
void getkey(TestData1 td) {
	keySize = td.keySize;
	int keylength = td.keySize;
	key = new char[keylength + 1];
	string s = td.key;
	int count = 1;
	for (int i = 0; i < s.length(); i++) {
		if ((s[i] >= 48 && s[i] <= 57) || (s[i] >= 97 && s[i] <= 102)) {
			string t = Hex2Binary(s[i]);
			for (int j = 0; j < 4; j++) {
				key[count++] = t[j];
			}
		}
	}
}
string ByteSub(string s) {
	string t = reverseGF(s);//得到对应的乘法逆元
	string r1 = "00000000";
	for (int i = 1; i <= 8; i++) {
		//每一个外层循环算出一个比特
		char tc='0';
		for (int j = 1; j <= 8; j++) {
			char tcc;
			if (matrix1[i][j] == '0' || t[j - 1] == '0') { tcc = '0'; }
			else { tcc = '1'; }
			if (tc == tcc) { tc = '0'; }
			else { tc = '1'; }
		}
		r1[i - 1] = tc;
	}
	for (int i = 1; i <= 8; i++) {
		if (r1[i - 1] == matrix2[i]) { r1[i - 1] = '0'; }
		else { r1[i - 1] = '1'; }
	}
	return r1;
}
//行移位
void shiftRow() {
	//构建矩阵形式的存储方式
	string store[5][9];
	for (int i = 1; i <= textSize / 32; i++) {//遍历列
		for (int j = 1; j <= 4; j++) {//遍历行
			string temp = "";
			for (int k = 1; k <= 8; k++) {
				temp.push_back(text[(i - 1) * 32 + (j - 1) * 8] + k);
			}
			store[j][i] = temp;
		}
	}
	//对第2-4行进行行移位
	for (int i = 2; i <= 4; i++) {
		int cross = shift[i - 1];//位移的位数
		for (int j = 1; j <= textSize / 32; j++) {
			vector<string>vs;//把这一列的所有字符串都先保存
			vs.push_back("");//占住零位
			for (int k = 1; k <= textSize / 32; k++) {
				vs.push_back(store[i][k]);
			}
			for (int k = 1; k <= textSize / 32; k++) {//移位
				if (k + cross <= textSize / 32) {
					store[i][k] = vs[k + cross];
				}
				else {
					store[i][k] = vs[k + cross-textSize/32];
				}
			}
		}
	}
}
//列混合
void MixColumn(int col){
	vector<string>vs;
	vector<string>rs;
	//取出text文件第col列的对应的4个字节
	for (int i = 1; i <= 4; i++) {
		string temp;
		for (int j = 1; j <= 8; j++) {
			temp.push_back(text[(col - 1) * 32 + (i - 1) * 8 + j]);
		}
		vs.push_back(temp);
	}
	//循环四次算出列混合后的四个字节
	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 4; j++) {
			vs[j-1]=(mulGF(matrix3[i][j], vs[j - 1]));//乘完之后的结果保存在原来的位置
		}
		string temp = "00000000";
		for (int k = 1; k <= 4; k++) {			
			temp = StringAddb2(temp, vs[k-1]);//对vs中的内容做累加
		}
		rs.push_back(temp);
	}
	//把结果填回去
	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 8; j++) {
			text[(col - 1) * 32 + (i - 1) * 8 + j] = rs[i - 1][j - 1];
		}
	}
}
//密钥加
void AddRoundKey(char* c) {
	for (int i = 1; i <= textSize; i++) {
		if (text[i] == c[i]) { text[i] = '0'; }
		else { text[i] = '1'; }
	}
}
void test() {
	string s1 = "00011011";
	string s2 = "00101101";
	//cout << mulGF(s1, s2)<<endl;
	string s3 = "01010111";
	//cout << reverseGF(s3);
	//gettext(td1);
	//printCStar(text, 1, 129);
	//getkey(td1);
	//printCStar(key, 1, 129);
	cout << ByteSub("11000001");
}

int main() {
	//test();
}