#pragma once
// определяет какого типа будет последовательность
#include <iostream>
#include <string>
#include <vector>
#include <cmath>


std::vector<int> inputVecB() {
	int temp;
	std::vector<int> vec;
	while (std::cin >> temp && temp != -2 * std::pow(10, 9)) {
		vec.push_back(temp);
	}
	return vec;
}


std::string defineType(const std::vector<int>& vec) {
	bool is_constant = true, is_ascending = true, is_weakly_ascending = true, is_descending = true,
		is_weakly_descending = true;
	for (int i = 1; i != vec.size(); ++i) {
		if (vec[i - 1] < vec[i]) {
			is_constant = false;
			is_descending = false;
			is_weakly_descending = false;
		}
		else if (vec[i - 1] == vec[i]) {
			is_ascending = false;
			is_descending = false;
		}
		else {
			is_constant = false;
			is_ascending = false;
			is_weakly_ascending = false;
		}
	}

	if (is_constant) return "CONSTANT";
	if (is_ascending) return "ASCENDING";
	if (is_weakly_ascending) return "WEAKLY ASCENDING";
	if (is_descending) return "DESCENDING";
	if (is_weakly_descending) return "WEAKLY DESCENDING";
	return "RANDOM";
}
