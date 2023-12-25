#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <string>


std::vector<int> inputVec1() {
    std::string buf;
    getline(std::cin, buf);
    std::stringstream ss;
    ss << buf;

    int temp;
    std::vector<int> vec;

    while (ss >> temp) {
        vec.push_back(temp);
    }
    return vec;
}


void intersection() {
    std::vector<int>  vec1 {inputVec1()}, vec2 {inputVec1()}, res;
    std::sort(vec1.begin(), vec1.end());
    std::sort(vec2.begin(), vec2.end());
    // Последовательность должна быть отсортированной
    std::set_intersection(vec1.begin(), vec1.end(),
                          vec2.begin(), vec2.end(), std::back_inserter(res));

    for (const auto& elem: res) std::cout << elem << ' ';
}