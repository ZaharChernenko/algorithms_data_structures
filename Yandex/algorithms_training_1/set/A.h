#include <iostream>
#include <unordered_set>


std::size_t solveA() {
    std::unordered_set<int> uniq;

    int temp;
    while (std::cin >> temp) uniq.insert(temp);
    return uniq.size();
}