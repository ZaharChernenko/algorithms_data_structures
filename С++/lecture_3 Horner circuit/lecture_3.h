#pragma once
std::string convertToAnotherBase(const std::string& num, const int& wanted_base, const int& cur_base=10){
    int sum = 0;
    if (cur_base != 10) {
        for (const auto& n: num) {
            sum *= cur_base;
            sum += n - '0';
        }
    }
    else sum = std::stoi(num);

    std::string result;
    while (sum > 0) {
        result += std::to_string(sum % wanted_base);
        sum /= wanted_base;
    }
    // reverse string, rbegin returns reversed
    // iterator
    return {result.rbegin(), result.rend()};
}