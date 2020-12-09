#pragma once

#include <vector>
#include <string>
#include <functional>
#include <map>

namespace passport_processing {
    using passport = std::map<std::string, std::string>;
    using valid_password_predicate = std::function<bool(const passport&)>;
    bool passport_has_required_fields(const passport& p);
    bool passport_has_valid_data(const passport& p);

    std::vector<passport> read_passport_file(const std::string& filename);
    std::vector<std::string> split(const std::string& str, const char& delim);
    int count_valid_passports(const std::vector<passport>& passports, const valid_password_predicate& predicate);
}
