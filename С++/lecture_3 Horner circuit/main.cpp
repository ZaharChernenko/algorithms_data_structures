#include <iostream>
#include "lecture_3.h"
#include "lecture_5.h"

using std::cin, std::cout;

int main() {
    using arr_of5 = int[5];
    arr_of5 arr{1, 2, 3, 4, 5};
    moveRight(arr, 5);
    printArr(arr, 5);
    moveLeft(arr, 5);
    printArr(arr, 5);
    reverseArr(arr, 5);
    printArr(arr, 5);
    cout << isPrime(20);

    return 0;
}