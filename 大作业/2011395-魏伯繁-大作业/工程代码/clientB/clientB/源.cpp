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
	cout << "[TIME] ��ϢʱЧΪ";
	cout << t.wYear << "��" << t.wMonth << "��" << t.wDay << "��" << t.wHour << "ʱ" << t.wMinute << "��" << t.wSecond << "��" << endl;
}
int AllocKey() {
	cout << "                         ***********************************************************************" << endl;
	cout << "                         *             �ɹ���ȡkey.txt�ļ�����¼���RSA��Կ��Ϣ                *" << endl;
	cout << "                         *          ����AES��Կ�Ľ����ߣ��뼰ʱ�ͶԷ�ȷ����������              *" << endl;
	cout << "                         *        ���Է�ȷ���������ߺ󽫽������ȷ���Լ�AES��Կ����            *" << endl;
	cout << "                         ***********************************************************************" << endl;
	//��һ�ν���
	char* recvbuffer = new char[10000];
	memset(recvbuffer, 0, 10000); 
	recvfrom(mySocket, recvbuffer, 10000, 0, (sockaddr*)&oppo_addr, &olen);
	string s = recvbuffer;
	s = cleanString(s);
	cout << "[TIPS] ��һ�ν��յ��������֤����Ϊ:" << s << endl;
	outTime();
	if (s.substr(0, 6) == "[IDEN]") {
		s = s.substr(6, 10000);
		cout << "[TIPS] ��һ�������֤����ֵ�ɹ�,���ڽ���..." << endl;
	}
	//cout << s << endl;
	s = decrypt_B_private(s);
	cout << "[TIPS] ��һ�������֤���ܺ�����Ϊ:" << s << endl;
	if (s == N1 + IDA) {
		cout << "[TIPS] ��һ�����ȷ�ϳɹ�" << endl;
	}
	else {
		cout << "[TIPS] ��һ�������֤ʧ��" << endl;
		return -1;
	}
	cout << endl;
	//�������ȷ��
	cout << "[TIPS] �ڶ��������֤����Ϊ: " <<  N1 + N2 << endl;
	string t = encrypt_A_public(N1 + N2);
	t = "[IDEN]" + t;
	cout << "[TIPS] ���ܺ�ڶ��������֤����Ϊ:" << t << endl;
	char* sendbuffer = new char[10000];
	memset(sendbuffer, 0, 10000);
	memcpy(sendbuffer, t.c_str(), t.size());
	sendto(mySocket, sendbuffer, 10000, 0, (sockaddr*)&oppo_addr, olen);
	cout << endl;
	//���ܵ��������ȷ����Ϣ
	memset(recvbuffer, 0, 10000);
	recvfrom(mySocket, recvbuffer, 10000, 0, (sockaddr*)&oppo_addr, &olen);
	s = recvbuffer;
	cout << "[TIPS] �����������֤����Ϊ: " << s << endl;
	outTime();
	if (s.substr(0, 6) == "[IDEN]") {
		s = s.substr(6, 10000);
		cout << "[TIPS] �����������֤����ֵƥ��ɹ�" << endl;
	}
	s = decrypt_B_private(s);
	cout << "[TIPS] ���ܺ�����������֤����Ϊ: " << s << endl;
	if (s == N2) {
		cout << "[TIPS] ���������ȷ�ϳɹ�" << endl;
	}
	else {
		cout << "[TIPS] ���������ȷ��ʧ��" << endl;
		return -1;
	}
	cout << "[TIPS] ����׼��������Կ..." << endl;
	cout << endl;
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
			cout << "[TIPS] ��Կ����������" << endl;
			outTime();
			//cout << "here3" << endl;
			break;
		}
	}
	//����AES��Կ
	string temp1, temp2;
	for (int i = 0; i < vs1.size(); i++) {
		cout << "[TIPS] AES��Կ��һ���ֵ�" << i + 1 << "�����ı�ʾΪ: " << vs1[i] << endl;
		vs1[i] = decrypt_B_private(vs1[i]);
		cout << "[TIPS] ���ܺ�AES��Կ��һ���ֵ�" << i + 1 << "�����ı�ʾΪ: " << vs1[i] << endl;
		temp1.append(vs1[i]);
	}
	for (int i = 0; i < vs2.size(); i++) {
		cout << "[TIPS] AES��Կ�ڶ����ֵ�" << i + 1 << "�����ı�ʾΪ: " << vs2[i] << endl;
		vs2[i] = decrypt_B_private(vs2[i]);
		cout << "[TIPS] ���ܺ�AES��Կ�ڶ����ֵ�" << i + 1 << "�����ı�ʾΪ: " << vs2[i] << endl;
		temp2.append(vs2[i]);
	}
	cout << "[TIPS] ��һ������������Ϊ: " << temp1 << endl;
	temp1 = decrypt_A_public(temp1);
	cout << "[TIPS] ��һ������������Ϊ: " << temp1 << endl;
	cout << "[TIPS] �ڶ�������������Ϊ: " << temp2 << endl;
	temp2 = decrypt_A_public(temp2);
	cout << "[TIPS] �ڶ�������������Ϊ: " << temp2 << endl;
	AESKey.append(temp1);
	AESKey.append(temp2);
	cout << "[TIPS] AESKey�������,����ʹ�õ�AES��ԿΪ:" << AESKey << endl;
	outTime();
	cout << endl;
}
void realmain() {
	File2Key();
	initalNeeded();//��ʼ��socketʲô��
	AllocKey();
	while (true) {
		cout << "                         ***********************************************************************" << endl;
		cout << "                         *            AES��Կ������ɣ���ѡ�����ڱ��δ����е����              *" << endl;
		cout << "                         *         ����1���������ļ����䷽������2���������ļ����շ�            *" << endl;
		cout << "                         ***********************************************************************" << endl;
		int c1; cin >> c1;
		if (c1 == 1) {
			string s = readFile();
			s = useAESencrypt(s, AESKey);
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
			sendto(mySocket, sendbuffer, s.size(), 0, (sockaddr*)&oppo_addr, olen);
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
				//cout << "here" << endl;
			}
			string s(recvbuffer);
			s = cleanString(s);
			//cout << "s1=" << s << endl;
			s = useAESdecrypt(s, AESKey);
			//cout << "s2=" << s << endl;
			WriteFile(s);
			cout << "[TIPS] ����ɹ�" << endl;
			outTime();
		}
		if(c1!=1&&c1!=2){ cout << "[TIPS] ���������" << endl; }
		cout << "                    ***********************************************************************" << endl;
		cout << "                    *                         ���ִδ����������                          *" << endl;
		cout << "                    *                   ����������һ�ִε��ļ����乤��                    *" << endl;
		cout << "                    ***********************************************************************" << endl;

	}
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