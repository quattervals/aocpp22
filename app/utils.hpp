#pragma once

#include <stdint.h>
#include <stdbool.h>

std::vector<std::string> split_to_vec(const std::string& in, const char delim);
std::vector<std::string> collect_numbers_to_vec(const std::string& in, const char delim);
