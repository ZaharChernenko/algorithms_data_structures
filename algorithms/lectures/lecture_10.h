#pragma once
#include <vector>

using std::cin, std::cout;


bool comp(const std::string& a, const std::string& b)
{
    int sum1 = 0, sum2 = 0;
    for (auto &d: a) {
        sum1 += d - '0';
    }
    for (auto &d: b) {
        sum2 += d - '0';
    }
    if (sum1 != sum2) return sum1 < sum2;
    return a < b;
}


template <typename T>
int binarySearch(const std::vector<T>& vec, const T& key) {
    int left = -1, right = vec.size(), middle = 0;
    while (right - left > 1) {
        middle = (left + right) / 2;
        if (vec[middle] < key) left = middle;
        else right = middle;
    }
    if (right != vec.size() && vec[right] == key) return right;
    return -1;
}


void test10() {
    std::vector<int> vec {0, 1, 2, 3, 4, 5, 7};
    auto iter = std::lower_bound(vec.begin(), vec.end(), 6);
    //if (iter == vec.end()) cout << -1;
    //else cout << iter - vec.begin();
    std::vector<std::string> vec1 {"123", "231"};
    std::sort(vec1.begin(), vec1.end(), comp);

    std::vector<int> v1 {123, 3, 123, 2, 1, 4};
    mergeSort(v1);

    std::size_t n = v1.size();
    for (std::size_t i = 0; i < n; ++i){
        if (i == 2) {
            v1.pop_back();
        }
        cout << v1.at(i) << '\t';
    }
}
