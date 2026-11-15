# Student-Management-Project
A console application in C++ that manages students and their grades using an SQLite database (students.db, created on first run).

Features
Add a student
View all students
Search a student by ID
Update a student's course
Delete a student (their grades are removed too, via ON DELETE CASCADE)
Add a grade for a student (0-100)
View a student's grades
Calculate a student's average grade

All queries use prepared statements with bound parameters.

Project layout
src/main.cpp                 Menu loop, database setup and schema
src/functions.h              Feature functions (one per menu option)
third_party/sqlite3/         SQLite amalgamation (sqlite3.c / sqlite3.h)
Build

With CMake:

sh
cmake -S . -B build
cmake --build build
./build/students

Or by hand (SQLite must be compiled as C, separately from the C++ code):

sh
gcc -c third_party/sqlite3/sqlite3.c -o sqlite3.o
g++ -I third_party/sqlite3 src/main.cpp sqlite3.o -o students -lpthread -ldl

In Visual Studio, add sqlite3.c as a C source file (not C++) and the other files as usual.

Schema
Student(id, name, program, year)
Grades(id, student_id, course, grade) with grade constrained to 0-100 and a foreign key to Student
