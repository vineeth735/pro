# finance_tracker.py

import json
import csv
import os
from datetime import datetime


# === Class: Transaction ===

class Transaction:
    def __init__(self, t_type, category, amount, note=""):
        self.date = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        self.type = t_type  # 'income' or 'expense'
        self.category = category
        self.amount = amount
        self.note = note

    def to_dict(self):
        return {
            "date": self.date,
            "type": self.type,
            "category": self.category,
            "amount": self.amount,
            "note": self.note
        }

    @staticmethod
    def from_dict(data):
        t = Transaction(data['type'], data['category'], data['amount'], data.get('note', ''))
        t.date = data['date']
        return t

    def __str__(self):
        return f"[{self.date}] {self.type.upper()} | {self.category} | ${self.amount:.2f} | {self.note}"


# === Class: FinanceTracker ===

class FinanceTracker:
    def __init__(self, filename="data.json"):
        self.transactions = []
        self.filename = filename
        self.load()

    def add_transaction(self, t_type, category, amount, note=""):
        if amount <= 0:
            print("Amount must be positive.")
            return
        self.transactions.append(Transaction(t_type, category, amount, note))
        print("Transaction added.")

    def view_all(self):
        if not self.transactions:
            print("No transactions found.")
            return
        for t in self.transactions:
            print(t)

    def view_by_type(self, t_type):
        filtered = [t for t in self.transactions if t.type == t_type]
        if not filtered:
            print(f"No {t_type} transactions found.")
            return
        for t in filtered:
            print(t)

    def search_by_category(self, keyword):
        matches = [t for t in self.transactions if keyword.lower() in t.category.lower()]
        if not matches:
            print("No matches found.")
            return
        for t in matches:
            print(t)

    def summary(self):
        total_income = sum(t.amount for t in self.transactions if t.type == "income")
        total_expense = sum(t.amount for t in self.transactions if t.type == "expense")
        balance = total_income - total_expense

        print("\n=== Summary ===")
        print(f"Total Income : ${total_income:.2f}")
        print(f"Total Expense: ${total_expense:.2f}")
        print(f"Balance      : ${balance:.2f}\n")

    def save(self):
        data = [t.to_dict() for t in self.transactions]
        with open(self.filename, "w") as f:
            json.dump(data, f, indent=4)
        print("Data saved.")

    def load(self):
        if not os.path.exists(self.filename):
            return
        with open(self.filename, "r") as f:
            data = json.load(f)
        self.transactions = [Transaction.from_dict(t) for t in data]

    def export_csv(self, csv_filename="transactions.csv"):
        with open(csv_filename, mode='w', newline='') as file:
            writer = csv.writer(file)
            writer.writerow(["Date", "Type", "Category", "Amount", "Note"])
            for t in self.transactions:
                writer.writerow([t.date, t.type, t.category, t.amount, t.note])
        print(f"Exported to {csv_filename}")

    def delete_all(self):
        confirm = input("Are you sure you want to delete all data? (y/n): ").lower()
        if confirm == 'y':
            self.transactions.clear()
            self.save()
            print("All data cleared.")
        else:
            print("Cancelled.")


# === UI: Menu System ===

def print_menu():
    print("\n=== Personal Finance Tracker ===")
    print("1. Add Income")
    print("2. Add Expense")
    print("3. View All Transactions")
    print("4. View Income Only")
    print("5. View Expenses Only")
    print("6. Search by Category")
    print("7. Summary")
    print("8. Export to CSV")
    print("9. Delete All Data")
    print("0. Save and Exit")


def get_float(prompt):
    while True:
        try:
            return float(input(prompt))
        except ValueError:
            print("Please enter a valid number.")


# === Main Program ===

def main():
    tracker = FinanceTracker()

    while True:
        print_menu()
        choice = input("Choose an option: ")

        if choice == "1":
            category = input("Income category (e.g., Salary, Bonus): ")
            amount = get_float("Amount: $")
            note = input("Note (optional): ")
            tracker.add_transaction("income", category, amount, note)

        elif choice == "2":
            category = input("Expense category (e.g., Rent, Food): ")
            amount = get_float("Amount: $")
            note = input("Note (optional): ")
            tracker.add_transaction("expense", category, amount, note)

        elif choice == "3":
            tracker.view_all()

        elif choice == "4":
            tracker.view_by_type("income")

        elif choice == "5":
            tracker.view_by_type("expense")

        elif choice == "6":
            keyword = input("Enter category keyword: ")
            tracker.search_by_category(keyword)

        elif choice == "7":
            tracker.summary()

        elif choice == "8":
            tracker.export_csv()

        elif choice == "9":
            tracker.delete_all()

        elif choice == "0":
            tracker.save()
            print("Goodbye!")
            break

        else:
            print("Invalid choice. Please select from 0-9.")

if __name__ == "__main__":
    main()

