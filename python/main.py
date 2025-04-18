
# Tries to read a users file.
def load_users(filename):
    users = {}
    try:
        with open(filename, "r") as file:
            for line in file:
                username, password = line.strip().split(":")
                users[username] = password
    except FileNotFoundError:
        open(filename, "w").close()  # Create the file if it doesn't exist
    return users

def save_user(filename, user, password):
    try:
        f = open(filename, "a")  
        f.write(user + ":" + password +"\n")
    except FileNotFoundError:
        open(filename, "w").close()

    
def main():
    filename = "users.txt"
    cond =save_user(filename, "mark", "iplier")

    if cond:
       print("hooray!")
    else:
        print("couldn't open the file?")


if __name__ == "__main__":
    main()