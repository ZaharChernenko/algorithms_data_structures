#pragma once
#include <vector>
#include <string>
#include <unordered_set>

using std::cin, std::cout;

void genBin(const int& len, std::vector<std::string>& vec, std::string prefix="") {
    if (len == 0) {
        vec.push_back(prefix);
        return;
    }
    for (const auto& d: {'0', '1'}) {
        genBin(len - 1, vec, prefix + d);
    }
}


void genN(const int& len, int base, std::vector<std::string>& vec, const std::string& prefix="") {
    if (len == 0) {
        vec.push_back(prefix);
        return;
    }
    for (int i = 0; i < base; ++i) {
        genN(len - 1, base, vec, prefix + std::to_string(i));
    }
}

template <typename T, typename D>
void genPermutations(const int& len, std::unordered_set<D>& col, std::vector<T>& vec, std::string prefix="") {
    if (len == 0) {
        vec.push_back(prefix);
        return;
    }
    for (const auto& el: col) {
        if (prefix.find(el) != std::string::npos) {
            continue;
        }
        genPermutations(len - 1, col, vec, prefix + el);
    }
}


void testP() {
    std::vector<std::string> vec;
    std::unordered_set<char> col{'a', 'b', 'c'};
    genPermutations(3, col, vec);
    for (const auto& el: vec) {
        cout << el << '\n';
    }
}
