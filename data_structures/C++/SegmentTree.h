/*
 TSegmentTree - базовый интерфейс дерева сегментов, который реализует первоначальное создание дерева,
 а также его обновление и вывод. Для создания дерева сегментов на основе этого интерфейса, необходимо
 реализовать метод fill, а также саму функцию для поиска значения на отрезке.
*/
#pragma once
#include <cmath>
#include <cstddef>
#include <iostream>
#include <limits>
#include <math.h>
#include <ostream>
#include <vector>

template <typename TData>
class ISegmentTree {
  public:
    template <typename TData1>
    friend std::ostream& operator<<(std::ostream& os, const ISegmentTree<TData1>& tree);

    void update(std::size_t index, const TData& value);

  protected:
    [[nodiscard]] inline std::size_t getParentsNumber() const noexcept;
    [[nodiscard]] inline std::size_t getLeavesNumber() const noexcept;
    void buildTree(const std::vector<TData>& points_arr, const TData& fill_value);
    [[nodiscard]] virtual TData fill(const std::size_t parent) = 0;
    [[nodiscard]] static constexpr std::size_t nearestDegreeOfTwo(std::size_t n) noexcept;
    static constexpr std::size_t overflow {std::numeric_limits<std::size_t>::max()};

  protected:
    std::vector<TData> m_segment_data;
};

template <typename TData1>
std::ostream& operator<<(std::ostream& os, const ISegmentTree<TData1>& tree) {
    typename std::vector<TData1>::const_iterator it {tree.m_segment_data.begin()};
    if (it != tree.m_segment_data.cend())
        os << *it++;
    for (; it != tree.m_segment_data.cend(); ++it)
        os << ' ' << *it;
    return os;
}

template <typename TData>
void ISegmentTree<TData>::update(std::size_t index, const TData& value) {
    std::size_t real_index {getParentsNumber() + index};
    m_segment_data[real_index] = value;
    while (real_index != 0) {
        std::size_t parent {((real_index - 1) >> 1)};
        m_segment_data[parent] = fill(parent);
        real_index = parent;
    }
}

template <typename TData>
std::size_t ISegmentTree<TData>::getParentsNumber() const noexcept {
    // листьев больше на 1, чем вершин, т.к. дерево всегда нечетное, то при целочисленном делении,
    // получаем число вершин, имеющих потомков
    return m_segment_data.size() >> 1;
}

template <typename TData>
std::size_t ISegmentTree<TData>::getLeavesNumber() const noexcept {
    return (m_segment_data.size() >> 1) + 1;
}

template <typename TData>
void ISegmentTree<TData>::buildTree(const std::vector<TData>& points_arr, const TData& fill_value) {
    m_segment_data = std::move(std::vector((nearestDegreeOfTwo(points_arr.size()) << 1) - 1, fill_value));
    std::size_t nparents {getParentsNumber()};
    std::copy(points_arr.begin(), points_arr.end(), m_segment_data.begin() + nparents);

    for (std::size_t parent {nparents - 1}; parent != overflow; --parent)
        m_segment_data[parent] = fill(parent);
}

template <typename TData>
constexpr std::size_t ISegmentTree<TData>::nearestDegreeOfTwo(std::size_t n) noexcept {
    if (n == 0) [[unlikely]]
        return 1;
    return 1 << (static_cast<std::size_t>(std::ceil(std::log2(n))));
}

// https://leetcode.com/problems/find-building-where-alice-and-bob-can-meet/description/
namespace NLeetCodeExample {
class TBuildingsSolver : public ISegmentTree<int> {
  public:
    TBuildingsSolver(const std::vector<int>& points_arr, const std::vector<int>& heights);

    [[nodiscard]] virtual int operator()(std::size_t lower_bound, std::size_t upper_bound, int height) const;

  protected:
    [[nodiscard]] virtual int fill(const std::size_t parent) override;
    [[nodiscard]] int search(std::size_t cur_index, std::size_t segment_lower_bound, std::size_t segment_upper_bound,
                             std::size_t lower_bound, std::size_t upper_bound, int height) const;

  protected:
    const std::vector<int>& m_heights;
};

TBuildingsSolver::TBuildingsSolver(const std::vector<int>& points_arr, const std::vector<int>& heights)
    : m_heights {heights} {
    buildTree(points_arr, -1);
};

int TBuildingsSolver::operator()(std::size_t lower_bound, std::size_t upper_bound, int height) const {
    return search(0, 0, getLeavesNumber() - 1, lower_bound, upper_bound, height);
}

int TBuildingsSolver::fill(const std::size_t parent) {
    size_t parent_doubled {parent << 1};
    if (m_segment_data[parent_doubled + 2] == -1 ||
        m_heights[m_segment_data[parent_doubled + 1]] >= m_heights[m_segment_data[parent_doubled + 2]])
        return m_segment_data[parent_doubled + 1];
    return m_segment_data[parent_doubled + 2];
}

int TBuildingsSolver::search(std::size_t cur_index, std::size_t segment_lower_bound, std::size_t segment_upper_bound,
                             std::size_t lower_bound, std::size_t upper_bound, int height) const {
    int cur_building {m_segment_data[cur_index]};
    if (segment_upper_bound < lower_bound || upper_bound < segment_lower_bound || cur_building == -1 ||
        m_heights[cur_building] <= height)
        return std::numeric_limits<int>::max();
    // ищем самую левую точку, поэтому при ее нахождении обрываем рекурсию
    if (segment_lower_bound == segment_upper_bound)
        return m_segment_data[cur_index];
    std::size_t middle {(segment_lower_bound + segment_upper_bound) >> 1};
    std::size_t index_doubled {cur_index << 1};
    int result {search(index_doubled + 1, segment_lower_bound, middle, lower_bound, upper_bound, height)};
    if (result == std::numeric_limits<int>::max())
        result = search(index_doubled + 2, middle + 1, segment_upper_bound, lower_bound, upper_bound, height);
    return result;
}

class Solution {
  public:
    std::vector<int> leftmostBuildingQueries(std::vector<int>& heights, std::vector<std::vector<int>>& queries) {
        std::vector<int> indexes(heights.size());
        for (int i {0}; i != heights.size(); ++i)
            indexes[i] = i;
        TBuildingsSolver tree(indexes, heights);

        std::vector<int> res(queries.size());
        for (size_t i {0}; i != queries.size(); ++i) {
            int &first {queries[i][0]}, second {queries[i][1]};
            if (second < first)
                std::swap(first, second);
            if (heights[first] < heights[second] || first == second)
                res[i] = second;
            else {
                int sum {tree(second + 1, heights.size() - 1, heights[first])};
                res[i] = sum != std::numeric_limits<int>::max() ? sum : -1;
            }
        }

        return res;
    }
};
} // namespace NLeetCodeExample
