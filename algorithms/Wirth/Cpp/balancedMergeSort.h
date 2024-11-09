#include "Rider.h"
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <functional>
#include <vector>

template <typename Container, typename Comparator = std::less_equal<typename Container::value_type>>
    requires IsValidContainer<Container>
void balancedMergeSort(Container& container,
                       const Comparator& comp = std::less_equal<typename Container::value_type>()) {
    using RT = Rider<Container, Comparator>;
    // начальное заполнение контейнеров источников
    RT source_rider {container};
    // минимум два массива источника должно быть, иначе бесконечный цикл
    std::size_t sources_arr_size = std::max(2.0, std::log2(container.size())), n_copied_series {0};
    std::vector<Container> sources_arr(sources_arr_size);

    for (std::size_t i {0}; source_rider; ++i) {
        source_rider.copySerieTo(sources_arr[i % sources_arr_size]);
        ++n_copied_series;
    }
    std::vector<RT> riders_arr(sources_arr_size);
    std::vector<std::size_t> index_mapper_arr(sources_arr_size);

    // если исходный контейнер пуст или отсортирован, то не заходим в основной цикл
    while (n_copied_series > 1) {
        // ставим бегунки только у действительных
        std::size_t n_real_sources {std::min(n_copied_series, sources_arr_size)};
        for (std::size_t i {0}; i != n_real_sources; ++i) {
            riders_arr[i] = sources_arr[i];
            index_mapper_arr[i] = i;
        }

        std::size_t receivers_arr_size {n_real_sources};
        std::vector<Container> receivers_arr(receivers_arr_size);
        n_copied_series = 0;

        while (n_real_sources != 0) {
            std::size_t n_real_series {n_real_sources};
            while (n_real_series != 0) {
                typename std::vector<std::size_t>::iterator min_iter {
                    std::min_element(index_mapper_arr.begin(), index_mapper_arr.begin() + n_real_series,
                                     [&comp, &riders_arr](std::size_t first, std::size_t second) {
                                         return comp(riders_arr[first].getElement(), riders_arr[second].getElement());
                                     })};
                (riders_arr[*min_iter]).copyTo(receivers_arr[(n_copied_series) % receivers_arr_size]);

                // если бегунок закончился, то меняем местами его с последней серией, после чего он будет недостижим
                if (!riders_arr[*min_iter]) {
                    --n_real_sources;
                    --n_real_series;
                    *min_iter = index_mapper_arr[n_real_series];
                    index_mapper_arr[n_real_series] = index_mapper_arr[n_real_sources];
                } else if (riders_arr[*min_iter].isEndOfSerie()) {
                    --n_real_series;
                    std::swap(*min_iter, index_mapper_arr[n_real_series]);
                }
            }

            ++n_copied_series;
        }
        std::swap(sources_arr, receivers_arr);
    }

    container = std::move(*sources_arr.begin());
}
