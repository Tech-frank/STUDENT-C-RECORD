#include <stdio.h>
#include <stdlib.h>

#define MAX_SUBJECTS 8 // Define the maximum number of subjects

// Define the Student structure
typedef struct {
    char name[50];          // Student's name
    float marks[MAX_SUBJECTS]; // Array to hold marks for each subject
    char status[20];     // Student's score status (e.g., "Pass", "Fail")
} Student;

// Function to save student records to a file
void saveToFile(Student* students, int size) {
  FILE *file;
  file = fopen("student_records.txt", "a");

  if (file == NULL) {
    printf("Error opening file.\n");
    return;
  }

  for (int i = 0; i < size; i++) {
    fprintf(file, "%s,", students[i].name); // Save student name
    for (int j = 0; j < MAX_SUBJECTS; j++) {
      fprintf(file, "%.2f,", students[i].marks[j]); // Save each mark
    }
    fprintf(file, "%s\n", students[i].status); // Save student status
  }

  fclose(file);
  printf("Records appended to student_records.txt successfully!\n");
}

int main() {
  // Example usage
  Student students[2] = {
    {"John Doe", {85.5, 90.0, 78.5, 34.9, 50.8, 45.7, 90.6, 78.3}, "Pass"},
    {"Jane Smith", {65.0, 70.5, 80.0, 60.0, 75.5, 55.5, 85.0, 90.0}, "Pass"}
  };

  saveToFile(students, 2); // Append the records of 2 students

  return 0;
}