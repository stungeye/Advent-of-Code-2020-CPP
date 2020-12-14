#pragma once

#include <string>

class BoardingPass {
    int boarding_id;

public:
    explicit BoardingPass(const std::string& code) : boarding_id{boarding_code_to_id(code)} {};
    explicit BoardingPass(const int& id) : boarding_id{id} {};

    friend bool operator==(const BoardingPass& bp1, const BoardingPass& bp2);
    friend bool operator!=(const BoardingPass& bp1, const BoardingPass& bp2);
    friend bool operator<(const BoardingPass& bp1, const BoardingPass& bp2);
    friend BoardingPass operator+(const BoardingPass& bp, const int& id);

private:
    [[nodiscard]] int boarding_code_to_id(const std::string& code) const;
};
