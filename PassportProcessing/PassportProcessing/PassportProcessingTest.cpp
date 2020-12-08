#include "PassportProcessing.h"
#include "test/catch.hpp"

using namespace passport_processing;

const std::string filename = "PassportProcessing.txt";

TEST_CASE("Custom Split Test") {
    std::string test_string{"this is the test string"};
    std::vector<std::string> expected_vector{"this", "is", "the", "test", "string"};

    REQUIRE(split(test_string, ' ') == expected_vector);

    test_string = "this:is:the:test:string";
    REQUIRE(split(test_string, ':') == expected_vector);
}

TEST_CASE("File Parsing Test") {
    passport first_expected_passport{
        {"byr", "1983"}, {"iyr", "2017"}, {"pid", "796082981"}, {"cid", "129"},
        {"eyr", "2030"}, {"ecl", "oth"}, {"hgt", "182cm"}
    };
    passport last_expected_passport{
        {"cid", "331"}, {"ecl", "blu"}, {"eyr", "2021"}, {"hcl", "#733820"}, {"hgt", "174cm"},
        {"iyr", "2010"}, {"byr", "1950"}, {"pid", "405416908"}
    };

    std::vector<passport> passports{read_passport_file(filename)};

    REQUIRE(passports.front() == first_expected_passport);
    REQUIRE(passports.back() == last_expected_passport);
    REQUIRE(passports.size() == 296);
}

TEST_CASE("PART 1") {
    std::vector<passport> passports{read_passport_file(filename)};
    REQUIRE(count_valid_passports(passports, passport_has_required_fields) == 239);
}
