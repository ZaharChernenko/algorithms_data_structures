#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>

int convert2Decimal(const std::string& s, int base) {
    if (base == 10) return std::stoi(s);

    int res {};
    for (int i = s.size() - 1; i != -1; --i) {
        res *= base;
        res += s[i] - '0';
    }
    return res;
}


std::string changeBase(const std::string& num, int wanted_base = 2, int cur_base = 10) {
    if (wanted_base > 16 || cur_base > 16) throw "Invalid input";

    int num_10 {};
    if (cur_base != 10) num_10 = convert2Decimal(num, cur_base);
    else num_10 = std::stoi(num);

    std::string res{};
    std::unordered_map<int, char> decode_from10 {{0, '0'}, {1, '1'}, {2, '2'}, {3, '3'}, {4, '4'}, {5, '5'},
        {6, '6'}, {7, '7'}, {8, '8'}, {9, '9'}, {10, 'A'}, {11, 'B'}, {12, 'C'}, {13, 'D'}, {14, 'E'}, {15, 'F'}};

    while (num_10 > 0) {
        res += decode_from10[num_10 % wanted_base];
        num_10 /= wanted_base;
    }
    std::reverse(res.begin(), res.end());
    return res;
}


int main() {
    std::cout << changeBase("15", 16, 10);
    return 0;
}

