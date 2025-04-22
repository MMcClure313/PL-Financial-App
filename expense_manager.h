// expense_manager.h
#ifndef EXPENSE_MANAGER_H
#define EXPENSE_MANAGER_H

#include <vector>
#include <string>
#include "expense.h"
#include "budget.h"

class ExpenseManager {
public:
    ExpenseManager(const std::string& dataFile, const std::string& budgetFile);

    // Load/save all expenses
    bool loadExpenses();
    bool saveExpenses() const;

    // Add or remove
    void addExpense(const Expense& exp);
    bool removeExpense(size_t index);

    // Listing/filtering
    std::vector<Expense> getAll() const;
    std::vector<Expense> filterByDate(const std::string& start, const std::string& end) const;

    // Totals & budget
    double totalInRange(const std::string& start, const std::string& end) const;
    bool loadBudget();
    bool saveBudget(const Budget& b);
    void clearBudget();

    // Access current budget
    const Budget* currentBudget() const;

private:
    std::string dataFile_;
    std::string budgetFile_;
    std::vector<Expense> expenses_;
    Budget budget_;
    bool hasBudget_;
};

#endif // EXPENSE_MANAGER_H
