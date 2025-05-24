#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Student {
    int roll;
    string name;
    string course;
    int year;
};

vector<Student> students;

void showMenu();
void addStudent();
void viewStudents();
void searchStudent();

int main() {
    int choice;
    do {
        showMenu();
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                viewStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 4);

    return 0;
}

void showMenu() {
    cout << "\n===== Student Record Manager =====\n";
    cout << "1. Add Student\n";
    cout << "2. View All Students\n";
    cout << "3. Search Student by Roll\n";
    cout << "4. Exit\n";
}

void addStudent() {
    Student s;
    cout << "Enter Roll Number: ";
    cin >> s.roll;
    cin.ignore();
    cout << "Enter Name: ";
    getline(cin, s.name);
    cout << "Enter Course: ";
    getline(cin, s.course);
    cout << "Enter Year: ";
    cin >> s.year;
    students.push_back(s);
    cout << "Student added successfully.\n";
}

void viewStudents() {
    if (students.empty()) {
        cout << "No student records available.\n";
        return;
    }

    cout << "\n--- Student List ---\n";
    for (const Student& s : students) {
        cout << "Roll: " << s.roll << "\n";
        cout << "Name: " << s.name << "\n";
        cout << "Course: " << s.course << "\n";
        cout << "Year: " << s.year << "\n\n";
    }
}

void searchStudent() {
    int roll;
    cout << "Enter Roll Number to search: ";
    cin >> roll;

    for (const Student& s : students) {
        if (s.roll == roll) {
            cout << "\n--- Student Found ---\n";
            cout << "Name: " << s.name << "\n";
            cout << "Course: " << s.course << "\n";
            cout << "Year: " << s.year << "\n";
            return;
        }
    }

    cout << "Student with Roll No. " << roll << " not found.\n";
}

