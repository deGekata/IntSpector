#include "Utilities.hpp"

std::string num_to_hex(uint64_t num) {
    std::stringstream ss;
    ss << std::hex << num;
    return ss.str();
}