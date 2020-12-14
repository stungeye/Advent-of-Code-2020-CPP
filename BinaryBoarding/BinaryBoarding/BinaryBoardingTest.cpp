#include "BoardingPass.h"
#include "PassengerRoster.h"
#include "file_helpers.h"
#include "test/catch.hpp"

using namespace file_helpers;

const std::string filename = "BinaryBoarding.txt";

TEST_CASE("File Loading Test") {
    const auto boarding_entries{ read_boarding_file((filename)) };

    REQUIRE(boarding_entries.size() == 826);
    REQUIRE(boarding_entries.front() == "FFBBFFBRRR");
    REQUIRE(boarding_entries.back() == "FFBFBFBRLL");
}

TEST_CASE("Binary Space Parition Row and Column Tests") {
    std::string code = "BFFFBBFRRR";
    REQUIRE(BoardingPass(code) == BoardingPass(567));
    REQUIRE(BoardingPass(567) == BoardingPass(code));

    code = "FFFBBBFRRR";
    REQUIRE(BoardingPass(code) == BoardingPass(119));

    code = "BBFFBBFRLL";
    REQUIRE(BoardingPass(code) == BoardingPass(820));
}

TEST_CASE("Max Boarding Id Mini Test") {
    std::vector<std::string> codes = { "BFFFBBFRRR", "FFFBBBFRRR", "BBFFBBFRLL" };
    REQUIRE(PassengerRoster(codes).max_boarding_pass() == BoardingPass(820));

    std::vector<std::string> rearranged_codes = { "BBFFBBFRLL", "BFFFBBFRRR", "FFFBBBFRRR" };

    REQUIRE(PassengerRoster(codes).max_boarding_pass() == BoardingPass(820));
}

TEST_CASE("Max Boarding Id Full Data") {
    const auto boarding_entries{ read_boarding_file((filename)) };
    REQUIRE(PassengerRoster(boarding_entries).max_boarding_pass() == BoardingPass(874));
}

TEST_CASE("Empty Seat Test") {
    const auto boarding_entries{ read_boarding_file((filename)) };
    REQUIRE(PassengerRoster(boarding_entries).first_empty_seat() == BoardingPass(594));
}

