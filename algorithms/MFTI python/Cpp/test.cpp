#include "lecture_3 Horner circuit.h"
#include "lecture_5 Byte shift.h"
#include <gtest/gtest.h>
#include <vector>

TEST(horner_circuit, convert2Decimal) {
    EXPECT_EQ(convert2Decimal("1000", 2), 8);
    EXPECT_EQ(convert2Decimal("FF", 16), 255);
}

TEST(horner_circuit, changeBase) {
    EXPECT_EQ(changeBase("1000", 2, 8), "10");
    EXPECT_EQ(changeBase("255", 10, 16), "FF");
}

TEST(arr_shifting, reverseArr) {
    int arr[] = {1, 2, 3, 4, 5};
    reverseArr(arr, 5);

    int reversed_arr[] = {5, 4, 3, 2, 1};
    for (std::size_t i {0}; i != 5; ++i)
        EXPECT_EQ(arr[i], reversed_arr[i]);
}

TEST(arr_shifting, moveLeft) {
    int arr[] = {1, 2, 3, 4, 5};
    moveLeft(arr, 5);

    int shifted_arr[] = {2, 3, 4, 5, 1};
    for (std::size_t i {0}; i != 5; ++i)
        EXPECT_EQ(arr[i], shifted_arr[i]);
}

TEST(arr_shifting, moveRight) {
    int arr[] = {1, 2, 3, 4, 5};
    moveRight(arr, 5);

    int shifted_arr[] = {5, 1, 2, 3, 4};
    for (std::size_t i {0}; i != 5; ++i)
        EXPECT_EQ(arr[i], shifted_arr[i]);
}

TEST(math, isPrime) {
    EXPECT_EQ(isPrime(5), true);
    EXPECT_EQ(isPrime(997), true);
    EXPECT_EQ(isPrime(4), false);
}

TEST(math, primesArr) {
    bool* primes_arr {primesArr(11)};
    std::vector<int> result {};

    for (size_t i {0}; i != 12; ++i)
        if (*(primes_arr + i))
            result.push_back(i);

    EXPECT_EQ(result, std::vector({2, 3, 5, 7, 11}));

    delete[] primes_arr;
}