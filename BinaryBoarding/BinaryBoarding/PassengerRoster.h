#pragma once

#include "BoardingPass.h"
#include <vector>

class PassengerRoster {
    std::vector<BoardingPass> boarding_passes;

public:
    explicit PassengerRoster(const std::vector<std::string>& codes);
    explicit PassengerRoster(std::vector<BoardingPass> passes): boarding_passes{std::move(passes)} {};
    [[nodiscard]] BoardingPass max_boarding_pass() const;
    [[nodiscard]] BoardingPass first_empty_seat() const;
};
