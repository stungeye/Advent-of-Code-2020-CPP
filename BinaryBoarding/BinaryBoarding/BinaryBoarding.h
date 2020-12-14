#pragma once

#include <vector>
#include <string>
#include <functional>
#include <map>

namespace binary_boarding {
    std::vector<std::string> read_boarding_file(const std::string& filename);
    int boarding_id(const std::string& code);
    std::vector<int> all_boarding_ids(const std::vector<std::string>& codes);
    int max_boarding_id(const std::vector<std::string>& codes);
    int first_empty_seat(const std::vector<std::string>& codes);
}
