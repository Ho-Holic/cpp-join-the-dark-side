#include <iostream>
#include <tuple>
#include <map>
#include <cassert>



template <typename... Ts>
struct LinkedTypesGetter  {
};

template <typename C>
struct LinkedTypesGetter<C>  {
    LinkedTypesGetter(const C& data) : m_data(data) {}

    template <typename T>
    T get() {
        return std::get<T>(m_data);
    }

    C m_data;
};


template <typename C, typename U1, typename... Us>
struct LinkedTypesGetter<C, U1, Us...> : LinkedTypesGetter<C, Us...>  {

    using Base = LinkedTypesGetter<C, Us...>;
    using Base::m_data;
    //using Base::operator Us...; // c++17

    LinkedTypesGetter(const C& data) : LinkedTypesGetter<C, Us...>(data) {}

    operator U1() {
        return std::get<U1>(m_data);
    }
};

template <size_t N, typename... Ts>
struct LinkedTypes  {
    //
};

template <size_t N, typename C, typename G>
struct LinkedTypes<N, C, G> {
    LinkedTypes(const C (&c)[N]) {
        for (size_t i = 0; i < N; ++i) {
            m_storage[i] = c[i];
        }
    }

    void operator()() {
        // to make 'using Base::operator();' work
    }

    C m_storage[N];
};

template <size_t N, typename C, typename G, typename U1, typename... Us>
struct LinkedTypes<N, C, G, U1, Us...> : LinkedTypes<N, C, G, Us...> {

    using Base = LinkedTypes<N, C, G, Us...>;
    using Base::m_storage;
    using Base::operator();

    LinkedTypes(const C (&c)[N]) : LinkedTypes<N, C, G, Us...>(c) {
        for (size_t i = 0; i < N; ++i) {
            m_layer.insert(std::make_pair(std::get<U1>(c[i]), i));
        }
    }

    G operator()(const U1& key) {
        auto found = m_layer.find(key);
        assert(found != m_layer.end());

        auto tupleRow = m_storage[found->second];
        return G(tupleRow);
    }
    std::map<U1, size_t> m_layer;
};

template <typename... Ts, size_t N>
auto makeLinkedTypes(const std::tuple<Ts...>(&items)[N])
-> LinkedTypes<N, std::tuple<Ts...>, LinkedTypesGetter<std::tuple<Ts...>, Ts...>, Ts...> {
    LinkedTypes<N, std::tuple<Ts...>, LinkedTypesGetter<std::tuple<Ts...>, Ts...>, Ts...> d ( items );
    return d;
}

// client

struct Point {
    Point() : x(0), y(0) {}
    Point(int x, int y) : x(x), y(y) {}
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


    auto data = makeLinkedTypes<std::string, int, Point>({
      {"cat", 42, {42, 12}},
      {"dog", 12, {1, 1}},
      {"parrot", 13, {8, 16}},
    });

    {
        auto g = data(Point(42, 12));
        std::string s = g;
        int i = g;
        Point p = g;

        std::cout << ">Cat" << std::endl;
        std::cout << "String: " <<  s << std::endl;
        std::cout << "Integer: " <<  i << std::endl;
        std::cout << "Point: " <<  p.x << "," << p.y << std::endl;
    }

    {
        auto g = data(12);
        std::string s = g;
        int i = g;
        Point p = g;

        std::cout << ">Dog" << std::endl;
        std::cout << "String: " <<  s << std::endl;
        std::cout << "Integer: " <<  i << std::endl;
        std::cout << "Point: " <<  p.x << "," << p.y << std::endl;
    }

    {
        auto g = data("parrot");
        std::string s = g;
        int i = g;
        Point p = g;

        std::cout << ">Parrot" << std::endl;
        std::cout << "String: " <<  s << std::endl;
        std::cout << "Integer: " <<  i << std::endl;
        std::cout << "Point: " <<  p.x << "," << p.y << std::endl;
    }


    return 0;
}
