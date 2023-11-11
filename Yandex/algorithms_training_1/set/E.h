#pragma once
#include <iostream>
#include <algorithm>
#include <set>


int solutionE() {
    std::set<short> btns;
    short temp;
    for (char i = 0; i != 3; ++i) {
        std::cin >> temp;
        btns.insert(temp);
    }

    int number;
    std::cin >> number;

    std::set<short> digits;
    while (number > 0) {
        digits.insert(number % 10);
        number /= 10;
    }

    std::set<short> res;
    std::set_difference(digits.begin(), digits.end(), btns.begin(), btns.end(),
                        std::inserter(res, res.begin()));
    std::cout << res.size();

}