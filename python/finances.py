import csv
from datetime import datetime

def menu(username):
    while True:
        print(f"\nWelcome, {username}! What would you like to do?")
        print("1. Add a cost")
        print("2. View costs")
        print("3. Logout")

        choice = input("Enter choice: ")

        if choice == "1":
            add_cost(username)
        elif choice == "2":
            view_costs(username)
        elif choice == "3":
            print("Logging out...")
            break
        else:
            print("Invalid option. Try again.")
            
def add_cost(username):
    date = input("Enter date (YYYY-MM-DD) or leave blank for today: ")
    if not date:
        date = datetime.now().strftime("%Y-%m-%d")
    description = input("Description: ")
    amount = input("Amount: ")
    category = input("Category: ")

    with open(f"{username}.csv", "a", newline='') as f:
        writer = csv.writer(f)
        writer.writerow([date, description, amount, category])

    print("Cost added successfully!")
    
def view_costs(username):
    try:
        with open(f"{username}.csv", "r") as f:
            reader = csv.reader(f)
            print("\nYour Costs:")
            for row in reader:
                print(", ".join(row))
    except FileNotFoundError:
        print("No records found.")