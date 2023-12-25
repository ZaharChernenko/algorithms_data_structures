#include <iostream>

using std::cin, std::cout;


void middleLev(const short* arr, int SIZE) {
    unsigned int* lev_arr {new unsigned int[SIZE]};
    unsigned int right_s = 0, left_s = 0;
    for (int i = 0; i != SIZE; ++i) right_s += arr[i];
    lev_arr[0] = right_s - arr[0] * SIZE;
    right_s -= arr[0];
    cout << lev_arr[0];
    for (int i = 1; i != SIZE; ++i) {
        left_s += i * (arr[i] - arr[i - 1]);
        lev_arr[i] = left_s + right_s - arr[i] * (SIZE - i);
        right_s -= arr[i];
        cout << ' ' << lev_arr[i];
    }
    delete[] lev_arr;
}


int inputE() {
    int SIZE;
    cin >> SIZE;
    short* arr {new short[SIZE]};
    for (int i = 0; i != SIZE; ++i) cin >> arr[i];
    middleLev(arr, SIZE);
    delete[] arr;
}