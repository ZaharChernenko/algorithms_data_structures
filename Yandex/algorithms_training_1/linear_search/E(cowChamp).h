#pragma once
#include <vector>

int countPlace(const std::vector<short>& vec) {
	short m = vec[0], vas = -1;
	for (int i = 1; i != vec.size() - 1; ++i) {
		if (m < vec[i]) {
			m = vec[i];
			vas = -1;
			continue;
		}

		if (vec[i] % 10 == 5 && vec[i] > vec[i + 1]) vas = std::max(vas, vec[i]);
	}

	int place = 1;
	for (const auto& elem : vec) {
		if (vas < elem) ++place;
	}
	if (vas == -1) return 0;
	return place;
}
