# Student Record System

## Overview

The **Student Record System** is a C program designed to manage student records. It includes functionalities to add, update, delete, and display student information. The system dynamically manages memory to handle a flexible number of student records and tracks each student's status as "Pass" or "Fail" based on their marks.

## Features

- **Add Student**: Adds a new student to the record.
- **Delete Student**: Removes a student from the record based on their roll number.
- **Update Student**: Updates an existing student’s information.
- **Display All Students**: Lists all students with their details.
- **Dynamic Memory Management**: Uses dynamic memory allocation to handle varying numbers of student records.

## Setup and Compilation

### Prerequisites

- C Compiler (e.g., GCC)
- Text editor or IDE for editing code

### Compilation

To compile the program, open a terminal or command prompt in the project directory and run:

```bash
gcc -Wall -Wextra -o student_record_system main.c
