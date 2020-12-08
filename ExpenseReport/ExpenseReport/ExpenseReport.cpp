#include "ExpenseReport.h"
#include <fstream>
#include <iostream>

namespace ExpenseReport {
    // Reads each line of the input file in a set of unique integers.
    // Note: Testing a set to see if it contains specific numbers is a very quick operation using find().
    std::unordered_set<int> read_expense_report_file(const std::string& filename) {
        std::ifstream input_file{filename};

        if (!input_file) {
            std::cerr << "Cannot open the File : " << filename << "\n";
        }

        std::unordered_set<int> expense_report{std::istream_iterator<int>{input_file}, {}};
        return expense_report;
    }

    // Searches through a set of unique numbers for two entries that add up to a given sum.
    // Returns the products of these two numbers.
    int product_of_two_expenses_that_equal_sum(const std::unordered_set<int>& expenses, const int& sum) {
        // Test each number in the set to see...
        for (const auto& candidate1 : expenses) {
            // ...if there's another number in the set that can be added to the first to make a given sum.
            const auto candidate2 = sum - candidate1;
            if (expenses.find(candidate2) != expenses.end()) {
                return candidate1 * candidate2;
            }
        }

        return 0; // If no pair was found.
    }

    // Searches through a set of unique numbers for three entries that add up to a given sum.
    // Returns the products of these three numbers.
    int product_of_three_expenses_that_equal_sum(const std::unordered_set<int>& expenses, const int& sum) {
        // Nested for-loops to test all possible combinations of pairs in the set to see...
        for (const auto& candidate1 : expenses) {
            for (const auto& candidate2 : expenses) {
                // ...if there's a third number in the set that when added to the pair makes a given sum.
                const auto candidate3 = sum - candidate1 - candidate2;
                if (expenses.find(candidate3) != expenses.end()) {
                    return candidate1 * candidate2 * candidate3;
                }
            }
        }

        return 0; // If no triplet was found.
    }
} // namespace ExpenseReport
