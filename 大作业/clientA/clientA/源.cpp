#include"BigInt.h"
#include"RSA.h"
#include"socket.h"
#include"dealFile.h"
#include"AES.h"
using namespace std;
string N1 = "0";
string N2 = "1";
string IDA = "A";
string AESKey = "2b7e151628aed2a6abf7158809cf4f3c";
string cleanString(string s) {
	int end = s.size() - 1;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == 0) { end = i - 1; }
	}
	return s.substr(0, end + 1);
}
int allocKey() {
	int check;
	cout << "您是AES密钥的分配者，请保证对方成功上线后再进行输入" << endl;
	cout << "请在开启客户端B后输入：1，之后将开始交换密钥" << endl;
	cin >> check;
	if (check != 1) { return -1; }
	//发送身份识别
	string t = N1 + IDA;
	cout << "第一次身份认证明文为" << t << endl;
	t = encrypt_B_public(t);
	t = "[IDEN]" + t;
	cout << "第一次身份认证密文为" << t << endl;
	char* sendbuffer = new char[10000];
	memcpy(sendbuffer, t.c_str(), t.size());
	int ii = sendto(mySocket, sendbuffer, t.size(), 0, (sockaddr*)&oppo_addr, olen);

	//接收反馈
	char* recvbuffer = new char[10000];
	memset(recvbuffer, 0, 10000);
	recvfrom(mySocket, recvbuffer, 10000, 0, (sockaddr*)&oppo_addr, &olen);
	string s = recvbuffer;
	s = cleanString(s);
	if (s.substr(0, 6) == "[IDEN]") {
		cout << "第二次身份认证匹配成功" << endl;
		s = s.substr(6, 10000);
	}
	cout << "第二次身份认证密文为" << s << endl;
	s = decrypt_A_private(s);
	cout << "第二次身份认证明文为" << s << endl;
	if (s == N1 + N2) {
		cout << "身份确认成功，即将进行再确认" << endl;
	}
	else {
		cout << "身份认证失败" << endl;
		return -1;
	}

	//再次准备发送
	t.clear();
	cout << "第三次身份认证明文为" << N2 << endl;
	t = encrypt_B_public(N2);
	t = "[IDEN]" + t;
	cout << "第三次身份认证密文为" << t << endl;
	memset(sendbuffer, 0, 10000);
	memcpy(sendbuffer, t.c_str(), t.size());
	sendto(mySocket, sendbuffer, 10000, 0, (sockaddr*)&oppo_addr, olen);

	Sleep(30 * 1000);

	//准备发送AES密钥的第一部分
	string key1 = AESKey.substr(0, 16);
	cout << "AES密钥切割第一部分为" << key1 << endl;
	key1 = encrypt_A_private(key1);
	cout << "使用A的私钥加密后为" << key1 << endl;
	int i = 0; vector<string>vs;
	while (i < key1.size()) {
		string temp = key1.substr(i, 16); i += 16;
		vs.push_back(temp);
	}
	for (int i = 0; i < vs.size(); i++) {
		cout << "二次切割后第" << i + 1 << "部分为" << vs[i] << endl;
		vs[i] = encrypt_B_public(vs[i]);
		cout << "使用B的公钥加密后为" << vs[i] << endl;
		memset(sendbuffer, 0, 10000);
		vs[i] = "[key1]" + vs[i];
		memcpy(sendbuffer, vs[i].c_str(), vs[i].size());
		sendto(mySocket, sendbuffer, 10000, 0, (sockaddr*)&oppo_addr, olen);
	}

	//准备发送AES密钥的第二部分
	string key2 = AESKey.substr(16, 16);
	cout << "AES密钥切割第二部分为" << key2 << endl;
	key2 = encrypt_A_private(key2);
	cout << "使用A的私钥加密后为" << key2 << endl;
	i = 0; vs.clear();
	while (i < key2.size()) {
		string temp = key2.substr(i, 16); i += 16;
		vs.push_back(temp);
	}
	for (int i = 0; i < vs.size(); i++) {
		cout << "二次切割后第" << i + 1 << "部分为" << vs[i] << endl;
		vs[i] = encrypt_B_public(vs[i]);
		cout << "加密后为" << vs[i] << endl;
		memset(sendbuffer, 0, 10000);
		vs[i] = "[key2]" + vs[i];
		memcpy(sendbuffer, vs[i].c_str(), vs[i].size());
		sendto(mySocket, sendbuffer, 10000, 0, (sockaddr*)&oppo_addr, olen);
	}

	string last = "[OVER]";
	memset(sendbuffer, 0, 10000);
	memcpy(sendbuffer, last.c_str(), last.size());
	sendto(mySocket, sendbuffer, 10000, 0, (sockaddr*)&oppo_addr, olen);
}
void realmain() {
	initalNeeded();//初始化socket什么的
	//allocKey();
	cout << "请选择您是收方还是发方：\n 输入1代表发方，输入2代表收方" << endl;
	int c1; cin >> c1;
	if (c1 == 1) {
		string s = readFile();
		s = useAESencrypt(s);
		char* sendbuffer = new char[10000];
		memcpy(sendbuffer, s.c_str(), s.size());
		cout << "请先确认接收端成功开启，如果接收端成功开启，请输入1\n 输入后将立即发送消息\n请务必确保接收端已经正确选择“接收模式”" << endl;
		int i = 0; while (i != 1) {
			cin >> i;
		}
		int e=sendto(mySocket, sendbuffer, s.size(), 0, (sockaddr*)&oppo_addr, olen);
		cout << e << endl;
		cout << WSAGetLastError() << endl;
		cout << "发送成功" << endl;
		while (true) {

		}
		return;
	}
	if (c1 == 2) {
		char* recvbuffer = new char[10000];
		memset(recvbuffer, 0, 10000);
		cout << "客户端准备完成" << endl;
		while (recvfrom(mySocket, recvbuffer, 10000, 0, (sockaddr*)&oppo_addr, &olen) <= 0) {

		}
		cout << "here" << endl;
		string s(recvbuffer);
		s = cleanZero(s);
		s = useAESdecrypt(s);
		WriteFile(s);
		cout << "保存成功" << endl;
		while (true) {

		}
		return;
	}
	cout << "错误的输入" << endl;
}
int main() {
	realmain();
	//initalNeeded();//初始化socket什么的
	//allocKey();
	
	//string s=readFile();
	//s= useAESencrypt(s);
	//s = useAESdecrypt(s);
	//WriteFile(s);

	//string s = useAESencrypt("3243f6a8885a308d313198a2e03707345678abcd");
	//cout << "最终密文为";
	//cout << s << endl;
	//s = useAESdecrypt(s);
	//cout << "最终明文为";
	//cout << s << endl;

	//Interaction();

	//myRSA();

	/*string s = encrypt_B_public("A1");
	cout << s << endl;*/

	/*string s = decrypt_A_private("3B0435391380D87FAC04BE721057CC61");
	cout << s << endl;*/

	/*string s = encrypt_A_private("ABCD");
	cout << s << endl;*/
}