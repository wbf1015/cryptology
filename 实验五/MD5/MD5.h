#pragma once
#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

void printVectorChar(vector<char>&vc) {
    for (int i = 0; i < vc.size(); i++) {
        cout << vc[i];
    }
    cout << endl;
}

void readFile(vector<char>&v) {
    v.clear();
    string filename;
    cout << "[INPUT]请输入要传输的文件名" << endl;
    cin >> filename;
    ifstream fin(filename.c_str(), ifstream::binary);//以二进制方式打开文件
    unsigned long long int index = 0;
    char temp = fin.get();
    while (fin)
    {
        v.push_back(temp);
        temp = fin.get();
    }
    fin.close();
    cout << "成功读取文件，文件大小为" << v.size() << endl;
    return;
}

bool checkBin(string s) {
    for (int i = 0; i < s.size(); i++) {
        if (s[i] != '0' && s[i] != '1') { return false; }
    }
    return true;
}

bool checkDec(string s) {
    for (int i = 0; i < s.size(); i++) {
        if (s[i] < 48 || s[i]>57) { return false; }
    }
    return true;
}

bool checkHex(string s) {
    for (int i = 0; i < s.size(); i++) {
        if ((s[i] >= 48 && s[i] <= 57) || (s[i] >= 65 && s[i] <= 70) || (s[i] >= 97 && s[i] <= 102)) { continue; }
        else { return false; }
    }
    return true;
}

