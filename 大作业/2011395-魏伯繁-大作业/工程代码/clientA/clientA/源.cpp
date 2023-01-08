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
	cout << "[TIME] ��ϢʱЧΪ";
	cout << t.wYear << "��" << t.wMonth << "��" << t.wDay << "��" << t.wHour << "ʱ" << t.wMinute << "��" << t.wSecond << "��" << endl;
}
int allocKey() {
	int check;
	cout << "                       ***********************************************************************" << endl;
	cout << "                       *             �ɹ���ȡkey.txt�ļ�����¼���RSA��Կ��Ϣ                *" << endl;
	cout << "                       *       ����AES��Կ�ķ����ߣ��뱣֤�Է��ɹ����ߺ��ٽ�������           *" << endl;
	cout << "                       *        ����ȷ���ͻ���B���������룺1��֮�󽫿�ʼ������Կ             *" << endl;
	cout << "                       ***********************************************************************" << endl;
	cin >> check;
	if (check != 1) { return -1; }
	//�������ʶ��
	string t = N1 + IDA;
	cout << "[TIPS] ��һ�������֤����Ϊ: " << t << endl;
	t = encrypt_B_public(t);
	t = "[IDEN]" + t;
	cout << "[TIPS] ʹ��RSA���ܺ��һ�������֤����Ϊ: " << t << endl;
	char* sendbuffer = new char[10000];
	memcpy(sendbuffer, t.c_str(), t.size());
	int ii = sendto(mySocket, sendbuffer, t.size(), 0, (sockaddr*)&oppo_addr, olen);
	cout << endl;
	//���շ���
	char* recvbuffer = new char[10000];
	memset(recvbuffer, 0, 10000);
	recvfrom(mySocket, recvbuffer, 10000, 0, (sockaddr*)&oppo_addr, &olen);
	string s = recvbuffer;
	s = cleanString(s);
	if (s.substr(0, 6) == "[IDEN]") {
		cout << "[TIPS] �ڶ��������֤ƥ��ɹ�" << endl;
		s = s.substr(6, 10000);
	}
	cout << "[TIPS] �ڶ��������֤����Ϊ: " << s << endl;
	outTime();
	s = decrypt_A_private(s);
	cout << "[TIPS] ���ܺ�ڶ��������֤����Ϊ: " << s << endl;
	if (s == N1 + N2) {
		cout << "[TIPS] ���ȷ�ϳɹ�������������ȷ��" << endl;
	}
	else {
		cout << "[TIPS] �����֤ʧ��" << endl;
		return -1;
	}
	cout << endl;
	//�ٴ�׼������
	t.clear();
	cout << "[TIPS] �����������֤����Ϊ: " << N2 << endl;
	t = encrypt_B_public(N2);
	t = "[IDEN]" + t;
	cout << "[TIPS] ���ܺ�����������֤����Ϊ: " << t << endl;
	memset(sendbuffer, 0, 10000);
	memcpy(sendbuffer, t.c_str(), t.size());
	sendto(mySocket, sendbuffer, 10000, 0, (sockaddr*)&oppo_addr, olen);

	Sleep(30 * 1000);
	cout << "[TIPS] ������ʼ��Կ����" << endl;
	//׼������AES��Կ�ĵ�һ����
	string key1 = AESKey.substr(0, 16);
	cout << "[TIPS] AES��Կ�и���һ����Ϊ: " << key1 << endl;
	key1 = encrypt_A_private(key1);
	cout << "[TIPS] ʹ��A��˽Կ���ܺ�Ϊ" << key1 << endl;
	int i = 0; vector<string>vs;
	while (i < key1.size()) {
		string temp = key1.substr(i, 16); i += 16;
		vs.push_back(temp);
	}
	for (int i = 0; i < vs.size(); i++) {
		cout << "[TIPS] ʹ��A��˽Կ���ܺ��������и���" << i + 1 << "����Ϊ: " << vs[i] << endl;
		vs[i] = encrypt_B_public(vs[i]);
		cout << "[TIPS] ʹ��B�Ĺ�Կ���ܺ�Ϊ: " << vs[i] << endl;
		memset(sendbuffer, 0, 10000);
		vs[i] = "[key1]" + vs[i];
		memcpy(sendbuffer, vs[i].c_str(), vs[i].size());
		sendto(mySocket, sendbuffer, 10000, 0, (sockaddr*)&oppo_addr, olen);
	}

	//׼������AES��Կ�ĵڶ�����
	string key2 = AESKey.substr(16, 16);
	cout << "[TIPS] AES��Կ�и�ڶ�����Ϊ: " << key2 << endl;
	key2 = encrypt_A_private(key2);
	cout << "[TIPS] ʹ��A��˽Կ���ܺ�Ϊ: " << key2 << endl;
	i = 0; vs.clear();
	while (i < key2.size()) {
		string temp = key2.substr(i, 16); i += 16;
		vs.push_back(temp);
	}
	for (int i = 0; i < vs.size(); i++) {
		cout << "[TIPS] ʹ��A��˽Կ���ܺ�����и���" << i + 1 << "����Ϊ: " << vs[i] << endl;
		vs[i] = encrypt_B_public(vs[i]);
		cout << "[TIPS] ʹ��B�Ĺ�Կ���ܺ�Ϊ" << vs[i] << endl;
		memset(sendbuffer, 0, 10000);
		vs[i] = "[key2]" + vs[i];
		memcpy(sendbuffer, vs[i].c_str(), vs[i].size());
		sendto(mySocket, sendbuffer, 10000, 0, (sockaddr*)&oppo_addr, olen);
	}

	string last = "[OVER]";
	memset(sendbuffer, 0, 10000);
	memcpy(sendbuffer, last.c_str(), last.size());
	sendto(mySocket, sendbuffer, 10000, 0, (sockaddr*)&oppo_addr, olen);
	cout << "[TIPS] ��Կ���ͳɹ�������ʹ�õ�AES��ԿΪ:" << AESKey << endl;
	outTime();
	cout << endl;
}
void realmain() {
	File2Key();
	initalNeeded();//��ʼ��socketʲô��
	allocKey();
	while (true) {
		cout << "                       ***********************************************************************" << endl;
		cout << "                       *            AES��Կ������ɣ���ѡ�����ڱ��δ����е����              *" << endl;
		cout << "                       *         ����1���������ļ����䷽������2���������ļ����շ�            *" << endl;
		cout << "                       ***********************************************************************" << endl;
		int c1; cin >> c1;
		if (c1 == 1) {
			string s = readFile();
			s = useAESencrypt(s);
			char* sendbuffer = new char[10000];
			memcpy(sendbuffer, s.c_str(), s.size());
			cout << "                    ***********************************************************************" << endl;
			cout << "                    *                    ���Ǳ����ļ������еķ�����...                    *" << endl;
			cout << "                    *        ����ȷ�Ͻ��ն˳ɹ�������������ն˳ɹ�������������1          *" << endl;
			cout << "                    *     ���������������Ϣ�������ȷ�����ն��Ѿ���ȷѡ�񡰽���ģʽ��  *" << endl;
			cout << "                    ***********************************************************************" << endl;
			int i = 0; while (i != 1) {
				cin >> i;
			}
			int e = sendto(mySocket, sendbuffer, s.size(), 0, (sockaddr*)&oppo_addr, olen);
			//cout << e << endl;
			//cout << WSAGetLastError() << endl;
			cout << "[TIPS] �ļ����ͳɹ�" << endl;
			outTime();
		}
		if (c1 == 2) {
			char* recvbuffer = new char[10000];
			memset(recvbuffer, 0, 10000);
			cout << "                    ***********************************************************************" << endl;
			cout << "                    *                    ���Ǳ����ļ������еĽ�����...                    *" << endl;
			cout << "                    *                        ���ѳɹ��������ģʽ                         *" << endl;
			cout << "                    *                   �����ĵȺ��Ͷ�ȷ�ϲ������ļ�                    *" << endl;
			cout << "                    ***********************************************************************" << endl;
			while (recvfrom(mySocket, recvbuffer, 10000, 0, (sockaddr*)&oppo_addr, &olen) <= 0) {

			}
			string s(recvbuffer);
			cout << s << endl;
			s = cleanString(s);
			cout << s << endl;
			s = useAESdecrypt(s);
			WriteFile(s);
			cout << "[TIPS] �ļ����ݱ���ɹ�" << endl;
			outTime();
		}
		if (c1 != 1 && c1 != 2) { cout << "[TIPS] ���������" << endl; }
		cout << "                    ***********************************************************************" << endl;
		cout << "                    *                         ���ִδ����������                          *" << endl;
		cout << "                    *                   ����������һ�ִε��ļ����乤��                    *" << endl;
		cout << "                    ***********************************************************************" << endl;
	}
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