#include<iostream>
#include<string>
#include<map>
#include<vector>
using namespace std;

//获取长度
int get_length(char* text) {
    int i = 0;
    while (text[i] != '\0') {
        i++;
    }
    return i;
}

//移位密码
int shiftword(){
    int n;//密钥
    cout << "请输入密钥" << endl;
    cin >> n;
    n=n%26;//大于等于26没有意义

    char *message=new char[1000];
    cout << "请输入明文" << endl;
    getchar();//防止cin.getline函数被跳过的情况发生
    cin.getline(message, 1000);
    int length=get_length(message);

    //存储密文
    char *secretmessage=new char[1000];
    
    for(int i=0;i<length;i++){
        if((message[i]>=65&&message[i]<=90)){
            secretmessage[i]=message[i]-n;
            if(secretmessage[i]<65){secretmessage[i]+=26;}
        }
        if(message[i]>=97&&message[i]<=122){
            secretmessage[i]=message[i]-n;
            if(secretmessage[i]<97){secretmessage[i]+=26;}
        }
        if(message[i]==32){
            secretmessage[i]=32;
        }
    }
    secretmessage[length + 1] = '\0';
    cout<<"您的密钥是:"<<n<<endl;
    cout<<"您的明文是:"<<message<<endl;
    cout<<"您的密文是:"<<secretmessage<<endl;
    return 0;
}

//攻击移位密码
int attackshift(){
    char *secretmessage=new char [1000];
    char *message=new char[1000];
    cout<<"请输入想要攻击的密文"<<endl;
    cin.getline(secretmessage,1000);
    int length=get_length(secretmessage);
    for(int i=0;i<26;i++){
        memcpy(message,secretmessage,length+1);
        for(int j=0;j<length;j++){
            if(message[j]>=65&&message[j]<=90){
                message[j]-=i;
                if(message[j]<65){message[j]+=26;}
            }
            if(message[j]>=97&&message[j]<=122){
                message[j]-=i;
                if(message[j]<97){message[j]+=26;}
            }
            if(message[j]==32){continue;}
        }
        cout<<"当密钥是"<<26-i<<"时解密的文件为："<<message<<endl;
    }
    return 0;
}

int singleTableChange(){
    map<char, char>table;
    vector<char>already;
    char* message = new char[26];
    memset(message, 0, 26);
    int nowbase = 0;
    cout << "请输入置换序列，如果输入大于26位则只取前26位" << endl;
    cin.getline(message, 26);
    for (int i = 0; i < 26; i++) {
        if (message[i] != 0) {
            if (find(already.begin(), already.end(), message[i]) == already.end()) {
                char big;
                char small;
                if (message[i] >= 65 && message[i] <= 90) {
                    big = message[i];
                    small = message[i] + 32;
                }
                else {
                    big = message[i] - 32;
                    small = message[i];
                }
                table.insert(pair<char, char>(char(65+nowbase), big));
                table.insert(pair<char, char>(char(97 + nowbase), small));
                already.push_back(big);
                already.push_back(small);
                nowbase++;
            }
            else {
                continue;
            }
        }
        else {
            break;
        }
    }
    for (int i = 0; i < 26; i++) {
        if (find(already.begin(), already.end(), char(65 + i)) == already.end()) {
            table.insert(pair<char, char>(char(65 + nowbase), char(65 + i)));
            table.insert(pair<char, char>(char(97 + nowbase), char(97 + i)));
            nowbase++;
        }
    }
    cout << "您的代换表为" << endl;
    for (int i = 0; i < 26; i++) {
        cout << char(97 + i) << " " << table.find(char(97 + i))->second <<" " << char(65 + i) << " " << table.find(65 + i)->second << endl;
    }
    cout << "请输入您的加密信息" << endl;
    message = new char[1000];
    cin.getline(message, 1000);
    char* secretmessage = new char[1000];
    int length = get_length(message);
    for (int i = 0; i < length; i++) {
        secretmessage[i] = table.find(message[i])->second;
    }
    secretmessage[length + 1] = '\0';
    cout << "您的明文是:" << message << endl;
    cout << "您的密文是:" << secretmessage << endl;
    return 0;
}

int main(){
    //shiftword();
    //attackshift();
    singleTableChange();
}