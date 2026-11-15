# Student Management System

A console-based Student Management System developed in **C++** with **SQLite** for persistent data storage.

This project allows users to manage student records, track academic grades, and perform database operations through an interactive menu-driven interface.

## Features

### Student Management
- Add new student records.
- View all registered students.
- Search for students using their unique ID.
- Update student information.
- Delete student records.

### Grade Management
- Add grades for existing students.
- View grades associated with a student.
- Calculate a student's average grade.
- Validate grades to ensure they are between 0 and 100.

### Database Management
- Persistent data storage using SQLite.
- Relational database structure with primary and foreign keys.
- Prepared SQL statements for database operations.
- Foreign key constraints to maintain data integrity.
- `ON DELETE CASCADE` to automatically remove associated grades when a student is deleted.

## Technologies Used

| Technology | Purpose |
|---|---|
| C++ | Application logic and user interface |
| SQLite | Database management and persistent storage |
| SQL | Database queries and operations |
| SQLite C API | Communication between C++ and SQLite |

## Database Structure

The application uses two relational tables:

**Student**

| Column | Description |
|---|---|
| id | Unique student identifier |
| name | Student's name |
| program | Student's program |
| year | Academic year |

**Grades**

| Column | Description |
|---|---|
| id | Unique grade record identifier |
| student_id | References the associated student |
| course | Course name |
| grade | Student's grade (0–100) |

The `Grades` table references the `Student` table through a foreign key relationship.

## Getting Started

### Prerequisites

- A C++ compiler supporting C++17 or later.
- SQLite source files (`sqlite3.c` and `sqlite3.h`).

### Installation

1. Clone the repository:

   ```bash
   git clone https://github.com/YOUR-USERNAME/YOUR-REPOSITORY.git
   ```

2. Navigate to the project directory:

   ```bash
   cd YOUR-REPOSITORY
   ```

3. Compile the application:

   ```bash
   gcc -std=c11 -O2 -c sqlite3.c -o sqlite3.o
   g++ -std=c++17 -Wall -Wextra -pedantic Source.cpp sqlite3.o -o student_app
   ```

4. Run the application:

   ```bash
   ./student_app
   ```

   On Windows, run:

   ```bash
   student_app.exe
   ```

The application automatically creates the `students.db` database and its tables when run for the first time.

## What I Learned

Through this project, I strengthened my understanding of:

- Integrating SQLite databases into C++ applications.
- Performing CRUD (Create, Read, Update, Delete) operations.
- Using prepared statements and parameter binding.
- Designing relational database schemas.
- Implementing primary and foreign key relationships.
- Working with SQL JOINs and aggregate functions.
- Handling database errors and validating user input.

## Future Improvements

- Support student names and course names containing spaces.
- Improve input validation across all operations.
- Add student authentication and role-based access.
- Introduce a graphical user interface.
- Add reporting and grade export functionality.

## Author

Developed as a personal project to practice C++, SQL, and relational database management.
