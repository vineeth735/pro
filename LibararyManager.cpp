#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Book {
private:
    int id;
    string title;
    string author;
    bool issued;

public:
    Book(int i, string t, string a) {
        id = i;
        title = t;
        author = a;
        issued = false;
    }

    int getId() const {
        return id;
    }

    string getTitle() const {
        return title;
    }

    string getAuthor() const {
        return author;
    }

    bool isIssued() const {
        return issued;
    }

    void issueBook() {
        if (issued) {
            cout << "Book already issued.\n";
        } else {
            issued = true;
            cout << "Book issued successfully.\n";
        }
    }

    void returnBook() {
        if (!issued) {
            cout << "Book is not issued.\n";
        } else {
            issued = false;
            cout << "Book returned successfully.\n";
        }
    }

    void display() const {
        cout << "ID: " << id << "\n";
        cout << "Title: " << title << "\n";
        cout << "Author: " << author << "\n";
        cout << "Status: " << (issued ? "Issued" : "Available") << "\n\n";
    }
};

class Library {
private:
    vector<Book> books;
    int nextId = 1;

public:
    void addBook() {
        string title, author;
        cin.ignore();
        cout << "Enter book title: ";
        getline(cin, title);
        cout << "Enter author name: ";
        getline(cin, author);
        books.push_back(Book(nextId++, title, author));
        cout << "Book added successfully.\n";
    }

    void issueBook() {
        int id;
        cout << "Enter book ID to issue: ";
        cin >> id;
        for (auto& book : books) {
            if (book.getId() == id) {
                book.issueBook();
                return;
            }
        }
        cout << "Book not found.\n";
    }

    void returnBook() {
        int id;
        cout << "Enter book ID to return: ";
        cin >> id;
        for (auto& book : books) {
            if (book.getId() == id) {
                book.returnBook();
                return;
            }
        }
        cout << "Book not found.\n";
    }

    void displayAll() const {
        if (books.empty()) {
            cout << "No books available.\n";
            return;
        }
        cout << "\n--- All Books ---\n";
        for (const auto& book : books) {
            book.display();
        }
    }

    void searchByTitle() {
        cin.ignore();
        string keyword;
        cout << "Enter keyword to search in title: ";
        getline(cin, keyword);

        bool found = false;
        for (const auto& book : books) {
            if (book.getTitle().find(keyword) != string::npos) {
                book.display();
                found = true;
            }
        }
        if (!found)
            cout << "No books found with given title keyword.\n";
    }

    void showMenu() {
        cout << "\n=== Library Management Menu ===\n";
        cout << "1. Add Book\n";
        cout << "2. Issue Book\n";
        cout << "3. Return Book\n";
        cout << "4. View All Books\n";
        cout << "5. Search Book by Title\n";
        cout << "6. Exit\n";
    }
};

int main() {
    Library library;
    int choice;

    do {
        library.showMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                library.addBook();
                break;
            case 2:
                library.issueBook();
                break;
            case 3:
                library.returnBook();
                break;
            case 4:
                library.displayAll();
                break;
            case 5:
                library.searchByTitle();
                break;
            case 6:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 6);

    return 0;
}

