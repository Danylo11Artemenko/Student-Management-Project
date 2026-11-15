#include <iostream>
using namespace std;
#include "sqlite3.h"
#include <string>
#include "functions.h"

int main() {
	sqlite3* DB;
	int option=-2;
	
	int result = sqlite3_open("students.db", &DB);
	
	if (result == SQLITE_OK) {
		int foreign_key=sqlite3_exec(DB, "PRAGMA foreign_keys = ON;", nullptr, nullptr, nullptr);
		if (foreign_key != SQLITE_OK) {
			cout << "Foreign key error" << endl << sqlite3_errmsg(DB) << endl;
			sqlite3_close(DB);
			return 1;
		}
		const char* createTables = R"(
    CREATE TABLE IF NOT EXISTS Student (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        name TEXT NOT NULL,
        program TEXT NOT NULL,
        year INTEGER NOT NULL
    );

    CREATE TABLE IF NOT EXISTS Grades (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        student_id INTEGER NOT NULL,
        course TEXT NOT NULL,
        grade INTEGER NOT NULL CHECK(grade BETWEEN 0 AND 100),
        FOREIGN KEY(student_id)
            REFERENCES Student(id)
            ON DELETE CASCADE
    );
)";

		int tableresult=sqlite3_exec(DB, createTables, nullptr, nullptr, nullptr);
		if (tableresult != SQLITE_OK) {
			cout << "Database creation error " << endl;
			cout << sqlite3_errmsg(DB);
			sqlite3_close(DB);
			return 1;

		}
		
		do {
			cout << "\n===== STUDENT MANAGEMENT SYSTEM =====\n";
			cout << "1. Add Student\n";
			cout << "2. View Students\n";
			cout << "3. Search Student\n";
			cout << "4. Update Student\n";
			cout << "5. Delete Student\n";
			cout << "6. Add Grade\n";
			cout << "7. View Grades\n";
			cout << "8. Calculate Average\n";
			cout << "0. Exit\n";
			cout << "Enter choice: ";

			cin >> option;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(10000, '\n');
				cout << "Wrong input! Please try again" << endl;
				continue;
			}

			switch (option) {
			case 1:Addstudent(DB); break;
			case 2:ViewStudent(DB); break;
			case 3:SearchStudent(DB); break;
			case 4:Update_Student(DB); break;
			case 5:Delete_User(DB); break;
			case 6:Add_Grade(DB); break;
			case 7:View_Grade(DB); break;
			case 8:Calculate_avg(DB); break;
			case 0:break;
			default:cout << "There is no such option!" << endl; break;
			}

		} while (option != 0);

		sqlite3_close(DB);
	}
	else {
		cout << "Error!" << endl;
		cout << sqlite3_errmsg(DB);
		sqlite3_close(DB);
		return 1;
	}
	return 0;
}
	







