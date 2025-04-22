// expense.cpp
#include "expense.h"
#include <sstream>
#include <vector>
#include <stdexcept>

// ---------------- Expense Methods ----------------

Expense::Expense(const std::string& date,
                 const std::string& description,
                 double amount,
                 const std::string& category,
                 Frequency frequency)
    : date_(date),
      description_(description),
      amount_(amount),
      category_(category),
      frequency_(frequency) { }

std::string Expense::toCSV() const {
    std::ostringstream oss;
    oss << date_ << ","
        << description_ << ","
        << amount_ << ","
        << category_ << ","
        << frequencyToString(frequency_);
    return oss.str();
}

Expense Expense::fromCSV(const std::string& csvLine) {
    std::istringstream iss(csvLine);
    std::string token;
    std::vector<std::string> parts;
    while (std::getline(iss, token, ',')) {
        parts.push_back(token);
    }
    if (parts.size() != 5) {
        throw std::runtime_error("Invalid CSV line for Expense");
    }

    const std::string& date        = parts[0];
    const std::string& description = parts[1];
    double amount                  = std::stod(parts[2]);
    const std::string& category    = parts[3];
    Frequency freq                 = stringToFrequency(parts[4]);

    return Expense(date, description, amount, category, freq);
}

const std::string& Expense::getDate() const {
    return date_;
}

const std::string& Expense::getDescription() const {
    return description_;
}

double Expense::getAmount() const {
    return amount_;
}

const std::string& Expense::getCategory() const {
    return category_;
}

Frequency Expense::getFrequency() const {
    return frequency_;
}

// --------------- Frequency Helpers ---------------

std::string frequencyToString(Frequency freq) {
    switch (freq) {
        case Frequency::DAILY:   return "DAILY";
        case Frequency::WEEKLY:  return "WEEKLY";
        case Frequency::MONTHLY: return "MONTHLY";
        case Frequency::NONE:
        default:                 return "NONE";
    }
}

Frequency stringToFrequency(const std::string& freqStr) {
    if (freqStr == "DAILY")   return Frequency::DAILY;
    if (freqStr == "WEEKLY")  return Frequency::WEEKLY;
    if (freqStr == "MONTHLY") return Frequency::MONTHLY;
    return Frequency::NONE;
}
