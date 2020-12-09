#pragma once

#include <vector>
#include <string>
#include <functional>
#include <map>

namespace passport_processing {
    using passport = std::map<std::string, std::string>;
    using required_fields_predicate = std::function<bool(const passport&)>;
    using valid_field_predicate = std::function<bool(const std::string&)>;
    using keyed_validation_predicates = std::map<std::string, valid_field_predicate>;

    std::vector<std::string> split(const std::string& str, const char& delimiter);
    std::vector<passport> read_passport_file(const std::string& filename);

    bool passport_has_required_fields(const passport& p);
    keyed_validation_predicates validators();

    int count_valid_passports(const std::vector<passport>& passports,
                              const required_fields_predicate& required_fields_predicate,
                              const keyed_validation_predicates& validations = {});
}
