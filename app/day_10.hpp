#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <string>
#include <vector>

int noop(std::vector<int>& reg, int pass_on);

int addx(std::vector<int>& reg, int op, int pass_on);

bool drawSolid(int idx, int val);

void print_screen(std::vector<char> const& input, int line_len = 40);

void day_10_executor(const std::string& filename);
