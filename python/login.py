import os

USERS_FILE = "users.txt"

# Tries to read a users file.
def load_users():
    users = {}
    try:
        with open(USERS_FILE, "r") as file:
            for line in file:
                username, password = line.strip().split(":")
                users[username] = password
    except FileNotFoundError:
        pass
    return users

# Does the actual writing to a file, leaving a new line for the next user.
def save_user(user, password):
    try:
        f = open(USERS_FILE, "a")  
        f.write(user + ":" + password +"\n")
    except FileNotFoundError:
        pass

# Creates the financial data file for the user and adds in some headers.
def create_user_csv(username):
    filename = f"{username}.csv"
    if not os.path.exists(filename):
        with open(filename, "w") as f:
            f.write("Date,Description,Amount,Category\n")  # headers for financial data

# Checks if the user exists first, then saves user based on params
def register_user(username, password):
    users = load_users()
    if username in users:
        return False, "User already exists."
    save_user(username, password)
    create_user_csv(username)
    return True, "Registered successfully!"

# Just checks if username and password match. Still hate this whole double return thing.
def login_user(username, password):
    users = load_users()
    if username not in users:
        return False, "Username not found."
    if users[username] != password:
        return False, "Incorrect password."
    return True, "Login successful!"


