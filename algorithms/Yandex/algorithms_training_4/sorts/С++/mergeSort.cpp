#include <iostream>
#include <vector>

using std::cin, std::cout;

void merge(std::vector<int>& res, std::vector<int>& left, std::vector<int>& right) {
    int index = 0, left_index = 0, right_index = 0;
    while (left_index < left.size() && right_index < right.size()) {
        if (left[left_index] <= right[right_index]) res[index++] = left[left_index++];
        else res[index++] = right[right_index++];
    }
    for (int i = left_index; i != left.size(); ++i) res[index++] = left[i];
    for (int i = right_index; i != right.size(); ++i) res[index++] = right[i];
}


std::vector<int> mergeSort(std::vector<int>& vec) {
    if (vec.size() <= 1) return vec;
    std::vector<int> left {vec.begin(), vec.begin() + vec.size() / 2};
    std::vector<int> right {vec.begin() + vec.size() / 2, vec.end()};
    mergeSort(left);
    mergeSort(right);
    merge(vec, left, right);
    return vec;
}


int main() {
    int size;
    cin >> size;

    if (size == 0) {
        cout << '\n';
        return 0;
    }
    std::vector<int> vec(size);
    for (int& elem: vec) cin >> elem;
    mergeSort(vec);
    for (int i = 0; i != vec.size() - 1; ++i) cout << vec[i] << ' ';
    cout << vec[vec.size() - 1];
    return 0;
}

