#include <stdio.h>
#include <string.h>

int main() {
    Student* add_student(Student* student_list, int* student_count) {
        student_list = resize_studet_array(student_list, *student_count+1);
        printf("Enter Roll Number: ");
        scanf("%d", &student_list[*student_count].roll_number);
        printf("Enter Name: ");
        scanf("%s", &student_list[*student_count].name);
        printf("Enter Marks: ");
        scanf("%f", &student_list[*student_count].marks);
        strcpy(student_list[*student_count].status, (student_list[*student_count].marks >= PASS_MARK) ? "Pass": "Fail");
        (*student_count)++;
        return student_list;
    }
    Student* delete_student(Student* student_list, int* student_count, int roll_number) {
        int index = find_student_by_roll(student_list, *student_count, roll_number);
        if (index == -1) {
            printf("Student not found.\n");
            return student_list;
        }
        for (int i = index; i < *student_count - 1; i++) {
            student_list[i] = student_list[i+1];
        }
        (*student_count)--;
        student_list = resize_student_array(student_list, *student_count);
        return student_list;
    }
    void update_student(Student* student_list, int student_count, int roll_number) {
        int index = find_student_by_roll(student_list, student_count, roll_number);
        if (index == -1 ) {
            printf("Student not found.\n");
            return;
        }
        printf("Enter new name: ");
        scanf("%s", student_list[index].name);
        printf("Enter new marks: ");
        scanf("%f", %student_list[index].marks);
        strcpy(student_list[index].status, (student_list[index].marks >= PASS_MARK) ? "Pass" : "Fail");
    }

}
