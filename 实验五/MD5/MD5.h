#pragma once
#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

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
    cout << "ѡ��ͬ�����뷽ʽ: 1������������ƣ�2��������ʮ���ƣ�3��������16����" << endl;
    cout << "��ܰ��ʾ������Ķ����ƺ�16���ƻ���Ϊ�ı��ַ������м��㣬�����ʮ�������ֽ�������ֵת��Ϊ�������ı��ַ�������" << endl;
    cin >> choose;
    if (choose == 1) {
        string s;
        cin >> s;
        if (checkBin(s)) {
            cout << "�ɹ�����������ı�" << endl;
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
            return;
        }
        else {
            if (choose == 3) {
                string s;
                cin >> s;
                s = Hex2Bin(s);
                cout << "�ɹ�ȥ��16�����ı���ת��Ϊ2����" << endl;
                return;
            }
            else {
                cout << "���������" << endl;
                return;
            }
        }
    }
    

}