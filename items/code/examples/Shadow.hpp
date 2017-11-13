#ifndef SHADOW_HPP
#define SHADOW_HPP

#include <stdexcept>
#include <utility>

template <typename... Ts>
class Shadow
{
public:
};

template <>
class Shadow<>
{
public:
};

template <typename T, typename... Ts>
class Shadow<T, Ts...> : public Shadow<Ts...>
{
    using Base = Shadow<Ts...>;
public:

    using Base::operator=;

    Shadow& operator=(T&& t){
        value = std::forward<T>(t);
        initialized = true;
    }


    operator T&() {
        if (!initialized) throw std::logic_error("bad shadow value");
        return value;
    }

    T value;
    bool initialized = false;
};




#endif // SHADOW_HPP
