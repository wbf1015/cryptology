#pragma once
#include<iostream>
#include<cmath>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;
int textSize;//���ĳ���
int keySize;
char* text;
char* key;
char* out;
int Myround;
int shift[4]{ 0 };
string mx = "100011011";
class TestData1 {
public:
	int textSize = 128;
	int keySize = 128;
	string text = "0001, 0001, 01a1, 98af, da78, 1734, 8615, 3566";
	string key = "0001, 2001, 7101, 98ae, da79, 1714, 6015, 3594";
	string out = "6cdd, 596b, 8f56, 42cb, d23b, 4798, 1a65, 422a";
	TestData1(int ts, int ks, string text, string key, string out = "") {
		this->textSize = ts;
		this->keySize = ks;
		this->text = text;
		this->key = key;
		this->out = out;
	}
	TestData1() {};
}td1;
TestData1 td2(128, 128, "3243, f6a8, 885a, 308d, 3131, 98a2, e037, 0734", "2b7e, 1516, 28ae, d2a6, abf7, 1588, 09cf, 4f3c", "3925, 841d, 02dc, 09fb, dc11, 8597, 196a, 0b32");

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

char matrix2[9]{ '0','1','1','0','0','0','1','1','0' };

string matrix3[5][5]{
	{"","","","",""},
	{"","00000010","00000011","00000001","00000001"},
	{"","00000001","00000010","00000011","00000001"},
	{"","00000001","00000001","00000010","00000011"},
	{"","00000011","00000001","00000001","00000010"},
};

char matrix4[9][9]{
	{},
	{'0','0','0','1','0','0','1','0','1'},
	{'0','1','0','0','1','0','0','1','0'},
	{'0','0','1','0','0','1','0','0','1'},
	{'0','1','0','1','0','0','1','0','0'},
	{'0','0','1','0','1','0','0','1','0'},
	{'0','0','0','1','0','1','0','0','1'},
	{'0','1','0','0','1','0','1','0','0'},
	{'0','0','1','0','0','1','0','1','0'},
};
char matrix5[9]{ '0','1','0','1','0','0','0','0','0' };

string matrix6[5][5]{
	{"","","","",""},
	{"","00001110","00001011","00001101","00001001"},
	{"","00001001","00001110","00001011","00001101"},
	{"","00001101","00001001","00001110","00001011"},
	{"","00001011","00001101","00001001","00001110"},
};
class KeyStore {
public:
	string l1;
	string l2;
	string l3;
	string l4;
	KeyStore() { l1 = ""; l2 = ""; l3 = ""; l4 = ""; }
	KeyStore(string s1, string s2, string s3, string s4) {
		l1 = s1; l2 = s2; l3 = s3; l4 = s4;
	}
};
vector<KeyStore>vks;

char Binary2Hex(string s) {
	if (s == "0000") { return '0'; }
	if (s == "0001") { return '1'; }
	if (s == "0010") { return '2'; }
	if (s == "0011") { return '3'; }
	if (s == "0100") { return '4'; }
	if (s == "0101") { return '5'; }
	if (s == "0110") { return '6'; }
	if (s == "0111") { return '7'; }
	if (s == "1000") { return '8'; }
	if (s == "1001") { return '9'; }
	if (s == "1010") { return 'A'; }
	if (s == "1011") { return 'B'; }
	if (s == "1100") { return 'C'; }
	if (s == "1101") { return 'D'; }
	if (s == "1110") { return 'E'; }
	if (s == "1111") { return 'F'; }
}

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
	if (c == 'a'||c=='A') { return "1010"; }
	if (c == 'b'||c=='B') { return "1011"; }
	if (c == 'c'||c=='C') { return "1100"; }
	if (c == 'd'||c=='D') { return "1101"; }
	if (c == 'e'||c=='E') { return "1110"; }
	if (c == 'f'||c=='F') { return "1111"; }
}

void printCStar(char* c, int start, int end) {
	for (int i = start; i < end; i++) {
		cout << c[i];
		if (i % 8 == 0) { cout << endl; }
	}cout << endl;
}
void CStar2HEX(char* c, int start, int end) {
	int count = 0;
	for (int i = start; i < end; i += 4) {
		string s = "";
		s.push_back(c[i]);
		s.push_back(c[i + 1]);
		s.push_back(c[i + 2]);
		s.push_back(c[i + 3]);
		//cout << Binary2Hex(s);
		count++;
		if (count % 4 == 0) { cout << ","; }
	}
	cout << endl;
}
string GetCstarHex(char* c, int start, int end) {
	string ret;
	for (int i = start; i < end; i += 4) {
		string s = "";
		s.push_back(c[i]);
		s.push_back(c[i + 1]);
		s.push_back(c[i + 2]);
		s.push_back(c[i + 3]);
		//cout << Binary2Hex(s);
		ret.push_back(Binary2Hex(s));
	}
	return ret;
}
int findDifference(char* c1, char* c2, int start, int end) {
	int count = 0;
	for (int i = start; i < end; i++) {
		if (c1[i] == c2[i]) { count++; }
	}
	return count;
}

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
			if (a[i] == '0' && jw == '0') { a[i] = '0'; jw = '0'; }
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

string StringAddb2(string a, string b) {
	string r = "00000000";
	for (int i = 0; i < 8; i++) {
		r[i] = CharAddb(a[i], b[i]);
	}
	return r;
}

