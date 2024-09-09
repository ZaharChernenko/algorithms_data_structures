#include <cstdint>
#include <stack>
#include <string>
#include <unordered_map>

bool validExp(const std::string& exp) {
    int64_t open_braces {0};
    for (char brace : exp) {
        if (brace == '(')
            ++open_braces;
        else if (!open_braces--)
            return false;
    }

    return open_braces == 0;
}

bool validExp1(const std::string& exp) {
    std::stack<char> open_braces {};
    const static std::unordered_map<char, char> open2close {{'(', ')'}, {'[', ']'}, {'{', '}'}};

    for (char brace : exp) {
        if (open2close.contains(brace))
            open_braces.push(brace);
        else {
            if (open2close.at(open_braces.top()) == brace)
                open_braces.pop();
            else
                return false;
        }
    }

    return open_braces.empty();
}
