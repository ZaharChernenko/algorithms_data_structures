#include <cstdint>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

// Для итеративной реализации алгоритмов
struct Storage {
    size_t index_on_row, index;
    Storage(size_t cur_pos, size_t index) : index_on_row {cur_pos}, index {index} {}
};

/*Генерация всех бинарных чисел определенной длины*/
void _genBinRecursive(std::string& prefix, int step, std::vector<std::string>& prefix_arr) {
    if (step == prefix.size()) {
        prefix_arr.push_back(prefix);
        return;
    }

    for (const char& digit : {'0', '1'}) { // "01" - C-string, last char \0
        prefix[step] = digit;
        _genBinRecursive(prefix, step + 1, prefix_arr);
    }
}

std::vector<std::string> genBinRecursive(int length) {
    std::string prefix(length, '0');
    std::vector<std::string> prefix_arr;
    _genBinRecursive(prefix, 0, prefix_arr);
    return prefix_arr;
}

std::vector<std::string> genBinIterative(size_t length) {
    std::vector<std::string> result_arr {};
    std::string prefix(length, '0');
    std::stack<Storage> stack {};
    stack.emplace(1, 0);
    stack.emplace(0, 0);

    while (!stack.empty()) {
        auto [cur_pos, index] {stack.top()};
        stack.pop();
        prefix[index] = cur_pos + 48;
        if (index + 1 == length)
            result_arr.push_back(prefix);
        else
            for (int8_t i {1}; i != -1; --i)
                stack.emplace(i, index + 1);
    }

    return result_arr;
}
/*Генерация всех бинарных чисел конец*/

/*Генерация всех чисел определенной длины в определенной системе счисления*/
void _genNumbersRecursive(std::string& prefix, int step, std::vector<std::string>& prefix_arr, int base) {
    if (step == prefix.size()) {
        prefix_arr.push_back(prefix);
        return;
    }

    for (int i = 0; i != base; ++i) {
        prefix[step] = '0' + i;
        _genNumbersRecursive(prefix, step + 1, prefix_arr, base);
    }
}

std::vector<std::string> genNumbersRecursive(int length, int base) {
    std::string prefix(length, '0');
    std::vector<std::string> prefix_arr;
    _genNumbersRecursive(prefix, 0, prefix_arr, base);
    return prefix_arr;
}

std::vector<std::string> genNumbersIterative(size_t length, char base) {
    std::vector<std::string> result_arr {};
    std::string prefix(length, '0');
    std::stack<Storage> stack {};
    for (int8_t i = base - 1; i != -1; --i)
        stack.emplace(i, 0);

    while (!stack.empty()) {
        auto [cur_pos, index] {stack.top()};
        stack.pop();
        prefix[index] = cur_pos + '0';
        if (index + 1 == length) {
            result_arr.push_back(prefix);
            continue;
        }
        for (int8_t i = base - 1; i != -1; --i)
            stack.emplace(i, index + 1);
    }

    return result_arr;
}
/*Генерация всех чисел определенной длины в определенной системе счисления конец*/

/*Генерация декартова произведения множеств*/
template <class T>
void _genDecRecursive(const std::vector<std::vector<T>>& sets_arr, size_t index, std::vector<T>& prefix,
                      std::vector<std::vector<T>>& result) {
    if (index == prefix.size()) {
        result.push_back(prefix);
        return;
    }
    for (const T& el : sets_arr[index]) {
        prefix[index] = el;
        _genDecRecursive(sets_arr, index + 1, prefix, result);
    }
}

/*
Генерация декартова произведения множеств
genDecRecurisive(std::vector<std::vector<int>>({{1, 2}, {3, 4}})) -> {{1, 3}, {1, 4}, {2, 3}, {2, 4}}
*/
template <class T>
std::vector<std::vector<T>> genDecRecurisive(const std::vector<std::vector<T>>& sets_arr) {
    std::vector<std::vector<T>> result {};
    std::vector<T> prefix(sets_arr.size());
    _genDecRecursive(sets_arr, 0, prefix, result);
    return result;
}

/*
Генерация декартова произведения множеств
genDecIterative(std::vector<std::vector<int>>({{1, 2}, {3, 4}})) -> {{1, 3}, {1, 4}, {2, 3}, {2, 4}}
Идея в том, чтобы добавить начальные элементы, а потом добавлять в стек только последующие индексы
*/
template <class T>
std::vector<std::vector<T>> genDecIterative(const std::vector<std::vector<T>>& sets_arr) {
    if (sets_arr.empty())
        return {{}};

    std::vector<std::vector<T>> result {};
    std::vector<T> prefix(sets_arr.size());
    std::stack<Storage> stack {};
    for (size_t index_on_row {sets_arr[0].size() - 1}; index_on_row != std::numeric_limits<size_t>::max();
         --index_on_row) // Закидываем в стек все индексы первого ряда в обратном порядке, т.к. стек FILO
        stack.emplace(index_on_row, 0);

    while (!stack.empty()) {
        auto [index_on_row, index] {stack.top()};
        stack.pop();

        prefix[index] = sets_arr[index][index_on_row];

        if (index + 1 == prefix.size()) {
            result.push_back(prefix);
            continue;
        }
        for (size_t index_on_row {sets_arr[++index].size() - 1}; index_on_row != std::numeric_limits<size_t>::max();
             --index_on_row) { // см. выше
            stack.emplace(index_on_row, index);
        }
    }

    return result;
}
