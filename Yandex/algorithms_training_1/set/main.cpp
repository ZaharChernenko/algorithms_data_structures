#include <iostream>
#include <unordered_set>


struct tuple {
    const int first, second;
    tuple(int first, int second): first {first}, second {second} {}
};


int main() {
    std::unordered_set<tuple> uniq;

    return 0;
}