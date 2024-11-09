#include "Rider.h"
#include <cmath>
#include <cstddef>
#include <functional>

template <typename Container, typename Comparator = std::less_equal<typename Container::value_type>>
    requires IsValidContainer<Container>
void naturalMergeSort(Container& container,
                      const Comparator& comp = std::less_equal<typename Container::value_type>()) {
    using RT = Rider<Container, Comparator>;
    std::size_t n_copied_series {0};
    while (n_copied_series != 1) {
        // распределяем серии из источника в приемники
        Container dest1 {}, dest2;
        RT source_rider {container};
        bool switcher {true};
        while (source_rider) {
            switcher ? source_rider.copySerieTo(dest1) : source_rider.copySerieTo(dest2);
            ++n_copied_series;
            switcher = !switcher;
        }
        // если скопировано 0, то источник пуст, если 1, то отсортирован изначально
        if (n_copied_series < 2) [[unlikely]]
            return;

        n_copied_series = 0;
        //  сливаем серии обратно
        source_rider.reset();
        RT rider1 {dest1}, rider2 {dest2};
        // если хоть один rider пустой, то сразу переходим к копированию из другого
        while (rider1 && rider2) {
            // без do не обойтись, т.к. начальное значение true
            // снизу везде move, т.к. мы точно знаем, что скопируется container.size() элементов
            do {
                // здесь сливаем две серии в одну
                if (comp(rider1.getElement(), rider2.getElement())) {
                    rider1.moveTo(source_rider);
                    if (rider1.isEndOfSerie())
                        rider2.moveSerieTo(source_rider);
                } else {
                    rider2.moveTo(source_rider);
                    if (rider2.isEndOfSerie())
                        rider1.moveSerieTo(source_rider);
                }
            } while (!(rider1.isEndOfSerie() && rider2.isEndOfSerie()));
            ++n_copied_series;
        }
        while (rider1) {
            rider1.moveSerieTo(source_rider);
            ++n_copied_series;
        }
        while (rider2) {
            rider2.moveSerieTo(source_rider);
            ++n_copied_series;
        }
    }
}
