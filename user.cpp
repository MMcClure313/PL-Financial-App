// user.cpp
#include "user.h"
#include <iostream>
#include <fstream>
#include <sstream>

// Path to the master users file
const std::string USERS_FILE = "users.txt";

bool userExists(const std::string& username) {
    std::ifstream in(USERS_FILE);
    if (!in) return false;  // no file means no users yet

    std::string line;
    while (std::getline(in, line)) {
        std::istringstream iss(line);
        std::string storedUser;
        if (std::getline(iss, storedUser, ',')) {
            if (storedUser == username) {
                return true;
            }
        }
    }
    return false;
}

bool registerUser() {
    std::string username, password;
    std::cout << "Choose a username: ";
    std::getline(std::cin, username);

    if (userExists(username)) {
        std::cout << "Error: Username already taken.\n";
        return false;
    }

    std::cout << "Choose a password: ";
    std::getline(std::cin, password);

    // Create a data file name
    std::string dataFile = username + ".csv";

    // Append new user record
    std::ofstream out(USERS_FILE, std::ios::app);
    if (!out) {
        std::cerr << "Error: Unable to open users file for writing.\n";
        return false;
    }
    out << username << "," << password << "," << dataFile << "\n";
    out.close();

    // Create an empty CSV with header for this user
    std::ofstream userData(dataFile);
    if (userData) {
        userData << "date,description,amount,category,frequency\n";
        userData.close();
    }

    std::cout << "Registered successfully! You can now log in.\n";
    return true;
}

bool loginUser(User& user) {
    std::string username, password;
    std::cout << "Username: ";
    std::getline(std::cin, username);
    std::cout << "Password: ";
    std::getline(std::cin, password);

    std::ifstream in(USERS_FILE);
    if (!in) {
        std::cerr << "Error: No users registered yet.\n";
        return false;
    }

    std::string line;
    while (std::getline(in, line)) {
        std::istringstream iss(line);
        std::string storedUser, storedPass, storedFile;
        if (std::getline(iss, storedUser, ',') &&
            std::getline(iss, storedPass, ',') &&
            std::getline(iss, storedFile, ',')) {
            if (storedUser == username && storedPass == password) {
                user.username = storedUser;
                user.dataFile = storedFile;
                std::cout << "Login successful!\n";
                return true;
            }
        }
    }

    std::cout << "Login failed: Invalid credentials.\n";
    return false;
}
