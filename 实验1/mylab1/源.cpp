#include<iostream>
#include<cstring>
#include<map>
#include<vector>
#include<fstream>
using namespace std;
float *ftable=new float [26];
char *frank=new char[26];


//获取长度
int get_length(char* text) {
    int i = 0;
    while (text[i] != '\0') {
        i++;
    }
    return i;
}

int get_length_without_blank(char* text) {
    int i = 0;
    int count = 0;
    while (text[i] != '\0') {
        i++;
        count++;
    }
    return count;
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
                continue;
            }
            if(message[j]>=97&&message[j]<=122){
                message[j]-=i;
                if(message[j]<97){message[j]+=26;}
                continue;
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

void initialftable(){
    ftable['e' - 97] = 11.67; frank[0] = 'e';
    ftable['t' - 97] = 9.53;  frank[1] = 't';
    ftable['o'-97]=8.22;  frank[2]='o';
    ftable['i'-97]=7.81;  frank[3]='i';
    ftable['a'-97]=7.73;  frank[4]='a';
    ftable['n'-97]=6.71;  frank[5]='n';
    ftable['s'-97]=6.55;  frank[6]='s';
    ftable['r'-97]=5.97;  frank[7]='r';
    ftable['h'-97]=4.52;  frank[8]='h';
    ftable['l'-97]=4.3;   frank[9]='l';
    ftable['d'-97]=3.24;  frank[10]='d';
    ftable['u'-97]=3.21;  frank[11]='u';
    ftable['c'-97]=3.06;  frank[12]='c';
    ftable['m'-97]=2.8;   frank[13]='m';
    ftable['p'-97]=2.34;  frank[14]='p';
    ftable['y'-97]=2.22;  frank[15]='y';
    ftable['f'-97]=2.14;  frank[16]='f';
    ftable['g'-97]=2.00;  frank[17]='g';
    ftable['w'-97]=1.69;  frank[18]='w';
    ftable['b'-97]=1.58;  frank[19]='b';
    ftable['v'-97]=1.03;  frank[20]='v';
    ftable['k'-97]=0.79;  frank[21]='k';
    ftable['x'-97]=0.3;   frank[22]='x';
    ftable['j'-97]=0.23;  frank[23]='j';
    ftable['q'-97]=0.12;  frank[24]='q';
    ftable['z'-97]=0.09;  frank[25]='z';
}
char findmax(map<char,double>&map) {
    char max_char;
    double max=0;
    for (auto it : map) {
        if (it.second >= max) {
            max_char = it.first;
            max = it.second;
        }
    }
    map.erase(max_char);
    return max_char;
}


int attackSingleTableChange(){
    initialftable();
    char *message=new char[1000];
    ifstream infile;
    infile.open("message1.txt",ios::in);
    if(!infile.is_open()){
        cout<<"读取文件失败"<<endl;
        return -1;
    }
    char buff[1000];
    while(infile.getline(buff,1000)){
        for (int i = 0; i < 1000; i++) {
            if (buff[i] != '\0') {
                message[i] = buff[i];
                continue;
            }
            if (buff[i] == '\0') {
                message[i] = '\0';
                break;
            }
        }
    }
    int n = get_length(message);
    int cn = get_length_without_blank(message);
    cout<<"您要攻击的密文长度为：" << get_length(message) << endl;
    cout << "您要攻击的密文信息为：" << message << endl;
    map<char, double>temprecord;
    map<char, double>record;//记录中每个字符串出现频率
    //记录每个字符出现的次数并转换为小写存储便于识别
    for (int i = 0; i < n; i++) {
        char temp;
        if (message[i] >= 65 && message[i] <= 90) {
            temp = message[i] + 32;
            message[i] = temp;
        }else{
            if (message[i] >= 97 && message[i] <= 122) {
                temp = message[i];
            }
            else {
                continue;
            }
        }
        if (temprecord.find(temp) != temprecord.end()) {
            temprecord[temp] += 1;
            record[temp] += 1;
            continue;
        }
        else {
            temprecord.insert(pair<char, double>(temp, 1.0));
            record.insert(pair<char, double>(temp, 1.0));
        }
    }
    cout << message << endl;
    //找那些没出现的
    for (int i = 97; i <= 122; i++) {
        if (record.find(char(i)) == record.end()) {
            record.insert(pair<char, char>(char(i), 0.0));
            temprecord.insert(pair<char, char>(char(i), 0.0));
        }
    }
    char myrank[26];//密文中字符串排名
    for (int i = 0; i < 26; i++) {
        myrank[i] = findmax(temprecord);
    }
    //展示单表代换对比结果
    cout << "下面展示初步单表代换结果" << endl;
    cout << "统计字符" << "    " << "统计字符频率" << "    " << "密文字符" << "    " << "密文字符频率" << endl;
    for (int i = 0; i < 26; i++) {
        cout <<"  " << frank[i] << "           " << ftable[frank[i] - 97] << "           " << myrank[i] << "           " << (record.find(myrank[i])->second / cn) * 100 << endl;;
    }
    //构造代换表
    map<char, char>stctable;
    for (int i = 0; i < 26; i++) {
        stctable.insert(pair<char, char>(frank[i], myrank[i]));
    }
    cout << endl;
    for (auto it : stctable) {
        cout << it.first << " " << it.second << endl;
    }
    cout << endl;
    cout << "根据频率的单表代换结果解密如下：" << endl;
    for (int i = 0; i < n; i++) {
        if (message[i] >= 97 && message[i] <= 122) { cout << stctable[message[i]]; }
        else { cout << message[i]; }
    }
}

int main(){
    //shiftword();
    attackshift();
    //singleTableChange();
    //attackSingleTableChange();
}