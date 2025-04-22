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
