// utils.cpp
#include "utils.h"
#include <algorithm>

// simple split
std::vector<std::string> split(const std::string& s, char delim) {
    std::vector<std::string> out;
    std::string cur;
    for (char c : s) {
        if (c == delim) {
            out.push_back(cur);
            cur.clear();
        } else {
            cur.push_back(c);
        }
    }
    out.push_back(cur);
    return out;
}

// lexicographic works for YYYY‑MM‑DD
bool isDateInRange(const std::string& date,
                   const std::string& start,
                   const std::string& end) {
    return date >= start && date <= end;
}

// Check if the date falls within a valid calender range
bool isValidDate(const std::string& date) {
    if (date.size() != 10 || date[4] != '-' || date[7] != '-')  // ex: 2025-04-25, checks if value matches correct format and '-' position
        return false;

    // check that non '-' characters are digits
    for (size_t i = 0; i < date.size(); ++i) {
        if (i != 4 && i != 7 && !std::isdigit(static_cast<unsigned char>(date[i]))) {
            return false;
        }
    }

    int month = std::stoi(date.substr(5, 2));
    int day = std::stoi(date.substr(8, 2));

    if (month >= 1 && month <= 12 && day >= 1 && day <= 31) {
        return true;
    } else {
        return false;
    }
}

// Check if monetary value entered is a positive value
bool isPositiveMonetaryValue(double x) {
    if (x > 0.0) {
        return true;
    } else {
        return false;
    }
}

// Check if the set payment frequency matches the valid options (ex. WEEKLY)
bool isValidExpenseFrequency(const std::string& freq) {
    if (freq == "NONE" || freq == "DAILY" || freq == "WEEKLY" || freq == "MONTHLY") {
        return true;
    } else {
        return false;
    }
}