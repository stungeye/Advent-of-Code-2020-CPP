#pragma once

#include <vector>
#include <string>

namespace toboggan_trajectory {
    struct trajectory {
        size_t x;
        size_t y;
    };

    std::vector<std::string> read_toboggan_trajectory_file(const std::string& filename);

    int count_tree_encounters(const std::vector<std::string>& tree_map, const trajectory& delta);

    long long product_of_tree_encounters(const std::vector<std::string>& tree_map, const std::vector<trajectory>& trajectories);
}
