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
    cout << "[INPUT]������Ҫ������ļ���" << endl;
    cin >> filename;
    ifstream fin(filename.c_str(), ifstream::binary);//�Զ����Ʒ�ʽ���ļ�
    unsigned long long int index = 0;
    char temp = fin.get();
    while (fin)
    {
        v.push_back(temp);
        temp = fin.get();
    }
    fin.close();
    cout << "�ɹ���ȡ�ļ����ļ���СΪ" << v.size() << endl;
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

void string2vectorChar(string s, vector<char>&c) {
    c.clear();
    for (int i = 0; i < s.size(); i++) {
        c.push_back(s[i]);
    }
    return;
}

void readcmd(vector<char>& v) {
    int choose;
    cout << "ѡ��ͬ�����뷽ʽ: 1������������ƣ�2��������ʮ���ƣ�3��������16����" << endl;
    cout << "��ܰ��ʾ������Ķ����ƺ�16���ƻ���Ϊ�ı��ַ������м��㣬�����ʮ�������ֽ�������ֵת��Ϊ�������ı��ַ�������" << endl;
    cin >> choose;
    if (choose == 1) {
        string s;
        cin >> s;
        if (checkBin(s)) {
            cout << "�ɹ�����������ı�" << endl;
            string2vectorChar(s, v);
            return;
        }
        else {
            cout << "�������" << endl;
            return;
        }
    }
    else {
        if (choose == 2) {
            int i;
            cin >> i;
            string s = Dec2Bin(i);
            cout << "�ɹ���ȡ10������ֵ��ת��" << endl;
            string2vectorChar(s, v);
            return;
        }
        else {
            if (choose == 3) {
                string s;
                cin >> s;
                if (!checkHex(s)) { cout << "���������" << endl; return; }
                s = Hex2Bin(s);
                cout << "�ɹ�ȥ��16�����ı���ת��Ϊ2����" << endl;
                string2vectorChar(s, v);
                return;
            }
            else {
                cout << "���������" << endl;
                return;
            }
        }
    }
    

}

//��ɵ�һ�����
void fill(vector<char>& v) {
    int n = v.size();
    if (n % 512 == 448) {
        //����Ѿ�����ģ512����448
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

//����С����
string smallEnd(string s) {
    if (s.size() != 64) {
        string s;
        cout << "�Ƿ��ĳ���" << endl;
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

//��䳤��
void fillLength(vector<char>& v,vector<char>&origin) {
    //64λ��ʹ��
    unsigned long long int n= origin.size();
    string s = Dec2Bin(n);//�õ���s�Ķ����Ʊ�ʾ�����ڻ���Ҫ�õ�����С�����ʾ
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

//ģ2^32�η��ļӷ��������޶�a b������32λ��
//����˵�н�λֱ�������Ϳ�����
string stringADD(string a, string b) {
    if (a.size() != 32 || b.size() != 32) {
        cout << "�Ƿ��ļӷ�" << endl;
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

//�ĸ��߼�����
string F(string b, string c, string d) {
    string ret;
    if (b.size() != 32 || c.size() != 32 || d.size() != 32) {
        cout << "F������������" << endl;
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
        cout << "F������������" << endl;
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
        cout << "F������������" << endl;
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
        cout << "F������������" << endl;
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
        cout << "CLS��������" << endl;
        return ret;
    }
    for (int j = 0; j < 32; j++) {
        char c;
        if (j + i > 32) {
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
    myMD5(vector<char>&vc);
    myMD5(const myMD5& m);
    int getGroupSize()const { return text.size() / 16; }//�ܹ��м��飬��������±��Ǵ�0��ʼ��
    int getWordSize() const { return text.size(); }//ͬ�������±�Ҳ�Ǵ�0��ʼ
    string getGroup(int i);
    string getWord(int i);
    friend ostream& operator<<(ostream& out, const myMD5& m);
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
        cout << "��������" << endl;
        return s;
    }
    else {
        string s;
        for (int j = 0; j < 16; j++) {
            s.append(this->text[i * 16 + j]);
        }
        return s;
    }
}
string myMD5::getWord(int i) {
    if (i >= this->getGroupSize()) {
        string s;
        cout << "������ֺ�" << endl;
        return s;
    }
    else {
        string s;
        s = this->text[i];
    }
}
ostream& operator<<(ostream& out, const myMD5& m) {
    for (int i = 0; i < m.getWordSize(); i++) {
        out << m.text[i] << endl;
    }
    return out;
}

void InitialRegister() {
    string sa = Hex2Bin("67452301");
    string sb = Hex2Bin("EFCDAB89");
    string sc = Hex2Bin("98BADCFE");
    string sd = Hex2Bin("10325476");
}