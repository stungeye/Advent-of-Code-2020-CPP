#include "PasswordPolicy.h"
#include <algorithm>
#include <fstream>
#include <iostream>


namespace password_policy {
    std::istream& operator>>(std::istream& is, password_policy_entry& ppe) {
        char t;
        is >> ppe.low >> t >> ppe.high >> ppe.character >> t >> ppe.password;
        return is;
    }

    std::vector<password_policy_entry> read_password_policy_file(const std::string& filename) {
        std::ifstream input_file{filename};

        if (!input_file) {
            std::cerr << "Cannot open the File : " << filename << "\n";
        }

        std::vector<password_policy_entry> password_policies{
            std::istream_iterator<password_policy_entry>{input_file}, {}
        };

        return password_policies;
    }

    bool password_policy_one(const password_policy_entry& ppe) {
        const auto letter_count = std::count(ppe.password.begin(), ppe.password.end(), ppe.character);
        return letter_count >= ppe.low && letter_count <= ppe.high;
    }

    bool password_policy_two(const password_policy_entry& ppe) {
        const auto low_c = ppe.password.at(ppe.low - 1);
        const auto high_c = ppe.password.at(ppe.high - 1);
        return (low_c == ppe.character) != (high_c == ppe.character); // != performs an XOR
    }

    int count_valid_passwords(const std::vector<password_policy_entry>& entries, const password_policy_predicate& predicate) {
        return std::count_if(entries.cbegin(), entries.cend(), predicate);
    }
} // namespace PasswordPolicy
