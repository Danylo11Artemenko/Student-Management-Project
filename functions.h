
#pragma once

#include <iostream>
#include <string>
#include "sqlite3.h"

using namespace std;

void Addstudent(sqlite3* DB) {
    int year, result;
    sqlite3_stmt* stmt;
    string name, program;

    cout << "Please enter student's name (No spaces): ";
    cin >> name;

    cout << "Please enter course (No spaces): ";
    cin >> program;

    cout << "Please enter student's year: ";
    cin >> year;
    while (year < 0) {
        cout << "This can't be right please double check students grade" << endl;;
        cout << "Please enter a correct year:"; cin >> year; cout << endl;
    }

    string sql =
        "INSERT INTO Student (name, program, year) "
        "VALUES (?, ?, ?);";

    result = sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, nullptr);

    if (result == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, program.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 3, year);

        int Stepresult = sqlite3_step(stmt);

        if (Stepresult == SQLITE_DONE) {
            cout << "Student added!" << endl;
        }
        else {
            cout << sqlite3_errmsg(DB) << endl;
        }

        sqlite3_finalize(stmt);
    }
    else {
        cout << sqlite3_errmsg(DB) << endl;
    }
}


void ViewStudent(sqlite3* DB) {
    sqlite3_stmt* stmt;
    string sql = "SELECT * FROM STUDENT;";

    int result = sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, nullptr);

    if (result == SQLITE_OK) {
        while ((result = sqlite3_step(stmt)) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            const unsigned char* name = sqlite3_column_text(stmt, 1);
            const unsigned char* program = sqlite3_column_text(stmt, 2);
            int year = sqlite3_column_int(stmt, 3);

            cout << "ID: " << id << endl;
            cout << "Name: " << name << endl;
            cout << "Course: " << program << endl;
            cout << "Year: " << year << endl;
            cout << "----------------------" << endl;
        }

        if (result != SQLITE_DONE) {
            cout << sqlite3_errmsg(DB) << endl;
        }

        sqlite3_finalize(stmt);
    }
    else {
        cout << sqlite3_errmsg(DB) << endl;
    }
}


void SearchStudent(sqlite3* DB) {
    sqlite3_stmt* stmt;
    string sql = "SELECT * FROM STUDENT WHERE id=?;";
    int id;

    cout << "Enter student ID to search: ";
    cin >> id;

    int result = sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, nullptr);

    if (result == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, id);

        int result1 = sqlite3_step(stmt);

        if (result1 == SQLITE_ROW) {
            int studentID = sqlite3_column_int(stmt, 0);
            const unsigned char* name = sqlite3_column_text(stmt, 1);
            const unsigned char* program = sqlite3_column_text(stmt, 2);
            int year = sqlite3_column_int(stmt, 3);

            cout << "ID: " << studentID << endl;
            cout << "Name: " << name << endl;
            cout << "Course: " << program << endl;
            cout << "Year: " << year << endl;
           
        }
        else if (result1 == SQLITE_DONE) {
            cout << "No student found with that ID." << endl;
        }
        else {
            cout << sqlite3_errmsg(DB) << endl;
        }

        sqlite3_finalize(stmt);
    }
    else {
        cout << sqlite3_errmsg(DB) << endl;
    }
}


void Update_Student(sqlite3* DB) {
    int id;
    sqlite3_stmt* stmt;
    string program;

    string sql = "UPDATE STUDENT SET program=? WHERE id=?";

    cout << "Enter student ID: ";
    cin >> id;

    cout << "Enter student's course: ";
    cin >> program;

    int result = sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, nullptr);

    if (result == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, program.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 2, id);

        int result1 = sqlite3_step(stmt);

        if (result1 == SQLITE_DONE) {
            if (sqlite3_changes(DB) > 0) {
                cout << "Student updated successfully!" << endl;
            }
            else {
                cout << "No student found with that ID." << endl;
            }
        }
        else {
            cout << "There was an error while updating the student." << endl;
            cout << sqlite3_errmsg(DB) << endl;
        }

        sqlite3_finalize(stmt);
    }
    else {
        cout << sqlite3_errmsg(DB) << endl;
    }
}


