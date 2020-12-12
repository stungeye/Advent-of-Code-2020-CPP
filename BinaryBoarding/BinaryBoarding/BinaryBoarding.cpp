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

    int find_bsp_position(const std::string& code, const int& max_position, const char& forward) {
        auto lower_bound = 0;
        auto upper_bound = max_position;

        for (auto forward_or_back : code) {
            const auto half = (upper_bound + 1 - lower_bound) / 2;
            if (forward_or_back == forward) {
                upper_bound -= half;
            }
            else {
                lower_bound += half;
            }
        }

        return lower_bound;
    }

    int boarding_id(const std::string& code, const int& max_rows, const int& max_columns) {
        const auto row_code = code.substr(0, 7);
        const auto column_code = code.substr(7);
        return max_columns * find_bsp_position(row_code, max_rows, 'F')
            + find_bsp_position(column_code, max_columns, 'L');
    }

    std::vector<int> all_boarding_ids(const std::vector<std::string>& codes, const int& max_rows,
                                      const int& max_columns) {
        std::vector<int> boarding_ids;
        std::transform(codes.begin(), codes.end(), std::back_inserter(boarding_ids),
                       [max_rows, max_columns](auto code) -> int { return boarding_id(code, max_rows, max_columns); });
        return boarding_ids;
    }

    int max_boarding_id(const std::vector<std::string>& codes, const int& max_rows, const int& max_columns) {
        const auto boarding_ids = all_boarding_ids(codes, max_rows, max_columns);
        return *std::max_element(boarding_ids.begin(), boarding_ids.end());
    }

    int first_empty_seat(const std::vector<std::string>& codes, const int& max_rows, const int& max_columns) {
        auto boarding_ids = all_boarding_ids(codes, max_rows, max_columns);
        std::sort(boarding_ids.begin(), boarding_ids.end(), std::less<>());

        return *std::adjacent_find(boarding_ids.begin(), boarding_ids.end(), [](int a, int b) {
            return a + 1 != b;
        }) + 1;
    }

}
