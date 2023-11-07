#include <iostream>
#include <vector>
#include <sstream>
#include <string>


// если не дан размер вектора (через консоль неудобно, так медленнее)
std::vector<int> inputVec() {
	int temp;
	std::vector<int> vec;

	while (std::cin >> temp) {
		vec.push_back(temp);
	}
	return vec;
}


// если не дан размер вектора (через консоль удобнее, так быстрее работает)
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


// если не дан размер вектора, но есть элемент, оканчивающий последовательность
std::vector<int> inputVec2() {
	int temp;
	std::vector<int> vec;
	while (std::cin >> temp && temp != -2 * std::pow(10, 9)) {
		vec.push_back(temp);
	}
	return vec;
}


// когда все-таки дали размер
std::vector<short> inputVec(const int& size) {
	std::vector<short> vec(size);
	for (auto& elem : vec) {
		std::cin >> elem;
	}
	return vec;
}
