#include <iostream>
#include <tuple>
#include <map>
#include <cassert>

// check for less operator
template<class T, class EqualTo>
struct has_operator_less_detail
{
    template<class U, class V>
    static auto test(U*) -> decltype(std::declval<U>() < std::declval<V>());
    template<typename, typename>
    static auto test(...) -> std::false_type;

    using type = typename std::is_same<bool, decltype(test<T, EqualTo>(0))>::type;
};

template<class T, class EqualTo = T>
struct has_operator_less : has_operator_less_detail<T, EqualTo>::type {};

// proxy for retrieving result
template <typename... Ts>
struct DimensionMapResult  {
};

template <typename C>
struct DimensionMapResult<C>  {
    DimensionMapResult(const C& data) : m_data(data) {}

    template <typename T>
    T get() {
        return std::get<T>(m_data);
    }

    C m_data;
};


template <typename C, typename U1, typename... Us>
struct DimensionMapResult<C, U1, Us...> : DimensionMapResult<C, Us...>  {

    using Base = DimensionMapResult<C, Us...>;
    using Base::m_data;    

    DimensionMapResult(const C& data) : DimensionMapResult<C, Us...>(data) {}

    operator U1() {
        return std::get<U1>(m_data);
    }
};

// trait for packing template arguments
template <size_t N, typename... Ts>
struct DimensionTrait
{
    enum : size_t { dimensions = N };
    using tuple_type = std::tuple<Ts...>;
    using result_type = DimensionMapResult<tuple_type, Ts...>;
};

// generate getter functions
template <typename DT, typename U1, bool B>
struct DimensionGetFunctions {
    DimensionGetFunctions(const typename DT::tuple_type (&c)[DT::dimensions]) : m_storageRef(c) {
        for (size_t i = 0; i < DT::dimensions; ++i) {
            m_layer.insert(std::make_pair(std::get<U1>(c[i]), i));
        }
    }

    typename DT::result_type operator()(const U1& key) {
        auto found = m_layer.find(key);
        assert(found != m_layer.end());

        auto tupleRow = m_storageRef[found->second];
        return typename DT::result_type(tupleRow);
    }

    std::map<U1, size_t> m_layer;
    const typename DT::tuple_type (&m_storageRef)[DT::dimensions];
};

template <typename DT, typename U1>
struct DimensionGetFunctions<DT, U1, false> {
    void operator()() {
        // to make 'using Base::operator();' work
    }
};

// main container
template <typename... Ts>
struct DimensionMap  {
    //
};

template <typename DT>
struct DimensionMap<DT> {
    DimensionMap(const typename DT::tuple_type (&c)[DT::dimensions]) {
        for (size_t i = 0; i < DT::dimensions; ++i) {
            m_storage[i] = c[i];
        }
    }

    typename DT::tuple_type m_storage[DT::dimensions];
};

// version with getter
template <typename DT, typename U1, typename... Us>
struct DimensionMap<DT, U1, Us...>
:   DimensionMap<DT, Us...>,
    DimensionGetFunctions<DT, U1, has_operator_less<U1>::value> {

    using Base = DimensionMap<DT, Us...>;
    using Base2 = DimensionGetFunctions<DT, U1, has_operator_less<U1>::value>;

    using Base::m_storage;
    using Base2::operator();

    DimensionMap(const typename DT::tuple_type (&c)[DT::dimensions])
    :   DimensionMap<DT, Us...>(c)
    ,   DimensionGetFunctions<DT, U1, has_operator_less<U1>::value>(m_storage) {
//        for (size_t i = 0; i < DT::dimensions; ++i) {
//            m_layer.insert(std::make_pair(std::get<U1>(c[i]), i));
//        }
    }

//    typename DT::result_type operator()(const U1& key) {
//        auto found = m_layer.find(key);
//        assert(found != m_layer.end());

//        auto tupleRow = m_storage[found->second];
//        return typename DT::result_type(tupleRow);
//    }

//    std::map<U1, size_t> m_layer;
};

//template <typename DT, typename U1, typename... Us>
//struct DimensionMap<DT, void, Us...>
//:   DimensionMap<DT, Us...> {

//    using Base = DimensionMap<DT, Us...>;
//    using Base::m_storage;
//    using Base::operator();

//    DimensionMap(const C (&c)[DT::dimensions]) : DimensionMap<DT, Us...>(c) {
//        //
//    }
//};

template <typename... Ts, size_t N>
auto makeDimensionMap(const std::tuple<Ts...>(&items)[N]) -> DimensionMap<DimensionTrait<N, Ts...>, Ts...> {
    DimensionMap<DimensionTrait<N, Ts...>, Ts...> d ( items );
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


    auto data = makeDimensionMap<std::string, int, Point>({
      {"cat", 42, {42, 12}},
      {"dog", 12, {1, 1}},
      {"parrot", 13, {8, 16}},
    });

//    {
//        auto g = data(Point(42, 12));
//        std::string s = g;
//        int i = g;
//        Point p = g;

//        std::cout << ">Cat" << std::endl;
//        std::cout << "String: " <<  s << std::endl;
//        std::cout << "Integer: " <<  i << std::endl;
//        std::cout << "Point: " <<  p.x << "," << p.y << std::endl;
//    }

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
