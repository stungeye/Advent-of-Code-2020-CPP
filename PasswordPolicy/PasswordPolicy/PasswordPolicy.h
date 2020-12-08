// SampleCMakeProject.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <string>
#include <functional>

namespace password_policy {
    struct password_entry {
        std::string password;
        char character;
        int low, high;
    };

    std::vector<password_entry> read_password_policy_file(const std::string& filename);
    
    using password_policy_predicate = std::function<bool(const password_entry&)>;
    bool password_policy_one(const password_entry& pe);
    bool password_policy_two(const password_entry& pe);

    int count_valid_passwords(const std::vector<password_entry>& entries, const password_policy_predicate& predicate);
}
