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
	cout << "����AES��Կ�ķ����ߣ��뱣֤�Է��ɹ����ߺ��ٽ�������" << endl;
	cout << "���ڿ����ͻ���B�����룺1��֮�󽫿�ʼ������Կ" << endl;
	cin >> check;
	if (check != 1) { return -1; }
	//�������ʶ��
	string t = N1 + IDA;
	cout << "��һ�������֤����Ϊ" << t << endl;
	t = encrypt_B_public(t);
	t = "[IDEN]" + t;
	cout << "��һ�������֤����Ϊ" << t << endl;
	char* sendbuffer = new char[10000];
	memcpy(sendbuffer, t.c_str(), t.size());
	int ii = sendto(mySocket, sendbuffer, t.size(), 0, (sockaddr*)&oppo_addr, olen);

	//���շ���
	char* recvbuffer = new char[10000];
	memset(recvbuffer, 0, 10000);
	recvfrom(mySocket, recvbuffer, 10000, 0, (sockaddr*)&oppo_addr, &olen);
	string s = recvbuffer;
	s = cleanString(s);
	if (s.substr(0, 6) == "[IDEN]") {
		cout << "�ڶ��������֤ƥ��ɹ�" << endl;
		s = s.substr(6, 10000);
	}
	cout << "�ڶ��������֤����Ϊ" << s << endl;
	s = decrypt_A_private(s);
	cout << "�ڶ��������֤����Ϊ" << s << endl;
	if (s == N1 + N2) {
		cout << "���ȷ�ϳɹ�������������ȷ��" << endl;
	}
	else {
		cout << "�����֤ʧ��" << endl;
		return -1;
	}

	//�ٴ�׼������
	t.clear();
	cout << "�����������֤����Ϊ" << N2 << endl;
	t = encrypt_B_public(N2);
	t = "[IDEN]" + t;
	cout << "�����������֤����Ϊ" << t << endl;
	memset(sendbuffer, 0, 10000);
	memcpy(sendbuffer, t.c_str(), t.size());
	sendto(mySocket, sendbuffer, 10000, 0, (sockaddr*)&oppo_addr, olen);

	Sleep(30 * 1000);

	//׼������AES��Կ�ĵ�һ����
	string key1 = AESKey.substr(0, 16);
	cout << "AES��Կ�и��һ����Ϊ" << key1 << endl;
	key1 = encrypt_A_private(key1);
	cout << "ʹ��A��˽Կ���ܺ�Ϊ" << key1 << endl;
	int i = 0; vector<string>vs;
	while (i < key1.size()) {
		string temp = key1.substr(i, 16); i += 16;
		vs.push_back(temp);
	}
	for (int i = 0; i < vs.size(); i++) {
		cout << "�����и���" << i + 1 << "����Ϊ" << vs[i] << endl;
		vs[i] = encrypt_B_public(vs[i]);
		cout << "ʹ��B�Ĺ�Կ���ܺ�Ϊ" << vs[i] << endl;
		memset(sendbuffer, 0, 10000);
		vs[i] = "[key1]" + vs[i];
		memcpy(sendbuffer, vs[i].c_str(), vs[i].size());
		sendto(mySocket, sendbuffer, 10000, 0, (sockaddr*)&oppo_addr, olen);
	}

	//׼������AES��Կ�ĵڶ�����
	string key2 = AESKey.substr(16, 16);
	cout << "AES��Կ�и�ڶ�����Ϊ" << key2 << endl;
	key2 = encrypt_A_private(key2);
	cout << "ʹ��A��˽Կ���ܺ�Ϊ" << key2 << endl;
	i = 0; vs.clear();
	while (i < key2.size()) {
		string temp = key2.substr(i, 16); i += 16;
		vs.push_back(temp);
	}
	for (int i = 0; i < vs.size(); i++) {
		cout << "�����и���" << i + 1 << "����Ϊ" << vs[i] << endl;
		vs[i] = encrypt_B_public(vs[i]);
		cout << "���ܺ�Ϊ" << vs[i] << endl;
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
	initalNeeded();//��ʼ��socketʲô��
	//allocKey();
	cout << "��ѡ�������շ����Ƿ�����\n ����1������������2�����շ�" << endl;
	int c1; cin >> c1;
	if (c1 == 1) {
		string s = readFile();
		s = useAESencrypt(s);
		char* sendbuffer = new char[10000];
		memcpy(sendbuffer, s.c_str(), s.size());
		cout << "����ȷ�Ͻ��ն˳ɹ�������������ն˳ɹ�������������1\n ���������������Ϣ\n�����ȷ�����ն��Ѿ���ȷѡ�񡰽���ģʽ��" << endl;
		int i = 0; while (i != 1) {
			cin >> i;
		}
		int e=sendto(mySocket, sendbuffer, s.size(), 0, (sockaddr*)&oppo_addr, olen);
		cout << e << endl;
		cout << WSAGetLastError() << endl;
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

		}
		cout << "here" << endl;
		string s(recvbuffer);
		s = cleanZero(s);
		s = useAESdecrypt(s);
		WriteFile(s);
		cout << "����ɹ�" << endl;
		while (true) {

		}
		return;
	}
	cout << "���������" << endl;
}
int main() {
	realmain();
	//initalNeeded();//��ʼ��socketʲô��
	//allocKey();
	
	//string s=readFile();
	//s= useAESencrypt(s);
	//s = useAESdecrypt(s);
	//WriteFile(s);

	//string s = useAESencrypt("3243f6a8885a308d313198a2e03707345678abcd");
	//cout << "��������Ϊ";
	//cout << s << endl;
	//s = useAESdecrypt(s);
	//cout << "��������Ϊ";
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