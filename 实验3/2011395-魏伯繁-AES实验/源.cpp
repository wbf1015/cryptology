#include<iostream>
#include<cmath>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;
int textSize;//���ĳ���
int keySize;//��Կ����
char* text;//���Ļ������ĵ�����
char* key;//��Կ����
char* out;//���
int Myround;//����������
int shift[4]{ 0 };//��λʱ��λ��
string mx = "100011011";
class TestData1 {
public:
	int textSize = 128;
	int keySize = 128;
	string text = "0001, 0001, 01a1, 98af, da78, 1734, 8615, 3566";
	string key = "0001, 2001, 7101, 98ae, da79, 1714, 6015, 3594";
	string out = "6cdd, 596b, 8f56, 42cb, d23b, 4798, 1a65, 422a";
	TestData1(int ts, int ks, string text, string key, string out="") {
		this->textSize = ts;
		this->keySize = ks;
		this->text = text;
		this->key = key;
		this->out = out;
	}
	TestData1() {};
}td1;
TestData1 td2(128, 128, "3243, f6a8, 885a, 308d, 3131, 98a2, e037, 0734", "2b7e, 1516, 28ae, d2a6, abf7, 1588, 09cf, 4f3c", "3925, 841d, 02dc, 09fb, dc11, 8597, 196a, 0b32");
//�ֽ��滻�ļ��ܾ���
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
//�ֽ��滻ʹ�õľ���
char matrix2[9]{ '0','1','1','0','0','0','1','1','0' };
//�л��ʹ�õľ���
string matrix3[5][5]{
	{"","","","",""},
	{"","00000010","00000011","00000001","00000001"},
	{"","00000001","00000010","00000011","00000001"},
	{"","00000001","00000001","00000010","00000011"},
	{"","00000011","00000001","00000001","00000010"},
};
//�ֽ��滻ʹ�õĽ��ܾ���
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
//���ܲ������л�Ͼ���
string matrix6[5][5]{
	{"","","","",""},
	{"","00001110","00001011","00001101","00001001"},
	{"","00001001","00001110","00001011","00001101"},
	{"","00001101","00001001","00001110","00001011"},
	{"","00001011","00001101","00001001","00001110"},
};
class KeyStore {//�������һ��
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
//2����ת��Ϊ16����
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
//16����ת��Ϊ2����
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
//��ӡchar*
void printCStar(char* c, int start, int end) {
	for (int i = start; i < end; i++) {
		cout << c[i];
		if (i % 8 == 0) { cout << endl; }
	}cout << endl;
}
void CStar2HEX(char* c, int start, int end) {
	int count = 0;
	for (int i = start; i < end; i+=4) {
		string s = "";
		s.push_back(c[i]);
		s.push_back(c[i+1]);
		s.push_back(c[i+2]);
		s.push_back(c[i+3]);
		cout << Binary2Hex(s);
		count++;
		if (count % 4 == 0) { cout << ","; }
	}
	cout << endl;
}
int findDifference(char* c1, char* c2, int start, int end) {
	int count = 0;
	for (int i = start; i < end; i++) {
		if (c1[i] == c2[i]) { count++; }
	}
	return count;
}
//-------------------------------------------------------٤�������ϵ�����-----------------------------------------------
//����������
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
//��string��ȡ��Ӧ��int
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
//��Ӧλ���
char CharAddb(char a, char b) {
	if (a == '0' && b == '0') { return '0'; }
	if (a == '0' && b == '1') { return '1'; }
	if (a == '1' && b == '0') { return '1'; }
	if (a == '1' && b == '1') { return '0'; }
}
//û�н�λ�ļӷ�
string StringAddb2(string a, string b) {
	string r = "00000000";
	for (int i = 0; i < 8; i++) {
		r[i] = CharAddb(a[i], b[i]);
	}
	return r;
}
//��٤�������ϵļӷ�(�мӷ�)
string StringAddb(string a, string b) {
	int la = a.length();//�õ�a�ĳ���
	int lb = b.length();//�õ�b�ĳ���
	int l;
	vector<char>ls;//������string��vector
	vector<char>ss;//����ε�string��vector
	vector<char>rs;//����ַ���
	if (la >= lb) {//a�Ǹ�����
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
//�൱����ȡģ����
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
//٤�������ϵĳ˷�����
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
	if (a == "00000000") { return "00000000"; }//0ӳ�䵽�Լ�
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
//-------------------------------------------------------٤�������ϵ�����-----------------------------------------------
//��Ҫ�ò�������2ֱ�Ӱ�TestData1�ĳ�TestData2����
void gettext(TestData1 td) {
	textSize = td.textSize;
	int textlength = td.textSize;
	text = new char[textlength + 1];
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
void getout(TestData1 td) {
	textSize = td.textSize;
	int textlength = td.textSize;
	text = new char[textlength + 1];
	string s = td.out;
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
void SetValue() {
	//�����õ�������
	if (textSize == 128 && keySize == 128) { Myround = 10; }
	if (textSize == 192 && keySize == 128) { Myround = 12; }
	if (textSize == 256 && keySize == 128) { Myround = 14; }
	if (textSize == 128 && keySize == 192) { Myround = 12; }
	if (textSize == 192 && keySize == 192) { Myround = 12; }
	if (textSize == 256 && keySize == 192) { Myround = 12; }
	if (textSize == 128 && keySize == 256) { Myround = 14; }
	if (textSize == 192 && keySize == 256) { Myround = 14; }
	if (textSize == 256 && keySize == 256) { Myround = 14; }
	//�������ƶ���λ����
	if (textSize == 128) { shift[1] = 1; shift[2] = 2; shift[3] = 3; }
	if (textSize == 192) { shift[1] = 1; shift[2] = 2; shift[3] = 3; }
	if (textSize == 256) { shift[1] = 1; shift[2] = 3; shift[3] = 4; }
}
//------------------------------------------------��������--------------------------------------------
//�ֽ��滻
string ByteSub(string s) {
	string t = reverseGF(s);//�õ���Ӧ�ĳ˷���Ԫ
	string r1 = "00000000";
	for (int i = 1; i <= 8; i++) {
		//ÿһ�����ѭ�����һ������
		char tc = '0';
		for (int j = 1; j <= 8; j++) {
			char tcc;
			if (matrix1[i][j] == '0' || t[7 - (j - 1)] == '0') { tcc = '0'; }//���ﰴ�����ϵĸ���һ�£���Ҳ��֪��ΪʲôҪ��ô��
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
//��text�е�����Ԫ������ֽ��滻
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
//����λ
void shiftRow() {
	//����������ʽ�Ĵ洢��ʽ
	string store[5][9];
	for (int i = 1; i <= textSize / 32; i++) {//������
		for (int j = 1; j <= 4; j++) {//������
			string temp = "";
			for (int k = 1; k <= 8; k++) {
				temp.push_back(text[(i - 1) * 32 + (j - 1) * 8 + k]);
			}
			store[j][i] = temp;
			//cout << j << " " << i << " " << temp << endl;
		}
	}
	//cout << endl;
	//�Ե�2-4�н�������λ
	for (int i = 2; i <= 4; i++) {
		int cross = shift[i - 1];//λ�Ƶ�λ��
		vector<string>vs;//����һ�е������ַ������ȱ���
		vs.push_back("");//ռס��λ
		for (int k = 1; k <= textSize / 32; k++) {
			vs.push_back(store[i][k]);
		}
		for (int k = 1; k <= textSize / 32; k++) {//��λ
			if (k + cross <= textSize / 32) {
				store[i][k] = vs[k + cross];
			}
			else {
				store[i][k] = vs[k + cross - textSize / 32];
			}
		}
	}
	//cout << endl;
	//��store�е�Ԫ��д�ص�text��
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
//�л��
void MixColumn(int col) {
	//cout << "col = " << col << endl;
	vector<string>vs;//һ��ʼ������text�е�һ��
	vector<string>vt;
	vector<string>rs;
	//ȡ��text�ļ���col�еĶ�Ӧ��4���ֽ�
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
	//ѭ���Ĵ�����л�Ϻ���ĸ��ֽ�
	for (int i = 1; i <= 4; i++) {
		vt.clear();
		for (int j = 1; j <= 4; j++) {
			vt.push_back(mulGF(matrix3[i][j], vs[j - 1]));
		}
		string temp = "00000000";
		for (int k = 1; k <= 4; k++) {
			temp = StringAddb2(temp, vt[k - 1]);//��vs�е��������ۼ�
		}
		rs.push_back(temp);
	}
	//�ѽ�����ȥ
	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 8; j++) {
			text[(col - 1) * 32 + (i - 1) * 8 + j] = rs[i - 1][j - 1];
		}
		//cout << rs[i-1] <<" ";
	}
	//cout << endl;
}
//��Կ��
void AddRoundKey(string s) {
	for (int i = 1; i <= textSize; i++) {
		if (text[i] == s[i - 1]) { text[i] = '0'; }
		else { text[i] = '1'; }
	}
}
//��Կ������RotByte��ʹ��
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
//��Կ��չ
void KeyExpansion() {
	vks.clear();
	//��Ԫ��Կ�Ž�ȥ
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
	//��ҪŪ��ô���г���
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
		}//����temp
		KeyStore t = vks[i - keySize / 32];//ȡ��ǰ���һ�����ڵĶ�Ӧλ�õ���
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
//ע��vks�Ǵӵ�0����ʼ,��[start����ʼȡ
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
	gettext(td);//��ʼ������
	getkey(td);//��ʼ������
	SetValue();//��ʼ����������Ϣ
	KeyExpansion();//�������Կ�ĳ�ʼ��
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
//------------------------------------------------��������--------------------------------------------
//------------------------------------------------��������--------------------------------------------
//���ܲ������ֽ��滻
string RByteSub(string s) {
	string t = s;//�õ���Ӧ�ĳ˷���Ԫ
	string r1 = "00000000";
	for (int i = 1; i <= 8; i++) {
		//ÿһ�����ѭ�����һ������
		char tc = '0';
		for (int j = 1; j <= 8; j++) {
			char tcc;
			if (matrix4[i][j] == '0' || t[7 - (j - 1)] == '0') { tcc = '0'; }//���ﰴ�����ϵĸ���һ�£���Ҳ��֪��ΪʲôҪ��ô��
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
//���ܲ������ֽ��滻
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
//����λ����任
void RshiftRow() {
	//����������ʽ�Ĵ洢��ʽ
	string store[5][9];
	for (int i = 1; i <= textSize / 32; i++) {//������
		for (int j = 1; j <= 4; j++) {//������
			string temp = "";
			for (int k = 1; k <= 8; k++) {
				temp.push_back(text[(i - 1) * 32 + (j - 1) * 8 + k]);
			}
			store[j][i] = temp;
			//cout << j << " " << i << " " << temp << endl;
		}
	}
	//cout << endl;
	//�Ե�2-4�н�������λ
	for (int i = 2; i <= 4; i++) {
		int cross =(textSize/32)-shift[i - 1];//λ�Ƶ�λ��
		vector<string>vs;//����һ�е������ַ������ȱ���
		vs.push_back("");//ռס��λ
		for (int k = 1; k <= textSize / 32; k++) {
			vs.push_back(store[i][k]);
		}
		for (int k = 1; k <= textSize / 32; k++) {//��λ
			if (k + cross <= textSize / 32) {
				store[i][k] = vs[k + cross];
			}
			else {
				store[i][k] = vs[k + cross - textSize / 32];
			}
		}
	}
	//cout << endl;
	//��store�е�Ԫ��д�ص�text��
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
//���ܲ������л��
void RMixColumn(int col) {
	//cout << "col = " << col << endl;
	vector<string>vs;//һ��ʼ������text�е�һ��
	vector<string>vt;
	vector<string>rs;
	//ȡ��text�ļ���col�еĶ�Ӧ��4���ֽ�
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
	//ѭ���Ĵ�����л�Ϻ���ĸ��ֽ�
	for (int i = 1; i <= 4; i++) {
		vt.clear();
		for (int j = 1; j <= 4; j++) {
			vt.push_back(mulGF(matrix6[i][j], vs[j - 1]));
		}
		string temp = "00000000";
		for (int k = 1; k <= 4; k++) {
			temp = StringAddb2(temp, vt[k - 1]);//��vs�е��������ۼ�
		}
		rs.push_back(temp);
	}
	//�ѽ�����ȥ
	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 8; j++) {
			text[(col - 1) * 32 + (i - 1) * 8 + j] = rs[i - 1][j - 1];
		}
		//cout << rs[i-1] <<" ";
	}
	//cout << endl;
}
//��������Կ���ɵ��л��
void RMixColumn(KeyStore &ks) {
	//cout << "col = " << col << endl;
	vector<string>vs;//һ��ʼ������text�е�һ��
	vector<string>vt;
	vector<string>rs;
	vs.push_back(ks.l1);
	vs.push_back(ks.l2);
	vs.push_back(ks.l3);
	vs.push_back(ks.l4);
	//cout << endl;
	//ѭ���Ĵ�����л�Ϻ���ĸ��ֽ�
	for (int i = 1; i <= 4; i++) {
		vt.clear();
		for (int j = 1; j <= 4; j++) {
			vt.push_back(mulGF(matrix6[i][j], vs[j - 1]));
		}
		string temp = "00000000";
		for (int k = 1; k <= 4; k++) {
			temp = StringAddb2(temp, vt[k - 1]);//��vs�е��������ۼ�
		}
		rs.push_back(temp);
	}
	ks.l1 = rs[0];
	ks.l2 = rs[1];
	ks.l3 = rs[2];
	ks.l4 = rs[3];
}
//�����㷨����Կ�ӣ��ͼ����㷨��û������
void RAddRoundKey(string s) {
	for (int i = 1; i <= textSize; i++) {
		if (text[i] == s[i - 1]) { text[i] = '0'; }
		else { text[i] = '1'; }
	}
}
//����ʱ����Կ��չ����Ҫ������vks��һ��reverse
void RKeyExpansion() {
	vks.clear();
	if (keySize / 32 <= 6) {//keySizeΪ128 192��ʱ��
		//��Ԫ��Կ�Ž�ȥ
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
		//��ҪŪ��ô���г���
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
			}//����temp
			KeyStore t = vks[i - keySize / 32];//ȡ��ǰ���һ�����ڵĶ�Ӧλ�õ���
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
	else {//keySizeΪ256��ʱ��
		//��Ԫ��Կ�Ž�ȥ
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
		//��ҪŪ��ô���г���
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
			}//����temp
			else {
				if ((i % (keySize / 32)) == 4) {
					temp.l1 = ByteSub(temp.l1);
					temp.l2 = ByteSub(temp.l2);
					temp.l3 = ByteSub(temp.l3);
					temp.l4 = ByteSub(temp.l4);
				}
			}
			KeyStore t = vks[i - keySize / 32];//ȡ��ǰ���һ�����ڵĶ�Ӧλ�õ���
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
}
//����ʱ���ֺ���
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
	getout(td);//��ʼ������
	getkey(td);//��ʼ����Կ
	SetValue();//��ʼ����������Ϣ
	RKeyExpansion();//�������Կ�ĳ�ʼ��
	//test1();
	//cout << endl;
	//printCStar(key, 1, 129);
	string s = generateUsedKey(vks.size()-textSize/32);
	//cout << s << endl;
	//printCStar(text, 1, 129);
	RAddRoundKey(s);
	//cout << "after add" << endl;
	//printCStar(text, 1, 129);
	for (int i = 1; i <= Myround; i++) {
		string s = generateUsedKey(vks.size()-((i+1) * textSize / 32));
		//cout << s << endl;
		if (i == Myround) { RFinalRound(s); break; }
		RRound(s);
	}
}
//------------------------------------------------��������--------------------------------------------
//------------------------------------------------ѩ��ЧӦ--------------------------------------------
void Avalanche() {
	cout << "���濪ʼѩ��ЧӦ���ԣ�����ʹ�õ�����Ϊ��" << endl;
	cout << "����Ϊ��" << td1.text << endl;
	cout << "��ԿΪ��" << td1.key << endl;
	cout << "��������ı����ĵ�128������λ���鿴���ĵĸı����" << endl;
	encrypt(td1);
	//��td1�ļ��ܽ��������text0��
	char* text0 = new char[129];
	memcpy(text0, text, 129);
	int count=0;
	for (int i = 1; i <= 128; i++) {
		//ֱ�Ӱ�encrypt�ĺ�������copy����
		gettext(td1);//��ʼ������
		if (text[i] == '0') { text[i] = '1'; }
		else { text[i] = '0'; }
		getkey(td1);//��ʼ������
		SetValue();//��ʼ����������Ϣ
		KeyExpansion();//�������Կ�ĳ�ʼ��
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
		cout << "�ı��" << i << "λ�Ľ��Ϊ" << endl;
		CStar2HEX(text, 1, 129);
		cout << "�ı���" << findDifference(text0, text, 1, 129) << "λ" << endl;;
		count += findDifference(text0, text, 1, 129);
	}
	double d = (double)count / 128.0;
	cout << "��128�ε���������ظı��У�ƽ��ÿ�����ĸı�ı�����Ϊ" << d << endl;
}
void Avalanche2() {
	cout << "���濪ʼѩ��ЧӦ���ԣ�����ʹ�õ�����Ϊ��" << endl;
	cout << "����Ϊ��" << td1.text << endl;
	cout << "��ԿΪ��" << td1.key << endl;
	cout << "������������ı���Կ��128������λ���鿴���ĵĸı����" << endl;
	encrypt(td1);
	//��td1�ļ��ܽ��������text0��
	char* text0 = new char[129];
	memcpy(text0, text, 129);
	int count = 0;
	for (int i = 1; i <= 128; i++) {
		//ֱ�Ӱ�encrypt�ĺ�������copy����
		gettext(td1);//��ʼ������
		getkey(td1);//��ʼ������
		if (key[i] == '0') { key[i] = '1'; }
		else { key[i] = '0'; }
		SetValue();//��ʼ����������Ϣ
		KeyExpansion();//�������Կ�ĳ�ʼ��
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
		cout << "�ı��" << i << "λ�Ľ��Ϊ" << endl;
		CStar2HEX(text, 1, 129);
		cout << "�ı���" << findDifference(text0, text, 1, 129) << "λ" << endl;;
		count += findDifference(text0, text, 1, 129);
	}
	double d = (double)count / 128.0;
	cout << "��128�ε���Կ����ظı��У�ƽ��ÿ�����ĸı�ı�����Ϊ" << d << endl;
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
	cout << "����������AES�㷨�ļӽ���" << endl;
	cout << "�鿴�������������룺1" << endl;
	cout << "������������룺2" << endl;
	cout << "������������룺3" << endl;
	cout << "����ѩ��ЧӦ��⣺4" << endl;
	int choose1;
	cin >> choose1;
	if (choose1 == 1) {
		cout << "չʾ����AES�ļӽ�������" << endl;
		cout << "����չʾ���ܵ�����" << endl;
		cout << "���ĳ�Ϊ" << td1.textSize << ",��Կ��Ϊ" << td1.keySize << endl;
		cout << "����Ϊ" << td1.text << endl;
		cout << "��ԿΪ" << td1.key << endl;
		cout << "���ڼ���...." << endl;
		encrypt(td1);
		cout << "���ܽ��Ϊ��" << endl;
		printCStar(text, 1, 129);
		cout << endl;
		CStar2HEX(text, 1, 129);
		cout << endl;

		cout << "������չʾ���ܵ�����" << endl;
		cout << "���ĳ�Ϊ" << td2.textSize << ",��Կ��Ϊ" << td2.keySize << endl;
		cout << "����Ϊ" << td2.text << endl;
		cout << "��ԿΪ" << td2.key << endl;
		cout << "���ڽ���...." << endl;
		decrypt(td2);
		cout << "���ܽ��Ϊ��" << endl;
		printCStar(text, 1, 129);
		cout << endl;
		CStar2HEX(text, 1, 129);
		cout << endl;
	}
	if (choose1 == 2) {
		cout << "���ܲ������밴��Ҫ�󼰸�ʽ�������" << endl;
		cout << "���������ĳ��ȣ���λΪ���أ�����ѡֵΪ128/192/256" << endl;
		int MytextSize; cin >> MytextSize;
		cout << "��������Կ���ȣ���λΪ���أ�����ѡֵΪ128/192/256" << endl;
		int MykeySize; cin >> MykeySize;
		getchar();
		cout << "��������������" << endl;
		cout << "�����ʽΪ����128λΪ������0001, 0001, 01a1, 98af, da78, 1734, 8615, 3566" << endl;
		string Mytext; getline(cin, Mytext);
		cout << "��������Կ����" << endl;
		cout << "�����ʽΪ����128λΪ������0001, 2001, 7101, 98ae, da79, 1714, 6015, 3594" << endl;
		string Mykey; getline(cin, Mykey);
		TestData1 td3(MytextSize, MykeySize, Mytext, Mykey);
		cout<<"MyText=" << Mytext << endl;
		cout << "MyKey=" << Mykey << endl;
		cout << "���ڼ���..." << endl;
		encrypt(td3);
		cout << "���ܽ���Ķ����Ʊ�ʾΪ��" << endl;
		printCStar(text, 1, textSize + 1);
		cout << "���ܽ����16���Ʊ�ʾΪ��" << endl;
		CStar2HEX(text, 1, textSize + 1);
	}
	if (choose1 == 3) {
		cout << "���ܲ������밴��Ҫ�󼰸�ʽ�������" << endl;
		cout << "���������ĳ��ȣ���λΪ���أ�����ѡֵΪ128/192/256" << endl;
		int MytextSize; cin >> MytextSize;
		cout << "��������Կ���ȣ���λΪ���أ�����ѡֵΪ128/192/256" << endl;
		int MykeySize; cin >> MykeySize;
		getchar();
		cout << "��������������" << endl;
		cout << "�����ʽΪ����128λΪ������6cdd, 596b, 8f56, 42cb, d23b, 4798, 1a65, 422a" << endl;
		string Mytext; getline(cin, Mytext);
		cout << "��������Կ����" << endl;
		cout << "�����ʽΪ����128λΪ������0001, 2001, 7101, 98ae, da79, 1714, 6015, 3594" << endl;
		string Mykey; getline(cin, Mykey);
		TestData1 td3(MytextSize, MykeySize, Mytext, Mykey,Mytext);
		cout << "MyText=" << Mytext << endl;
		cout << "MyKey=" << Mykey << endl;
		cout << "���ڽ���..." << endl;
		cout << endl;
		decrypt(td3);
		cout << "���ܽ���Ķ����Ʊ�ʾΪ��" << endl;
		printCStar(text, 1, textSize + 1);
		cout << "���ܽ����16���Ʊ�ʾΪ��" << endl;
		CStar2HEX(text, 1, textSize + 1);
	}
	if (choose1 == 4) {
		Avalanche();
		Avalanche2();
	}
	cout << "��л����ʹ�ã�" << endl;
}


int main() {
	//encrypt(td2);
	//printCStar(text, 1, 129);
	//decrypt(td2);
	//printCStar(text, 1, 129);
	//CStar2HEX(text, 1, 129);
	Interaction();
}