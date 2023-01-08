#include"BigInt.h"
#include"RSA.h"
#include"socket.h"
#include"AES.h"
#include"dealFile.h"
using namespace std;
string N1 = "0";
string N2 = "1";
string IDA = "A";
string AESKey="";
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
int AllocKey() {
	cout << "                         ***********************************************************************" << endl;
	cout << "                         *             成功读取key.txt文件中您录入的RSA密钥信息                *" << endl;
	cout << "                         *          您是AES密钥的接受者，请及时和对方确认您已上线              *" << endl;
	cout << "                         *        待对方确认您已上线后将进行身份确认以及AES密钥分配            *" << endl;
	cout << "                         ***********************************************************************" << endl;
	//第一次接收
	char* recvbuffer = new char[10000];
	memset(recvbuffer, 0, 10000); 
	recvfrom(mySocket, recvbuffer, 10000, 0, (sockaddr*)&oppo_addr, &olen);
	string s = recvbuffer;
	s = cleanString(s);
	cout << "[TIPS] 第一次接收到的身份认证密文为:" << s << endl;
	outTime();
	if (s.substr(0, 6) == "[IDEN]") {
		s = s.substr(6, 10000);
		cout << "[TIPS] 第一次身份认证特征值成功,正在解密..." << endl;
	}
	//cout << s << endl;
	s = decrypt_B_private(s);
	cout << "[TIPS] 第一次身份认证解密后明文为:" << s << endl;
	if (s == N1 + IDA) {
		cout << "[TIPS] 第一次身份确认成功" << endl;
	}
	else {
		cout << "[TIPS] 第一次身份认证失败" << endl;
		return -1;
	}
	cout << endl;
	//发送身份确认
	cout << "[TIPS] 第二次身份认证明文为: " <<  N1 + N2 << endl;
	string t = encrypt_A_public(N1 + N2);
	t = "[IDEN]" + t;
	cout << "[TIPS] 加密后第二次身份认证密文为:" << t << endl;
	char* sendbuffer = new char[10000];
	memset(sendbuffer, 0, 10000);
	memcpy(sendbuffer, t.c_str(), t.size());
	sendto(mySocket, sendbuffer, 10000, 0, (sockaddr*)&oppo_addr, olen);
	cout << endl;
	//接受第三次身份确认信息
	memset(recvbuffer, 0, 10000);
	recvfrom(mySocket, recvbuffer, 10000, 0, (sockaddr*)&oppo_addr, &olen);
	s = recvbuffer;
	cout << "[TIPS] 第三次身份认证密文为: " << s << endl;
	outTime();
	if (s.substr(0, 6) == "[IDEN]") {
		s = s.substr(6, 10000);
		cout << "[TIPS] 第三次身份认证特征值匹配成功" << endl;
	}
	s = decrypt_B_private(s);
	cout << "[TIPS] 解密后第三次身份认证明文为: " << s << endl;
	if (s == N2) {
		cout << "[TIPS] 第三次身份确认成功" << endl;
	}
	else {
		cout << "[TIPS] 第三次身份确认失败" << endl;
		return -1;
	}
	cout << "[TIPS] 正在准备接收密钥..." << endl;
	cout << endl;
	//接收AES密钥
	vector<string>vs1; vector<string>vs2;
	while (true) {
		memset(recvbuffer, 0, 10000);
		recvfrom(mySocket, recvbuffer, 10000, 0, (sockaddr*)&oppo_addr, &olen);
		string temp = recvbuffer;
		temp = cleanString(temp);
		if (temp.substr(0, 6) == "[key1]") {
			temp = temp.substr(6, 10000);
			vs1.push_back(temp);
			//cout << "here1" << endl;
			continue;
		}
		if (temp.substr(0, 6) == "[key2]") {
			temp = temp.substr(6, 10000);
			vs2.push_back(temp);
			//cout << "here2" << endl;
			continue;
		}
		if (temp.substr(0, 6) == "[OVER]") {
			cout << "[TIPS] 密钥组件接收完成" << endl;
			outTime();
			//cout << "here3" << endl;
			break;
		}
	}
	//重组AES密钥
	string temp1, temp2;
	for (int i = 0; i < vs1.size(); i++) {
		cout << "[TIPS] AES密钥第一部分第" << i + 1 << "组密文表示为: " << vs1[i] << endl;
		vs1[i] = decrypt_B_private(vs1[i]);
		cout << "[TIPS] 解密后AES密钥第一部分第" << i + 1 << "组明文表示为: " << vs1[i] << endl;
		temp1.append(vs1[i]);
	}
	for (int i = 0; i < vs2.size(); i++) {
		cout << "[TIPS] AES密钥第二部分第" << i + 1 << "组密文表示为: " << vs2[i] << endl;
		vs2[i] = decrypt_B_private(vs2[i]);
		cout << "[TIPS] 解密后AES密钥第二部分第" << i + 1 << "组明文表示为: " << vs2[i] << endl;
		temp2.append(vs2[i]);
	}
	cout << "[TIPS] 第一部分最终密文为: " << temp1 << endl;
	temp1 = decrypt_A_public(temp1);
	cout << "[TIPS] 第一部分最终明文为: " << temp1 << endl;
	cout << "[TIPS] 第二部分最终密文为: " << temp2 << endl;
	temp2 = decrypt_A_public(temp2);
	cout << "[TIPS] 第二部分最终明文为: " << temp2 << endl;
	AESKey.append(temp1);
	AESKey.append(temp2);
	cout << "[TIPS] AESKey接收完毕,最终使用的AES密钥为:" << AESKey << endl;
	outTime();
	cout << endl;
}
void realmain() {
	File2Key();
	initalNeeded();//初始化socket什么的
	AllocKey();
	while (true) {
		cout << "                         ***********************************************************************" << endl;
		cout << "                         *            AES密钥交换完成，请选择您在本次传输中的身份              *" << endl;
		cout << "                         *         输入1代表您是文件传输方，输入2代表您是文件接收方            *" << endl;
		cout << "                         ***********************************************************************" << endl;
		int c1; cin >> c1;
		if (c1 == 1) {
			string s = readFile();
			s = useAESencrypt(s, AESKey);
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
			sendto(mySocket, sendbuffer, s.size(), 0, (sockaddr*)&oppo_addr, olen);
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
				//cout << "here" << endl;
			}
			string s(recvbuffer);
			s = cleanString(s);
			//cout << "s1=" << s << endl;
			s = useAESdecrypt(s, AESKey);
			//cout << "s2=" << s << endl;
			WriteFile(s);
			cout << "[TIPS] 保存成功" << endl;
			outTime();
		}
		if(c1!=1&&c1!=2){ cout << "[TIPS] 错误的输入" << endl; }
		cout << "                    ***********************************************************************" << endl;
		cout << "                    *                         本轮次传输任务完成                          *" << endl;
		cout << "                    *                   即将开启下一轮次的文件传输工作                    *" << endl;
		cout << "                    ***********************************************************************" << endl;

	}
}
int main() {
	//initalNeeded();//初始化socket什么的
	//AllocKey();

	/*string s = readFile();
	s = useAESencrypt(s,AESKey);
	s = useAESdecrypt(s,AESKey);
	WriteFile(s);*/
	realmain();
	
	/*string s = decrypt_B_private("959B19486DFC11EB6EB62EE3993EEA4F");
	cout << s << endl;*/

	/*string s = encrypt_A_public("01");
	cout << s << endl;*/

	/*string s = decrypt_A_public("7D6E4CA0B56D98A9FDF5FEDDBC03D03760");
	cout << s << endl;*/
}