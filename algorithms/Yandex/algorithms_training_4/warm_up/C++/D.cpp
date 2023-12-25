#include <iostream>
#include <string>
#include <unordered_map>

using std::cin, std::cout;


std::string check(const std::string& first, const std::string& second) {
    std::unordered_map<char, int> freq_map {};
    for (const char& elem: first) freq_map.insert_or_assign(elem, ++freq_map[elem]);
    for (const char& elem: second) {
        if (freq_map.count(elem) == 0) return "NO";
        --freq_map[elem];
        if (freq_map[elem] == 0) freq_map.erase(elem);
    }
    if (freq_map.empty()) return "YES";
    return "NO";
}

int inputD() {
    std::string first, second;
    cin >> first >> second;
    cout << check(first, second);
    return 0;
}