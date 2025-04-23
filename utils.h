// utils.h
#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

// Split a string by delimiter
std::vector<std::string> split(const std::string& s, char delim);

// Check if date (YYYY‑MM‑DD) is in [start, end]
bool isDateInRange(const std::string& date,
                   const std::string& start,
                   const std::string& end);

// Check if the date falls within a valid calender range
bool isValidDate(const std::string& date);

// Check if monetary value entered is a positive value
bool isPositiveMonetaryValue(double x);

// Check if the set payment frequency matches the valid options (ex. WEEKLY)
bool isValidExpenseFrequency(const std::string& freq);

#endif // UTILS_H
