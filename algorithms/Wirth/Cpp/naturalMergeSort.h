#include <algorithm>
#include <cstddef>
#include <functional>
#include <stdexcept>

template <typename Container>
concept IsValidContainer = requires(Container container) {
    typename Container::iterator;
    container.begin();
    container.end();
    ++(container.begin());
    (container.begin())++;
    *container.begin();
    container.push_back(typename Container::value_type());
};

template <typename Container, typename Comparator>
    requires IsValidContainer<Container>
class Rider

{
    using value_type = typename Container::value_type;
    using iterator = typename Container::iterator;

  public:
    Rider(Container& container);
    inline void copyTo(Container& other);
    inline void moveTo(Rider& other);
    void copySerieTo(Container& other);
    void moveSerieTo(Rider& other);
    inline bool isEndOfSerie() const;
    inline bool isEnd() const;
    inline const value_type& getElement() const;
    void reset();

  protected:
    iterator _it;
    Container& _container;
    static constexpr Comparator _comp {};
    bool _is_end_of_serie {true};
};

template <typename Container, typename Comparator>
    requires IsValidContainer<Container>
Rider<Container, Comparator>::Rider(Container& container) : _it {container.begin()}, _container {container} {}

template <typename Container, typename Comparator>
    requires IsValidContainer<Container>
void Rider<Container, Comparator>::copyTo(Container& other) {
    if (_it == _container.end()) [[unlikely]]
        throw std::runtime_error("Out of bounds");

    iterator cur_iter {_it++};
    other.push_back(*cur_iter);

    _is_end_of_serie = (_it == _container.end() || (!_comp(*cur_iter, *_it)));
}

template <typename Container, typename Comparator>
    requires IsValidContainer<Container>
void Rider<Container, Comparator>::moveTo(Rider& other) {
    if (_it == _container.end()) [[unlikely]]
        throw std::runtime_error("Out of bounds");

    *other._it = std::move(*_it++);
    _is_end_of_serie = (_it == _container.end() || (!_comp(*other._it, *_it)));
    ++other._it;
}

template <typename Container, typename Comparator>
    requires IsValidContainer<Container>
void Rider<Container, Comparator>::copySerieTo(Container& other) {
    if (_it == _container.end()) [[unlikely]]
        throw std::runtime_error("Out of bounds");
    do {
        copyTo(other);
    } while (!_is_end_of_serie);
}

template <typename Container, typename Comparator>
    requires IsValidContainer<Container>
void Rider<Container, Comparator>::moveSerieTo(Rider& other) {
    if (_it == _container.end()) [[unlikely]]
        throw std::runtime_error("Out of bounds");
    do {
        moveTo(other);
    } while (!_is_end_of_serie);
}

template <typename Container, typename Comparator>
    requires IsValidContainer<Container>
bool Rider<Container, Comparator>::isEndOfSerie() const {
    return _is_end_of_serie;
}

template <typename Container, typename Comparator>
    requires IsValidContainer<Container>
bool Rider<Container, Comparator>::isEnd() const {
    return _it == _container.end();
}

template <typename Container, typename Comparator>
    requires IsValidContainer<Container>
const typename Rider<Container, Comparator>::value_type& Rider<Container, Comparator>::getElement() const {
    return *_it;
}

template <typename Container, typename Comparator>
    requires IsValidContainer<Container>
void Rider<Container, Comparator>::reset() {
    _it = _container.begin();
}

template <typename Container, typename Comparator = std::less_equal<typename Container::value_type>>
    requires IsValidContainer<Container>
void naturalMergeSort(Container& container) {
    constexpr static Comparator comp {};
    std::size_t n_copied_series {0};
    while (n_copied_series != 1) {
        // распределяем серии из источника в приемники
        Container dest1 {}, dest2;
        Rider<Container, Comparator> source_rider {container};
        bool switcher {true};
        while (!source_rider.isEnd()) {
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
        Rider<Container, Comparator> rider1 {dest1}, rider2 {dest2};
        // если хоть один rider пустой, то сразу переходим к копированию из другого
        while (!(rider1.isEnd() || rider2.isEnd())) {
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
        while (!rider1.isEnd()) {
            rider1.moveSerieTo(source_rider);
            ++n_copied_series;
        }
        while (!rider2.isEnd()) {
            rider2.moveSerieTo(source_rider);
            ++n_copied_series;
        }
    }
}
