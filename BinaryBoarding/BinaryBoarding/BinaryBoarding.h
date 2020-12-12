#pragma once

#include <vector>
#include <string>
#include <functional>
#include <map>

namespace binary_boarding {
    const auto max_rows = 127;
    const auto max_columns = 8;
    std::vector<std::string> read_boarding_file(const std::string& filename);
    int find_bsp_position(const std::string& code, const int& max_position, const char& forward);
    int boarding_id(const std::string& code, const int& max_rows, const int& max_columns);
    std::vector<int> all_boarding_ids(const std::vector<std::string>& codes, const int& max_rows, const int& max_columns);
    int max_boarding_id(const std::vector<std::string>& codes, const int& max_rows, const int& max_columns);
    int first_empty_seat(const std::vector<std::string>& codes, const int& max_rows, const int& max_columns);

}
