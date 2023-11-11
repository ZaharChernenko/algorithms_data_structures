#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>


int solutionD() {
    std::ifstream fin;
    fin.open("input.txt");

    std::unordered_set<std::string> uniq;
    std::string word;

    while (fin >> word) {
        uniq.insert(word);
    }

    std::cout << uniq.size();
    return 0;
}