string StringAddb(string a, string b) {
	int la = a.length();
	int lb = b.length();
	int l;
	vector<char>ls;
	vector<char>ss;
	vector<char>rs;
	if (la >= lb) {
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
	for (int i = 0; i <= ls.size() - 1; i++) {
		if (i <= ss.size() - 1) {
			if (ls[i] == ss[i]) { rs.push_back('0'); }
			else { rs.push_back('1'); }
		}
		else {
			rs.push_back(ls[i]);
		}
	}
	string s = "";
	int lr = rs.size();
	for (int i = lr - 1; i >= 0; i--) {
		string temp(1, rs[i]);
		s.append(temp);
	}
	return s;
}

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
	for (int i = la - 1 - 7; i <= la - 1; i++) {
		string t(1, temp[i]);
		rs.append(t);
	}
	return rs;
}

string mulGF(string a, string b) {
	if (a == "00000000" || b == "00000000") {
		return "00000000";
	}
	string temp = a;
	int lb = b.length();
	string front = "";
	string back = "";
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
	if (a == "00000000") { return "00000000"; }
	string s = "00000000";
	for (int i = 1; i <= 256; i++) {
		;
		if (mulGF(a, s) == "00000001") {
			return s;
		}
		else {
			s = StringInc(s);
		}
	}
	return s;
}

