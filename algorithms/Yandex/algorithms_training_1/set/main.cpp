#include <iostream>
#include <unordered_set>
#include <string>

int main() {
    std::unordered_set<std::string> uniq_langs, everyone_langs;
    int n, n_langs, n_first_langs;
    std::cin >> n >> n_first_langs;

    std::string lang;
    for (int i = 0; i != n_first_langs; ++i) {
        std::cin >> lang;
        uniq_langs.insert(lang);
        everyone_langs.insert(lang);
    }

    std::unordered_set<std::string> others_langs, temp_set;
    for (int i = 1; i != n; ++i) {
        std::cin >> n_langs;
        for (int j = 0; j != n_langs; ++j) {
            std::cin >> lang;
            uniq_langs.insert(lang);
            others_langs.insert(lang);
        }
        temp_set = everyone_langs;
        for (const auto& elem: temp_set) {
            if (others_langs.count(elem) == 0) everyone_langs.erase(elem);
        }
        others_langs.clear();
    }

    std::cout << everyone_langs.size() << '\n';
    for (const auto& elem: everyone_langs) std::cout << elem << '\n';

    std::cout << uniq_langs.size() << '\n';
    for (const auto& elem: uniq_langs) std::cout << elem << '\n';

    return 0;
}