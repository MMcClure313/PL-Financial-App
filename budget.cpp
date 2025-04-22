// budget.cpp
#include "budget.h"
#include <fstream>
#include <sstream>
#include <cstdio>

// Save the given budget to a file (overwrites any existing)
bool saveBudget(const Budget& budget, const std::string& budgetFile) {
    std::ofstream out(budgetFile);
    if (!out) return false;
    out << budget.amount << ","
        << budget.startDate << ","
        << budget.endDate << "\n";
    return true;
}

// Load the budget from a file; returns false if no budget is set or parse fails
bool loadBudget(Budget& budget, const std::string& budgetFile) {
    std::ifstream in(budgetFile);
    if (!in) return false;

    std::string line;
    if (!std::getline(in, line)) return false;

    std::istringstream iss(line);
    std::string token;

    // Amount
    if (!std::getline(iss, token, ',')) return false;
    try {
        budget.amount = std::stod(token);
    } catch (...) {
        return false;
    }

    // Start date
    if (!std::getline(iss, budget.startDate, ',')) return false;

    // End date
    if (!std::getline(iss, budget.endDate, ',')) return false;

    return true;
}

// Delete any existing budget (resets to “no budget”)
bool clearBudget(const std::string& budgetFile) {
    // Remove the budget file if it exists
    std::remove(budgetFile.c_str());
    return true;
}
