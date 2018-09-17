#ifndef DIMENSIONMAP_HPP
#define DIMENSIONMAP_HPP

#include <tuple>
#include <map>
#include <cassert>

#include "Traits.hpp"

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

// trait with useful types
template <size_t N, typename... Ts>
struct DimensionTrait
{
    enum : size_t { dimensions = N };
    using tuple_type = std::tuple<Ts...>;
    using result_type = DimensionMapResult<tuple_type, Ts...>;
};

// main template
template <bool B, typename... Ts>
struct DimensionMap  {
    //
};

template <bool B, typename DT>
struct DimensionMap<B, DT> {
    DimensionMap(const typename DT::tuple_type (&c)[DT::dimensions]) {
        for (size_t i = 0; i < DT::dimensions; ++i) {
            m_storage[i] = c[i];
        }
    }

    void operator()() {
        // to make 'using Base::operator();' work
    }

    typename DT::tuple_type m_storage[DT::dimensions];
};

template <bool B, typename DT, typename U1, typename... Us>
struct DimensionMap<B, DT, U1, Us...>
:   DimensionMap<has_operator_less<U1>::value, DT, U1, U1, Us...> {

   using Base = DimensionMap<has_operator_less<U1>::value, DT, U1, U1, Us...>;
   using Base::m_storage;
   using Base::operator();

   DimensionMap(const typename DT::tuple_type (&c)[DT::dimensions]) : DimensionMap<has_operator_less<U1>::value, DT, U1, U1, Us...>(c) {
       //
   }
};

// With Less Operator Version
template <bool B, typename DT, typename U1, typename... Us>
struct DimensionMap<B, DT, U1, U1, Us...> : DimensionMap<B, DT, Us...> {

    using Base = DimensionMap<B, DT, Us...>;
    using Base::m_storage;
    using Base::operator();

    DimensionMap(const typename DT::tuple_type (&c)[DT::dimensions]) : DimensionMap<B, DT, Us...>(c) {
        for (size_t i = 0; i < DT::dimensions; ++i) {
            m_layer.insert(std::make_pair(std::get<U1>(c[i]), i));
        }
    }

    typename DT::result_type operator()(const U1& key) {
        auto found = m_layer.find(key);
        assert(found != m_layer.end());

        auto tupleRow = m_storage[found->second];
        return typename DT::result_type(tupleRow);
    }

    template <typename Any>
    Any operator()(const U1& key, const Any& fallback) {
        auto found = m_layer.find(key);
        return found != m_layer.end() ? std::get<Any>(m_storage[found->second]) : fallback;
    }

    std::map<U1, size_t> m_layer;
};

// Without Less operator Version
template <typename DT, typename U1, typename... Us>
struct DimensionMap<false, DT, U1, U1, Us...> : DimensionMap<false, DT, Us...> {

    using Base = DimensionMap<false, DT, Us...>;
    using Base::m_storage;
    using Base::operator();

    DimensionMap(const typename DT::tuple_type (&c)[DT::dimensions]) : DimensionMap<false, DT, Us...>(c) {
        //
    }
    void foo(){} // what!?
};

// client function
template <typename... Ts, size_t N>
auto makeDimensionMap(const std::tuple<Ts...>(&items)[N]) -> DimensionMap<false, DimensionTrait<N, Ts...>, Ts...> {
    DimensionMap<false, DimensionTrait<N, Ts...>, Ts...> d ( items );
    return d;
}

#endif // DIMENSIONMAP_HPP
