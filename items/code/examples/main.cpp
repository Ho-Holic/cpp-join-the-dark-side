#include <iostream>
#include <tuple>
#include <map>
#include <cassert>


template <size_t N, typename... Ts>
struct LinkedTypes  {
    //
};

//template <>
//struct LinkedTypes<0> {
//    //
//};


template <size_t N, typename C>
struct LinkedTypes<N, C> {
    LinkedTypes(const C (&c)[N])  {
        for (size_t i = 0; i < N; ++i) {
            m_storage[i] = c[i];
        }
    }
    C m_storage[N];
};

template <typename C>
struct LinkedTypesGetter  {
    LinkedTypesGetter(const C& data) : m_data(data) {}

    template <typename T>
    T get() {
        return std::get<T>(m_data);
    }

    C m_data;
};

//template <typename T, typename... Ts>
//struct LinkedTypesGetter<T, Ts...> : LinkedTypesGetter<Ts...> {
//    LinkedTypesGetter(std::tuple<T, Ts...> data) : LinkedTypesGetter<Ts...>(data) {}
//    operator T() {
//        return std::get<T>(m_data);
//    }
//};

template <size_t N, typename C, typename U1, typename... Us>
struct LinkedTypes<N, C, U1, Us...> : LinkedTypes<N, C, Us...> {

    using Base = LinkedTypes<N, C, Us...>;
    using Base::m_storage;

    LinkedTypes(const C (&c)[N]) : LinkedTypes<N, C, Us...>(c) {
        for (size_t i = 0; i < N; ++i) {
            m_layer.insert(std::make_pair(std::get<U1>(c[i]), i));
        }
    }

    LinkedTypesGetter<C> operator()(const U1& key) {
        auto found = m_layer.find(key);
        assert(found != m_layer.end());

        auto tupleRow = m_storage[found->second];
        return LinkedTypesGetter<C>(tupleRow);
    }
    std::map<U1, size_t> m_layer;
};

template <size_t N, typename... Ts>
auto makeLinkedTypes(const std::tuple<Ts...>(&items)[N]) -> LinkedTypes<N, std::tuple<Ts...>, Ts...> {
    LinkedTypes<N, std::tuple<Ts...>, Ts...> d ( items );
    return d;
}

// client

struct Point {
    //Point(int x, int y) : x(x), y(y) {}
    int x;
    int y;
};

bool operator< (const Point& left, const Point& right) {
    if (left.x == right.x) {
        return left.y < right.y;
    }
    return left.x < right.x;
}

int main() {


    auto map = makeLinkedTypes<2, std::string, int, Point>({
      {"cat", 42, {42, 12}},
      {"dog", 12, {1, 1}},
    });

    Point p = map(std::string("cat")).get<Point>();

    std::cout << "result: " <<  p.x << "," << p.y << std::endl;

    return 0;
}
