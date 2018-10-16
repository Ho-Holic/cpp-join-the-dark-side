#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <random>
#include <algorithm>
#include <iterator>
#include <cmath>
#include <cassert>
#include <initializer_list>


struct FastRandomTraits
{
    using GeneratorType = std::mt19937;
    static GeneratorType& generator();
};

//
// if you want one generator for all translation units, please use custom traits
//
inline std::mt19937& FastRandomTraits::generator()
{
    static std::random_device s_device;
    static std::mt19937 s_fastGenerator(s_device());
    return s_fastGenerator;
}


template <typename RandomTraits>
class RandomBase
{
public:
    template <typename T>
    static T uniform();
    template <typename T>
    static T uniform(T to);
    template <typename T>
    static T uniform(T from, T to);
    template <typename T>
    static T probability();

    template <typename T>
    static T uniformf();
    template <typename T>
    static T uniformf(T to);
    template <typename T>
    static T uniformf(T from, T to);
    template <typename T>
    static T probabilityf();

    static bool yesNo();

    template <typename T>
    static T normalf(T mean, T stddev);

    template <typename C>
    static typename C::value_type uniformFrom(const C& collection);

    template <typename C>
    static typename C::value_type weightedUniformFrom(const std::vector<float>& weights, const C& collection);

    template <class RandomAccessIterator>
    static void shuffle(RandomAccessIterator first, RandomAccessIterator last);

    template <typename T>
    static T triangularf(T a, T b, T c);
};


// implementation

template <typename RandomTraits>
template <typename T>
T RandomBase<RandomTraits>::triangularf(T a, T b, T c)
{
    static_assert(std::is_floating_point<T>::value, "Floating point required.");

    //
    // https://en.wikipedia.org/wiki/Triangular_distribution#Generating_triangular-distributed_random_variates
    //
    const auto u = RandomBase::uniformf<T>();
    const auto f = (c - a) / (b - a);

    if (u < f) {
        return a + std::sqrt(u * (b - a) * (c - a));
    } else {
        return b - std::sqrt((1 - u) * (b - a) * (b - c));
    }
}

template <typename RandomTraits>
template <typename T>
T RandomBase<RandomTraits>::normalf(T mean, T stddev)
{
    static_assert(std::is_floating_point<T>::value, "Floating point required.");
    std::normal_distribution<T> dis{ mean, stddev };
    return dis(RandomTraits::generator());
}

template <typename RandomTraits>
inline bool RandomBase<RandomTraits>::yesNo() { return static_cast<bool>(uniform<int>(0, 1)); }

template <typename RandomTraits>
template <typename T>
T RandomBase<RandomTraits>::probability()
{
    static_assert(std::is_integral<T>::value, "Integral required.");
    std::uniform_int_distribution<T> dis(static_cast<T>(0), static_cast<T>(100));
    return dis(RandomTraits::generator());
}

template <typename RandomTraits>
template <typename T>
T RandomBase<RandomTraits>::probabilityf()
{
    static_assert(std::is_floating_point<T>::value, "Floating point required.");
    std::uniform_real_distribution<T> dis(
        static_cast<T>(0.f), static_cast<T>(std::nextafter(1.f, std::numeric_limits<T>::max())));
    // nextafter used to simulate closed interval
    return dis(RandomTraits::generator());
}

template <typename RandomTraits>
template <typename T>
T RandomBase<RandomTraits>::uniform()
{
    static_assert(std::is_integral<T>::value, "Integral required.");

    std::uniform_int_distribution<T> dis;
    return dis(RandomTraits::generator());
}

template <typename RandomTraits>
template <typename T>
T RandomBase<RandomTraits>::uniform(T to)
{
    static_assert(std::is_integral<T>::value, "Integral required.");

    std::uniform_int_distribution<T> dis(static_cast<T>(0), to);
    return dis(RandomTraits::generator());
}

template <typename RandomTraits>
template <typename T>
T RandomBase<RandomTraits>::uniform(T from, T to)
{
    static_assert(std::is_integral<T>::value, "Integral required.");

    std::uniform_int_distribution<T> dis(from, to);
    return dis(RandomTraits::generator());
}

template <typename RandomTraits>
template <typename T>
T RandomBase<RandomTraits>::uniformf()
{
    static_assert(std::is_floating_point<T>::value, "Floating point required.");

    //
    // INFO: Don't add nextafter, correct range is (0, 1]
    //
    std::uniform_real_distribution<T> dis(static_cast<T>(0), static_cast<T>(1));
    return dis(RandomTraits::generator());
}

template <typename RandomTraits>
template <typename T>
T RandomBase<RandomTraits>::uniformf(T to)
{
    static_assert(std::is_floating_point<T>::value, "Floating point required.");

    std::uniform_real_distribution<T> dis(
        static_cast<T>(0), static_cast<T>(std::nextafter(to, std::numeric_limits<T>::max())));
    return dis(RandomTraits::generator());
}

template <typename RandomTraits>
template <typename T>
T RandomBase<RandomTraits>::uniformf(T from, T to)
{
    static_assert(std::is_floating_point<T>::value, "Floating point required.");

    std::uniform_real_distribution<T> dis(from, to);
    return dis(RandomTraits::generator());
}

template <typename RandomTraits>
template <class RandomAccessIterator>
void RandomBase<RandomTraits>::shuffle(RandomAccessIterator first, RandomAccessIterator last)
{
    //
    // std::random_shuffle is depricated and removed in C++17, don't use it
    //
    // https://meetingcpp.com/blog/items/stdrandom_shuffle-is-deprecated.html
    //
    std::shuffle(first, last, RandomTraits::generator());
}

template <typename RandomTraits>
template <typename C>
typename C::value_type RandomBase<RandomTraits>::weightedUniformFrom(const std::vector<float>& weights, const C& collection)
{
    std::discrete_distribution<size_t> dis(weights.begin(), weights.end());

    auto offset = dis(RandomTraits::generator());

    auto it = collection.begin();
    std::advance(it, static_cast<long>(offset));

    assert(it != collection.end());

    return *it;
}

//
// Don't change type 'C::value_type' to reference type, because we can
// pick item from collection on rvalue object e.g.'uniformFrom(getMyFancyVector())'
//
template <typename RandomTraits>
template <typename C>
typename C::value_type RandomBase<RandomTraits>::uniformFrom(const C& collection)
{
    //
    // TODO: uncomment this line when C++17 would be available
    //
    // auto offset = uniform(std::size(collection) - 1);
    //

    assert(!collection.empty());

    auto offset = uniform(collection.size() - 1);

    auto it = collection.begin();
    std::advance(it, static_cast<long>(offset));

    assert(it != collection.end());

    return *it;
}

//
// use types below
//
using Random = RandomBase<FastRandomTraits>;

#endif // RANDOM_HPP
