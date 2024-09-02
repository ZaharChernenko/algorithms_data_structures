#include <cstddef>
#include <cstdint>
#include <limits>
#include <vector>

constexpr int64_t int64_t_min {std::numeric_limits<int64_t>::min()};
constexpr int64_t int64_t_max {std::numeric_limits<int64_t>::max()};

uint64_t findWaysNum(std::size_t n_rows, std::size_t n_cols) {
    std::vector<std::vector<uint64_t>> ways(n_rows, std::vector<uint64_t>(n_cols));
    for (std::size_t i {0}; i != n_rows; ++i)
        ways[i][0] = 1;
    for (std::size_t i {0}; i != n_cols; ++i)
        ways[0][i] = 1;

    for (std::size_t i {1}; i != n_rows; ++i) {
        for (std::size_t j {1}; j != n_cols; ++j)
            ways[i][j] = ways[i - 1][j] + ways[i][j - 1];
    }

    return ways[n_rows - 1][n_cols - 1];
}

template <class T>
std::vector<std::vector<std::size_t>> matrixLCS(const T& sequence_1, const T& sequence_2) {
    std::size_t n_rows {sequence_1.size() + 1}, n_cols {sequence_2.size() + 1};
    std::vector<std::vector<std::size_t>> matrix(n_rows, std::vector<std::size_t>(n_cols, 0));

    for (std::size_t i {1}; i != n_rows; ++i) {
        for (std::size_t j {1}; j != n_cols; ++j) {
            if (sequence_1[i - 1] != sequence_2[j - 1])
                matrix[i][j] = std::max(matrix[i - 1][j], matrix[i][j - 1]);
            else
                matrix[i][j] = matrix[i - 1][j - 1] + 1;
        }
    }

    return matrix;
}

template <class T>
T findLCS(const T& sequence_1, const T& sequence_2) {
    std::vector<std::vector<std::size_t>> matrix_lcs {matrixLCS(sequence_1, sequence_2)};
    std::size_t row {sequence_1.size()}, col {sequence_2.size()};
    T result {};

    while (row * col != 0) {
        if (sequence_1[row - 1] == sequence_2[col - 1]) {
            result.push_back(sequence_1[row - 1]);
            --row;
            --col;
        } else if (matrix_lcs[row - 1][col] > matrix_lcs[row][col - 1])
            --row;
        else
            --col;
    }
    std::reverse(result.begin(), result.end());

    return result;
}

template <class T>
std::size_t lengthLCS(const T& sequence_1, const T& sequence_2) {
    std::size_t n_cols {sequence_2.size() + 1};
    std::vector<std::size_t> prev_row(n_cols, 0), cur_row(n_cols);

    for (std::size_t i {0}; i != sequence_1.size(); ++i) {
        for (std::size_t j {1}; j != n_cols; ++j) {
            if (sequence_1[i] != sequence_2[j - 1])
                cur_row[j] = std::max(prev_row[j], cur_row[j - 1]);
            else
                cur_row[j] = prev_row[j - 1] + 1;
        }
        std::swap(prev_row, cur_row);
        cur_row = std::vector<std::size_t>(n_cols);
    }

    return prev_row[n_cols - 1];
}

template <class T>
std::size_t squareLIS(const T& sequence) {
    // lis_arr[i] это длина наибольшей подпоследовательности, с sequence[i] элементом
    std::vector<std::size_t> lis_arr(sequence.size(), 0);

    for (std::size_t i {0}; i != sequence.size(); ++i) {
        for (std::size_t j {0}; j != i; ++j) {
            if (sequence[i] > sequence[j] && lis_arr[i] < lis_arr[j])
                lis_arr[i] = lis_arr[j];
        }
        ++lis_arr[i];
    }

    return *std::max_element(lis_arr.begin(), lis_arr.end());
}

template <class T>
std::size_t lengthLIS(const T& sequence) {
    // lis_arr[i] это наименьший элемент, на который оканчивается последовательность длины i
    std::vector<int64_t> lis_arr(sequence.size() + 1, int64_t_max);
    lis_arr[0] = int64_t_min;
    // ge_index (greatest or equal index) - первый индекс lis_arr, такой, что lis_arr[ge_index] >= текущему sequence[i]
    // т.к. считаем строго возрастающую последовательность, то для замены ge_elem на sequence[i],
    // sequence[i] должно быть строго меньше ge_elem
    // если же последовательность не строго возрастающая, то можно было бы использовать std::upper_bound
    std::size_t length {0}, ge_index;

    for (const auto& el : sequence) {
        ge_index = std::distance(lis_arr.begin(), std::lower_bound(lis_arr.begin(), lis_arr.end(), el));
        if (lis_arr[ge_index - 1] < el && el < lis_arr[ge_index]) { // любой ge_index > 0 т.к. 0 это -inf
            lis_arr[ge_index] = el;
            length = std::max(ge_index, length);
        }
    }

    return length;
}

template <class T>
std::vector<T> LIS(const std::vector<T>& sequence) {
    // lis_arr[i] это индекс наименьшего элемента из sequence, на который оканчивается подпоследовательность длины i
    std::vector<int64_t> lis_arr(sequence.size() + 1, int64_t_max);
    lis_arr[0] = int64_t_min;
    // prev_arr[i] - содержит в себе предшествующие индексы для каждого i
    std::vector<int64_t> prev_arr(sequence.size());
    std::size_t length {0}, ge_index;

    for (int64_t i {0}; i != sequence.size(); ++i) {
        // у компоратора в lower_bound второй элемент всегда наше значение, которое является 3 аргументом в lower_bound
        ge_index = std::lower_bound(lis_arr.begin(), lis_arr.end(), sequence[i],
                                    [&sequence](int64_t index, const T& val) {
                                        if (index == int64_t_min)
                                            return true;
                                        if (index == int64_t_max)
                                            return false;
                                        return sequence[index] < val;
                                    }) -
                   lis_arr.begin();
        if (lis_arr[ge_index] == int64_t_max || sequence[i] < sequence[lis_arr[ge_index]]) {
            lis_arr[ge_index] = i;
            prev_arr[i] = lis_arr[ge_index - 1];
            length = std::max(length, ge_index);
        }
    }

    std::vector<T> result(length);
    for (int64_t seq_index {lis_arr[length]}, result_index = length - 1; seq_index != int64_t_min;
         seq_index = prev_arr[seq_index], --result_index)
        result[result_index] = sequence[seq_index];

    return result;
}
