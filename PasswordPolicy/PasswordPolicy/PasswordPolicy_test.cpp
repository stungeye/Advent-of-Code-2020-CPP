#include "PasswordPolicy.h"
#include "test/catch.hpp"
#include <unordered_set>

using namespace password_policy;
const std::string filename = "PasswordPolicy.txt";

TEST_CASE("File Input Test") {
    REQUIRE(read_password_policy_file(filename).size() == 1000);
}

TEST_CASE("Part 1 - Password Policy") {
    std::vector<password_policy_entry> password_policy_entries = read_password_policy_file(filename);
    REQUIRE(count_valid_passwords(password_policy_entries, password_policy_one) == 445);
}

TEST_CASE("Part 2 - Password Policy") {
    std::vector<password_policy_entry> password_policy_entries = read_password_policy_file(filename);
    REQUIRE(count_valid_passwords(password_policy_entries, password_policy_two) == 491);
}

/* Missing tests for the individual policy predicates. */
