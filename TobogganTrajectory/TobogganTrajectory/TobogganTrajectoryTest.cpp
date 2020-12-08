#include "TobogganTrajectory.h"
#include "test/catch.hpp"
#include <unordered_set>

using namespace toboggan_trajectory;

const std::string filename = "TobogganTrajectory.txt";
const auto map = read_toboggan_trajectory_file(filename);
const std::vector<trajectory> trajectories = {{1, 1}, {3, 1}, {5, 1}, {7, 1}, {1, 2}};
const std::vector<std::string> mini_map{
    "..##.......",
    "#...#...#..",
    ".#....#..#.",
    "..#.#...#.#",
    ".#...##..#.",
    "..#.##.....",
    ".#.#.#....#",
    ".#........#",
    "#.##...#...",
    "#...##....#",
    ".#..#...#.#"
};

TEST_CASE("File Input Test") {
    REQUIRE(read_toboggan_trajectory_file(filename).size() == 323);
}

TEST_CASE("Part 1 - Mini Map") {
    const trajectory delta{ 3, 1 };
    REQUIRE(count_tree_encounters(mini_map, delta) == 7);
}

TEST_CASE("PART 1 - Full Map") {
    const trajectory delta{ 3, 1 };
    REQUIRE(count_tree_encounters(map, delta) == 205);
}

TEST_CASE("PART 2 - Mini Map") {
    REQUIRE(product_of_tree_encounters(mini_map, trajectories) == 336);
}

TEST_CASE("PART 2 - Full Map") {
    REQUIRE(product_of_tree_encounters(map, trajectories) == 3952146825);
}
