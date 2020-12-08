#include "PassportProcessing.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>


namespace passport_processing {

    std::vector<std::string> split(const std::string& str, const char& delim) {
        std::istringstream iss(str);
        std::vector<std::string> splits;
        std::string s;

        while (std::getline(iss, s, delim)) {
            splits.emplace_back(s);
        }

        return splits;
    }

    bool passport_has_required_fields(const passport& p) {
        const std::vector<std::string> required_fields = {"hcl", "iyr", "eyr", "ecl", "pid", "byr", "hgt"};
        return std::all_of(required_fields.cbegin(), required_fields.cend(), [&p](const std::string& field) {
            return p.find(field) != p.end();
        });
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

        passports.emplace_back(current_passport);

        return passports;
    }

    int count_valid_passports(const std::vector<passport>& passports, const valid_password_predicate& predicate) {
        return std::count_if(passports.cbegin(), passports.cend(), predicate);
    }

} // namespace passport_processing