void gettext(TestData1 td) {
	textSize = td.textSize;
	int textlength = td.textSize;
	text = new char[textlength + 1];
	string s = td.text;
	int count = 1;
	for (int i = 0; i < s.length(); i++) {
		if ((s[i] >= 48 && s[i] <= 57) || (s[i] >= 97 && s[i] <= 102) || (s[i] >= 65 && s[i] <= 70)) {
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
		if ((s[i] >= 48 && s[i] <= 57) || (s[i] >= 97 && s[i] <= 102) || (s[i] >= 65 && s[i] <= 70)) {
			string t = Hex2Binary(s[i]);
			for (int j = 0; j < 4; j++) {
				key[count++] = t[j];
			}
		}
	}
}
void getout(TestData1 td) {
	textSize = td.textSize;
	int textlength = td.textSize;
	text = new char[textlength + 1];
	string s = td.out;
	int count = 1;
	for (int i = 0; i < s.length(); i++) {
		if ((s[i] >= 48 && s[i] <= 57) || (s[i] >= 97 && s[i] <= 102) || (s[i] >= 65 && s[i] <= 70)) {
			string t = Hex2Binary(s[i]);
			for (int j = 0; j < 4; j++) {
				text[count++] = t[j];
			}
		}
	}
}
void SetValue() {

	if (textSize == 128 && keySize == 128) { Myround = 10; }
	if (textSize == 192 && keySize == 128) { Myround = 12; }
	if (textSize == 256 && keySize == 128) { Myround = 14; }
	if (textSize == 128 && keySize == 192) { Myround = 12; }
	if (textSize == 192 && keySize == 192) { Myround = 12; }
	if (textSize == 256 && keySize == 192) { Myround = 12; }
	if (textSize == 128 && keySize == 256) { Myround = 14; }
	if (textSize == 192 && keySize == 256) { Myround = 14; }
	if (textSize == 256 && keySize == 256) { Myround = 14; }

	if (textSize == 128) { shift[1] = 1; shift[2] = 2; shift[3] = 3; }
	if (textSize == 192) { shift[1] = 1; shift[2] = 2; shift[3] = 3; }
	if (textSize == 256) { shift[1] = 1; shift[2] = 3; shift[3] = 4; }
}


string ByteSub(string s) {
	string t = reverseGF(s);
	string r1 = "00000000";
	for (int i = 1; i <= 8; i++) {

		char tc = '0';
		for (int j = 1; j <= 8; j++) {
			char tcc;
			if (matrix1[i][j] == '0' || t[7 - (j - 1)] == '0') { tcc = '0'; }
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
	reverse(r1.begin(), r1.end());
	return r1;
}

void MyByteSub() {
	for (int i = 1; i <= textSize / 8; i++) {
		string t = "00000000";
		for (int j = 1; j <= 8; j++) {
			t[j - 1] = (text[(i - 1) * 8 + j]);
		}
		//cout << t << " ";
		t = ByteSub(t);
		//cout << t << " "<<endl;
		for (int j = 1; j <= 8; j++) {
			text[(i - 1) * 8 + j] = t[j - 1];
		}
	}
	//printCStar(text, 1, 129);
}

void shiftRow() {

	string store[5][9];
	for (int i = 1; i <= textSize / 32; i++) {
		for (int j = 1; j <= 4; j++) {
			string temp = "";
			for (int k = 1; k <= 8; k++) {
				temp.push_back(text[(i - 1) * 32 + (j - 1) * 8 + k]);
			}
			store[j][i] = temp;
			//cout << j << " " << i << " " << temp << endl;
		}
	}
	//cout << endl;

	for (int i = 2; i <= 4; i++) {
		int cross = shift[i - 1];
		vector<string>vs;
		vs.push_back("");
		for (int k = 1; k <= textSize / 32; k++) {
			vs.push_back(store[i][k]);
		}
		for (int k = 1; k <= textSize / 32; k++) {
			if (k + cross <= textSize / 32) {
				store[i][k] = vs[k + cross];
			}
			else {
				store[i][k] = vs[k + cross - textSize / 32];
			}
		}
	}
	//cout << endl;

	for (int i = 1; i <= textSize / 32; i++) {
		for (int j = 1; j <= 4; j++) {
			string s = store[j][i];
			for (int k = 1; k <= 8; k++) {
				text[(i - 1) * 32 + (j - 1) * 8 + k] = s[k - 1];
			}
			//cout << j << " " << i << " " << s << endl;
		}
	}
}

void MixColumn(int col) {
	//cout << "col = " << col << endl;
	vector<string>vs;
	vector<string>vt;
	vector<string>rs;

	for (int i = 1; i <= 4; i++) {
		string temp;
		for (int j = 1; j <= 8; j++) {
			temp.push_back(text[(col - 1) * 32 + (i - 1) * 8 + j]);
			//int tempi = (col - 1) * 32 + (i - 1) * 8 + j;
			//char c = text[tempi];
			//char cc = text[1];
		}
		vs.push_back(temp);
		//cout << temp <<" ";
	}
	//cout << endl;

	for (int i = 1; i <= 4; i++) {
		vt.clear();
		for (int j = 1; j <= 4; j++) {
			vt.push_back(mulGF(matrix3[i][j], vs[j - 1]));
		}
		string temp = "00000000";
		for (int k = 1; k <= 4; k++) {
			temp = StringAddb2(temp, vt[k - 1]);
		}
		rs.push_back(temp);
	}

	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 8; j++) {
			text[(col - 1) * 32 + (i - 1) * 8 + j] = rs[i - 1][j - 1];
		}
		//cout << rs[i-1] <<" ";
	}
	//cout << endl;
}

void AddRoundKey(string s) {
	for (int i = 1; i <= textSize; i++) {
		if (text[i] == s[i - 1]) { text[i] = '0'; }
		else { text[i] = '1'; }
	}
}

void RotByte(KeyStore& ks) {
	string temp = ks.l1;
	ks.l1 = ks.l2;
	ks.l2 = ks.l3;
	ks.l3 = ks.l4;
	ks.l4 = temp;
}
string GenerateRC(int i) {
	string temp = "00000000";
	if (i <= 8) {
		temp[8 - i] = '1';
		return temp;
	}
	else {
		for (int j = i - 8; j > 0; j--) {
			temp.push_back('0');
		}
		temp[0] = '1';
		temp = StringModb(temp);
		return temp;
	}
}

void KeyExpansion() {
	vks.clear();

	for (int i = 0; i < keySize / 32; i++) {
		vector<string>tvs;
		for (int j = 1; j <= 4; j++) {
			string temp = "";
			for (int k = 1; k <= 8; k++) {
				temp.push_back(key[(i) * 32 + (j - 1) * 8 + k]);
			}
			tvs.push_back(temp);
		}
		KeyStore ks(tvs[0], tvs[1], tvs[2], tvs[3]);
		vks.push_back(ks);
	}
	for (int i = keySize / 32; i <= (textSize / 32) * (Myround + 1); i++) {
		KeyStore temp = vks[i - 1];
		if ((i % (keySize / 32)) == 0) {
			RotByte(temp);
			temp.l1 = ByteSub(temp.l1);
			temp.l2 = ByteSub(temp.l2);
			temp.l3 = ByteSub(temp.l3);
			temp.l4 = ByteSub(temp.l4);
			string  s = GenerateRC(i / (keySize / 32));
			temp.l1 = StringAddb2(temp.l1, s);
			//cout << temp.l1 << " " << temp.l2 << " " << temp.l3 << " " << temp.l4 << endl;
		}//????temp
		KeyStore t = vks[i - keySize / 32];
		//cout << "temp:" << temp.l1 << " " << temp.l2 << " " << temp.l3 << " " << temp.l4 << endl;
		//cout << "t:" << t.l1 << " " << t.l2 << " " << t.l3 << " " << t.l4 << endl;
		string s1 = StringAddb2(temp.l1, t.l1);
		string s2 = StringAddb2(temp.l2, t.l2);
		string s3 = StringAddb2(temp.l3, t.l3);
		string s4 = StringAddb2(temp.l4, t.l4);
		KeyStore rs(s1, s2, s3, s4);
		//cout << s1 << " " << s2 << " " << s3 <<" "<< s4 << endl;
		vks.push_back(rs);
	}
}

string generateUsedKey(int start) {
	string s = "";
	for (int i = 1; i <= textSize / 32; i++) {
		KeyStore ks = vks[start + i - 1];
		s.append(ks.l1);
		s.append(ks.l2);
		s.append(ks.l3);
		s.append(ks.l4);
	}
	return s;
	//cout << s << endl;
}
void test1() {
	printCStar(text, 1, 129);
	printCStar(key, 1, 129);
	cout << textSize << " " << keySize << " " << Myround << endl;
	cout << shift[1] << " " << shift[2] << " " << shift[3];
}
void Round(string KeyS) {//col>=1
	MyByteSub();
	//cout << "after bytesub  "<<endl;
	//printCStar(text, 1, 129);
	shiftRow();
	//cout << "after shiftRow  "<<endl;
	//printCStar(text, 1, 129);
	for (int i = 1; i <= textSize / 32; i++) {
		MixColumn(i);
	}
	//cout << "after mix column" << endl;
	//printCStar(text, 1, 129);
	AddRoundKey(KeyS);
	//cout << "after addRoundKey" << endl;
	//printCStar(text, 1, 129);
}
void FinalRound(string KeyS) {
	MyByteSub();
	shiftRow();
	AddRoundKey(KeyS);
}
void encrypt(TestData1 td) {
	gettext(td);
	getkey(td);
	SetValue();
	KeyExpansion();
	//test1();
	//printCStar(key, 1, 129);
	string s = generateUsedKey(0);
	//cout << s << endl;
	//printCStar(text, 1, 129);
	AddRoundKey(s);
	//cout << "after add" << endl;
	//printCStar(text, 1, 129);
	for (int i = 1; i <= Myround; i++) {
		string s = generateUsedKey(i * textSize / 32);
		//cout << s << endl;
		if (i == Myround) { FinalRound(s); break; }
		Round(s);
	}
}



string RByteSub(string s) {
	string t = s;
	string r1 = "00000000";
	for (int i = 1; i <= 8; i++) {

		char tc = '0';
		for (int j = 1; j <= 8; j++) {
			char tcc;
			if (matrix4[i][j] == '0' || t[7 - (j - 1)] == '0') { tcc = '0'; }
			else { tcc = '1'; }
			if (tc == tcc) { tc = '0'; }
			else { tc = '1'; }
		}
		r1[i - 1] = tc;
	}
	for (int i = 1; i <= 8; i++) {
		if (r1[i - 1] == matrix5[i]) { r1[i - 1] = '0'; }
		else { r1[i - 1] = '1'; }
	}
	reverse(r1.begin(), r1.end());
	r1 = reverseGF(r1);
	return r1;
}

void RMyByteSub() {
	for (int i = 1; i <= textSize / 8; i++) {
		string t = "00000000";
		for (int j = 1; j <= 8; j++) {
			t[j - 1] = (text[(i - 1) * 8 + j]);
		}
		//cout << t << " ";
		t = RByteSub(t);
		//cout << t << " "<<endl;
		for (int j = 1; j <= 8; j++) {
			text[(i - 1) * 8 + j] = t[j - 1];
		}
	}
	//printCStar(text, 1, 129);
}

void RshiftRow() {

	string store[5][9];
	for (int i = 1; i <= textSize / 32; i++) {
		for (int j = 1; j <= 4; j++) {
			string temp = "";
			for (int k = 1; k <= 8; k++) {
				temp.push_back(text[(i - 1) * 32 + (j - 1) * 8 + k]);
			}
			store[j][i] = temp;
			//cout << j << " " << i << " " << temp << endl;
		}
	}
	//cout << endl;

	for (int i = 2; i <= 4; i++) {
		int cross = (textSize / 32) - shift[i - 1];
		vector<string>vs;
		vs.push_back("");
		for (int k = 1; k <= textSize / 32; k++) {
			vs.push_back(store[i][k]);
		}
		for (int k = 1; k <= textSize / 32; k++) {
			if (k + cross <= textSize / 32) {
				store[i][k] = vs[k + cross];
			}
			else {
				store[i][k] = vs[k + cross - textSize / 32];
			}
		}
	}
	//cout << endl;

	for (int i = 1; i <= textSize / 32; i++) {
		for (int j = 1; j <= 4; j++) {
			string s = store[j][i];
			for (int k = 1; k <= 8; k++) {
				text[(i - 1) * 32 + (j - 1) * 8 + k] = s[k - 1];
			}
			//cout << j << " " << i << " " << s << endl;
		}
	}
}

void RMixColumn(int col) {
	//cout << "col = " << col << endl;
	vector<string>vs;
	vector<string>vt;
	vector<string>rs;

	for (int i = 1; i <= 4; i++) {
		string temp;
		for (int j = 1; j <= 8; j++) {
			temp.push_back(text[(col - 1) * 32 + (i - 1) * 8 + j]);
			//int tempi = (col - 1) * 32 + (i - 1) * 8 + j;
			//char c = text[tempi];
			//char cc = text[1];
		}
		vs.push_back(temp);
		//cout << temp <<" ";
	}
	//cout << endl;
	for (int i = 1; i <= 4; i++) {
		vt.clear();
		for (int j = 1; j <= 4; j++) {
			vt.push_back(mulGF(matrix6[i][j], vs[j - 1]));
		}
		string temp = "00000000";
		for (int k = 1; k <= 4; k++) {
			temp = StringAddb2(temp, vt[k - 1]);
		}
		rs.push_back(temp);
	}

	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 8; j++) {
			text[(col - 1) * 32 + (i - 1) * 8 + j] = rs[i - 1][j - 1];
		}
		//cout << rs[i-1] <<" ";
	}
	//cout << endl;
}

