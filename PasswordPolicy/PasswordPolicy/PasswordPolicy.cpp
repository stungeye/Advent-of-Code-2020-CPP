#include "PasswordPolicy.h"
#include <algorithm>
#include <fstream>
#include <iostream>


namespace password_policy {
    std::istream& operator>>(std::istream& is, password_entry& ppe) {
        char t;
        is >> ppe.low >> t >> ppe.high >> ppe.character >> t >> ppe.password;
        return is;
    }

    std::vector<password_entry> read_password_policy_file(const std::string& filename) {
        std::ifstream input_file{filename};

        if (!input_file) {
            std::cerr << "Cannot open the File : " << filename << "\n";
        }

        std::vector<password_entry> password_policies{
            std::istream_iterator<password_entry>{input_file}, {}
        };

        return password_policies;
    }

    bool password_policy_one(const password_entry& pe) {
        const auto letter_count = std::count(pe.password.begin(), pe.password.end(), pe.character);
        return letter_count >= pe.low && letter_count <= pe.high;
    }

    bool password_policy_two(const password_entry& pe) {
        const auto low_c = pe.password.at(pe.low - 1);
        const auto high_c = pe.password.at(pe.high - 1);
        return (low_c == pe.character) != (high_c == pe.character); // != performs an XOR
    }

    int count_valid_passwords(const std::vector<password_entry>& entries, const password_policy_predicate& predicate) {
        return std::count_if(entries.cbegin(), entries.cend(), predicate);
    }
} // namespace PasswordPolicy
