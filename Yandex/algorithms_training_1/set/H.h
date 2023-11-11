#pragma once
#include <iostream>
#include <unordered_set>

int solutionH() {
    std::unordered_set<int> uniq_x;
    int n, x, y;;
    std::cin >> n;

    for (int i = 0; i != n; ++i) {
        std::cin >> x >> y;
        uniq_x.insert(x);
    }
    std::cout << uniq_x.size();
    return 0;
}