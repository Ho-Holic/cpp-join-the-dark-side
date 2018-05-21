#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <random>
#include <algorithm>
#include <iterator>
#include <cmath>
#include <cassert>
#include <initializer_list>


class Random
{
public:
    template <typename T> static T uniform();
    template <typename T> static T uniform(T to);
    template <typename T> static T uniform(T from, T to);
    template <typename T> static T uniformf(T from, T to);
    template <typename T> static T probabilityf();
    template <typename T> static T probability();

    static bool yesNo();

    template <typename T>
    static T normalf(T mean, T stddev);

    template <typename C>
    static typename C::value_type uniformFrom(const C& collection);

    template <class RandomAccessIterator>
    static void shuffle(RandomAccessIterator first, RandomAccessIterator last);

    template <typename Result, typename... Args>
    static Result uniformCall(std::initializer_list<Result(Args...)> functions, Args&&... args)
    {
        auto index = uniform<size_t>(functions.size() - 1);
        return functions[index](std::forward(args)...);
    }

private:
    static std::random_device& randomDevice();
};

// implementation


template <typename T>
T Random::normalf(T mean, T stddev)
{
    static_assert(std::is_floating_point<T>::value, "Floating point required.");
    std::normal_distribution<T> dis { mean, stddev };
    return dis(randomDevice());
}

inline bool Random::yesNo()
{
    return static_cast<bool>(Random::uniform<int>(0, 1));
}

template <typename T>
T Random::probability()
{
    static_assert(std::is_integral<T>::value, "Integral required.");
    std::uniform_int_distribution<T> dis(static_cast<T>(0), static_cast<T>(100));
    return dis(randomDevice());
}

template <typename T>
T Random::probabilityf()
{
    static_assert(std::is_floating_point<T>::value, "Floating point required.");
    std::uniform_real_distribution<T> dis(static_cast<T>(0.f),
                                          static_cast<T>(std::nextafter(1.f, std::numeric_limits<T>::max())));
    // nextafter used to simulate closed interval
    return dis(randomDevice());
}

template <typename T>
T Random::uniform()
{
    static_assert(std::is_integral<T>::value, "Integral required.");

    std::uniform_int_distribution<T> dis;
    return dis(randomDevice());
}

template <typename T>
T Random::uniform(T to)
{
    static_assert(std::is_integral<T>::value, "Integral required.");

    std::uniform_int_distribution<T> dis(static_cast<T>(0), to);
    return dis(randomDevice());
}

template <typename T>
T Random::uniform(T from, T to)
{
    static_assert(std::is_integral<T>::value, "Integral required.");

    std::uniform_int_distribution<T> dis(from, to);
    return dis(randomDevice());
}

template <typename T>
T Random::uniformf(T from, T to)
{
    static_assert(std::is_floating_point<T>::value, "Floating point required.");

    std::uniform_real_distribution<T> dis(from, to);
    return dis(randomDevice());
}

template <class RandomAccessIterator>
void Random::shuffle(RandomAccessIterator first, RandomAccessIterator last)
{
    //
    // std::random_shuffle is depricated and removed in C++17, don't use it
    //
    // https://meetingcpp.com/blog/items/stdrandom_shuffle-is-deprecated.html
    //
    std::shuffle(first, last, randomDevice());
}

//
// Don't change type 'C::value_type' to reference type, because we can
// pick item from collection on rvalue object e.g.'uniformFrom(getMyFancyVector())'
//
template <typename C>
typename C::value_type Random::uniformFrom(const C& collection)
{
    //
    // TODO: uncomment this line when C++17 would be available
    //
    // auto offset = uniform(std::size(collection) - 1);
    //

    Z_ASSERT(!collection.empty());

    auto offset = uniform(collection.size() - 1);

    auto it = collection.begin();
    std::advance(it, static_cast<long>(offset));

    Z_ASSERT(it != collection.end());

    return *it;
}

inline std::random_device& Random::randomDevice()
{
    static std::random_device s_device;
    return s_device;
}

#endif // RANDOM_HPP
