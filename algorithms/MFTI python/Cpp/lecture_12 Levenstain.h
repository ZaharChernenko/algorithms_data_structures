#include <algorithm>
#include <cstddef>
#include <string>
#include <utility>
#include <vector>

std::size_t levenstain(const std::string& str1, const std::string& str2) {
    const std::string& str1_view = str1.size() < str2.size() ? str1 : str2;
    const std::string& str2_view = str1.size() < str2.size() ? str2 : str1;

    std::size_t n_cols {str2_view.size() + 1};
    std::vector<std::size_t> prev(n_cols), cur(n_cols);
    for (std::size_t i {0}; i != n_cols; ++i)
        prev[i] = i;

    for (std::size_t i {0}; i != str1_view.size(); ++i) {
        cur[0] = i + 1;
        for (std::size_t j {1}; j != n_cols; ++j) {
            if (str1_view[i] == str2_view[j - 1])
                cur[j] = prev[j - 1];
            else
                // prev[j - 1] - замена одного символа на другой
                // prev[j] - удаление одного символа
                // cur[j - 1] - вставка одного символа (либо удаление по горизонтали)
                cur[j] = 1 + std::min({prev[j - 1], prev[j], cur[j - 1]});
        }
        std::swap(prev, cur);
        cur = std::vector<std::size_t>(n_cols);
    }

    return prev[n_cols - 1];
}

std::size_t prefixFunc(const std::string& str) {
    if (str.size() <= 1) {
        return 0;
    }

    // prefix_arr[i] - длина максимального собственного префикса,
    // который является суффиксом строки от 0 до i включительно
    std::vector<std::size_t> prefix_arr(str.size(), 0);
    // длина предыдущего префикса
    std::size_t prev_prefix_size;
    for (std::size_t i {1}; i != prefix_arr.size(); ++i) {
        prev_prefix_size = prefix_arr[i - 1];

        // prev_prefix_size всегда указывает на следующий элемент, поэтому если он равен,
        // то мы завершаем цикл
        while (prev_prefix_size != 0 && str[prev_prefix_size] != str[i])
            // префикс предыдущей строки нам не подходит, однако если мы возьмем префикс от префикса
            // то он также будет и суффиксом, тогда можно попробовать сравнить его
            // prev_prefix_size указывает на длину префикса, тогда prev_prefix_size - 1 будет
            // указывать на префикс от него
            prev_prefix_size = prefix_arr[prev_prefix_size - 1];

        if (str[prev_prefix_size] == str[i])
            ++prev_prefix_size;
        prefix_arr[i] = prev_prefix_size;
    }

    return prefix_arr[str.size() - 1];
}
