#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PASS_MARK 40

// Define the Student structure
typedef struct {
    int roll_number;
    char name[50];
    float marks;
    char status[10];
} Student;

// Function Prototypes

// User Interface & Greeting (Person 1)
void ui_greet_user(); // Greets the user and prompts for their name
void ui_display_menu(); // Displays the main menu options
int ui_get_choice(); // Gets and validates user input for menu choice

// Student Data Structure & Memory Management (Person 2)
Student* student_create_list(); // Initializes the student list
Student* student_resize_list(Student* student_list, int new_size); // Dynamically resizes the student list
void student_free_list(Student* student_list); // Frees allocated memory for the student list

// Add Student (Person 3)
Student* student_add(Student* student_list, int* student_count); // Adds a new student to the list
void student_set_status(Student* student); // Determines and sets the student’s pass/fail status

// Delete Student (Person 4)
Student* student_delete(Student* student_list, int* student_count, int roll_number); // Deletes a student by roll number
void student_shift_records(Student* student_list, int index, int* student_count); // Shifts student records after deletion

// Update Student (Person 5)
void student_update_name(Student* student_list, int index); // Updates a student’s name
void student_update_marks(Student* student_list, int index); // Updates a student’s marks
void student_update_status(Student* student_list, int index); // Updates the student’s status based on new marks

// Display Functions (Person 6)
void display_student(Student student); // Displays the details of a single student
void display_all_students(Student* student_list, int student_count); // Displays details of all students in the list
void display_student_count(int student_count); // Shows the total number of students

// File Operations (Person 7)
void file_save_students(Student* student_list, int student_count); // Saves student records to a file
Student* file_load_students(int* student_count); // Loads student records from a file

// Search Functionality (Person 8)
int search_by_roll_number(Student* student_list, int student_count, int roll_number); // Finds a student by roll number
void search_display_result(Student* student_list, int index); // Displays search results (if found)

// Calculations and Sorting (Person 9)
float calculate_average_marks(Student* student_list, int student_count); // Calculates the average marks of all students
void sort_students_by_marks(Student* student_list, int student_count); // Sorts students by marks
void sort_students_by_name(Student* student_list, int student_count); // Sorts students by name

// Main Program Control & Integration Testing (Person 10)
void main_init_system(); // Initializes the system (loads students and displays the menu)
void main_handle_choice(Student** student_list, int* student_count, int choice); // Handles menu choices and calls relevant functions
void main_exit_system(Student* student_list, int student_count); // Saves data and exits the program


// Implementations

// User Interface & Greeting (Person 1)
void ui_greet_user() {
    char name[50];
    printf("Welcome to the Student Record System!\n");
    printf("Please enter your name: ");
    scanf("%s", name);
    printf("Hello, %s! Let's get started.\n", name);
}

void ui_display_menu() {
    printf("\n--- Main Menu ---\n");
    printf("1. Add Student\n");
    printf("2. Delete Student\n");
    printf("3. Update Student\n");
    printf("4. Display All Students\n");
    printf("5. Search Student by Roll Number\n");
    printf("6. Calculate Average Marks\n");
    printf("7. Sort Students by Marks\n");
    printf("8. Sort Students by Name\n");
    printf("9. Exit\n");
}

int ui_get_choice() {
    int choice;
    printf("Enter your choice: ");
    scanf("%d", &choice);
    return choice;
}

// Student Data Structure & Memory Management (Person 2)
Student* student_create_list() {
    return NULL;
}

Student* student_resize_list(Student* student_list, int new_size) {
    return (Student*) realloc(student_list, new_size * sizeof(Student));
}

void student_free_list(Student* student_list) {
    free(student_list);
}

// Add Student (Person 3)
Student* student_add(Student* student_list, int* student_count) {
    student_list = student_resize_list(student_list, *student_count + 1);
    printf("Enter Roll Number: ");
    scanf("%d", &student_list[*student_count].roll_number);
    printf("Enter Name: ");
    scanf("%s", student_list[*student_count].name);
    printf("Enter Marks: ");
    scanf("%f", &student_list[*student_count].marks);
    student_set_status(&student_list[*student_count]);
    (*student_count)++;
    return student_list;
}

void student_set_status(Student* student) {
    strcpy(student->status, (student->marks >= PASS_MARK) ? "Pass" : "Fail");
}

// Delete Student (Person 4)
Student* student_delete(Student* student_list, int* student_count, int roll_number) {
    int index = search_by_roll_number(student_list, *student_count, roll_number);
    if (index == -1) {
        printf("Student not found.\n");
        return student_list;
    }
    student_shift_records(student_list, index, student_count);
    student_list = student_resize_list(student_list, *student_count);
    return student_list;
}

void student_shift_records(Student* student_list, int index, int* student_count) {
    for (int i = index; i < *student_count - 1; i++) {
        student_list[i] = student_list[i + 1];
    }
    (*student_count)--;
}

// Update Student (Person 5)
void student_update_name(Student* student_list, int index) {
    printf("Enter new name: ");
    scanf("%s", student_list[index].name);
}

void student_update_marks(Student* student_list, int index) {
    printf("Enter new marks: ");
    scanf("%f", &student_list[index].marks);
}

