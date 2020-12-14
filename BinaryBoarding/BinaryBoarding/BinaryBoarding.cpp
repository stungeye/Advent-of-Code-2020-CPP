#include "BinaryBoarding.h"
#include <fstream>
#include <iostream>
#include <algorithm>

namespace binary_boarding {
    std::vector<std::string> read_boarding_file(const std::string& filename) {
        std::ifstream input_file{filename};

        return std::vector<std::string>{
            std::istream_iterator<std::string>{input_file}, {}
        };
    }

    int boarding_id(const std::string& code) {
        std::string binary_string(code.length(), '0'); 
        std::transform(code.cbegin(), code.cend(), binary_string.begin(),
            [](auto c) { return (c == 'B' || c == 'R') ? '1' : '0'; });

        return std::stoi(binary_string, nullptr, 2);
    }

    std::vector<int> all_boarding_ids(const std::vector<std::string>& codes) {
        std::vector<int> boarding_ids;
        std::transform(codes.begin(), codes.end(), std::back_inserter(boarding_ids),
                       [](auto code) -> int { return boarding_id(code); });

        return boarding_ids;
    }

    int max_boarding_id(const std::vector<std::string>& codes) {
        const auto boarding_ids = all_boarding_ids(codes);
        return *std::max_element(boarding_ids.begin(), boarding_ids.end());
    }

    int first_empty_seat(const std::vector<std::string>& codes) {
        auto boarding_ids = all_boarding_ids(codes);
        std::sort(boarding_ids.begin(), boarding_ids.end(), std::less<>());

        // Error if nothing is found because we'll still try to dereference boarding_ids.end().
        return *std::adjacent_find(boarding_ids.begin(), boarding_ids.end(), [](int a, int b) {
            return a + 1 != b;
        }) + 1;
    }
}