void RMixColumn(KeyStore& ks) {
	//cout << "col = " << col << endl;
	vector<string>vs;
	vector<string>vt;
	vector<string>rs;
	vs.push_back(ks.l1);
	vs.push_back(ks.l2);
	vs.push_back(ks.l3);
	vs.push_back(ks.l4);
	for (int i = 1; i <= 4; i++) {
		vt.clear();
		for (int j = 1; j <= 4; j++) {
			vt.push_back(mulGF(matrix6[i][j], vs[j - 1]));
		}
		string temp = "00000000";
		for (int k = 1; k <= 4; k++) {
			temp = StringAddb2(temp, vt[k - 1]);
		}
		rs.push_back(temp);
	}
	ks.l1 = rs[0];
	ks.l2 = rs[1];
	ks.l3 = rs[2];
	ks.l4 = rs[3];
}

void RAddRoundKey(string s) {
	for (int i = 1; i <= textSize; i++) {
		if (text[i] == s[i - 1]) { text[i] = '0'; }
		else { text[i] = '1'; }
	}
}

void RKeyExpansion() {
	vks.clear();
	if (keySize / 32 <= 6) {
		for (int i = 0; i < keySize / 32; i++) {
			vector<string>tvs;
			for (int j = 1; j <= 4; j++) {
				string temp = "";
				for (int k = 1; k <= 8; k++) {
					temp.push_back(key[(i) * 32 + (j - 1) * 8 + k]);
				}
				tvs.push_back(temp);
			}
			KeyStore ks(tvs[0], tvs[1], tvs[2], tvs[3]);
			vks.push_back(ks);
		}
		for (int i = keySize / 32; i < (textSize / 32) * (Myround + 1); i++) {
			KeyStore temp = vks[i - 1];
			if ((i % (keySize / 32)) == 0) {
				RotByte(temp);
				temp.l1 = ByteSub(temp.l1);
				temp.l2 = ByteSub(temp.l2);
				temp.l3 = ByteSub(temp.l3);
				temp.l4 = ByteSub(temp.l4);
				string  s = GenerateRC(i / (keySize / 32));
				temp.l1 = StringAddb2(temp.l1, s);
				//cout << temp.l1 << " " << temp.l2 << " " << temp.l3 << " " << temp.l4 << endl;
			}
			KeyStore t = vks[i - keySize / 32];
			//cout << "temp:" << temp.l1 << " " << temp.l2 << " " << temp.l3 << " " << temp.l4 << endl;
			//cout << "t:" << t.l1 << " " << t.l2 << " " << t.l3 << " " << t.l4 << endl;
			string s1 = StringAddb2(temp.l1, t.l1);
			string s2 = StringAddb2(temp.l2, t.l2);
			string s3 = StringAddb2(temp.l3, t.l3);
			string s4 = StringAddb2(temp.l4, t.l4);
			KeyStore rs(s1, s2, s3, s4);
			//cout << s1 << " " << s2 << " " << s3 <<" "<< s4 << endl;
			vks.push_back(rs);
		}
	}
	else {
		for (int i = 0; i < keySize / 32; i++) {
			vector<string>tvs;
			for (int j = 1; j <= 4; j++) {
				string temp = "";
				for (int k = 1; k <= 8; k++) {
					temp.push_back(key[(i) * 32 + (j - 1) * 8 + k]);
				}
				tvs.push_back(temp);
			}
			KeyStore ks(tvs[0], tvs[1], tvs[2], tvs[3]);
			vks.push_back(ks);
		}
		for (int i = keySize / 32; i < (textSize / 32) * (Myround + 1); i++) {
			KeyStore temp = vks[i - 1];
			if ((i % (keySize / 32)) == 0) {
				RotByte(temp);
				temp.l1 = ByteSub(temp.l1);
				temp.l2 = ByteSub(temp.l2);
				temp.l3 = ByteSub(temp.l3);
				temp.l4 = ByteSub(temp.l4);
				string  s = GenerateRC(i / (keySize / 32));
				temp.l1 = StringAddb2(temp.l1, s);
			}
			else {
				if ((i % (keySize / 32)) == 4) {
					temp.l1 = ByteSub(temp.l1);
					temp.l2 = ByteSub(temp.l2);
					temp.l3 = ByteSub(temp.l3);
					temp.l4 = ByteSub(temp.l4);
				}
			}
			KeyStore t = vks[i - keySize / 32];
			string s1 = StringAddb2(temp.l1, t.l1);
			string s2 = StringAddb2(temp.l2, t.l2);
			string s3 = StringAddb2(temp.l3, t.l3);
			string s4 = StringAddb2(temp.l4, t.l4);
			KeyStore rs(s1, s2, s3, s4);
			//cout << s1 << " " << s2 << " " << s3 <<" "<< s4 << endl;
			vks.push_back(rs);
		}
	}
}

