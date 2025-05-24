#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define FILENAME "students.txt"

typedef struct {
    int roll;
    char name[50];
    int age;
    float marks;
} Student;

Student students[MAX];
int count = 0;

// Function prototypes
void loadFromFile();
void saveToFile();
void menu();
void addStudent();
void viewAllStudents();
void searchStudent();
void updateStudent();
void deleteStudent();
void pressEnterToContinue();

int main() {
    loadFromFile();
    int choice;

    do {
        menu();
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                viewAllStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                updateStudent();
                break;
            case 5:
                deleteStudent();
                break;
            case 6:
                saveToFile();
                printf("Data saved. Exiting.\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 6);

    return 0;
}

// Menu
void menu() {
    printf("\n==== Student Management System ====\n");
    printf("1. Add Student\n");
    printf("2. View All Students\n");
    printf("3. Search Student by Roll No.\n");
    printf("4. Update Student\n");
    printf("5. Delete Student\n");
    printf("6. Save & Exit\n");
}

// Add new student
void addStudent() {
    if (count >= MAX) {
        printf("Student limit reached!\n");
        return;
    }

    Student s;
    printf("Enter Roll Number: ");
    scanf("%d", &s.roll);
    getchar(); // clear newline

    printf("Enter Name: ");
    fgets(s.name, sizeof(s.name), stdin);
    s.name[strcspn(s.name, "\n")] = '\0'; // remove newline

    printf("Enter Age: ");
    scanf("%d", &s.age);
    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    students[count++] = s;
    printf("Student added successfully.\n");

    pressEnterToContinue();
}

// View all students
void viewAllStudents() {
    if (count == 0) {
        printf("No student records found.\n");
        pressEnterToContinue();
        return;
    }

    printf("\n--- All Student Records ---\n");
    for (int i = 0; i < count; i++) {
        printf("Roll: %d | Name: %s | Age: %d | Marks: %.2f\n",
               students[i].roll, students[i].name, students[i].age, students[i].marks);
    }

    pressEnterToContinue();
}

// Search student by roll
void searchStudent() {
    int roll;
    printf("Enter Roll Number to search: ");
    scanf("%d", &roll);

    for (int i = 0; i < count; i++) {
        if (students[i].roll == roll) {
            printf("Found: Roll: %d | Name: %s | Age: %d | Marks: %.2f\n",
                   students[i].roll, students[i].name, students[i].age, students[i].marks);
            pressEnterToContinue();
            return;
        }
    }

    printf("Student with roll %d not found.\n", roll);
    pressEnterToContinue();
}

// Update student
void updateStudent() {
    int roll;
    printf("Enter Roll Number to update: ");
    scanf("%d", &roll);

    for (int i = 0; i < count; i++) {
        if (students[i].roll == roll) {
            printf("Current Name: %s\n", students[i].name);
            getchar(); // clear buffer
            printf("Enter new name: ");
            fgets(students[i].name, sizeof(students[i].name), stdin);
            students[i].name[strcspn(students[i].name, "\n")] = '\0';

            printf("Enter new age: ");
            scanf("%d", &students[i].age);

            printf("Enter new marks: ");
            scanf("%f", &students[i].marks);

            printf("Student updated.\n");
            pressEnterToContinue();
            return;
        }
    }

    printf("Student with roll %d not found.\n", roll);
    pressEnterToContinue();
}

// Delete student
void deleteStudent() {
    int roll, i;
    printf("Enter Roll Number to delete: ");
    scanf("%d", &roll);

    for (i = 0; i < count; i++) {
        if (students[i].roll == roll) {
            break;
        }
    }

    if (i == count) {
        printf("Student not found.\n");
        pressEnterToContinue();
        return;
    }

    for (int j = i; j < count - 1; j++) {
        students[j] = students[j + 1];
    }
    count--;
    printf("Student deleted successfully.\n");
    pressEnterToContinue();
}

// Save to file
void saveToFile() {
    FILE* fp = fopen(FILENAME, "w");
    if (!fp) {
        printf("Error opening file for saving.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(fp, "%d,%s,%d,%.2f\n",
                students[i].roll, students[i].name,
                students[i].age, students[i].marks);
    }

    fclose(fp);
}

// Load from file
void loadFromFile() {
    FILE* fp = fopen(FILENAME, "r");
    if (!fp) {
        return;
    }

    while (fscanf(fp, "%d,%49[^,],%d,%f\n",
                  &students[count].roll,
                  students[count].name,
                  &students[count].age,
                  &students[count].marks) == 4) {
        count++;
        if (count >= MAX) break;
    }

    fclose(fp);
}

// Pause
void pressEnterToContinue() {
    printf("\nPress Enter to continue...");
    getchar(); // consume previous newline
    getchar();
}

