#include <stdio.h>

typedef struct {
    char firstName[50];
    char lastName[50];
    char course1[50];
    char course2[50];
    char course3[50];
} Student;

int main() {
    Student students[2];
    FILE *file;

    for (int i = 0; i < 2; i++) {
        printf("\nEnter the student's first name: ");
        scanf("%s", students[i].firstName);

        printf("Enter the student's last name: ");
        scanf("%s", students[i].lastName);

        printf("Enter the student's first course: ");
        scanf("%s", students[i].course1);

        printf("Enter the student's second course: ");
        scanf("%s", students[i].course2);

        printf("Enter the student's third course: ");
        scanf("%s", students[i].course3);
    }

    // Open the file in append mode
    file = fopen("student.txt", "a");

    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    // Write the student data to the file
    for (int i = 0; i < 2; i++) {
        fprintf(file, "\nStudent %d\n", i+1);
        fprintf(file, "First Name: %s\n", students[i].firstName);
        fprintf(file, "Last Name: %s\n", students[i].lastName);
        fprintf(file, "Course 1: %s\n", students[i].course1);
        fprintf(file, "Course 2: %s\n", students[i].course2);
        fprintf(file, "Course 3: %s\n", students[i].course3);

    }

    // Close the file
    fclose(file);

    int studentNum;
    printf("Enter the number of the student you want to modify (1 or 2): ");
    scanf("%d", &studentNum);

    // Open the file in append mode
    file = fopen("student.txt", "a");

    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    // Modify the student data
    printf("\nEnter the new information for student %d:\n", studentNum);

    printf("First Name: ");
    scanf("%s", students[studentNum-1].firstName);

    printf("Last Name: ");
    scanf("%s", students[studentNum-1].lastName);

    printf("First Course: ");
    scanf("%s", students[studentNum-1].course1);

    printf("Second Course: ");
    scanf("%s", students[studentNum-1].course2);

    printf("Third Course: ");
    scanf("%s", students[studentNum-1].course3);

    // Write the modified student data to the file
    fprintf(file, "\nStudent %d (Modified)\n", studentNum);
    fprintf(file, "First Name: %s\n", students[studentNum-1].firstName);
    fprintf(file, "Last Name: %s\n", students[studentNum-1].lastName);
    fprintf(file, "Course 1: %s\n", students[studentNum-1].course1);
    fprintf(file, "Course 2: %s\n", students[studentNum-1].course2);
    fprintf(file, "Course 3: %s\n", students[studentNum-1].course3);

    // Close the file
    fclose(file);
    file = fopen("student.txt", "r");

    printf("Student data has been modified and saved to student.txt\n");

    return 0;
}