void RRound(string KeyS) {//col>=1
	RshiftRow();
	//cout << "after shiftRow  " << endl;
	//printCStar(text, 1, 129);

	RMyByteSub();
	//cout << "after bytesub  "<<endl;
	//printCStar(text, 1, 129);

	RAddRoundKey(KeyS);
	//cout << "after addRoundKey" << endl;
	//printCStar(text, 1, 129);

	for (int i = 1; i <= textSize / 32; i++) {
		RMixColumn(i);
	}
	//cout << "after mix column" << endl;
	//printCStar(text, 1, 129);

}
void RFinalRound(string KeyS) {
	RshiftRow();
	RMyByteSub();
	RAddRoundKey(KeyS);
}
void decrypt(TestData1 td) {
	getout(td);
	getkey(td);
	SetValue();
	RKeyExpansion();
	//test1();
	//cout << endl;
	//printCStar(key, 1, 129);
	string s = generateUsedKey(vks.size() - textSize / 32);
	//cout << s << endl;
	//printCStar(text, 1, 129);
	RAddRoundKey(s);
	//cout << "after add" << endl;
	//printCStar(text, 1, 129);
	for (int i = 1; i <= Myround; i++) {
		string s = generateUsedKey(vks.size() - ((i + 1) * textSize / 32));
		//cout << s << endl;
		if (i == Myround) { RFinalRound(s); break; }
		RRound(s);
	}
}
//------------------------------------------------ѩ������--------------------------------------------
void Avalanche() {
	cout << "����������ѩ��ЧӦ�Ĳ���" << endl;
	cout << "����ʹ�õ�����Ϊ��" << td1.text << endl;
	cout << "����ʹ�õ���ԿΪ��" << td1.key << endl;
	cout << "��������ظ��������Թ۲����ı任�ı�����" << endl;
	encrypt(td1);
	char* text0 = new char[129];
	memcpy(text0, text, 129);
	int count = 0;
	for (int i = 1; i <= 128; i++) {
		gettext(td1);
		if (text[i] == '0') { text[i] = '1'; }
		else { text[i] = '0'; }
		getkey(td1);
		SetValue();
		KeyExpansion();
		string s = generateUsedKey(0);
		AddRoundKey(s);
		for (int i = 1; i <= Myround; i++) {
			string s = generateUsedKey(i * textSize / 32);
			if (i == Myround) { FinalRound(s); break; }
			Round(s);
		}
		cout << "�ı��" << i << "λ��Ľ��Ϊ" << endl;
		CStar2HEX(text, 1, 129);
		cout << "��ԭ�������" << findDifference(text0, text, 1, 129) << "λ" << endl;;
		count += findDifference(text0, text, 1, 129);
	}
	double d = (double)count / 128.0;
	cout << "ͨ������ظ������ģ�ƽ���䶯������λ��Ϊ" << d << endl;
}
void Avalanche2() {
	cout << "������ͨ������ظ�����Կ������ѩ������" << endl;
	cout << "ʹ�õ�����Ϊ��" << td1.text << endl;
	cout << "ʹ�õ���ԿΪ��" << td1.key << endl;
	cout << "��������ظ�����Կ�Թ۲����ı任�ı�����" << endl;
	encrypt(td1);
	char* text0 = new char[129];
	memcpy(text0, text, 129);
	int count = 0;
	for (int i = 1; i <= 128; i++) {
		gettext(td1);
		getkey(td1);
		if (key[i] == '0') { key[i] = '1'; }
		else { key[i] = '0'; }
		SetValue();
		KeyExpansion();
		string s = generateUsedKey(0);
		AddRoundKey(s);
		for (int i = 1; i <= Myround; i++) {
			string s = generateUsedKey(i * textSize / 32);
			if (i == Myround) { FinalRound(s); break; }
			Round(s);
		}
		cout << "�ı��" << i << "λ�������Ϊ" << endl;
		CStar2HEX(text, 1, 129);
		cout << "��ԭ�������" << findDifference(text0, text, 1, 129) << "λ" << endl;;
		count += findDifference(text0, text, 1, 129);
	}
	double d = (double)count / 128.0;
	cout << "ͨ������ظ������ģ�ƽ���䶯������λ��Ϊ" << d << endl;
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
void Interaction() {
	cout << "����������AES�ļӽ���" << endl;
	cout << "�鿴ʾ���ļӽ��ܽ�����룺1" << endl;
	cout << "�������������룺2" << endl;
	cout << "�������������룺3" << endl;
	cout << "�鿴ѩ��ЧӦ�����룺4" << endl;
	int choose1;
	cin >> choose1;
	if (choose1 == 1) {
		cout << "ʾ������ʦ�ṩ������AES�����" << endl;
		cout << "����չʾAES����" << endl;
		cout << "���ĵĳ���Ϊ" << td1.textSize << "����Կ�ĳ���Ϊ" << td1.keySize << endl;
		cout << "��������Ϊ" << td1.text << endl;
		cout << "��Կ����Ϊ" << td1.key << endl;
		cout << "���ڼ���...." << endl;
		encrypt(td1);
		cout << "���ܽ���Ķ����Ʊ�ʾΪ" << endl;
		printCStar(text, 1, 129);
		cout << endl;
		CStar2HEX(text, 1, 129);
		cout << endl;

		cout << "����չʾAES����" << endl;
		cout << "���ĵĳ���Ϊ" << td2.textSize << "����Կ�ĳ���Ϊ" << td2.keySize << endl;
		cout << "���ĵ�����Ϊ" << td2.out << endl;
		cout << "��Կ������Ϊ" << td2.key << endl;
		cout << "���ڽ���...." << endl;
		decrypt(td2);
		cout << "���ܽ���Ķ����Ʊ�ʾΪ" << endl;
		printCStar(text, 1, 129);
		cout << endl;
		CStar2HEX(text, 1, 129);
		cout << endl;
	}
	if (choose1 == 2) {
		cout << "������м������㣬����ϸ�Ķ����򲢽�������¼��" << endl;
		cout << "���������ĳ��ȣ����ĳ��ȿ�ѡ��Ϊ?128/192/256" << endl;
		int MytextSize; cin >> MytextSize;
		cout << "��������Կ���ȣ���Կ���ȿ�ѡ��Ϊ128/192/256" << endl;
		int MykeySize; cin >> MykeySize;
		getchar();
		cout << "����������" << endl;
		cout << "���ĵ������ʽΪ������128λΪ����0001, 0001, 01a1, 98af, da78, 1734, 8615, 3566" << endl;
		string Mytext; getline(cin, Mytext);
		cout << "��������Կ" << endl;
		cout << "��Կ�������ʽΪ������128λΪ����0001, 2001, 7101, 98ae, da79, 1714, 6015, 3594" << endl;
		string Mykey; getline(cin, Mykey);
		TestData1 td3(MytextSize, MykeySize, Mytext, Mykey);
		cout << "MyText=" << Mytext << endl;
		cout << "MyKey=" << Mykey << endl;
		cout << "���ڼ���..." << endl;
		encrypt(td3);
		cout << "���ܺ�Ķ����Ʊ�ʾΪ" << endl;
		printCStar(text, 1, textSize + 1);
		cout << "���ܺ��ʮ�����Ʊ�ʾΪ" << endl;
		CStar2HEX(text, 1, textSize + 1);
	}
	if (choose1 == 3) {
		cout << "������н������㣬����ϸ�Ķ����򲢽�������¼��" << endl;
		cout << "���������ĳ��ȣ����ĳ��ȿ�ѡ��Ϊ?128/192/256" << endl;
		int MytextSize; cin >> MytextSize;
		cout << "��������Կ���ȣ���Կ���ȿ�ѡ��Ϊ128/192/256" << endl;
		int MykeySize; cin >> MykeySize;
		getchar();
		cout << "����������" << endl;
		cout << "���ĵ������ʽΪ������128λΪ����6cdd, 596b, 8f56, 42cb, d23b, 4798, 1a65, 422a" << endl;
		string Mytext; getline(cin, Mytext);
		cout << "��������Կ" << endl;
		cout << "��Կ�������ʽΪ������128λΪ����0001, 2001, 7101, 98ae, da79, 1714, 6015, 3594" << endl;
		string Mykey; getline(cin, Mykey);
		TestData1 td3(MytextSize, MykeySize, Mytext, Mykey, Mytext);
		cout << "MyText=" << Mytext << endl;
		cout << "MyKey=" << Mykey << endl;
		cout << "���ڽ���..." << endl;
		cout << endl;
		decrypt(td3);
		cout << "���ܺ�Ķ����Ʊ�ʾΪ" << endl;
		printCStar(text, 1, textSize + 1);
		cout << "���ܺ��ʮ�����Ʊ�ʾΪ" << endl;
		CStar2HEX(text, 1, textSize + 1);
	}
	if (choose1 == 4) {
		Avalanche();
		Avalanche2();
	}
	cout << "��л����ʹ��" << endl;
}

string OriginKey = "2b7e151628aed2a6abf7158809cf4f3c";
string AppendStringzero(string s) {
	string ss = s;
	while (ss.size() < 32) {
		ss.push_back('0');
	}
	return ss;
}
string AppendStringdh(string s) {
	string ret = "";
	for (int i = 0; i < s.size(); i+=4) {
		string t = s.substr(0, 4);
		t.push_back('��');
		ret.append(t);
	}
	ret.pop_back();
	return ret;
}
string Hex2Bin(string s) {
	string ret;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == '0') { ret.append("0000"); }
		if (s[i] == '1') { ret.append("0001"); }
		if (s[i] == '2') { ret.append("0010"); }
		if (s[i] == '3') { ret.append("0011"); }
		if (s[i] == '4') { ret.append("0100"); }
		if (s[i] == '5') { ret.append("0101"); }
		if (s[i] == '6') { ret.append("0110"); }
		if (s[i] == '7') { ret.append("0111"); }
		if (s[i] == '8') { ret.append("1000"); }
		if (s[i] == '9') { ret.append("1001"); }
		if (s[i] == 'a' || s[i] == 'A') { ret.append("1010"); }
		if (s[i] == 'b' || s[i] == 'B') { ret.append("1011"); }
		if (s[i] == 'c' || s[i] == 'C') { ret.append("1100"); }
		if (s[i] == 'd' || s[i] == 'D') { ret.append("1101"); }
		if (s[i] == 'e' || s[i] == 'E') { ret.append("1110"); }
		if (s[i] == 'f' || s[i] == 'F') { ret.append("1111"); }
	}
	return ret;
}
string Bin2Hex(string s) {
	if (s.size() % 4 != 0) {
		reverse(s.begin(), s.end());
		for (int i = 1; i <= 4 - (s.size() % 4); i++) {
			s.append(string(1, '0'));
		}
		reverse(s.begin(), s.end());
	}
	string ret;
	for (int i = 0; i < s.size(); i += 4) {
		if (s[i] == '0' && s[i + 1] == '0' && s[i + 2] == '0' && s[i + 3] == '0') { ret.append(string(1, '0')); continue; }
		if (s[i] == '0' && s[i + 1] == '0' && s[i + 2] == '0' && s[i + 3] == '1') { ret.append(string(1, '1')); continue; }
		if (s[i] == '0' && s[i + 1] == '0' && s[i + 2] == '1' && s[i + 3] == '0') { ret.append(string(1, '2')); continue; }
		if (s[i] == '0' && s[i + 1] == '0' && s[i + 2] == '1' && s[i + 3] == '1') { ret.append(string(1, '3')); continue; }
		if (s[i] == '0' && s[i + 1] == '1' && s[i + 2] == '0' && s[i + 3] == '0') { ret.append(string(1, '4')); continue; }
		if (s[i] == '0' && s[i + 1] == '1' && s[i + 2] == '0' && s[i + 3] == '1') { ret.append(string(1, '5')); continue; }
		if (s[i] == '0' && s[i + 1] == '1' && s[i + 2] == '1' && s[i + 3] == '0') { ret.append(string(1, '6')); continue; }
		if (s[i] == '0' && s[i + 1] == '1' && s[i + 2] == '1' && s[i + 3] == '1') { ret.append(string(1, '7')); continue; }
		if (s[i] == '1' && s[i + 1] == '0' && s[i + 2] == '0' && s[i + 3] == '0') { ret.append(string(1, '8')); continue; }
		if (s[i] == '1' && s[i + 1] == '0' && s[i + 2] == '0' && s[i + 3] == '1') { ret.append(string(1, '9')); continue; }
		if (s[i] == '1' && s[i + 1] == '0' && s[i + 2] == '1' && s[i + 3] == '0') { ret.append(string(1, 'A')); continue; }
		if (s[i] == '1' && s[i + 1] == '0' && s[i + 2] == '1' && s[i + 3] == '1') { ret.append(string(1, 'B')); continue; }
		if (s[i] == '1' && s[i + 1] == '1' && s[i + 2] == '0' && s[i + 3] == '0') { ret.append(string(1, 'C')); continue; }
		if (s[i] == '1' && s[i + 1] == '1' && s[i + 2] == '0' && s[i + 3] == '1') { ret.append(string(1, 'D')); continue; }
		if (s[i] == '1' && s[i + 1] == '1' && s[i + 2] == '1' && s[i + 3] == '0') { ret.append(string(1, 'E')); continue; }
		if (s[i] == '1' && s[i + 1] == '1' && s[i + 2] == '1' && s[i + 3] == '1') { ret.append(string(1, 'F')); continue; }
	}
	return ret;
}
//ģ2^32�η��ļӷ��������޶�a b������32λ��
//����˵�н�λֱ�������Ϳ�����
string stringADD(string a, string b) {
	if (a.size() != 128 || b.size() != 128) {
		cout << "�Ƿ��ļӷ�" << endl;
		string s;
		return s;
	}
	string mya(a);
	string myb(b);
	string ret;
	for (int i = 0; i < 128; i++) {
		if (mya[i] == '0' && myb[i] == '0') { ret.push_back('0'); continue; }
		if (mya[i] == '0' && myb[i] == '1') { ret.push_back('1'); continue; }
		if (mya[i] == '1' && myb[i] == '0') { ret.push_back('1'); continue; }
		if (mya[i] == '1' && myb[i] == '1') { ret.push_back('0'); continue; }
	}
	return ret;
}

