#include "TobogganTrajectory.h"
#include <fstream>
#include <iostream>
#include <numeric>


namespace toboggan_trajectory {
    std::vector<std::string> read_toboggan_trajectory_file(const std::string& filename) {
        std::ifstream input_file{filename};

        if (!input_file) {
            std::cerr << "Cannot open the File : " << filename << "\n";
        }

        std::vector<std::string> tree_map{std::istream_iterator<std::string>{input_file}, {}};

        return tree_map;
    }

    int count_tree_encounters(const std::vector<std::string>& tree_map, const trajectory& delta) {
        const auto wrap{tree_map[0].size()};
        auto count{0};

        for (size_t y{0}, x{0}; y < tree_map.size(); y += delta.y, x += delta.x) {
            count += static_cast<int>(tree_map[y].at(x % wrap) == '#');
        }

        return count;
    }

    long long product_of_tree_encounters(const std::vector<std::string>& tree_map, const std::vector<trajectory>& trajectories) {
        return std::reduce(trajectories.cbegin(), trajectories.cend(), 1LL,
                               [tree_map](const long long& total, const trajectory& delta) {
                                   return total * count_tree_encounters(tree_map, delta);
                               });
    }

} // namespace toboggan_trajectory
