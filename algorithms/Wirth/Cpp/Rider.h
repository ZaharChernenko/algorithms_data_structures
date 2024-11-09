#include <algorithm>
#include <cmath>
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
    container.empty();
    container.size();
};

template <typename Container, typename Comparator>
    requires IsValidContainer<Container>
class Rider {
    using value_type = typename Container::value_type;
    using iterator = typename Container::iterator;

  public:
    Rider() = default;
    Rider(Container& container);

    Rider& operator=(Container& container);
    explicit operator bool() const;

    inline void copyTo(Container& other);
    inline void moveTo(Rider& other);
    void copySerieTo(Container& other);
    void moveSerieTo(Rider& other);
    inline bool isEndOfSerie() const;
    inline const value_type& getElement() const;
    void reset();

  protected:
    iterator _it;
    Container* _container_ptr {nullptr};
    static constexpr Comparator _comp {};
    bool _is_end_of_serie {true};
};

template <typename Container, typename Comparator>
    requires IsValidContainer<Container>
Rider<Container, Comparator>::Rider(Container& container) : _it {container.begin()}, _container_ptr {&container} {}

template <typename Container, typename Comparator>
    requires IsValidContainer<Container>
Rider<Container, Comparator>& Rider<Container, Comparator>::operator=(Container& container) {
    _it = container.begin();
    _container_ptr = &container;
    _is_end_of_serie = true;
    return *this;
}

template <typename Container, typename Comparator>
    requires IsValidContainer<Container>
Rider<Container, Comparator>::operator bool() const {
    return _it != _container_ptr->end();
}

template <typename Container, typename Comparator>
    requires IsValidContainer<Container>
void Rider<Container, Comparator>::copyTo(Container& other) {
    if (_it == _container_ptr->end()) [[unlikely]]
        throw std::runtime_error("Out of bounds");

    iterator cur_iter {_it++};
    other.push_back(*cur_iter);

    _is_end_of_serie = (_it == _container_ptr->end() || (!_comp(*cur_iter, *_it)));
}

template <typename Container, typename Comparator>
    requires IsValidContainer<Container>
void Rider<Container, Comparator>::moveTo(Rider& other) {
    if (_it == _container_ptr->end()) [[unlikely]]
        throw std::runtime_error("Out of bounds");

    *other._it = std::move(*_it++);
    _is_end_of_serie = (_it == _container_ptr->end() || (!_comp(*other._it, *_it)));
    ++other._it;
}

template <typename Container, typename Comparator>
    requires IsValidContainer<Container>
void Rider<Container, Comparator>::copySerieTo(Container& other) {
    if (_it == _container_ptr->end()) [[unlikely]]
        throw std::runtime_error("Out of bounds");
    do {
        copyTo(other);
    } while (!_is_end_of_serie);
}

template <typename Container, typename Comparator>
    requires IsValidContainer<Container>
void Rider<Container, Comparator>::moveSerieTo(Rider& other) {
    if (_it == _container_ptr->end()) [[unlikely]]
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
const typename Rider<Container, Comparator>::value_type& Rider<Container, Comparator>::getElement() const {
    return *_it;
}

template <typename Container, typename Comparator>
    requires IsValidContainer<Container>
void Rider<Container, Comparator>::reset() {
    _it = _container_ptr->begin();
}
