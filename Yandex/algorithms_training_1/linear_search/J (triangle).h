#pragma once
#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>


int triangle() {
    int n_req;
    std::cin >> n_req;

    double now, prev, left = 30, right = 4000;
    std::string far;

    std::cin >> prev;
    for (int i = 1; i != n_req; ++i) {
        std::cin >> now >> far;
        if (std::abs(now - prev) < std::pow(10, -6)) continue;

        if (far == "closer") {
            if (now < prev) right = std::min(right, (now + prev) / 2);
            else left = std::max(left, (now + prev) / 2);
        }

        else {
            if (now > prev) right = std::min(right, (now + prev) / 2);
            else left = std::max(left, (now + prev) / 2);
        }
        prev = now;
    }
    std::cout << std::setprecision(15) << left << ' ' << right;
    return 0;
}
