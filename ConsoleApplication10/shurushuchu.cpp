#include "sqlite3.h"
#include "stdafx.h"
#include "shuru.h"
using namespace std;
extern sqlite3 *db;
extern char *zErrMsg;
extern int rc;

char* G2U(const char* gb2312)
{
	int len = MultiByteToWideChar(CP_ACP, 0, gb2312, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	MultiByteToWideChar(CP_ACP, 0, gb2312, -1, wstr, len);
	len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
	return str;
}
char* U2G(const char* utf8)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wstr, len);
	len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, wstr, -1, str, len, NULL, NULL);
	return str;
}
int callback(void *NotUsed, int argc, char **argv, char **azColName) {
	int i;
	for (i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;

}

string quotesql(const string& s) {
	return string("'") + s + string("'");
}
void iodat::createtable()
{
	sql = "CREATE TABLE yudin("  \
		"ID             INTEGER PRIMARY KEY   ,"\
		"NAME           CHAR(50)    NOT NULL," \
		"DATE           CHAR(50)     NOT NULL," \
		"TIME        CHAR(50) ,"\
		"TABNUM         INT);";
	sqlite3_exec(db, sql, callback, 0, &zErrMsg);



}
void iodat::inputdata()
{


	
	cout << "请输入预约内容:预约人名字（张三） 日期（2017-5-17） 时间（午） 桌数（1）" << endl;

	cin >> name;
	cin >> date;
	cin >> time;
	cin >> number;
	char*utfname = G2U(name);
	char*utftime = G2U(time);
	int ids = returnrows();
	ids++;
	string a =
		"INSERT INTO yudin(ID,NAME,DATE,TIME,TABNUM)VALUES(NULL, "
		
		+ quotesql(utfname) + ","
		+ quotesql(date) + ","
		+ quotesql(utftime) + ","
		+ to_string(number) + ");";
	sql = const_cast<char*>(a.c_str());
	sqlite3_exec(db, sql, callback, 0, &zErrMsg);

}

void iodat::outputdata()
{
	sqlite3_stmt *smt;
	string c = "SELECT * FROM yudin";
	string b = "SELECT COUNT(*) FROM yudin";

	sql = const_cast<char*>(b.c_str());
	const char *pztail = sql;
	sqlite3_prepare_v2(db, sql, -1, &smt, &pztail);
	sqlite3_step(smt);
	int rows = sqlite3_column_int(smt, NULL);
	sqlite3_finalize(smt);
	sql = const_cast<char*>(c.c_str());
	pztail = sql;
	sqlite3_prepare_v2(db, sql, -1, &smt, &pztail);
	sqlite3_step(smt);
	int cols = sqlite3_column_count(smt);
	sqlite3_finalize(smt);
	cout << "有" << rows << "行" << cols << "列" << endl;
	sql = const_cast<char*>(c.c_str());
	pztail = sql;
	sqlite3_prepare_v2(db, sql, -1, &smt, &pztail);
	const  char *p;

	cout << "编号   名字    日期   时间   桌数" << endl;
	for (int i = 0; i < rows; i++)
	{
		sqlite3_step(smt);

		for (int j = 0; j < cols; j++)
		{

			p = (char*)sqlite3_column_text(smt, j);

			cout << U2G(p) << "    ";
		}
		cout << endl;

	}

	sqlite3_finalize(smt);

}
void iodat::deletedata() 
{
	int id;
	cout << "请输入要删除的id" << endl;
	cin >> id;
	sqlite3_stmt *smt;
	string c = "DELETE FROM yudin WHERE ID = " + to_string(id) + ";";
	sql = const_cast<char*>(c.c_str());
	const char *pztail = sql;
	sqlite3_prepare_v2(db, sql, -1, &smt, &pztail);
	sqlite3_step(smt);
	sqlite3_finalize(smt);
}

int iodat::returnrows() 
{
	sqlite3_stmt *smt;
	string b = "SELECT COUNT(*) FROM yudin";
	sql = const_cast<char*>(b.c_str());
	const char *pztail = sql;
	sqlite3_prepare_v2(db, sql, -1, &smt, &pztail);
	sqlite3_step(smt);
	int rows = sqlite3_column_int(smt, NULL);
	sqlite3_finalize(smt);
	return rows;
}