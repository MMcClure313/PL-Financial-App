// budget.h
#ifndef BUDGET_H
#define BUDGET_H

#include <string>

// Represents a user’s budget over a date range
struct Budget {
    double amount;         // budget limit
    std::string startDate; // inclusive, e.g. "2025-04-01"
    std::string endDate;   // inclusive, e.g. "2025-04-30"
};

// Save the given budget to a file (e.g. "<username>_budget.txt")
bool saveBudget(const Budget& budget, const std::string& budgetFile);

// Load the budget from a file; returns false if no budget is set
bool loadBudget(Budget& budget, const std::string& budgetFile);

// Delete any existing budget (resets to “no budget”)
bool clearBudget(const std::string& budgetFile);

#endif // BUDGET_H
