#include <iostream>
#include <unordered_set>


int solutionG() {
    std::unordered_set<std::string> uniq2;
    std::string firstG, secondG, bi;
    std::cin >> firstG >> secondG;
    for (int i = 0; i != secondG.size() - 1; ++i) uniq2.insert(secondG.substr(i, 2));

    int counter = 0;
    for (int i = 0; i != firstG.size(); ++i) {
        if (uniq2.count(firstG.substr(i, 2))) ++counter;
    }

    std::cout << counter;
    return 0;
}