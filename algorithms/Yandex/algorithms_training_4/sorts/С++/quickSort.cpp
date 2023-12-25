#include <iostream>
#include <vector>

using std::cin, std::cout;


bool isSorted(std::vector<int>& vec) {
    for (int i = 1; i != vec.size(); ++i) {
        if (vec[i - 1] > vec[i]) return false;
    }
    return true;
}


int partition(std::vector<int>& vec, int left, int right) {
    int equal = left, greater = left;
    int pivot = vec[std::rand() % (right - left) + left];
    for (int i = left; i != right; ++i) {
        if (vec[i] < pivot) {
            std::swap(vec[i], vec[greater]);
            std::swap(vec[equal], vec[greater]);
            ++equal; ++greater;
        }
        else if (vec[i] == pivot) {
            std::swap(vec[i], vec[greater]);
            ++greater;
        }
    }
    return equal;
}


void _quickSort(std::vector<int>& vec, int left, int right) {
    if (left < right) {
        int sorted_elem_index = partition(vec, left, right);
        _quickSort(vec, left, sorted_elem_index);
        _quickSort(vec, sorted_elem_index + 1, right);
    }
}


void quickSort(std::vector<int>& vec) {
    _quickSort(vec, 0, vec.size());
}


int inputQuick() {
    int size;
    cin >> size;
    if (size == 0) {
        cout << '\n';
        return 0;
    }
    std::vector<int> vec (size);
    for (int& elem: vec) cin >> elem;
    if (!isSorted(vec)) quickSort(vec);
    for (int i = 0; i != vec.size() - 1; ++i) cout << vec[i] << ' ';
    cout << vec[vec.size() - 1];
    return 0;
}