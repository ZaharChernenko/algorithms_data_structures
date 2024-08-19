#pragma once
#include <algorithm>
#include <string>
#include <unordered_map>

int convert2Decimal(const std::string& num, short cur_base);
std::string changeBase(const std::string& num, short cur_base, short wanted_base);