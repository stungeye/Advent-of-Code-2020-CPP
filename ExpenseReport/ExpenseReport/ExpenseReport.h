// SampleCMakeProject.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <string>
#include <unordered_set>

namespace ExpenseReport {
    std::unordered_set<int> read_expense_report_file(const std::string& filename);

    int product_of_two_expenses_that_equal_sum(const std::unordered_set<int>& expenses, const int& sum);
    int product_of_three_expenses_that_equal_sum(const std::unordered_set<int>& expenses, const int& sum);
}
