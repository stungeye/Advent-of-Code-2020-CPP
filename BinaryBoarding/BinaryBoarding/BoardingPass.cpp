#include "BoardingPass.h"
#include <algorithm>

bool operator==(const BoardingPass& bp1, const BoardingPass& bp2) {
    return bp1.boarding_id == bp2.boarding_id;
}

bool operator!=(const BoardingPass& bp1, const BoardingPass& bp2) {
    return !(bp1 == bp2);
}

bool operator<(const BoardingPass& bp1, const BoardingPass& bp2) {
    return bp1.boarding_id < bp2.boarding_id;
}

BoardingPass operator+(const BoardingPass& bp, const int& id) {
    return BoardingPass(bp.boarding_id + id);
}

int BoardingPass::boarding_code_to_id(const std::string& code) const {
    std::string binary_string(code.length(), '0');
    std::transform(code.cbegin(), code.cend(), binary_string.begin(),
                   [](auto c) -> char { return (c == 'B' || c == 'R') ? '1' : '0'; });

    return std::stoi(binary_string, nullptr, 2);
}
