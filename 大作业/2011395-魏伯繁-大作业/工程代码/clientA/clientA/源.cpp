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
	if (s.size() == 0) { return ""; }
	string ret(s);
	reverse(s.begin(), s.end());
	while ((int)s[s.size() - 1] == 0) { s.pop_back(); }
	reverse(s.begin(), s.end());
	return ret;
}
void outTime() {
	SYSTEMTIME t;
	GetLocalTime(&t);
	cout << "[TIME] 消息时效为";
	cout << t.wYear << "年" << t.wMonth << "月" << t.wDay << "日" << t.wHour << "时" << t.wMinute << "分" << t.wSecond << "秒" << endl;
}
int allocKey() {
	int check;
	cout << "                       ***********************************************************************" << endl;
	cout << "                       *             成功读取key.txt文件中您录入的RSA密钥信息                *" << endl;
	cout << "                       *       您是AES密钥的分配者，请保证对方成功上线后再进行输入           *" << endl;
	cout << "                       *        请在确保客户端B开启后输入：1，之后将开始交换密钥             *" << endl;
	cout << "                       ***********************************************************************" << endl;
	cin >> check;
	if (check != 1) { return -1; }
	//发送身份识别
	string t = N1 + IDA;
	cout << "[TIPS] 第一次身份认证明文为: " << t << endl;
	t = encrypt_B_public(t);
	t = "[IDEN]" + t;
	cout << "[TIPS] 使用RSA加密后第一次身份认证密文为: " << t << endl;
	char* sendbuffer = new char[10000];
	memcpy(sendbuffer, t.c_str(), t.size());
	int ii = sendto(mySocket, sendbuffer, t.size(), 0, (sockaddr*)&oppo_addr, olen);
	cout << endl;
	//接收反馈
	char* recvbuffer = new char[10000];
	memset(recvbuffer, 0, 10000);
	recvfrom(mySocket, recvbuffer, 10000, 0, (sockaddr*)&oppo_addr, &olen);
	string s = recvbuffer;
	s = cleanString(s);
	if (s.substr(0, 6) == "[IDEN]") {
		cout << "[TIPS] 第二次身份认证匹配成功" << endl;
		s = s.substr(6, 10000);
	}
	cout << "[TIPS] 第二次身份认证密文为: " << s << endl;
	outTime();
	s = decrypt_A_private(s);
	cout << "[TIPS] 解密后第二次身份认证明文为: " << s << endl;
	if (s == N1 + N2) {
		cout << "[TIPS] 身份确认成功，即将进行再确认" << endl;
	}
	else {
		cout << "[TIPS] 身份认证失败" << endl;
		return -1;
	}
	cout << endl;
	//再次准备发送
	t.clear();
	cout << "[TIPS] 第三次身份认证明文为: " << N2 << endl;
	t = encrypt_B_public(N2);
	t = "[IDEN]" + t;
	cout << "[TIPS] 加密后第三次身份认证密文为: " << t << endl;
	memset(sendbuffer, 0, 10000);
	memcpy(sendbuffer, t.c_str(), t.size());
	sendto(mySocket, sendbuffer, 10000, 0, (sockaddr*)&oppo_addr, olen);

	Sleep(30 * 1000);
	cout << "[TIPS] 即将开始密钥传输" << endl;
	//准备发送AES密钥的第一部分
	string key1 = AESKey.substr(0, 16);
	cout << "[TIPS] AES密钥切割后第一部分为: " << key1 << endl;
	key1 = encrypt_A_private(key1);
	cout << "[TIPS] 使用A的私钥加密后为" << key1 << endl;
	int i = 0; vector<string>vs;
	while (i < key1.size()) {
		string temp = key1.substr(i, 16); i += 16;
		vs.push_back(temp);
	}
	for (int i = 0; i < vs.size(); i++) {
		cout << "[TIPS] 使用A的私钥加密后做二次切割后第" << i + 1 << "部分为: " << vs[i] << endl;
		vs[i] = encrypt_B_public(vs[i]);
		cout << "[TIPS] 使用B的公钥加密后为: " << vs[i] << endl;
		memset(sendbuffer, 0, 10000);
		vs[i] = "[key1]" + vs[i];
		memcpy(sendbuffer, vs[i].c_str(), vs[i].size());
		sendto(mySocket, sendbuffer, 10000, 0, (sockaddr*)&oppo_addr, olen);
	}

	//准备发送AES密钥的第二部分
	string key2 = AESKey.substr(16, 16);
	cout << "[TIPS] AES密钥切割第二部分为: " << key2 << endl;
	key2 = encrypt_A_private(key2);
	cout << "[TIPS] 使用A的私钥加密后为: " << key2 << endl;
	i = 0; vs.clear();
	while (i < key2.size()) {
		string temp = key2.substr(i, 16); i += 16;
		vs.push_back(temp);
	}
	for (int i = 0; i < vs.size(); i++) {
		cout << "[TIPS] 使用A的私钥加密后二次切割后第" << i + 1 << "部分为: " << vs[i] << endl;
		vs[i] = encrypt_B_public(vs[i]);
		cout << "[TIPS] 使用B的公钥加密后为" << vs[i] << endl;
		memset(sendbuffer, 0, 10000);
		vs[i] = "[key2]" + vs[i];
		memcpy(sendbuffer, vs[i].c_str(), vs[i].size());
		sendto(mySocket, sendbuffer, 10000, 0, (sockaddr*)&oppo_addr, olen);
	}

	string last = "[OVER]";
	memset(sendbuffer, 0, 10000);
	memcpy(sendbuffer, last.c_str(), last.size());
	sendto(mySocket, sendbuffer, 10000, 0, (sockaddr*)&oppo_addr, olen);
	cout << "[TIPS] 密钥发送成功，本次使用的AES密钥为:" << AESKey << endl;
	outTime();
	cout << endl;
}
void realmain() {
	File2Key();
	initalNeeded();//初始化socket什么的
	allocKey();
	while (true) {
		cout << "                       ***********************************************************************" << endl;
		cout << "                       *            AES密钥交换完成，请选择您在本次传输中的身份              *" << endl;
		cout << "                       *         输入1代表您是文件传输方，输入2代表您是文件接收方            *" << endl;
		cout << "                       ***********************************************************************" << endl;
		int c1; cin >> c1;
		if (c1 == 1) {
			string s = readFile();
			s = useAESencrypt(s);
			char* sendbuffer = new char[10000];
			memcpy(sendbuffer, s.c_str(), s.size());
			cout << "                    ***********************************************************************" << endl;
			cout << "                    *                    您是本次文件传输中的发送者...                    *" << endl;
			cout << "                    *        请先确认接收端成功开启，如果接收端成功开启，请输入1          *" << endl;
			cout << "                    *     输入后将立即发送消息，请务必确保接收端已经正确选择“接收模式”  *" << endl;
			cout << "                    ***********************************************************************" << endl;
			int i = 0; while (i != 1) {
				cin >> i;
			}
			int e = sendto(mySocket, sendbuffer, s.size(), 0, (sockaddr*)&oppo_addr, olen);
			//cout << e << endl;
			//cout << WSAGetLastError() << endl;
			cout << "[TIPS] 文件发送成功" << endl;
			outTime();
		}
		if (c1 == 2) {
			char* recvbuffer = new char[10000];
			memset(recvbuffer, 0, 10000);
			cout << "                    ***********************************************************************" << endl;
			cout << "                    *                    您是本次文件传输中的接收者...                    *" << endl;
			cout << "                    *                        您已成功进入接收模式                         *" << endl;
			cout << "                    *                   请耐心等候发送端确认并发送文件                    *" << endl;
			cout << "                    ***********************************************************************" << endl;
			while (recvfrom(mySocket, recvbuffer, 10000, 0, (sockaddr*)&oppo_addr, &olen) <= 0) {

			}
			string s(recvbuffer);
			cout << s << endl;
			s = cleanString(s);
			cout << s << endl;
			s = useAESdecrypt(s);
			WriteFile(s);
			cout << "[TIPS] 文件内容保存成功" << endl;
			outTime();
		}
		if (c1 != 1 && c1 != 2) { cout << "[TIPS] 错误的输入" << endl; }
		cout << "                    ***********************************************************************" << endl;
		cout << "                    *                         本轮次传输任务完成                          *" << endl;
		cout << "                    *                   即将开启下一轮次的文件传输工作                    *" << endl;
		cout << "                    ***********************************************************************" << endl;
	}
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