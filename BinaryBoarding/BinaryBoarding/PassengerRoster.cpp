#include "PassengerRoster.h"
#include <algorithm>
#include <iterator>

PassengerRoster::PassengerRoster(const std::vector<std::string>& codes) {
    std::transform(codes.cbegin(), codes.cend(), std::back_inserter(boarding_passes),
                   [](auto code) -> BoardingPass { return BoardingPass(code); });

    std::sort(boarding_passes.begin(), boarding_passes.end(), std::less<>());
}

BoardingPass PassengerRoster::max_boarding_pass() const {
    return *std::max_element(boarding_passes.cbegin(), boarding_passes.cend());
}

BoardingPass PassengerRoster::first_empty_seat() const {
    // Error if nothing is found because we'll still try to dereference boarding_passes.end().
    return *std::adjacent_find(boarding_passes.cbegin(), boarding_passes.cend(),
                               [](const BoardingPass& bp1, const BoardingPass& bp2) -> bool {
                                   return bp1 + 1 != bp2;
                               }) + 1;
}
