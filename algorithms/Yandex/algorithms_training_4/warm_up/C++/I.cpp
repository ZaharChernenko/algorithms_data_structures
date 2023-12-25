#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
using std::cin, std::cout;

std::string validExp(const std::string& exp) {
    std::unordered_map<char, char> tokens {{'(', ')'}, {'[', ']'}, {'{', '}'}};
    std::string back {")]}"};
    std::vector<char> stack {};
    for (const auto& elem: exp) {
        if (tokens.count(elem)) stack.push_back(elem);
        else if (back.find(elem) != std::string::npos) {
            if (stack.empty() || tokens[stack.back()] != elem) {
                return "no";
            }
            stack.pop_back();
        }
    }
    if (stack.empty()) return "yes";
    return "no";
}

int main() {
    std::string exp;
    cin >> exp;
    cout << validExp(exp);
    return 0;
}
