#include <iostream>
using namespace std;

bool isPalindrome(string::iterator start, string::iterator end) {
    size_t half = (end - start) / 2;
    for (size_t i = 0; i < half; ++i) {
        if (*(start + i) != *(end - i - 1)) return false;
    }
    return true;
}

    string longestPalindrome(string s) {
        if (isPalindrome(s.begin(), s.end())) return s;
        size_t start = 0, size = 1, l, r;
        for (size_t i = 1; i < s.size(); ++i) {
            l = i - size; r = i + 1;
            if (l - 1 >= 0 and isPalindrome(s.begin() + l - 1, s.begin() + r)) {
                size += 2; start = l - 1;
            }
            else if (isPalindrome(s.begin() + l, s.begin() + r)) {
                size += 1; start = l;
            }
        }
        return {s.begin() + start, s.begin() + start + size};
    }


int main() {
    cout << longestPalindrome("xaabacxcabaaxcabaax");
    return 0;
}