//������Ҫ���ܵ�16�����ַ���
string useAESencrypt(string s) {
	if (s.size() <= 32) {
		if (s.size() < 32) {
			s = AppendStringzero(s);
		}
		//����Ϊֹ������һ��128λ���������ڰѶ��ż���
		//s = AppendStringdh(s);
		string keys = OriginKey;
		cout << "ֻ��Ҫһ�μ��ܼ���" << endl;
		cout << "����Ϊ" << s << endl;
		cout << "��ԿΪ" << keys << endl;
		cout << keys << endl;
		TestData1 mytd(128, 128, s, keys);
		encrypt(mytd);
		string ret = GetCstarHex(text, 1, 129);
		cout << "���ܽ��Ϊ" << ret << endl;
		return ret;
	}
	else {
		vector<string>vs;
		string ret="";
		string lastsecret = "";
		string keynow = OriginKey;
		//�и�
		for(int i=0;i<s.size();i+=32){
			string temp = s.substr(i, 32);
			vs.push_back(temp);
		}
		//����
		for (int i = 0; i < vs.size(); i++) {
			vs[i] = AppendStringzero(vs[i]);
		}
		cout << "��Ҫ" << vs.size() << "�μ���" << endl;
		for (int i = 0; i < vs.size(); i++) {
			if (i == 0) {
				cout << "��һ�μ�������Ϊ" << vs[i] << endl;
				cout << "��һ�μ�����ԿΪ" << keynow << endl;
				TestData1 mytd(128, 128, vs[i], keynow);
				encrypt(mytd);
				//���ܺ�ĳ�Ϊ��temp
				string temp = GetCstarHex(text, 1, 129);
				cout << "��һ�μ�������Ϊ" << temp << endl;
				ret.append(temp);
				lastsecret = temp;
			}
			else {
				//CBC
				string a = Hex2Bin(vs[i]);
				string b = Hex2Bin(lastsecret);
				string t = stringADD(a, b);
				t = Bin2Hex(t);
				cout << "��" << i + 1 << "�μ�������Ϊ" << t << endl;
				cout << "��" << i + 1 << "�μ�����ԿΪ" << keynow << endl;
				TestData1 mytd(128, 128, t, keynow);
				encrypt(mytd);
				//���ܺ�ĳ�Ϊ��temp
				string temp = GetCstarHex(text, 1, 129);
				cout << "��" << i + 1 << "�μ��ܽ��Ϊ" << temp << endl;
				ret.append(temp);
				lastsecret = temp;
			}
		}
		return ret;
	}
}
string useAESdecrypt(string s) {
	if (s.size() <= 32) {
		if (s.size() < 32) {
			s = AppendStringzero(s);
		}
		string keys = OriginKey;
		cout << s << endl;
		cout << keys << endl;
		/*memset(text, 0, 129);
		memset(key, 0, 129);*/
		TestData1 mytd(128, 128,s,keys,s);
		decrypt(mytd);
		string ret = GetCstarHex(text, 1, 129);
		cout << "ֻ��Ҫһ�ν��ܼ���" << endl;
		cout << "����Ϊ" << s << endl;
		cout << "��ԿΪ" << keys << endl;
		cout << "���ܺ�����Ϊ" << ret << endl;
		return ret;
	}
	else {
		vector<string>vs;
		string ret;
		for (int i = 0; i < s.size(); i+=32) {
			string temp = s.substr(i, 32);
			vs.push_back(temp);
		}
		cout << "��Ҫ" << vs.size() << "�ν���" << endl;
		for(int i=0;i<vs.size();i++){
			if (i == 0) {
				TestData1 mytd(128, 128, vs[i], OriginKey, vs[i]);
				decrypt(mytd);
				string temp = GetCstarHex(text, 1, 129);
				cout << "��" << i + 1 << "������Ϊ" << vs[i] << endl;
				cout << "��" << i + 1 << "����ԿΪ" << OriginKey << endl;
				cout << "��" << i + 1 << "������Ϊ" << temp << endl;
				ret.append(temp);
			}
			else {
				TestData1 mytd(128, 128, vs[i], OriginKey, vs[i]);
				decrypt(mytd);
				string temp = GetCstarHex(text, 1, 129);
				string a = Hex2Bin(temp);
				string b = Hex2Bin(vs[i - 1]);
				string t = stringADD(a, b);
				t = Bin2Hex(t);
				cout << "��" << i + 1 << "������Ϊ" << vs[i] << endl;
				cout << "��" << i + 1 << "����ԿΪ" << OriginKey << endl;
				cout << "��" << i + 1 << "������Ϊ" << t << endl;
				ret.append(t);
			}
		}
		return ret;
	}
}
