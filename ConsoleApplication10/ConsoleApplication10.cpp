// ConsoleApplication10.cpp : �������̨Ӧ�ó������ڵ㡣
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
		cout << "1.����ԤԼ" << endl;
		cout << "2.��ʾ����ԤԼ" << endl;
		cout << "3.�뿪" << endl;
		cout << "4.ɾ��ԤԼ" << endl;
		cout << "5.��ѯ" << endl;
		
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

