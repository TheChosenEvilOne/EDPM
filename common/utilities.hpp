#pragma once

#include <regex>
#include <string>
#include <vector>

namespace EDPM {
    class Utils {
        public:
            static std::vector<std::string> Tokenise(const std::string &string, const std::string &regex) {
                std::regex re(regex);

                return std::vector<std::string> (
                    std::sregex_token_iterator{string.cbegin(), string.cend(), re, -1},
                    std::sregex_token_iterator{}
                );
            }
    };
}