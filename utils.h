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

#endif // UTILS_H
