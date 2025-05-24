#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Task {
    string description;
    bool completed;
};

vector<Task> tasks;

void menu();
void addTask();
void viewTasks();
void markTask();

int main() {
    int choice;
    do {
        menu();
        cout << "Choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: addTask(); break;
            case 2: viewTasks(); break;
            case 3: markTask(); break;
            case 4: cout << "Goodbye!\n"; break;
            default: cout << "Invalid option.\n";
        }
    } while (choice != 4);
    return 0;
}

void menu() {
    cout << "\n=== To-Do List ===\n";
    cout << "1. Add Task\n";
    cout << "2. View Tasks\n";
    cout << "3. Mark Task as Done\n";
    cout << "4. Exit\n";
}

void addTask() {
    Task t;
    cout << "Enter task description: ";
    getline(cin, t.description);
    t.completed = false;
    tasks.push_back(t);
    cout << "Task added.\n";
}

void viewTasks() {
    if (tasks.empty()) {
        cout << "No tasks found.\n";
        return;
    }

    cout << "\n--- Tasks ---\n";
    for (size_t i = 0; i < tasks.size(); ++i) {
        cout << i + 1 << ". " << tasks[i].description;
        cout << (tasks[i].completed ? " [Done]\n" : " [Pending]\n");
    }
}

void markTask() {
    int num;
    viewTasks();
    cout << "Enter task number to mark as done: ";
    cin >> num;
    if (num < 1 || num > tasks.size()) {
        cout << "Invalid number.\n";
        return;
    }
    tasks[num - 1].completed = true;
    cout << "Task marked as done.\n";
}

