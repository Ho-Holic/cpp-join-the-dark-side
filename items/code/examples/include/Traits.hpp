#ifndef TRAITS_HPP
#define TRAITS_HPP

#include <utility>

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

#endif // TRAITS_HPP
