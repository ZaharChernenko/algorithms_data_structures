#pragma once

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>

template <typename DataType>
class OptimalBST {
  public:
    OptimalBST(const std::vector<DataType>& elements, const std::vector<int64_t>& weights);
    void printTree() const;
    int64_t weight() const;

  protected:
    void _printTree(std::size_t lower_bound, std::size_t upper_bound, std::size_t level) const;

  protected:
    std::vector<DataType> m_elements;
    std::vector<std::vector<int64_t>> m_costs;
    std::vector<std::vector<std::size_t>> m_root_index;
};

template <typename DataType>
OptimalBST<DataType>::OptimalBST(const std::vector<DataType>& elements, const std::vector<int64_t>& weights)
    : m_elements {elements}, m_costs(elements.size() + 1, std::vector<int64_t>(elements.size() + 1, 0)),
      m_root_index(elements.size() + 1, std::vector<std::size_t>(elements.size() + 1, 0)) {
    // prefix_weights[i] - вес всех вершин до i НЕ включительно
    std::size_t n {elements.size()};
    std::vector<int64_t> prefix_weights(n + 1, 0);
    for (std::size_t i {1}; i != prefix_weights.size(); ++i)
        prefix_weights[i] = prefix_weights[i - 1] + weights[i - 1];

    // заполняем диагональ выше главной - она состоит из деревьев размером 1
    for (std::size_t root {0}; root != n; ++root) {
        std::size_t upper_bound {root + 1};
        m_costs[root][upper_bound] = weights[root];
        m_root_index[root][upper_bound] = root;
    }

    // итеративно создаем оптимальные деревья размером от 2 до n элементов
    // каждый раз заполняется диагональ, диагонали заполняются от главной, до правого верхнего угла
    for (std::size_t height {2}; height != n + 1; ++height) {
        for (std::size_t lower_bound {0}; lower_bound != n + 1 - height; ++lower_bound) {
            // верхняя граница, НЕ включительно
            std::size_t upper_bound {lower_bound + height};
            std::size_t root_min {m_root_index[lower_bound][upper_bound - 1]};
            std::int64_t cost_min {m_costs[lower_bound][root_min] + m_costs[root_min + 1][upper_bound]};

            for (size_t root_new {root_min + 1}; root_new != m_root_index[lower_bound + 1][upper_bound] + 1;
                 ++root_new) {
                int64_t new_cost {m_costs[lower_bound][root_new] + m_costs[root_new + 1][upper_bound]};
                if (new_cost < cost_min) {
                    cost_min = new_cost;
                    root_min = root_new;
                }
            }

            // в новом дереве все элементы будут на один уровень ниже, кроме корневого, который тоже нужно прибавить,
            // т.к. до этого его не прибавляли
            m_costs[lower_bound][upper_bound] = cost_min + prefix_weights[upper_bound] - prefix_weights[lower_bound];
            m_root_index[lower_bound][upper_bound] = root_min;
        }
    }
}

template <typename DataType>
void OptimalBST<DataType>::printTree() const {
    _printTree(0, m_elements.size(), 0);
}

template <typename DataType>
int64_t OptimalBST<DataType>::weight() const {
    return m_costs[0][m_elements.size()];
}

template <typename DataType>
void OptimalBST<DataType>::_printTree(std::size_t lower_bound, std::size_t upper_bound, std::size_t level) const {
    // т.к. _printTree печатает [lower_bound, upper_bound), то необходимо след. условие:
    if (lower_bound < upper_bound) {
        size_t root_index {m_root_index[lower_bound][upper_bound]};
        _printTree(lower_bound, root_index, level + 1);
        for (size_t i {0}; i < level; ++i)
            std::cout << '\t';
        std::cout << m_elements[root_index] << '\n';
        _printTree(root_index + 1, upper_bound, level + 1);
    }
}
