#pragma once
#include <algorithm>
#include <string>
#include <unordered_map>

int convert2Decimal(const std::string& num, short cur_base) {
    std::unordered_map<char, short> hex2decimal {{'0', 0},  {'1', 1},  {'2', 2},  {'3', 3}, {'4', 4},  {'5', 5},
                                                 {'6', 6},  {'7', 7},  {'8', 8},  {'9', 9}, {'A', 10}, {'B', 11},
                                                 {'C', 12}, {'D', 13}, {'E', 14}, {'F', 15}};
    int result {};
    for (char digit : num) {
        result *= cur_base;
        result += hex2decimal[digit];
    }
    return result;
}

std::string changeBase(const std::string& num, short cur_base, short wanted_base) {
    std::unordered_map<short, char> decimal2hex {{0, '0'},  {1, '1'},  {2, '2'},  {3, '3'}, {4, '4'},  {5, '5'},
                                                 {6, '6'},  {7, '7'},  {8, '8'},  {9, '9'}, {10, 'A'}, {11, 'B'},
                                                 {12, 'C'}, {13, 'D'}, {14, 'E'}, {15, 'F'}};
    int num_decimal {};
    if (cur_base == 10)
        num_decimal = std::stoi(num);
    else
        num_decimal = convert2Decimal(num, cur_base);

    std::string result {};
    for (; num_decimal != 0; num_decimal /= wanted_base)
        result += decimal2hex[num_decimal % wanted_base];
    std::reverse(result.begin(), result.end());

    return result;
}