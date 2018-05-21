#ifndef ENUMFLATTENER_HPP
#define ENUMFLATTENER_HPP

#include <vector>

template <typename Enum>
constexpr size_t enumValue(Enum e)
{
    return static_cast<size_t>(e);
}

template <>
constexpr size_t enumValue<bool>(bool e)
{
    return e ? 1 : 0;
}


template <typename Enum>
constexpr size_t enumSize()
{
    return enumValue(Enum::ENUM_END);
}

template <>
constexpr size_t enumSize<bool>()
{
    return 2;
}

template <typename Enum1>
constexpr size_t enumOffset(size_t acc, Enum1 e)
{
    return acc * enumSize<Enum1>() + enumValue(e);
}

template <typename Enum1, typename... Enums>
constexpr size_t enumOffset(size_t acc, Enum1 e1, Enums... enums)
{
    return enumOffset(acc * enumSize<Enum1>() + enumValue(e1), enums...);
}



template <typename... Enums>
struct FlattenEnums
{
    constexpr size_t operator()(Enums... all) {
        return enumOffset(0, all...);
    }
};

#endif // ENUMFLATTENER_HPP
