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
	char buff[100];
	f_inifile.open("HF1.2B_Config.ini");

	if (!f_inifile.is_open()){
		cout << "���ö�ȡʧ��!" << endl;
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
	}
	//f_inifile.close();

	MYSQL conn;
	mysql_init(&conn);

	if (!mysql_real_connect(&conn, host.c_str(), user.c_str(), password.c_str(), database.c_str(), stoi(port), NULL, 0)) {
		cout << "Failed to connect to database: Error:" << mysql_error(&conn) << endl;
	}
	else {
		ifstream f_patched;
		f_patched.open("patch.txt");
		if (!f_patched.is_open()){
			cout << "��ȡ�����ļ�ʧ��." << endl;
		}
		int i = 1;
		while (f_patched.getline(buff,255)){
			if (mysql_query(&conn, buff)) {//ͨ��mysql_query����ִ��SQL���
				cout << mysql_error(&conn) << endl;
			}
			else{
				cout << "��" << i << "�����ִ�гɹ�" << endl;
			}
			i++;
		}
		//f_patched.close();
	}
	mysql_close(&conn);
	system("pause");
}