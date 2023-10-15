#pragma once

using std::cin, std::cout;


template <typename T>
void swap(T& ref1, T& ref2) {
    T temp = ref1;
    ref1 = ref2;
    ref2 = temp;
}


template <typename T>
T* copyArr(T* arr, int size) {
    T* temp_arr = new int[size];
    for (int i = 0; i < size; ++i) {
        temp_arr[i] = arr[i];
    }
    return temp_arr;
}


template <typename T>
T* insertSort(T* arr, int size) {
    T* temp_arr = copyArr(arr, size);
    int i = 0;
    for (int top = 1; top < size; ++top) {
        i = top;
        while (i > 0 && temp_arr[i - 1] > temp_arr[i]) {
            swap(temp_arr[i - 1], temp_arr[i]);
            --i;
        }
    }
    return temp_arr;
}


template <typename T>
T* choiceSort(T* arr, int size) {
    T* temp_arr = copyArr(arr, size);
    for (int pos = 0; pos < size - 1; ++pos) {
        for (int i = pos + 1; i < size; ++i) {
            if (temp_arr[pos] > temp_arr[i]) {
                swap(temp_arr[pos], temp_arr[i]);
            }
        }
    }
    return temp_arr;
}


template <typename T>
T* bubbleSort(T* arr, int size) {
    T* temp_arr = copyArr(arr, size);
    for (int bypass = 0; bypass < size - 1; ++bypass) {
        for (int i = 1; i < size - bypass; ++i) {
            if (temp_arr[i - 1] > temp_arr[i]) {
                swap(temp_arr[i - 1], temp_arr[i]);
            }
        }
    }
    return temp_arr;
}


int findMax(const int* arr, int size) {
    int max = *arr;
    for (int i = 1; i < size; ++i) {
        if (max < arr[i]) max = arr[i];
    }
    return max;
}


int* countSort(int* arr, int size) {
    int* temp_arr = new int[size];
    int count_size = findMax(arr, size) + 1;
    int* count_arr = new int[count_size];
    for (int i = 0; i < size; ++i) {
        ++count_arr[arr[i]];
    }

    int index = 0;
    for (int i = 0; i < count_size; ++i) {
        while (count_arr[i] > 0) {
            temp_arr[index] = i;
            --count_arr[i];
            index += 1;
        }
    }
    return temp_arr;
}

void test() {
    int arr1[]{5, 3, 2, 4, 1, 7, 7, 89, 98, 0};
    int* arr2 = insertSort(arr1, 10);
    printArr(arr2, 10);
    int* arr3 = choiceSort(arr1, 10);
    printArr(arr3, 10);
    int* arr4 = countSort(arr1, 10);
    printArr(arr4, 10);
}


