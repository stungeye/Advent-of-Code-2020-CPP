#include "BinaryBoarding.h"
#include "test/catch.hpp"

using namespace binary_boarding;

const std::string filename = "BinaryBoarding.txt";

TEST_CASE("File Loading Test") {
    const auto boarding_entries{ read_boarding_file((filename)) };
    REQUIRE(boarding_entries.size() == 826);
}

TEST_CASE("Binary Space Partition Row Tests") {
    std::string row_entry = "BFFFBBF";
    REQUIRE(find_bsp_position(row_entry, max_rows, 'F') == 70);

    row_entry = "FFFBBBF";
    REQUIRE(find_bsp_position(row_entry, max_rows, 'F') == 14);

    row_entry = "BBFFBBF";
    REQUIRE(find_bsp_position(row_entry, max_rows, 'F') == 102);
}

TEST_CASE("Binary Space Partition Column Tests") {
    std::string column_entry = "RRR";
    REQUIRE(find_bsp_position(column_entry, max_columns, 'L') == 7);

    column_entry = "RLL";
    REQUIRE(find_bsp_position(column_entry, max_columns, 'L') == 4);
}

TEST_CASE("Binary Space Parition Row and Column Tests") {
    std::string code = "BFFFBBFRRR";
    REQUIRE(boarding_id(code, max_rows, max_columns) == 567);

    code = "FFFBBBFRRR";
    REQUIRE(boarding_id(code, max_rows, max_columns) == 119);

    code = "BBFFBBFRLL";
    REQUIRE(boarding_id(code, max_rows, max_columns) == 820);
}

TEST_CASE("Max Boarding Id Mini Test") {
    std::vector<std::string> codes = { "BFFFBBFRRR", "FFFBBBFRRR", "BBFFBBFRLL" };
    REQUIRE(max_boarding_id(codes, max_rows, max_columns) == 820);

    std::vector<std::string> rearranged_codes = { "BBFFBBFRLL", "BFFFBBFRRR", "FFFBBBFRRR" };

    REQUIRE(max_boarding_id(rearranged_codes, max_rows, max_columns) == 820);
}

TEST_CASE("Max Boarding Id Full Data") {
    const auto boarding_entries{ read_boarding_file((filename)) };
    REQUIRE(max_boarding_id(boarding_entries, max_rows, max_columns) == 874);
}

TEST_CASE("Empty Seat Test") {
    const auto boarding_entries{ read_boarding_file((filename)) };
    REQUIRE(first_empty_seat(boarding_entries, max_rows, max_columns) == 594);
}
