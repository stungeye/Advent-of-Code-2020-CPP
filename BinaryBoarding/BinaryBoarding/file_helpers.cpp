#include "file_helpers.h"
#include <fstream>

namespace file_helpers {
    std::vector<std::string> read_boarding_file(const std::string& filename) {
        std::ifstream input_file{filename};

        return std::vector<std::string>{
            std::istream_iterator<std::string>{input_file}, {}
        };
    }
}

