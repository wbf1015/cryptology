#include"BigInt.h"
#include"RSA.h"
#include"socket.h"
#include"AES.h"
#include"dealFile.h"
using namespace std;
string N1 = "0";
string N2 = "1";
string IDA = "A";
string AESKey="2b7e151628aed2a6abf7158809cf4f3c";
string cleanString(string s) {
	int end=s.size()-1;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == 0) { end = i - 1; }
	}
	return s.substr(0, end + 1);
}
int AllocKey() {
	//��һ�ν���
	char* recvbuffer = new char[10000];
	memset(recvbuffer, 0, 10000);
	recvfrom(mySocket, recvbuffer, 10000, 0, (sockaddr*)&oppo_addr, &olen);
	string s = recvbuffer;
	s = cleanString(s);
	cout << "��һ�������֤����Ϊ" << s << endl;
	if (s.substr(0, 6) == "[IDEN]") {
		s = s.substr(6, 10000);
		cout << "��һ�������֤ƥ��ɹ�" << endl;
	}
	cout << s << endl;
	s = decrypt_B_private(s);
	cout << "��һ�������֤����Ϊ" << s << endl;
	if (s == N1 + IDA) {
		cout << "��һ�����ȷ�ϳɹ�" << endl;
	}
	else {
		cout << "��һ�������֤ʧ��" << endl;
		return -1;
	}

	//�������ȷ��
	cout << "�ڶ��������֤����Ϊ" <<  N1 + N2 << endl;
	string t = encrypt_A_public(N1 + N2);
	t = "[IDEN]" + t;
	cout << "�ڶ��������֤����Ϊ" << t << endl;
	char* sendbuffer = new char[10000];
	memset(sendbuffer, 0, 10000);
	memcpy(sendbuffer, t.c_str(), t.size());
	sendto(mySocket, sendbuffer, 10000, 0, (sockaddr*)&oppo_addr, olen);

	//���ܵ��������ȷ����Ϣ
	memset(recvbuffer, 0, 10000);
	recvfrom(mySocket, recvbuffer, 10000, 0, (sockaddr*)&oppo_addr, &olen);
	s = recvbuffer;
	cout << "�����������֤����Ϊ" << s << endl;
	if (s.substr(0, 6) == "[IDEN]") {
		s = s.substr(6, 10000);
		cout << "�����������֤ƥ��ɹ�" << endl;
	}
	s = decrypt_B_private(s);
	cout << "�����������֤����Ϊ" << s << endl;
	if (s == N2) {
		cout << "���������ȷ�ϳɹ�" << endl;
	}
	else {
		cout << "���������ȷ��ʧ��" << endl;
		return -1;
	}

	//����AES��Կ
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
			cout << "��Կ����������" << endl;
			cout << "here3" << endl;
			break;
		}
	}
	//����AES��Կ
	string temp1, temp2;
	for (int i = 0; i < vs1.size(); i++) {
		cout << "��һ���ֵ�" << i + 1 << "�����ı�ʾΪ" << vs1[i] << endl;
		vs1[i] = decrypt_B_private(vs1[i]);
		cout << "��һ���ֵ�" << i + 1 << "�����ı�ʾΪ" << vs1[i] << endl;
		temp1.append(vs1[i]);
	}
	for (int i = 0; i < vs2.size(); i++) {
		cout << "�ڶ����ֵ�" << i + 1 << "�����ı�ʾΪ" << vs2[i] << endl;
		vs2[i] = decrypt_B_private(vs2[i]);
		cout << "�ڶ����ֵ�" << i + 1 << "�����ı�ʾΪ" << vs2[i] << endl;
		temp2.append(vs2[i]);
	}
	cout << "��һ������������Ϊ" << temp1 << endl;
	temp1 = decrypt_A_public(temp1);
	cout << "��һ������������Ϊ" << temp1 << endl;
	cout << "�ڶ�������������Ϊ" << temp2 << endl;
	temp2 = decrypt_A_public(temp2);
	cout << "�ڶ�������������Ϊ" << temp2 << endl;
	AESKey.append(temp1);
	AESKey.append(temp2);
	cout << "AESKey�������:" << AESKey << endl;
}
void realmain() {
	initalNeeded();//��ʼ��socketʲô��
	//AllocKey();
	cout << "��ѡ�������շ����Ƿ�����\n ����1������������2�����շ�" << endl;
	int c1; cin >> c1;
	if (c1 == 1) {
		string s = readFile();
		s = useAESencrypt(s, AESKey);
		char* sendbuffer = new char[10000];
		memcpy(sendbuffer, s.c_str(), s.size());
		cout << "����ȷ�Ͻ��ն˳ɹ�������������ն˳ɹ�������������1\n ���������������Ϣ\n�����ȷ�����ն��Ѿ���ȷѡ�񡰽���ģʽ��" << endl;
		int i = 0; while (i != 1) {
			cin >> i;
		}
		sendto(mySocket, sendbuffer, s.size(), 0, (sockaddr*)&oppo_addr, olen);
		cout << "���ͳɹ�" << endl;
		while (true) {

		}
		return;
	}
	if (c1 == 2) {
		char* recvbuffer = new char[10000];
		memset(recvbuffer, 0, 10000);
		cout << "�ͻ���׼�����" << endl;
		while (recvfrom(mySocket, recvbuffer, 10000, 0, (sockaddr*)&oppo_addr, &olen) <= 0) {
			//cout << "here" << endl;
		}
		string s(recvbuffer);
		s = cleanZero(s);
		cout << "s1=" << s << endl;
		s = useAESdecrypt(s, AESKey);
		cout << "s2=" << s << endl;
		WriteFile(s);
		cout << "����ɹ�" << endl;
		while (true) {

		}
		return; 
	}
	cout << "���������" << endl;
}
int main() {
	//initalNeeded();//��ʼ��socketʲô��
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