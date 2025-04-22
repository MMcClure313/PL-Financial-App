// expense.h
#ifndef EXPENSE_H
#define EXPENSE_H

#include <string>

enum class Frequency {
    NONE,
    DAILY,
    WEEKLY,
    MONTHLY
};

class Expense {
public:
    // Constructor
    Expense(const std::string& date,
            const std::string& description,
            double amount,
            const std::string& category,
            Frequency frequency);

    // Serialize to a CSV row
    std::string toCSV() const;

    // Deserialize from a CSV row
    static Expense fromCSV(const std::string& csvLine);

    // Getters
    const std::string& getDate() const;
    const std::string& getDescription() const;
    double getAmount() const;
    const std::string& getCategory() const;
    Frequency getFrequency() const;

private:
    std::string date_;         // e.g. "2025-04-20"
    std::string description_;  // e.g. "Coffee"
    double amount_;            // e.g. 3.50
    std::string category_;     // e.g. "Food"
    Frequency frequency_;      // NONE, DAILY, WEEKLY, MONTHLY
};

// Helper to convert between Frequency enum and string
std::string frequencyToString(Frequency freq);
Frequency stringToFrequency(const std::string& freqStr);

#endif // EXPENSE_H
