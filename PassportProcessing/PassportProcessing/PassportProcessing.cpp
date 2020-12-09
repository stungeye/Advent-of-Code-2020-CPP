#include "PassportProcessing.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <regex>

namespace passport_processing {
    std::vector<std::string> split(const std::string& str, const char& delimiter) {
        std::istringstream iss(str);
        std::vector<std::string> splits;
        std::string s;

        while (std::getline(iss, s, delimiter)) {
            splits.emplace_back(s);
        }

        return splits;
    }

    std::vector<passport> read_passport_file(const std::string& filename) {
        std::ifstream input_file{filename};

        if (!input_file) {
            std::cerr << "Cannot open the File : " << filename << "\n";
        }

        std::vector<passport> passports;
        passport current_passport;
        std::string line;

        while (getline(input_file, line)) {
            if (line.empty()) {
                passports.emplace_back(current_passport);
                current_passport.clear();
            }

            for (const auto& record : split(line, ' ')) {
                const auto split_record = split(record, ':');
                current_passport[split_record.front()] = split_record.back();
            }
        }

        // File doesn't end in a blank line, so we have one more passport to emplace. 
        passports.emplace_back(current_passport);

        return passports;
    }


    bool passport_has_required_fields(const passport& p) {
        const std::vector<std::string> required_fields = {"hcl", "iyr", "eyr", "ecl", "pid", "byr", "hgt"};
        return std::all_of(required_fields.cbegin(), required_fields.cend(), [&p](const auto& field) {
            return p.find(field) != p.end();
        });
    }

    keyed_validation_predicates validators() {
        return keyed_validation_predicates{
            {
                "byr", [](const auto& value) -> bool {
                    const auto birth_year = std::stoi(value);
                    return birth_year >= 1920 && birth_year <= 2002;
                }
            },
            {
                "iyr", [](const auto& value) -> bool {
                    const auto issue_year = std::stoi(value);
                    return issue_year >= 2010 && issue_year <= 2020;
                }
            },
            {
                "eyr", [](const auto& value) {
                    const auto expiration_year = std::stoi(value);
                    return expiration_year >= 2020 && expiration_year <= 2030;
                }
            },
            {
                "hgt", [](const auto& value) {
                    const auto height = std::stoi(value);
                    const auto height_unit = value.substr(value.length() - 2);
                    return (height_unit == "cm" && height >= 150 && height <= 193)
                        || (height_unit == "in" && height >= 59 && height <= 76);
                }
            },
            {
                "hcl", [](const auto& value) {
                    return std::regex_match(value, std::regex("#[0-9a-f]{6}"));
                }
            },
            {
                "ecl", [](const auto& value) {
                    return std::regex_match(value, std::regex("amb|blu|brn|gry|grn|hzl|oth"));
                }
            },
            {
                "pid", [](const auto& value) {
                    return std::regex_match(value, std::regex("\\d{9}"));
                }
            }
        };
    }

    int count_valid_passports(const std::vector<passport>& passports,
                              const require_fields_predicate& required_fields_predicate,
                              const keyed_validation_predicates& validations) {
        return std::count_if(passports.cbegin(), passports.cend(), [&](const auto& p) -> bool {
            if (!required_fields_predicate(p)) return false;

            return std::all_of(validations.cbegin(), validations.cend(), [&p](const auto& pair) {
                const auto& [key, validator] = pair;
                return validator(p.at(key));
            });
        });
    }
} // namespace passport_processing
