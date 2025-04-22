// user.h
#ifndef USER_H
#define USER_H

#include <string>

struct User {
    std::string username;
    std::string dataFile; // e.g., "bob.csv"
};

// Function to register a new user
bool registerUser();

// Function to log in an existing user
bool loginUser(User& user);

// Helper to check if a user already exists
bool userExists(const std::string& username);

#endif // USER_H
