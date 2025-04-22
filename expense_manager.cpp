// expense_manager.cpp
#include "expense_manager.h"
#include "utils.h"
#include <fstream>
#include <sstream>

// ctor
ExpenseManager::ExpenseManager(const std::string& dataFile, const std::string& budgetFile)
  : dataFile_(dataFile), budgetFile_(budgetFile), hasBudget_(false) {}

// load all expenses from CSV
bool ExpenseManager::loadExpenses() {
    expenses_.clear();
    std::ifstream in(dataFile_);
    if (!in) return false;
    std::string line;
    std::getline(in, line); // skip header
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        expenses_.push_back(Expense::fromCSV(line));
    }
    return true;
}

// write back
bool ExpenseManager::saveExpenses() const {
    std::ofstream out(dataFile_);
    if (!out) return false;
    out << "date,description,amount,category,frequency\n";
    for (auto& e : expenses_) {
        out << e.toCSV() << "\n";
    }
    return true;
}

void ExpenseManager::addExpense(const Expense& exp) {
    expenses_.push_back(exp);
}

bool ExpenseManager::removeExpense(size_t idx) {
    if (idx >= expenses_.size()) return false;
    expenses_.erase(expenses_.begin() + idx);
    return true;
}

std::vector<Expense> ExpenseManager::getAll() const {
    return expenses_;
}

std::vector<Expense> ExpenseManager::filterByDate(const std::string& start, const std::string& end) const {
    std::vector<Expense> out;
    for (auto& e : expenses_) {
        if (isDateInRange(e.getDate(), start, end))
            out.push_back(e);
    }
    return out;
}

double ExpenseManager::totalInRange(const std::string& start, const std::string& end) const {
    double sum = 0;
    for (auto& e : filterByDate(start, end))
        sum += e.getAmount();
    return sum;
}

bool ExpenseManager::loadBudget() {
    hasBudget_ = ::loadBudget(budget_, budgetFile_);  // qualified to call the free function
    return hasBudget_;
}

bool ExpenseManager::saveBudget(const Budget& b) {
    budget_ = b;
    hasBudget_ = true;
    return ::saveBudget(budget_, budgetFile_);
}

void ExpenseManager::clearBudget() {
    ::clearBudget(budgetFile_);
    hasBudget_ = false;
}

const Budget* ExpenseManager::currentBudget() const {
    return hasBudget_ ? &budget_ : nullptr;
}

