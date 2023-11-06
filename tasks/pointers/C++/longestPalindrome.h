#pragma once
#include <string>

using namespace std;

class Solution {
public:
    bool isPalindrome(string& s) {
        for (size_t i = 0; i != s.size() / 2; ++i) {
            if (s[i] != s[s.size() - i - 1]) return false;
        }
        return true;
    }
    string longestPalindrome(string s) {
        int start = 0, size = 1, left, right;
        string s1, s2;
        for (int i = 1; i != s.size(); ++i) {
            left = i - size; right = i + 1;
            if (left >= 1) {
                s1 = string(s.begin() + left - 1, s.begin() + right);
                if (isPalindrome(s1)) {
                    start = left - 1;
                    size += 2;
                    continue;
                }
            }
            s2 = string(s.begin() + left, s.begin() + right);
            if (isPalindrome(s2)) {
                start = left;
                size += 1;
            }
        }
        return string(s.begin() + start, s.begin() + start + size);
    }
};