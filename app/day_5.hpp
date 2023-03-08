#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <vector>
#include <string>

void day_5_executor(const std::string& filename);
void crane(uint32_t quantity, uint32_t from, uint32_t to, std::vector<std::vector<char>>& dock);
void crane_9001(uint32_t quantity, uint32_t from, uint32_t to, std::vector<std::vector<char>>& dock);
