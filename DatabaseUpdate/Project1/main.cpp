#include <windows.h>
#include <iostream>
#include <fstream>
#include <assert.h>
#include <mysql.h>
#include <string>
using namespace std;
int main() {

	//读取文件获取信息
	ifstream f_inifile;
	char buff[255];
	f_inifile.open("HF1.2B_Config.ini");
	if (!f_inifile.is_open()){
		cout << "配置打开失败失败!" << endl;
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
		cout << "配置信息缺失,检查ini文件" << endl;
		system("pause");
		return 0;
	}
	f_inifile.close();

	MYSQL conn;
	mysql_init(&conn);

	ifstream f_patched;
	if (!mysql_real_connect(&conn, host.c_str(), user.c_str(), password.c_str(), database.c_str(), stoi(port), NULL, 0)) {
		cout << "连接数据库失败!" << mysql_error(&conn) << endl;
		system("pause");
		return 0;
	}
	else {
		f_patched.open("patch.txt");
		if (!f_patched.is_open()){
			cout << "读取更新文件失败." << endl;
			system("pause");
			return 0;
		}
		int i = 1;
		while (f_patched.getline(buff,255)){
			if (mysql_query(&conn, buff)) {//通过mysql_query函数执行SQL语句
				cout << "第" << i << "条语句执行失败!!请检查SQL语句!" << endl;
				cout << mysql_error(&conn) << endl;
				system("pause");
				return 0;
			}
			else{
				cout << "第" << i << "条语句执行成功" << endl;
			}
			i++;
		}
	}
	cout << "=======" << endl;
	cout << "更新成功" << endl;
	cout << "=======" << endl;
	f_patched.close();
	mysql_close(&conn);
	system("pause");
	return 0;
}