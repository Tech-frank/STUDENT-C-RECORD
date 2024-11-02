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

// Function prototypes
Student* add_student(Student* student_list, int* student_count);
Student* delete_student(Student* student_list, int* student_count, int roll_number);
void update_student(Student* student_list, int student_count, int roll_number);
void display_all_students(Student* student_list, int student_count);
void main_menu(Student* student_list, int* student_count);
Student* resize_student_array(Student* student_list, int new_size);
int find_student_by_roll(Student* student_list, int student_count, int roll_number);

int main() {
    int student_count = 0;
    Student* student_list = NULL;

    // Start the main menu
    main_menu(student_list, &student_count);

    return 0;
}

// Function to add a student to the list
Student* add_student(Student* student_list, int* student_count) {
    // Resize the student array to add a new student
    student_list = resize_student_array(student_list, *student_count + 1);
    printf("Enter Roll Number: ");
    scanf("%d", &student_list[*student_count].roll_number);
    printf("Enter Name: ");
    scanf("%s", student_list[*student_count].name); // Corrected: no '&' needed for character arrays
    printf("Enter Marks: ");
    scanf("%f", &student_list[*student_count].marks);

    // Set status based on marks
    strcpy(student_list[*student_count].status, (student_list[*student_count].marks >= PASS_MARK) ? "Pass" : "Fail");
    (*student_count)++; // Increase the student count
    return student_list;
}

// Function to delete a student by roll number
Student* delete_student(Student* student_list, int* student_count, int roll_number) {
    int index = find_student_by_roll(student_list, *student_count, roll_number);
    if (index == -1) {
        printf("Student not found.\n");
        return student_list;
    }
    
    // Shift students to remove the deleted student and keep array compact
    for (int i = index; i < *student_count - 1; i++) {
        student_list[i] = student_list[i+1];
    }
    
    (*student_count)--; // Decrease the student count
    student_list = resize_student_array(student_list, *student_count); // Resize the array
    return student_list;
}

// Function to update a student's details
void update_student(Student* student_list, int student_count, int roll_number) {
    int index = find_student_by_roll(student_list, student_count, roll_number);
    if (index == -1) {
        printf("Student not found.\n");
        return;
    }
    printf("Enter new name: ");
    scanf("%s", student_list[index].name); // Update name
    printf("Enter new marks: ");
    scanf("%f", &student_list[index].marks); // Corrected: removed incorrect '%' symbol

    // Update the pass/fail status based on new marks
    strcpy(student_list[index].status, (student_list[index].marks >= PASS_MARK) ? "Pass" : "Fail");
}

// Function to resize the student array dynamically
Student* resize_student_array(Student* student_list, int new_size) {
    return (Student*) realloc(student_list, new_size * sizeof(Student));
}

// Function to find a student by roll number
int find_student_by_roll(Student* student_list, int student_count, int roll_number) {
    for (int i = 0; i < student_count; i++) {
        if (student_list[i].roll_number == roll_number) {
            return i;
        }
    }
    return -1; // Return -1 if student is not found
}

// Function to display all students
void display_all_students(Student* student_list, int student_count) {
    printf("\n--- Student Records ---\n");
    for (int i = 0; i < student_count; i++) {
        printf("Roll Number: %d, Name: %s, Marks: %.2f, Status: %s\n",
               student_list[i].roll_number,
               student_list[i].name,
               student_list[i].marks,
               student_list[i].status);
    }
}

// Main menu function
void main_menu(Student* student_list, int* student_count) {
    int choice, roll_number;

    while (1) {
        // Display the menu options
        printf("\n--- Student Record System ---\n");
        printf("1. Add Student\n");
        printf("2. Delete Student\n");
        printf("3. Update Student\n");
        printf("4. Display All Students\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // Handle each menu option
        switch (choice) {
            case 1:
                student_list = add_student(student_list, student_count);
                break;
            case 2:
                printf("Enter roll number to delete: ");
                scanf("%d", &roll_number);
                student_list = delete_student(student_list, student_count, roll_number);
                break;
            case 3:
                printf("Enter roll number to update: ");
                scanf("%d", &roll_number);
                update_student(student_list, *student_count, roll_number);
                break;
            case 4:
                display_all_students(student_list, *student_count);
                break;
            case 5:
                printf("Exiting...\n");
                free(student_list); // Free allocated memory before exiting
                return;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}
