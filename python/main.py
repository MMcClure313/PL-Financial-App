import login
import finances

def main():
    print("Welcome to the Finance App!")
    while True:
        print("\n1. Register\n2. Login\n3. Exit")
        choice = input("Choose: ")
        if choice == "1":
            u = input("Username: ")
            p = input("Password: ")
            success, message = login.register_user(u, p)
            print(message)
        elif choice == "2":
            u = input("Username: ")
            p = input("Password: ")
            success, message = login.login_user(u, p)
            print(message)
            if success:
                finances.menu(u)
        elif choice == "3":
            break
        else:
            print("Invalid choice.")


if __name__ == "__main__":
    main()