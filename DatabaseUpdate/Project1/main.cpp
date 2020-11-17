#include <windows.h>
#include <iostream>
#include <fstream>
#include <assert.h>
#include <mysql.h>
#include <string>
using namespace std;
int main() {

	//��ȡ�ļ���ȡ��Ϣ
	ifstream f_inifile;
	char buff[255];
	f_inifile.open("HF1.2B_Config.ini");
	if (!f_inifile.is_open()){
		cout << "���ô�ʧ��ʧ��!" << endl;
		system("pause");
		return 0;
	}

	string host;
	string user;
	string password;
	string database;
	string port;
	while (f_inifile.getline(buff, 255)){
		string line(buff);
		if (line.find("host") != -1){
			host = line.substr(5, line.size());
		}
		if (line.find("user") != -1){
			user = line.substr(5, line.size());
		}
		if (line.find("password") != -1){
			password = line.substr(9, line.size());
		}
		if (line.find("database") != -1){
			database = line.substr(9, line.size());
		}
		if (line.find("port") != -1){
			port = line.substr(5, line.size());
		}
		if (host.size()>0&&user.size()>0&&password.size()>0&&database.size()>0&&port.size()>0)
		{
			break;
		}
	}
	if (host.size() == 0 || user.size() == 0 || password.size() == 0 || database.size() == 0 || port.size() == 0)
	{
		cout << "������Ϣȱʧ,���ini�ļ�" << endl;
		system("pause");
		return 0;
	}
	f_inifile.close();

	MYSQL conn;
	mysql_init(&conn);

	ifstream f_patched;
	if (!mysql_real_connect(&conn, host.c_str(), user.c_str(), password.c_str(), database.c_str(), stoi(port), NULL, 0)) {
		cout << "�������ݿ�ʧ��!" << mysql_error(&conn) << endl;
		system("pause");
		return 0;
	}
	else {
		f_patched.open("patch.txt");
		if (!f_patched.is_open()){
			cout << "��ȡ�����ļ�ʧ��." << endl;
			system("pause");
			return 0;
		}
		int i = 1;
		while (f_patched.getline(buff,255)){
			if (mysql_query(&conn, buff)) {//ͨ��mysql_query����ִ��SQL���
				cout << "��" << i << "�����ִ��ʧ��!!����SQL���!" << endl;
				cout << mysql_error(&conn) << endl;
				system("pause");
				return 0;
			}
			else{
				cout << "��" << i << "�����ִ�гɹ�" << endl;
			}
			i++;
		}
	}
	cout << "=======" << endl;
	cout << "���³ɹ�" << endl;
	cout << "=======" << endl;
	f_patched.close();
	mysql_close(&conn);
	system("pause");
	return 0;
}