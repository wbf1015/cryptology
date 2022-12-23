#pragma once
#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

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

string Dec2Bin(int i) {
    vector<int>vi;
    while (i != 0) {
        vi.push_back(i % 2);
        i = i / 2;
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
    string s;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '0') { s.append("0000"); }
        if (s[i] == '1') { s.append("0001"); }
        if (s[i] == '2') { s.append("0010"); }
        if (s[i] == '3') { s.append("0011"); }
        if (s[i] == '4') { s.append("0100"); }
        if (s[i] == '5') { s.append("0101"); }
        if (s[i] == '6') { s.append("0110"); }
        if (s[i] == '7') { s.append("0111"); }
        if (s[i] == '8') { s.append("1000"); }
        if (s[i] == '9') { s.append("1001"); }
        if (s[i] == 'a' || s[i] == 'A') { s.append("1010"); }
        if (s[i] == 'b' || s[i] == 'B') { s.append("1011"); }
        if (s[i] == 'c' || s[i] == 'C') { s.append("1100"); }
        if (s[i] == 'd' || s[i] == 'D') { s.append("1101"); }
        if (s[i] == 'e' || s[i] == 'E') { s.append("1110"); }
        if (s[i] == 'f' || s[i] == 'F') { s.append("1111"); }
    }
}


void readcmd(vector<char>& v) {
    int choose;
    cout << "选择不同的输入方式: 1代表输入二进制，2代表输入十进制，3代表输入16进制" << endl;
    cout << "温馨提示：输入的二进制和16进制会作为文本字符串进行计算，输入的十进制数字将根据数值转换为二进制文本字符串计算" << endl;
    cin >> choose;
    if (choose == 1) {
        string s;
        cin >> s;
        if (checkBin(s)) {
            cout << "成功输入二进制文本" << endl;
            return;
        }
        else {
            cout << "输入错误" << endl;
            return;
        }
    }
    else {
        if (choose == 2) {
            int i;
            cin >> i;
            string s = Dec2Bin(i);
            cout << "成功读取10进制数值并转换" << endl;
            return;
        }
        else {
            if (choose == 3) {
                string s;
                cin >> s;
                s = Hex2Bin(s);
                cout << "成功去读16进制文本并转换为2进制" << endl;
                return;
            }
            else {
                cout << "错误的输入" << endl;
                return;
            }
        }
    }
    

}