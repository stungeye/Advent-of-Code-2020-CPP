#include "BinaryBoarding.h"
#include "test/catch.hpp"

using namespace binary_boarding;

const std::string filename = "BinaryBoarding.txt";

TEST_CASE("File Loading Test") {
    const auto boarding_entries{ read_boarding_file((filename)) };
    REQUIRE(boarding_entries.size() == 826);
}


TEST_CASE("Binary Space Parition Row and Column Tests") {
    std::string code = "BFFFBBFRRR";
    REQUIRE(boarding_id(code) == 567);

    code = "FFFBBBFRRR";
    REQUIRE(boarding_id(code) == 119);

    code = "BBFFBBFRLL";
    REQUIRE(boarding_id(code) == 820);
}

TEST_CASE("Max Boarding Id Mini Test") {
    std::vector<std::string> codes = { "BFFFBBFRRR", "FFFBBBFRRR", "BBFFBBFRLL" };
    REQUIRE(max_boarding_id(codes) == 820);

    std::vector<std::string> rearranged_codes = { "BBFFBBFRLL", "BFFFBBFRRR", "FFFBBBFRRR" };

    REQUIRE(max_boarding_id(rearranged_codes) == 820);
}

TEST_CASE("Max Boarding Id Full Data") {
    const auto boarding_entries{ read_boarding_file((filename)) };
    REQUIRE(max_boarding_id(boarding_entries) == 874);
}

TEST_CASE("Empty Seat Test") {
    const auto boarding_entries{ read_boarding_file((filename)) };
    REQUIRE(first_empty_seat(boarding_entries) == 594);
}
