#pragma once
// ������� ���������� ��������� ����������
#include <vector>


int localMax(const std::vector<int>& vec) {
	int count = 0;
	for (int i = 1; i + 1 < vec.size(); ++i) { // i + 1 ����� ������, ��� ������ �������, ������� ����� ����� <
		if (vec[i - 1] < vec[i] && vec[i] > vec[i + 1]) ++count;
	}
	return count;
}