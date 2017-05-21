// ConsoleApplication10.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "shuru.h"
#include "sqlite3.h"

sqlite3 *db;
char *zErrMsg = 0;
int rc;
int main()
{
	
	
	rc = sqlite3_open("test.db", &db);

	if (rc) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		
	}
	else {
		fprintf(stderr, "Opened database successfully\n");
	}
	iodat a;
	a.createtable();
	int i;
	do {
		cout << "1.新增预约" << endl;
		cout << "2.显示所有预约" << endl;
		cout << "3.离开" << endl;
		cout << "4.删除预约" << endl;
		cout << "5.查询" << endl;
		
		cin >> i;
		switch (i)
		{
		case 1: {a.inputdata();
			break; }
		case 2: {a.outputdata();
			break; }
		case 3:break;
		case 4: {a.deletedata();
			
			break;
		}
		case 5: {a.selectdata();

			break;
		}
		
		default:
			break;
		}
	} while (i != 3);
	sqlite3_close(db);

	
    return 0; 
}

