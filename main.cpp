// main.cpp
#include <iostream>
#include <limits>
#include "user.h"
#include "expense_manager.h"
#include "utils.h"
#include "budget.h"
#include "expense.h"

static std::string prompt(const std::string& msg) {
    std::string s;
    std::cout << msg;
    std::getline(std::cin, s);
    return s;
}

static double promptDouble(const std::string& msg) {
    while (true) {
        std::cout << msg;
        std::string s;
        std::getline(std::cin, s);
        try {
            return std::stod(s);
        } catch (...) {
            std::cout << "Invalid number. Try again.\n";
        }
    }
}

int main() {
    User user;
    while (true) {
        std::cout << "1) Register   2) Login   0) Exit\n> ";
        std::string choice; std::getline(std::cin, choice);
        if (choice=="1") { registerUser(); }
        else if (choice=="2" && loginUser(user)) { break; }
        else if (choice=="0") return 0;
    }

    ExpenseManager mgr(user.dataFile, user.username + "_budget.txt");
    mgr.loadExpenses();
    mgr.loadBudget();

    bool running = true;
    while (running) {
        std::cout << "\n--- Menu ---\n"
                     "1) Add Expense\n"
                     "2) Remove Expense\n"
                     "3) List All\n"
                     "4) List by Range\n"
                     "5) Set Budget\n"
                     "6) View Budget\n"
                     "7) Clear Budget\n"
                     "0) Logout/Exit\n> ";
        std::string opt; std::getline(std::cin, opt);

        if (opt=="1") {
            std::string date;
            do {
                date = prompt("Date (YYYY-MM-DD): ");
                if (!isValidDate(date)) {
                    std::cout << "Invalid date. Please enter the date in YYYY-MM-DD format. \n";
                }
            } while (!isValidDate(date));

            std::string desc = prompt("Description: ");
            double amt;
            do {
                amt = promptDouble("Amount: ");
                if (!isPositiveMonetaryValue(amt)) {
                    std::cout << "Invalid value. Please enter a non-negative amount. \n";
                }
            } while (!isPositiveMonetaryValue(amt));
            
            std::string cat = prompt("Category: ");
            std::string freq;
            do {
                freq = prompt("Frequency (NONE/DAILY/WEEKLY/MONTHLY): ");
                if (!isValidExpenseFrequency(freq)) {
                    std::cout << "Invalid expense frequency. Please enter NONE/DAILY/WEEKLY/MONTHLY. \n";
                }
            } while (!isValidExpenseFrequency(freq));
            Expense e(date, desc, amt, cat, stringToFrequency(freq));
            mgr.addExpense(e);
            mgr.saveExpenses();
            std::cout << "Added.\n";
        }
        else if (opt=="2") {
            auto all = mgr.getAll();
            for (size_t i=0; i<all.size(); ++i)
                std::cout << i << ": " << all[i].toCSV() << "\n";
            size_t idx = (size_t)promptDouble("Index to remove: ");
            if (mgr.removeExpense(idx)) {
                mgr.saveExpenses();
                std::cout << "Removed.\n";
            } else {
                std::cout << "Invalid index.\n";
            }
        }
        else if (opt=="3") {
            for (auto& e : mgr.getAll())
                std::cout << e.toCSV() << "\n";
            if (auto b = mgr.currentBudget()) {
                double tot = mgr.totalInRange(b->startDate, b->endDate);
                std::cout << "Total: " << tot
                          << " / Budget: " << b->amount;
                if (tot > b->amount)
                    std::cout << " (over by " << tot - b->amount << ")";
                std::cout << "\n";
            }
        }
        else if (opt=="4") {
            std::string s = prompt("Start date: ");
            std::string e = prompt("End date: ");
            for (auto& ex : mgr.filterByDate(s,e))
                std::cout << ex.toCSV() << "\n";
            std::cout << "Total in range: "
                      << mgr.totalInRange(s,e) << "\n";
        }
        else if (opt=="5") {
            Budget b;
            b.amount = promptDouble("Budget amount: ");
            b.startDate = prompt("Start date: ");
            b.endDate   = prompt("End date: ");
            mgr.saveBudget(b);
            std::cout << "Budget set.\n";
        }
        else if (opt=="6") {
            if (auto b = mgr.currentBudget()) {
                std::cout << "Budget " << b->amount
                          << " from " << b->startDate
                          << " to " << b->endDate << "\n";
            } else {
                std::cout << "No budget set.\n";
            }
        }
        else if (opt=="7") {
            mgr.clearBudget();
            std::cout << "Budget cleared.\n";
        }
        else if (opt=="0") {
            running = false;
        }
        else {
            std::cout << "Unknown option.\n";
        }
    }

    return 0;
}

