import csv
from datetime import datetime

def menu(username):
    while True:
        print(f"\nWelcome, {username}! What would you like to do?")
        print("1. Add a cost")
        print("2. Remove a cost")
        print("3. View costs")
        print("4. Modify monthly budget")
        print("5. Logout")

        choice = input("Enter choice: ")

        if choice == "1":
            add_cost(username)
        elif choice == "2":
            remove_cost(username)
        elif choice == "3":
            view_costs(username)
        elif choice == "4":
            update_budget(username)
        elif choice == "5":
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
    try:
        float(amount)
    except ValueError:
        print("\033[91mInvalid number entered.\033[0m")
        return False
    
    category = input("Category: ")
    while True:
        print("Select frequency of the purchase")
        print("0. One time\n1. Daily\n2. Weekly\n3. Monthly")
        choice = input("Enter the associated number: ")
        if choice in {"0", "1", "2", "3"}:
            break
        else:
            print("Invalid choice. Please enter a number from 0 to 3.")

    with open(f"{username}.csv", "a", newline='') as f:
        writer = csv.writer(f)
        writer.writerow([date, description, amount, category, choice])

    print("Cost added successfully!")

def remove_cost(username):
    filename = f"{username}.csv"
    try:
        with open(filename, "r") as f:
            rows = list(csv.reader(f))

        if len(rows) <= 2:
            print("\nNo costs to remove.")
            return

        print("\nExisting Costs:")
        for idx, row in enumerate(rows[2:], start=1):  # skip budget and header
            print(f"{idx}. {row[0]} | {row[1]} | ${row[2]} | {row[3]}")

        choice = input("\nEnter the number of the cost to remove (or press enter to cancel): ")
        if not choice.isdigit():
            print("Invalid input. Cancelled.")
            return

        choice = int(choice)
        if 1 <= choice <= len(rows) - 2:
            rows.pop(choice + 1)  # +1 because row[0] is budget, row[1] is header
            with open(filename, "w", newline="") as f:
                writer = csv.writer(f)
                writer.writerows(rows)
            print(f"\nRemoved cost")
        else:
            print("Number out of range.")
    except FileNotFoundError:
        print("File not found.")
 
def update_budget(username):
    filename= f"{username}.csv"
    try:
        with open(filename, "r") as f:
            lines = f.readlines()
            
        new_budget = input("Enter your new budget (0 for none): ")
            
        try:
            float(new_budget)
        except ValueError:
            print("\033[91mInvalid number entered.\033[0m")
            return False
                
        if lines and lines[0].startswith("Budget,"):
            lines[0] = f"Budget,{new_budget}\n"
        else:
            lines.insert(0, f"Budget,{new_budget}\n")
        
        with open(filename, "w") as f:
            f.writelines(lines)
        
        return True

    except FileNotFoundError:
        print(f"File for {username} not found.")
        return False

def view_costs(username):
    freq_map = {
        "0": "One time",
        "1": "Daily",
        "2": "Weekly",
        "3": "Monthly"
    }
    
    total_cost_month = 0
    total_cost_year = 0
    budget = get_budget(username)
    
    try:
        with open(f"{username}.csv", "r") as f:
            reader = csv.reader(f)
            lines = list(reader)
            
            
            print("\nYour Costs:")
            print("-" * 80)
            for i, row in enumerate(lines):
                if i == 0 and row[0].startswith("Budget"):
                    continue
                elif i == 1:
                    print(
                        f"\033[91m{row[0]:<12}\033[0m | "  # Date (Red)
                        f"\033[92m{row[1]:<25}\033[0m | "  # Description (Green)
                        f"\033[93m{row[2]:>7}\033[0m | "   # Amount (Yellow)
                        f"\033[94m{row[3]:<15}\033[0m | "     # Category (Blue)
                        f"\033[95m{row[4]:<10}\033[0m | " #Frequency is Pink
                        f"\033[96mMonthly cost\033[0m | "
                        f"\033[97mYearly cost\033[0m"

                    )
                else:
                    monthly, yearly = get_row_cost(row)
                    total_cost_month += monthly
                    total_cost_year += yearly
                    
                    freq = freq_map.get(row[4], row[4])
                    row[4] = freq
                    # Data rows - normal formatting
                    print(
                        f"{row[0]:<12} | "
                        f"{row[1]:<25} | "
                        f"${row[2]:>6} | "
                        f"{row[3]:<15} | "
                        f"{row[4]:<10} | "
                        f"${monthly:<11} | "
                        f"${yearly}"
                    )
            print(f"\n\nTotal costs in the month: $\033[93m{total_cost_month:.2f}\033[0m\nTotal costs in the year: $\033[93m{total_cost_year:.2f}\033[0m")
            if(total_cost_month < budget):
                print(f"\n\033[92mYou are still within your monthly budget of ${budget:.2f} with ${budget - total_cost_month:.2f} remaining!\033[0m")
            elif(total_cost_month > budget):
                print(f"\n\033[91mYou are over your monthly budget of ${budget:.2f}, spending ${budget - total_cost_month:.2f} over! Consider cutting non-essential costs.\033[0m")

                
                
    except FileNotFoundError:
        print("No records found.")
        
        
def get_budget(username):
    try:
        with open(f"{username}.csv", "r") as f:
            reader = csv.reader(f)
            first_line = next(reader)
            if first_line[0].lower() == "budget":
                return float(first_line[1])
    except (FileNotFoundError, IndexError, ValueError):
        pass
    return 0.0  # default if not found or file corrupted


def get_row_cost(row):
    try:
        cost = float(row[2])
        freq = int(row[4])
        if(freq == 0):
            return cost, cost
        elif(freq == 1):
            return cost * 30, cost * 365
        elif(freq == 2):
            return cost * 4, cost * 52
        elif(freq == 3):
            return cost, cost*12
    except (ValueError, IndexError):
        pass
    
    return 0.0, 0.0