#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <vector>

int noop(std::vector<int>& reg, int pass_on);
int addx(std::vector<int>& reg, int op, int pass_on);

void day_10_executor(const std::string& filename);
