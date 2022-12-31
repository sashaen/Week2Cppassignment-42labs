#include <iostream>
#include "sqlite-amalgamation-3390400\sqlite3.h"
using namespace std;

static int callback(void* data, int argc, char** argv, char** azColName)
{
	int i;
	fprintf(stderr, "%s: ", (const char*)data);

	for (i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}

	printf("\n");
	return 0;
}

int main(int argc, char** argv)
{
    sqlite3* DB;
	string sql = "CREATE TABLE STUDENT("
					"ROLLNO INT PRIMARY KEY	 NOT NULL, "
					"NAME		 TEXT NOT NULL, "
                    "MATHS		 INT, "
                    "SCIENCE        INT, "
                    "SOCIAL	      INT);";
	int exit = 0;
	exit = sqlite3_open("Experiment.db", &DB);
	char* messaggeError;
	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);

	if (exit != SQLITE_OK) {
		cerr << "Error Create Table" << std::endl;
		sqlite3_free(messaggeError);
	}
	else
		std::cout << "Table created Successfully" << std::endl;

	string query = "SELECT * FROM STUDENT;";

	cout << "STATE OF TABLE BEFORE INSERT" << endl;

	sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);

	sql = "INSERT INTO STUDENT VALUES(1, 'STEVE', 56, 30, 100);"
			"INSERT INTO STUDENT VALUES(2, 'BILL', 78, 80, 32);"
			"INSERT INTO STUDENT VALUES(3, 'PAUL', 89, 24, 99);";

	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
	if (exit != SQLITE_OK) {
		std::cerr << "Error Insert" << std::endl;
		sqlite3_free(messaggeError);
	}
	else
		std::cout << "Records created Successfully!" << std::endl;

	cout << "STATE OF TABLE AFTER INSERT" << endl;

	sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);

	
	sql = "UPDATE STUDENT set MATHS = 25 where ROLLNO=1;";
   
        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
	if (exit != SQLITE_OK) {
		std::cerr << "Error Update" << std::endl;
		sqlite3_free(messaggeError);
	}
	else
		std::cout << "Records Updated Successfully!" << std::endl;
	
	cout << "STATE OF TABLE AFTER UPDATE" << endl;

	sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);
	
	sql = "DELETE FROM STUDENT WHERE ROLLNO = 2;";
	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
	if (exit != SQLITE_OK) {
		cerr << "Error DELETE" << endl;
		sqlite3_free(messaggeError);
	}
	else
		cout << "Record deleted Successfully!" <<endl;

	cout << "STATE OF TABLE AFTER DELETE OF ELEMENT" << endl;
	sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);

	sqlite3_close(DB);
	return (0);
}
