#include <iostream>
#include "lecture_10.h"

using std::cin, std::cout;

int main() {
    cout << countWays2(5) << '\n';
    cout << countWaysBool(5, {1, 1, 1, 0, 1});
    return 0;
}
