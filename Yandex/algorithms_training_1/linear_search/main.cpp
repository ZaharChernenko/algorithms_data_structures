#include <queue>
#include <vector>
#include <iostream>


auto compare = [](int a, int b) {return a > b; };

std::vector<int> maxMul3(const std::vector<int>& vec) {
	std::priority_queue<int, std::vector<int>, decltype(compare)> heap3(compare);
	std::priority_queue<int> heap2;

	for (const auto& elem : vec) {
		if (heap3.size() < 3) heap3.push(elem);
		else if (heap3.top() < elem) {
			heap3.pop();
			heap3.push(elem);
		}

		if (heap2.size() < 2) heap2.push(elem);
		else if (heap2.top() > elem) {
			heap2.pop();
			heap2.push(elem);
		}

	}

	std::vector<int> pos(3);
	std::vector<int> neg(2);
	
	for (auto& elem : pos) {
		elem = heap3.top();
		heap3.pop();
	}

	for (auto& elem : neg) {
		elem = heap2.top();
		heap2.pop();
	}

	if ((static_cast<long long>(neg[0]) * neg[1] > static_cast<long long>(pos[0]) * pos[1]) && pos[2] > 0) return std::vector<int> {neg[0], neg[1], pos[2]};
	return pos;
}


std::vector<int> inputVec() {
	int temp;
	std::vector<int> vec;

	while (std::cin >> temp) {
		vec.push_back(temp);
	}
	return vec;
}


int main() {
	std::vector<int> vec {inputVec()};
	std::vector<int> res {maxMul3(vec)};
	for (const auto& elem : res) {
		std::cout << elem << ' ';
	}
	return 0;
}