#include "ExpenseReport.h"
#include "test/catch.hpp"
#include <unordered_set>

TEST_CASE("File Input Test") {
    const std::string filename = "ExpenseReport.txt";

    REQUIRE(ExpenseReport::read_expense_report_file(filename).size() == 200);
}

TEST_CASE("Mini Input Test - Two Numbers") {
    const std::unordered_set<int> expenses{ 1721, 979, 366, 299, 675, 1456 };
    REQUIRE(ExpenseReport::product_of_two_expenses_that_equal_sum(expenses, 2020) == 514579);
}

TEST_CASE("Full Input Test - Two Numbers") {
    const std::string filename = "ExpenseReport.txt";
    const std::unordered_set<int> expenses = ExpenseReport::read_expense_report_file(filename);
    REQUIRE(ExpenseReport::product_of_two_expenses_that_equal_sum(expenses, 2020) == 436404);
}

TEST_CASE("Mini Input Test - Three Numbers") {
    const std::unordered_set<int> expenses{ 1721, 979, 366, 299, 675, 1456 };
    REQUIRE(ExpenseReport::product_of_three_expenses_that_equal_sum(expenses, 2020) == 241861950);
}

TEST_CASE("Full Input Test - Three Numbers") {
    const std::string filename = "ExpenseReport.txt";
    const std::unordered_set<int> expenses = ExpenseReport::read_expense_report_file(filename);
    REQUIRE(ExpenseReport::product_of_three_expenses_that_equal_sum(expenses, 2020) == 274879808);
}

