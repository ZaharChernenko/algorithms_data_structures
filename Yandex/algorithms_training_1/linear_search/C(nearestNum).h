#pragma once
// находит ближайшее число до num
#include <iostream>
#include <vector>
#include <cmath>

std::vector<short> inputVecC(const int& size) {
	std::vector<short> vec(size);
	for (auto& elem : vec) {
		std::cin >> elem;
	}
	return vec;
}


short nearestNum(const std::vector<short>& vec, short num) {
	short diff = std::abs(vec[0] - num);
	short nearest_num = vec[0], temp_diff;
	for (short i = 1; i != vec.size(); ++i) {
		temp_diff = std::abs(vec[i] - num);
		if (temp_diff < diff) {
			diff = temp_diff;
			nearest_num = vec[i];
			if (diff == 0) break;
		}
	}
	return nearest_num;
}
