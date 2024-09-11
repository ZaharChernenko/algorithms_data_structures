#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <vector>

int64_t backpack(const std::vector<int64_t>& prices, const std::vector<uint32_t>& weights, uint32_t capacity) {
    std::size_t n_elements {prices.size()};
    std::vector<std::vector<int64_t>> backpack(n_elements + 1, std::vector<int64_t>(capacity + 1, 0));

    for (std::size_t el_index {1}; el_index != n_elements + 1; ++el_index) {
        for (uint32_t cur_capacity {1}; cur_capacity != capacity + 1; ++cur_capacity) {
            uint32_t el_weight {weights[el_index - 1]};
            if (cur_capacity < el_weight)
                backpack[el_index][cur_capacity] = backpack[el_index - 1][cur_capacity];
            else {
                backpack[el_index][cur_capacity] =
                    std::max(backpack[el_index - 1][cur_capacity],
                             backpack[el_index - 1][cur_capacity - el_weight] + prices[el_index - 1]);
            }
        }
    }

    return backpack[n_elements][capacity];
}

int64_t backpackDiscr(const std::vector<std::vector<int64_t>>& profit_matrix, uint32_t discr_step,
                      uint32_t total_invest) {
    std::size_t n_elements {profit_matrix.size()}, compressed_invest {total_invest / discr_step};
    std::vector<std::vector<int64_t>> backpack(n_elements + 1, std::vector<int64_t>(compressed_invest + 1, 0));

    for (std::size_t el_index {1}; el_index != n_elements + 1; ++el_index) {
        for (std::size_t cur_invest {1}; cur_invest != compressed_invest + 1; ++cur_invest) {
            int64_t max_profit {0};
            for (std::size_t invest_on_cur_el {1}; invest_on_cur_el != cur_invest + 1; ++invest_on_cur_el) {
                max_profit = std::max(
                    max_profit,
                    profit_matrix[el_index - 1][invest_on_cur_el - 1] + // invest_on_cur_el - 1 потому что матрица
                                                                        // профита начинается не с 0 инвестиций
                        backpack[el_index - 1][cur_invest - invest_on_cur_el]);
            }
            backpack[el_index][cur_invest] = std::max(
                max_profit, backpack[el_index - 1][cur_invest]); // также поскольку начинается не с 0, мы не берем
                                                                 // максимум без этого элемента в предыдущем цикле
        }
    }

    return backpack[n_elements][compressed_invest];
}
