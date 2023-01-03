#include"BigInt.h"
#include"RSA.h"
#include"socket.h"
using namespace std;
string N1 = "0";
string N2 = "1";
string IDA = "A";
string AESKey;
string cleanString(string s) {
	int end=s.size()-1;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == 0) { end = i - 1; }
	}
	return s.substr(0, end + 1);
}
int AllocKey() {
	//第一次接收
	char* recvbuffer = new char[10000];
	memset(recvbuffer, 0, 10000);
	recvfrom(mySocket, recvbuffer, 10000, 0, (sockaddr*)&oppo_addr, &olen);
	string s = recvbuffer;
	s = cleanString(s);
	cout << "第一次身份认证密文为" << s << endl;
	if (s.substr(0, 6) == "[IDEN]") {
		s = s.substr(6, 10000);
		cout << "第一次身份认证匹配成功" << endl;
	}
	cout << s << endl;
	s = decrypt_B_private(s);
	cout << "第一次身份认证明文为" << s << endl;
	if (s == N1 + IDA) {
		cout << "第一次身份确认成功" << endl;
	}
	else {
		cout << "第一次身份认证失败" << endl;
		return -1;
	}

	//发送身份确认
	cout << "第二次身份认证明文为" <<  N1 + N2 << endl;
	string t = encrypt_A_public(N1 + N2);
	t = "[IDEN]" + t;
	cout << "第二次身份认证密文为" << t << endl;
	char* sendbuffer = new char[10000];
	memset(sendbuffer, 0, 10000);
	memcpy(sendbuffer, t.c_str(), t.size());
	sendto(mySocket, sendbuffer, 10000, 0, (sockaddr*)&oppo_addr, olen);

	//接受第三次身份确认信息
	memset(recvbuffer, 0, 10000);
	recvfrom(mySocket, recvbuffer, 10000, 0, (sockaddr*)&oppo_addr, &olen);
	s = recvbuffer;
	cout << "第三次身份认证密文为" << s << endl;
	if (s.substr(0, 6) == "[IDEN]") {
		s = s.substr(6, 10000);
		cout << "第三次身份认证匹配成功" << endl;
	}
	s = decrypt_B_private(s);
	cout << "第三次身份认证明文为" << s << endl;
	if (s == N2) {
		cout << "第三次身份确认成功" << endl;
	}
	else {
		cout << "第三次身份确认失败" << endl;
		return -1;
	}

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
			cout << "here1" << endl;
			continue;
		}
		if (temp.substr(0, 6) == "[key2]") {
			temp = temp.substr(6, 10000);
			vs2.push_back(temp);
			cout << "here2" << endl;
			continue;
		}
		if (temp.substr(0, 6) == "[OVER]") {
			cout << "密钥组件接收完成" << endl;
			cout << "here3" << endl;
			break;
		}
	}
	//重组AES密钥
	string temp1, temp2;
	for (int i = 0; i < vs1.size(); i++) {
		cout << "第一部分第" << i + 1 << "组密文表示为" << vs1[i] << endl;
		vs1[i] = decrypt_B_private(vs1[i]);
		cout << "第一部分第" << i + 1 << "组明文表示为" << vs1[i] << endl;
		temp1.append(vs1[i]);
	}
	for (int i = 0; i < vs2.size(); i++) {
		cout << "第二部分第" << i + 1 << "组密文表示为" << vs2[i] << endl;
		vs2[i] = decrypt_B_private(vs2[i]);
		cout << "第二部分第" << i + 1 << "组明文表示为" << vs2[i] << endl;
		temp2.append(vs2[i]);
	}
	cout << "第一部分最终密文为" << temp1 << endl;
	temp1 = decrypt_A_public(temp1);
	cout << "第一部分最终明文为" << temp1 << endl;
	cout << "第二部分最终密文为" << temp2 << endl;
	temp2 = decrypt_A_public(temp2);
	cout << "第二部分最终明文为" << temp2 << endl;
	AESKey.append(temp1);
	AESKey.append(temp2);
	cout << "AESKey接收完毕:" << AESKey << endl;
}
int main() {
	initalNeeded();//初始化socket什么的
	AllocKey();
	
	/*string s = decrypt_B_private("959B19486DFC11EB6EB62EE3993EEA4F");
	cout << s << endl;*/

	/*string s = encrypt_A_public("01");
	cout << s << endl;*/

	/*string s = decrypt_A_public("7D6E4CA0B56D98A9FDF5FEDDBC03D03760");
	cout << s << endl;*/
}