#include "PassportProcessing.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <regex>

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

    bool passport_has_valid_data(const passport& p) {

        if (!passport_has_required_fields(p)) return false;

       // const std::vector<std::pair<std::string, std::function<bool(const std::string&)>>> validators{
        const auto birth_year = std::stoi(p.at("byr"));
        const auto v_birth_year = birth_year >= 1920 && birth_year <= 2002;

        const auto issue_year = std::stoi(p.at("iyr"));
        const auto v_issue_year = issue_year >= 2010 && issue_year <= 2020;

        const auto expiration_year = std::stoi(p.at("eyr"));
        const auto v_expiration_year = expiration_year >= 2020 && expiration_year <= 2030;

        const auto& sheight = p.at("hgt");
        const auto height = std::stoi(sheight);
        const auto height_unit = sheight.substr(sheight.length() - 2);
        const auto v_height = (height_unit == "cm" && height >= 150 && height <= 193)
            || (height_unit == "in" && height >= 59 && height <= 76);

        const auto v_hair_color = std::regex_match(p.at("hcl"), std::regex("#[0-9a-f]{6}"));

        const auto v_eye_color = std::regex_match(p.at("ecl"), std::regex("amb|blu|brn|gry|grn|hzl|oth"));

        const auto v_passport_id = std::regex_match(p.at("pid"), std::regex("\\d{9}"));

        return v_birth_year && v_issue_year && v_expiration_year && v_height && v_hair_color && v_eye_color && v_passport_id;
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

    int count_valid_passports(const std::vector<passport>& passports, const valid_password_predicate& predicate) {
        return std::count_if(passports.cbegin(), passports.cend(), predicate);
    }

} // namespace passport_processing
