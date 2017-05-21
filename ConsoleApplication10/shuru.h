#pragma once
#include<string>
using namespace std;

class iodat
{
public:
	void inputdata();
	void outputdata();
	void createtable();
	int returnrows();
	void deletedata();
	
	void selectdata();
private:
	char name[50];
	char date[50];
	char time[50];
	int number;
	char *sql;

};
int callback(void *NotUsed, int argc, char **argv, char **azColName);
int callback2(void *NotUsed, int argc, char **argv, char **azColName);
string quotesql(const string& s);
char* G2U(const char* gb2312);
char* U2G(const char* utf8);