void Delete_User(sqlite3* DB) {
    sqlite3_stmt* stmt;
    int id;

    cout << "Enter ID of the student you wish to delete: ";
    cin >> id;

    string sql = "DELETE FROM Student WHERE id=?";

    int result = sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, nullptr);

    if (result == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, id);

        int result1 = sqlite3_step(stmt);

        if (result1 == SQLITE_DONE) {
            if (sqlite3_changes(DB) > 0) {
                cout << "Student has been deleted." << endl;
            }
            else {
                cout << "No student found with that ID." << endl;
            }
        }
        else {
            cout << "There was an error deleting the student." << endl;
            cout << sqlite3_errmsg(DB) << endl;
        }

        sqlite3_finalize(stmt);
    }
    else {
        cout << sqlite3_errmsg(DB) << endl;
    }
}


void Add_Grade(sqlite3* DB) {
    sqlite3_stmt* stmt;
    int id;

    cout << "Please enter student's ID: ";
    cin >> id;

    string sql = "SELECT * FROM Student WHERE id=?;";

    int result = sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, nullptr);

    if (result == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, id);

        int stepResult = sqlite3_step(stmt);

        if (stepResult == SQLITE_ROW) {
            cout << "Student exists. Please proceed." << endl;

            int grade;
            string course;

            cout << "Please enter the course (No spaces): ";
            cin >> course;

            cout << "Please enter the grade: ";
            cin >> grade;
            while(grade > 100 || grade < 0) {
                cout << "This can't be right please double check students grade" << endl;
                cout << "Please enter a correct grade"; cin >> grade; cout << endl;
            }

            string insertSQL =
                "INSERT INTO Grades (student_id, course, grade) "
                "VALUES (?, ?, ?);";

            sqlite3_stmt* insertstmt;

            int insertResult = sqlite3_prepare_v2(
                DB, insertSQL.c_str(), -1, &insertstmt, nullptr
            );

            if (insertResult == SQLITE_OK) {
                sqlite3_bind_int(insertstmt, 1, id);
                sqlite3_bind_text(
                    insertstmt, 2, course.c_str(), -1, SQLITE_TRANSIENT
                );
                sqlite3_bind_int(insertstmt, 3, grade);

                int insertStepResult = sqlite3_step(insertstmt);

                if (insertStepResult == SQLITE_DONE) {
                    cout << "Grade added successfully!" << endl;
                }
                else {
                    cout << sqlite3_errmsg(DB) << endl;
                }

                sqlite3_finalize(insertstmt);
            }
            else {
                cout << sqlite3_errmsg(DB) << endl;
            }
        }
        else if (stepResult == SQLITE_DONE) {
            cout << "Student does not exist. Please check the ID." << endl;
        }
        else {
            cout << sqlite3_errmsg(DB) << endl;
        }

        sqlite3_finalize(stmt);
    }
    else {
        cout << sqlite3_errmsg(DB) << endl;
    }
}


void Calculate_avg(sqlite3* DB) {
    sqlite3_stmt* stmt;
    int id;

    cout << "Please enter student's ID: ";
    cin >> id;

    string sql = "SELECT AVG(grade) FROM Grades WHERE student_id=?;";

    int result = sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, nullptr);

    if (result == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, id);

        result = sqlite3_step(stmt);

        if (result == SQLITE_ROW) {
            if (sqlite3_column_type(stmt, 0) != SQLITE_NULL) {
                double average = sqlite3_column_double(stmt, 0);
                cout << "Student's average is: " << average << endl;
            }
            else {
                cout << "This student doesn't have any grades yet." << endl;
            }
        }
        else {
            cout << sqlite3_errmsg(DB) << endl;
        }

        sqlite3_finalize(stmt);
    }
    else {
        cout << sqlite3_errmsg(DB) << endl;
    }
}


void View_Grade(sqlite3* DB) {
    bool found = false;
    sqlite3_stmt* stmt;
    int id;

    cout << "Please enter student's ID: ";
    cin >> id;

    string sql =
        "SELECT Student.name, Grades.course, Grades.grade "
        "FROM Student "
        "JOIN Grades ON Student.id = Grades.student_id "
        "WHERE Student.id=?;";

    int result = sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, nullptr);

    if (result == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, id);

        while ((result = sqlite3_step(stmt)) == SQLITE_ROW) {
            cout << "Name: " << sqlite3_column_text(stmt, 0) << endl;
            cout << "Course: " << sqlite3_column_text(stmt, 1) << endl;
            cout << "Grade: " << sqlite3_column_int(stmt, 2) << endl;
            cout << "----------------------" << endl;

            found = true;
        }

        if (result == SQLITE_DONE) {
            if (!found) {
                cout << "There are no grades for this student." << endl;
            }
        }
        else {
            cout << sqlite3_errmsg(DB) << endl;
        }

        sqlite3_finalize(stmt);
    }
    else {
        cout << sqlite3_errmsg(DB) << endl;
    }
}

