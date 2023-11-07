#pragma once
// Является ли последовательность возрастающей
#include <iostream>
#include <string>
#include <vector>
#include <sstream>


std::vector<int> inputVecA() {
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


std::vector<int> inputVecA1() {
	int temp;
	std::vector<int> vec;

	while (std::cin >> temp) {
		vec.push_back(temp);
	}
	return vec;
}


std::string isIncreasing(const std::vector<int>& vec) {
	for (int i = 1; i != vec.size(); ++i) {
		if (vec[i - 1] >= vec[i]) return "NO";
	}
	return "YES";
}
