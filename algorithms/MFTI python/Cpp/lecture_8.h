#include <iostream>
#include <string>
#include <vector>


void _genBin(std::string& prefix, int step, std::vector<std::string>& prefix_arr) {
    if (step == prefix.size()) {
        prefix_arr.push_back(prefix);
        return;
    }

    for (const char& digit: {'0', '1'}) { // "01" - C-string, last char \0
        prefix[step] = digit;
        _genBin(prefix, step + 1, prefix_arr);
    }
}


std::vector<std::string> genBin(int length) {
    std::string prefix(length, '0');
    std::vector<std::string> prefix_arr;
    _genBin(prefix, 0, prefix_arr);
    return prefix_arr;
}


void _genNumbers(std::string& prefix, int step, std::vector<std::string>& prefix_arr, int base) {
    if (step == prefix.size()) {
        prefix_arr.push_back(prefix);
        return;
    }

    for (int i = 0; i != base; ++i) {
        prefix[step] = '0' + i;
        _genNumbers(prefix, step + 1, prefix_arr, base);
    }
}


std::vector<std::string> genNumbers(int length, int base) {
    std::string prefix(length, '0');
    std::vector<std::string> prefix_arr;
    _genNumbers(prefix, 0, prefix_arr, base);
    return prefix_arr;
}


void _genDec(std::vector<int>& prefix, int step, std::vector<std::vector<int>>& prefix_arr,
        const std::vector<std::vector<int>>& arr2d) {
    if (step == prefix.size()) {
        prefix_arr.push_back(prefix);
        return;
    }

    for (const int& num: arr2d[step]) {
        prefix[step] = num;
        _genDec(prefix, step + 1, prefix_arr, arr2d);
    }
}


std::vector<std::vector<int>> genDec(const std::vector<std::vector<int>>& arr2d) {
    std::vector<int> prefix(arr2d.size(), 0);
    std::vector<std::vector<int>> prefix_arr;
    _genDec(prefix, 0, prefix_arr, arr2d);
    return prefix_arr;
}

