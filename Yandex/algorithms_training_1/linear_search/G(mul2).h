#pragma once
#include <iostream>
#include <vector>


std::vector<long long> findMaxMult(const std::vector<int>& vec) {
	long long first_max = std::max(vec[0], vec[1]), second_max = std::min(vec[0], vec[1]);
	long long first_min = second_max, second_min = first_max;
	for (int i = 2; i != vec.size(); ++i) {
		if (vec[i] > second_max) {
			if (vec[i] > first_max) {
				second_max = first_max;
				first_max = vec[i];
			}
			else second_max = vec[i];
		}

		if (vec[i] < second_min) {
			if (vec[i] < first_min) {
				second_min = first_min;
				first_min = vec[i];
			}
			else second_min = vec[i];
		}
	}

	if (first_max * second_max > first_min * second_min) return std::vector<long long> {second_max, first_max};
	return std::vector<long long> {first_min, second_min};
}
