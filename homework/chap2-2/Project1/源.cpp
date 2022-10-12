#include <iostream>
#include<map>
using namespace std;
int store[49] = { 1,1,1,0,0,0,0,0,1,0,1,1,1,1,1,1,0,0,0,1,1,1,0,1,1,1,1,1,1,0,0,1,1,0,0,0,1,1,1,1,0,0,0,0,1,0,0,1,1 };
map <int, int>ans;
int main() {
    for (int i = 0; i <= 48; i++) {
        int same = 0;
        int diff = 0;
        for (int j = 0; j <= 48; j++) {
            if (store[j] == store[(j + i) % 49]) { same++; }
            else { diff++; }
        }
        int res = same - diff;
        cout << "λ��Ϊ" << i << "ʱ" << "�칹����غ����ķ�ĸΪ" << res << endl;
        if (ans.find(res) == ans.end()) {
            ans.insert(pair<int, int>(res, 1));
        }
        else {
            ans[res] = ans[res] + 1;
        }
    }
    for (auto it : ans) {
        cout << it.first << " " << it.second << endl;
    }
}
