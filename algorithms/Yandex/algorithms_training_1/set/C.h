#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>


std::vector<int> inputVec(const int& size) {
    std::vector<int> vec(size);
    for (auto& elem : vec) {
        std::cin >> elem;
    }
    return vec;
}


int solutionC() {
    int n_ann, n_borya;
    std::cin >> n_ann >> n_borya;
    std::vector<int>  ann_vec {inputVec(n_ann)}, borya_vec {inputVec(n_borya)};
    std::vector<int> res;

    std::sort(ann_vec.begin(), ann_vec.end());
    std::sort(borya_vec.begin(), borya_vec.end());

    std::set_intersection(ann_vec.begin(), ann_vec.end(),
                          borya_vec.begin(), borya_vec.end(),
                          std::back_inserter(res));

    std::cout << res.size() << '\n';
    for (const auto& elem: res) std::cout << elem << ' ';
    std::cout << '\n';

    std::unordered_set<int> intersection {res.begin(), res.end()};

    std::cout << n_ann - intersection.size() << '\n';
    for (const auto& elem: ann_vec) {
        if (intersection.count(elem)) continue;
        std::cout << elem << ' ';
    }
    std::cout << '\n';

    std::cout << n_borya - intersection.size() << '\n';
    for (const auto& elem: borya_vec) {
        if (intersection.count(elem)) continue;
        std::cout << elem << ' ';
    }
}