void student_update_status(Student* student_list, int index) {
    student_set_status(&student_list[index]);
}

// Display Functions (Person 6)
void display_student(Student student) {
    printf("Roll Number: %d, Name: %s, Marks: %.2f, Status: %s\n",
           student.roll_number, student.name, student.marks, student.status);
}

void display_all_students(Student* student_list, int student_count) {
    for (int i = 0; i < student_count; i++) {
        display_student(student_list[i]);
    }
}

void display_student_count(int student_count) {
    printf("Total number of students: %d\n", student_count);
}

// File Operations (Person 7)
void file_save_students(Student* student_list, int student_count) {
    FILE *file = fopen("students.txt", "w");
    if (file) {
        for (int i = 0; i < student_count; i++) {
            fprintf(file, "%d %s %.2f %s\n", student_list[i].roll_number, student_list[i].name, student_list[i].marks, student_list[i].status);
        }
        fclose(file);
    }
}

Student* file_load_students(int* student_count) {
    FILE *file = fopen("students.txt", "r");
    Student* student_list = NULL;
    *student_count = 0;
    if (file) {
        Student temp;
        while (fscanf(file, "%d %s %f %s", &temp.roll_number, temp.name, &temp.marks, temp.status) == 4) {
            student_list = student_resize_list(student_list, *student_count + 1);
            student_list[*student_count] = temp;
            (*student_count)++;
        }
        fclose(file);
    }
    return student_list;
}

// Search Functionality (Person 8)
int search_by_roll_number(Student* student_list, int student_count, int roll_number) {
    for (int i = 0; i < student_count; i++) {
        if (student_list[i].roll_number == roll_number) {
            return i;
        }
    }
    return -1;
}

void search_display_result(Student* student_list, int index) {
    if (index != -1) {
        display_student(student_list[index]);
    } else {
        printf("Student not found.\n");
    }
}

// Calculations and Sorting (Person 9)
float calculate_average_marks(Student* student_list, int student_count) {
    float sum = 0;
    for (int i = 0; i < student_count; i++) {
        sum += student_list[i].marks;
    }
    return (student_count > 0) ? sum / student_count : 0;
}

void sort_students_by_marks(Student* student_list, int student_count) {
    for (int i = 0; i < student_count - 1; i++) {
        for (int j = i + 1; j < student_count; j++) {
            if (student_list[i].marks > student_list[j].marks) {
                Student temp = student_list[i];
                student_list[i] = student_list[j];
                student_list[j] = temp;
            }
        }
    }
}

void sort_students_by_name(Student* student_list, int student_count) {
    for (int i = 0; i < student_count - 1; i++) {
        for (int j = i + 1; j < student_count; j++) {
            if (strcmp(student_list[i].name, student_list[j].name) > 0) {
                Student temp = student_list[i];
                student_list[i] = student_list[j];
                student_list[j] = temp;
            }
        }
    }
}

// Main Program Control & Integration Testing (Person 10)
void main_init_system() {
    int student_count = 0;
    Student* student_list = file_load_students(&student_count); // Load students from file if any

    ui_greet_user(); // Greet the user

    while (1) {
        ui_display_menu();
        int choice = ui_get_choice();
        main_handle_choice(&student_list, &student_count, choice);
    }
}

void main_handle_choice(Student** student_list, int* student_count, int choice) {
    int roll_number;
    float average_marks;
    int index;

    switch (choice) {
        case 1:
            *student_list = student_add(*student_list, student_count);
            break;
        case 2:
            printf("Enter roll number to delete: ");
            scanf("%d", &roll_number);
            *student_list = student_delete(*student_list, student_count, roll_number);
            break;
        case 3:
            printf("Enter roll number to update: ");
            scanf("%d", &roll_number);
            index = search_by_roll_number(*student_list, *student_count, roll_number);
            if (index != -1) {
                student_update_name(*student_list, index);
                student_update_marks(*student_list, index);
                student_update_status(*student_list, index);
            } else {
                printf("Student not found.\n");
            }
            break;
        case 4:
            display_all_students(*student_list, *student_count);
            break;
        case 5:
            printf("Enter roll number to search: ");
            scanf("%d", &roll_number);
            index = search_by_roll_number(*student_list, *student_count, roll_number);
            search_display_result(*student_list, index);
            break;
        case 6:
            average_marks = calculate_average_marks(*student_list, *student_count);
            printf("Average marks of all students: %.2f\n", average_marks);
            break;
        case 7:
            sort_students_by_marks(*student_list, *student_count);
            printf("Students sorted by marks.\n");
            display_all_students(*student_list, *student_count);
            break;
        case 8:
            sort_students_by_name(*student_list, *student_count);
            printf("Students sorted by name.\n");
            display_all_students(*student_list, *student_count);
            break;
        case 9:
            main_exit_system(*student_list, *student_count);
            exit(0);
        default:
            printf("Invalid choice! Please try again.\n");
    }
}

void main_exit_system(Student* student_list, int student_count) {
    file_save_students(student_list, student_count); // Save data before exit
    student_free_list(student_list); // Free allocated memory
}
