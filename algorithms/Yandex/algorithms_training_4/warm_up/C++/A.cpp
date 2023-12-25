#include <iostream>
#include <string>

using std::cin, std::cout;


std::string notMin(short* arr, short left, short right) {
    short cur = arr[left];
    for (short i = left + 1; i != right + 1; ++i) {
        if (cur > arr[i]) return std::to_string(cur);
        if (cur < arr[i]) return std::to_string(arr[i]);
    }
    return "NOT FOUND";
}

// компоновщик будет кидать исключение, если в разных файлах будут одинаковые функции
int inputA()  {
    short arr_size;
    short n_req;
    cin >> arr_size >> n_req;

    short* arr {new short[arr_size]};
    for (short i = 0; i != arr_size; ++i) cin >> arr[i];

    short left, right;
    for (short i = 0; i != n_req; ++i) {
        cin >> left >> right;
        cout << notMin(arr, left, right) << '\n';
    }

    delete[] arr;
    return 0;
}