string Dec2Bin(unsigned long long int i) {
    vector<int>vi;
    unsigned long long int myi = i;
    while (myi != 0) {
        vi.push_back(myi % 2);
        myi = myi / 2;
    }
    reverse(vi.begin(), vi.end());
    string s;
    for (int i = 0; i < vi.size(); i++) {
        if (vi[i] == 0) { s.append(string(1, '0')); }
        else { s.append(string(1, '1')); }
    }
    return s;
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

string Dec2Hex(int n) {
    string s;
    string t = "0123456789ABCDEF";
    int x;
    while (n != 0) {
        x = n % 16;
        // 将 n % 16 转换为字符逆序存入 s 
        s = t[x] + s;
        n = n / 16;
    }

    if (s == "") {
        cout << "错误的十进制转16进制输入" << endl;
        return s;
    }
    else {
        return s;
    }
}

string Text2Hex(string s) {
    string ret;
    for (int i = 0; i < s.size(); i++) {
        int t = s[i];
        string ss = Dec2Hex(t);
        ret.append(ss);
    }
    return ret;
}

string Bin2Hex(string s) {
    if (s.size() % 4 != 0) {
        reverse(s.begin(), s.end());
        for (int i = 1; i <= 4-(s.size() % 4); i++) {
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

void string2vectorChar(string s, vector<char>&c) {
    c.clear();
    for (int i = 0; i < s.size(); i++) {
        c.push_back(s[i]);
    }
    return;
}

void readcmd(vector<char>& v) {
    cout << "请输入文本字符串" << endl;
    char c[10000];
    cin.get(c, 10000);
    string s(c);
    s = Text2Hex(s);
    s = Hex2Bin(s);
    string2vectorChar(s, v);
}

//完成第一步填充
void fill(vector<char>& v) {
    int n = v.size();
    if (n % 512 == 448) {
        //如果已经满足模512等于448
        v.push_back('1');
        for (int i = 1; i <= 511; i++) {
            v.push_back('0');
        }
        return;
    }
    else {
        v.push_back('1');
        while (v.size() % 512 != 448) {
            v.push_back('0');
        }
        return;
    }
}

//返回小端序
string smallEnd(string s) {
    if (s.size() != 64) {
        string s;
        cout << "非法的长度" << endl;
        return s;
    }
    string vs[8];
    for (int i = 0; i < 8; i++) {
        vs[i] = s.substr(i * 8, 8);
    }
    string ret;
    for (int i = 7; i >= 0; i--) {
        ret.append(vs[i]);
    }
    return ret;
}

string smallEndRegister(string s) {
    string ret;
    if (s.size() != 32) {
        cout << "寄存器小端转换字符错误" << endl;
        return ret;
    }
    string s1 = s.substr(0, 8);
    string s2 = s.substr(8, 8);
    string s3 = s.substr(16, 8);
    string s4 = s.substr(24, 8);
    ret.append(s4);
    ret.append(s3);
    ret.append(s2);
    ret.append(s1);
    return ret;
}

//填充长度
void fillLength(vector<char>& v,vector<char>&origin) {
    //64位的使用
    unsigned long long int n= origin.size();
    string s = Dec2Bin(n);//拿到了s的二进制表示，现在还需要拿到他的小端序表示
    if (s.size() < 64) {
        reverse(s.begin(), s.end());
        while (s.size() < 64) {
            s.append(string(1, '0'));
        }
        reverse(s.begin(), s.end());
    }
    s = smallEnd(s);
    for (int i = 0; i < 64; i++) {
        v.push_back(s[i]);
    }
    return;

}

//模2^32次方的加法，而且限定a b必须是32位的
//所以说有进位直接舍弃就可以了
string stringADD(string a, string b) {
    if (a.size() != 32 || b.size() != 32) {
        cout << "非法的加法" << endl;
        string s;
        return s;
    }
    string mya(a);
    string myb(b);
    reverse(mya.begin(), mya.end());
    reverse(myb.begin(), myb.end());
    char jw = '0';
    string ret;
    for (int i = 0; i < 32; i++) {
        if (mya[i] == '0' && myb[i] == '0' && jw == '0') { ret.append(string(1, '0')); jw = '0'; continue; }
        if (mya[i] == '0' && myb[i] == '0' && jw == '1') { ret.append(string(1, '1')); jw = '0'; continue; }
        if (mya[i] == '0' && myb[i] == '1' && jw == '0') { ret.append(string(1, '1')); jw = '0'; continue; }
        if (mya[i] == '0' && myb[i] == '1' && jw == '1') { ret.append(string(1, '0')); jw = '1'; continue; }
        if (mya[i] == '1' && myb[i] == '0' && jw == '0') { ret.append(string(1, '1')); jw = '0'; continue; }
        if (mya[i] == '1' && myb[i] == '0' && jw == '1') { ret.append(string(1, '0')); jw = '1'; continue; }
        if (mya[i] == '1' && myb[i] == '1' && jw == '0') { ret.append(string(1, '0')); jw = '1'; continue; }
        if (mya[i] == '1' && myb[i] == '1' && jw == '1') { ret.append(string(1, '1')); jw = '1'; continue; }
    }
    reverse(ret.begin(), ret.end());
    return ret;
}



string registerA;
string registerB;
string registerC;
string registerD;

int clss[5][17]{
    {},
    {0,7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22},
    {0,5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20},
    {0,4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23},
    {0,6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21}
};
string T[65]{
    "",
    "d76aa478", "e8c7b756", "242070db", "c1bdceee",
    "f57c0faf", "4787c62a", "a8304613", "fd469501",
    "698098d8", "8b44f7af", "ffff5bb1", "895cd7be",
    "6b901122", "fd987193", "a679438e", "49b40821",
    "f61e2562", "c040b340", "265e5a51", "e9b6c7aa",
    "d62f105d", "02441453", "d8a1e681", "e7d3fbc8",
    "21e1cde6", "c33707d6", "f4d50d87", "455a14ed",
    "a9e3e905", "fcefa3f8", "676f02d9", "8d2a4c8a",
    "fffa3942", "8771f681", "6d9d6122", "fde5380c",
    "a4beea44", "4bdecfa9", "f6bb4b60", "bebfbc70",
    "289b7ec6", "eaa127fa", "d4ef3085", "04881d05",
    "d9d4d039", "e6db99e5", "1fa27cf8", "c4ac5665",
    "f4292244", "432aff97", "ab9423a7", "fc93a039",
    "655b59c3", "8f0ccc92", "ffeff47d", "85845dd1",
    "6fa87e4f", "fe2ce6e0", "a3014314", "4e0811a1",
    "f7537e82", "bd3af235", "2ad7d2bb", "eb86d391"
};
int round2(int i) {
    return (1 + 5 * i) % 16;
}
int round3(int i) {
    return (5 + 3 * i) % 16;
}
int round4(int i) {
    return (7 * i) % 16;
}

//四个逻辑函数
string F(string b, string c, string d) {
    string ret;
    if (b.size() != 32 || c.size() != 32 || d.size() != 32) {
        cout << "F函数参数错误" << endl;
        return ret;
    }
    for (int i = 0; i < 32; i++) {
        if (b[i] == '0' && c[i] == '0' && d[i] == '0') { ret.append(string(1, '0')); continue; }
        if (b[i] == '0' && c[i] == '0' && d[i] == '1') { ret.append(string(1, '1')); continue; }
        if (b[i] == '0' && c[i] == '1' && d[i] == '0') { ret.append(string(1, '0')); continue; }
        if (b[i] == '0' && c[i] == '1' && d[i] == '1') { ret.append(string(1, '1')); continue; }
        if (b[i] == '1' && c[i] == '0' && d[i] == '0') { ret.append(string(1, '0')); continue; }
        if (b[i] == '1' && c[i] == '0' && d[i] == '1') { ret.append(string(1, '0')); continue; }
        if (b[i] == '1' && c[i] == '1' && d[i] == '0') { ret.append(string(1, '1')); continue; }
        if (b[i] == '1' && c[i] == '1' && d[i] == '1') { ret.append(string(1, '1')); continue; }
    }
    return ret;
}

string G(string b, string c, string d) {
    string ret;
    if (b.size() != 32 || c.size() != 32 || d.size() != 32) {
        cout << "G函数参数错误" << endl;
        return ret;
    }
    for (int i = 0; i < 32; i++) {
        if (b[i] == '0' && c[i] == '0' && d[i] == '0') { ret.append(string(1, '0')); continue; }
        if (b[i] == '0' && c[i] == '0' && d[i] == '1') { ret.append(string(1, '0')); continue; }
        if (b[i] == '0' && c[i] == '1' && d[i] == '0') { ret.append(string(1, '1')); continue; }
        if (b[i] == '0' && c[i] == '1' && d[i] == '1') { ret.append(string(1, '0')); continue; }
        if (b[i] == '1' && c[i] == '0' && d[i] == '0') { ret.append(string(1, '0')); continue; }
        if (b[i] == '1' && c[i] == '0' && d[i] == '1') { ret.append(string(1, '1')); continue; }
        if (b[i] == '1' && c[i] == '1' && d[i] == '0') { ret.append(string(1, '1')); continue; }
        if (b[i] == '1' && c[i] == '1' && d[i] == '1') { ret.append(string(1, '1')); continue; }
    }
    return ret;
}

string H(string b, string c, string d) {
    string ret;
    if (b.size() != 32 || c.size() != 32 || d.size() != 32) {
        cout << "H函数参数错误" << endl;
        return ret;
    }
    for (int i = 0; i < 32; i++) {
        if (b[i] == '0' && c[i] == '0' && d[i] == '0') { ret.append(string(1, '0')); continue; }
        if (b[i] == '0' && c[i] == '0' && d[i] == '1') { ret.append(string(1, '1')); continue; }
        if (b[i] == '0' && c[i] == '1' && d[i] == '0') { ret.append(string(1, '1')); continue; }
        if (b[i] == '0' && c[i] == '1' && d[i] == '1') { ret.append(string(1, '0')); continue; }
        if (b[i] == '1' && c[i] == '0' && d[i] == '0') { ret.append(string(1, '1')); continue; }
        if (b[i] == '1' && c[i] == '0' && d[i] == '1') { ret.append(string(1, '0')); continue; }
        if (b[i] == '1' && c[i] == '1' && d[i] == '0') { ret.append(string(1, '0')); continue; }
        if (b[i] == '1' && c[i] == '1' && d[i] == '1') { ret.append(string(1, '1')); continue; }
    }
    return ret;
}

string I(string b, string c, string d) {
    string ret;
    if (b.size() != 32 || c.size() != 32 || d.size() != 32) {
        cout << "I函数参数错误" << endl;
        return ret;
    }
    for (int i = 0; i < 32; i++) {
        if (b[i] == '0' && c[i] == '0' && d[i] == '0') { ret.append(string(1, '1')); continue; }
        if (b[i] == '0' && c[i] == '0' && d[i] == '1') { ret.append(string(1, '0')); continue; }
        if (b[i] == '0' && c[i] == '1' && d[i] == '0') { ret.append(string(1, '0')); continue; }
        if (b[i] == '0' && c[i] == '1' && d[i] == '1') { ret.append(string(1, '1')); continue; }
        if (b[i] == '1' && c[i] == '0' && d[i] == '0') { ret.append(string(1, '1')); continue; }
        if (b[i] == '1' && c[i] == '0' && d[i] == '1') { ret.append(string(1, '1')); continue; }
        if (b[i] == '1' && c[i] == '1' && d[i] == '0') { ret.append(string(1, '0')); continue; }
        if (b[i] == '1' && c[i] == '1' && d[i] == '1') { ret.append(string(1, '0')); continue; }
    }
    return ret;
}

string CLS(string s,int i) {
    string ret;
    if (s.size() != 32) {
        cout << "CLS参数错误" << endl;
        return ret;
    }
    for (int j = 0; j < 32; j++) {
        char c;
        if (j + i >= 32) {
            c = s[j + i - 32];
        }
        else {
            c = s[j + i];
        }
        ret.append(string(1, c));
    }
    return ret;
}

class myMD5 {
public:
    vector<string>text;
    vector<string>smallText;
    myMD5(vector<char>&vc);
    myMD5(const myMD5& m);
    int getGroupSize()const { return text.size() / 16; }//总共有几组，但是组的下标是从0开始的
    int getWordSize() const { return text.size(); }//同理分组的下标也是从0开始
    string getGroup(int i);
    string getWord(int i);
    friend ostream& operator<<(ostream& out, const myMD5& m);
    void printSmallText();
    void getSmallText();
};
myMD5::myMD5(vector<char>&vc) {
    for (int i = 0; i < vc.size(); i += 32) {
        string s;
        for (int j = i; j < (i + 32); j++) {
            s.append(string(1, vc[j]));
        }
        text.push_back(s);
    }
}
myMD5::myMD5(const myMD5& m) {
    for (int i = 0; i < m.text.size(); i++) {
        this->text.push_back(m.text[i]);
    }
}
string myMD5::getGroup(int i) {
    if (i >= getGroupSize()) {
        string s;
        cout << "错误的组号" << endl;
        return s;
    }
    else {
        string s;
        for (int j = 0; j < 16; j++) {
            s.append(this->smallText[i * 16 + j]);
        }
        return s;
    }
}
string myMD5::getWord(int i) {
    if (i >= this->getWordSize()) {
        string s;
        cout << "错误的字号" << endl;
        return s;
    }
    else {
        string s;
        s = this->smallText[i];
        return s;
    }
}
void myMD5::getSmallText() {
    for (int i = 0; i < text.size(); i++) {
        string s = text[i];
        string s1 = s.substr(0, 8);
        string s2 = s.substr(8, 8);
        string s3 = s.substr(16, 8);
        string s4 = s.substr(24, 8);
        s.clear();
        s.append(s4); s.append(s3); s.append(s2); s.append(s1);
        smallText.push_back(s);
    }
}
void myMD5::printSmallText() {
    cout << "MD5的小端序表示为" << endl;
    for (int i = 0; i < smallText.size(); i++) {
        cout << smallText[i] << endl;
    }
}
ostream& operator<<(ostream& out, const myMD5& m) {
    for (int i = 0; i < m.getWordSize(); i++) {
        out << m.text[i] << endl;
    }
    return out;
}
void Myround(int q, int round, myMD5& m);
void step(int q, int round, int i, myMD5& m);

void InitialRegister() {
    string sa = Hex2Bin("67452301");
    string sb = Hex2Bin("EFCDAB89");
    string sc = Hex2Bin("98BADCFE");
    string sd = Hex2Bin("10325476");
    registerA = sa;
    registerB = sb;
    registerC = sc;
    registerD = sd;
}

string HashMD5(myMD5& m) {
    InitialRegister();
    m.getSmallText();
    m.printSmallText();
    for (int k = 0; k < m.getGroupSize(); k++) {
        string ra = registerA;
        string rb = registerB;
        string rc = registerC;
        string rd = registerD;
        for (int j = 1; j <= 4; j++) {
            Myround(k, j, m);
        }
        registerA = stringADD(registerA, ra);
        registerB = stringADD(registerB, rb);
        registerC = stringADD(registerC, rc);
        registerD = stringADD(registerD, rd);
    }
    string ret;
    ret.append(smallEndRegister(registerA));
    ret.append(smallEndRegister(registerB));
    ret.append(smallEndRegister(registerC));
    ret.append(smallEndRegister(registerD));
    return ret;
}


//这个就是每一轮
void Myround(int q, int round, myMD5& m) {
    for (int i = 1; i <= 16; i++) {
        step(q, round, i, m);
    }
}

//q代表着是第几个512比特的分组，round代表着是第几轮，i代表着是这一轮的第几步
//round的取值范围是1-4 step是1-16
//q应该是从0开始的
void step(int q, int round, int i,myMD5 &m) {
    //把bcd寄存器和逻辑函数的取值计算出来
    string ADDbcd;
    if (round == 1) {
        ADDbcd = F(registerB, registerC, registerD);
    }
    if (round == 2) {
        ADDbcd = G(registerB, registerC, registerD);
    }
    if (round == 3) {
        ADDbcd = H(registerB, registerC, registerD);
    }
    if (round == 4) {
        ADDbcd = I(registerB, registerC, registerD);
    }
    //A和逻辑函数的取值
    string Add1;
    Add1 = stringADD(registerA, ADDbcd);
    //然后把X[k]取出来
    int k;
    if (round == 1) { k = i-1; }
    if (round == 2) { k = round2(i-1); }
    if (round == 3) { k = round3(i-1); }
    if (round == 4) { k = round4(i-1); }
    //完成对于Xk的加法
    string Xk = m.getWord(q*16+k);
    string Add2 = stringADD(Xk, Add1);
    //完成对于Ti的加法
    string Ti = T[16 * (round - 1)+i];
    Ti = Hex2Bin(Ti);
    string Add3 = stringADD(Ti, Add2);
    //完成对于ADD3的移位
    string moveS = CLS(Add3, clss[round][i]);
    string newA = stringADD(moveS, registerB);
    //完成寄存器的交换
    string ra = registerA;
    string rb = registerB;
    string rc = registerC;
    string rd = registerD;
    registerA = rd;
    registerB = newA;
    registerC = rb;
    registerD = rc;

    cout << "第" << round << "轮,第" << i << "步后经过寄存器交换后的值为" << endl;
    cout << "k=" << k << endl;
    cout << Bin2Hex(registerA) << endl;
    //cout << registerA << endl;
    cout << Bin2Hex(registerB) << endl;
    //cout << registerB << endl;
    cout << Bin2Hex(registerC) << endl;
    //cout << registerC << endl;
    cout << Bin2Hex(registerD) << endl;
    cout << "------------------------------------------------------------------------" << endl;
}