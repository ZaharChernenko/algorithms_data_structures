#pragma once
#include <vector>
#include <iostream>
// каких элементов не хватает до симметричной последовательности


std::vector<short> inputVecC(const int& size) {
	std::vector<short> vec(size);
	for (auto& elem : vec) {
		std::cin >> elem;
	}
	return vec;
}



std::vector<short> simmetricSquare(const std::vector<short>& vec) {
	int i = 0, end;
	for (int start = 0; start != vec.size(); ++start) {
		i = start;
		end = vec.size() - 1;
		while (i <= end && vec[i] == vec[end]) {
			++i; --end;
		}
		if (i <= end) {
			std::vector<short> res;
			for (int j = start - 1; j != -1; --j) {
				res.push_back(vec[j]);
			}
			return res;
		}
	}
}

std::vector<short> simmetricLinear(const std::vector<short>& vec) {
	int start = 0, end = vec.size() - 1;
	while (start != vec.size()) {
		if (vec[start] == vec[end]) {
			++start; --end;
		}
		else if (end == vec.size() - 1) ++start;
		else end = vec.size() - 1;
	}
	std::vector<short> res(end + 1);
	for (int i = end, j = 0; i != -1; --i, ++j) res[j] = vec[i];
    return res;
}
