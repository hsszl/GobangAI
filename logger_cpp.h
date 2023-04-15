#define _CRT_SECURE_NO_DEPRECATE

#include<fstream>
#include<iostream>
#include<io.h>
#include<direct.h>
#include<ctime>
#include<string>

using namespace std;
#define TRACE 0
#define DEBUG 1
#define INFO 2
#define WARNING 3
#define ERROR 4
#define EXCEPTION 5

string name;
fstream f;
int e_level;

int init(string name_, int level_) {
	name = name_;                           // logger名
	e_level = level_;                         // 打印最低等级

	string prefix = "./log/";
	if (_access(prefix.c_str(), 0) == -1) {	//文件夹是否存在 
		_mkdir(prefix.c_str());
	}

	time_t now = time(0);
	tm* ltm = localtime(&now);
	string now_s = "log/" + to_string(1900 + ltm->tm_year) + "-" + to_string(1 + ltm->tm_mon) + "-" + to_string(ltm->tm_mday) + "-" +
		to_string(ltm->tm_hour) + "-" + to_string(ltm->tm_min) + "-" + to_string(ltm->tm_sec) + ".log";
	cout << "日志地址：" << now_s << endl;
	ofstream MyFile(now_s);
	MyFile.close();
	f.open(now_s, ios::out);

	return 0;
}

int log(string log_info, int level, string error_level) {
	time_t now = time(0);
	tm* ltm = localtime(&now);
	string log_s = "[" + name + "][" + to_string(ltm->tm_hour) + ":" + to_string(ltm->tm_min) + ":" + to_string(ltm->tm_sec) + "][" + error_level + "]:" + log_info;
	f << log_s << endl;
	if (level >= e_level) cout << log_s << endl;
	return 0;
}

void trace(string log_info) { log(log_info, TRACE, "TRACE"); }
void debug(string log_info) { log(log_info, DEBUG, "DEBUG"); }
void info(string log_info) { log(log_info, INFO, "INFO"); }
void warning(string log_info) { log(log_info, WARNING, "WARNING"); }
void error(string log_info) { log(log_info, ERROR, "ERROR"); }
void exception_(string log_info) { log(log_info, EXCEPTION, "EXCEPTION"); }

void file_close() { f.close(); }
