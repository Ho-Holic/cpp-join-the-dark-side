```cpp
#include <iostream>

template <typename Enum>
constexpr size_t enumValue(Enum e)
{
    return static_cast<size_t>(e);
}

template <typename Enum>
constexpr size_t enumSize()
{
    return enumValue(Enum::ENUM_END);
}

template <typename Enum1, typename... Enums>
constexpr size_t enumOffset(size_t acc, Enum1 e1, Enums... enums)
{
    return enumOffset(acc * enumSize<Enum1>() + enumValue(e1), enums...);
}

template <typename Enum1>
constexpr size_t enumOffset(size_t acc, Enum1 e)
{
    return acc * enumSize<Enum1>() + enumValue(e);
}

template <typename... Enums>
struct FlattenEnums 
{
    constexpr size_t operator()(Enums... all) { 
        return enumOffset(0, all...);
    }
};

enum class Color { RED, GREEN, BLUE, ENUM_END };
enum class Size { SMALL, MEDIUM, LARGE, ENUM_END };
enum class Shape { RECT, ROUND, ENUM_END };

int main() {
    auto print = [](const std::string& data) {
        std::cout << data << std::endl;
    };
    FlattenEnums<Color, Size, Shape> flattenEnums;
    auto input = flattenEnums(Color::RED, Size::MEDIUM, Shape::RECT);
    switch (input) {
        case flattenEnums(Color::RED, Size::SMALL, Shape::RECT): print("rs[]"); break;
        case flattenEnums(Color::RED, Size::MEDIUM, Shape::RECT): print("rm[]"); break;
        case flattenEnums(Color::RED, Size::LARGE, Shape::RECT): print("rl[]"); break;
        case flattenEnums(Color::RED, Size::SMALL, Shape::ROUND): print("rs()"); break;
        case flattenEnums(Color::RED, Size::MEDIUM, Shape::ROUND): print("rm()"); break;
        case flattenEnums(Color::RED, Size::LARGE, Shape::ROUND): print("rl()"); break;
        
        case flattenEnums(Color::GREEN, Size::SMALL, Shape::RECT): print("gs[]"); break;
        case flattenEnums(Color::GREEN, Size::MEDIUM, Shape::RECT): print("gm[]"); break;
        case flattenEnums(Color::GREEN, Size::LARGE, Shape::RECT): print("gl[]"); break;
        case flattenEnums(Color::GREEN, Size::SMALL, Shape::ROUND): print("gs()"); break;
        case flattenEnums(Color::GREEN, Size::MEDIUM, Shape::ROUND): print("gm()"); break;
        case flattenEnums(Color::GREEN, Size::LARGE, Shape::ROUND): print("gl()"); break;
        
        case flattenEnums(Color::BLUE, Size::SMALL, Shape::RECT): print("bs[]"); break;
        case flattenEnums(Color::BLUE, Size::MEDIUM, Shape::RECT): print("bm[]"); break;
        case flattenEnums(Color::BLUE, Size::LARGE, Shape::RECT): print("bl[]"); break;
        case flattenEnums(Color::BLUE, Size::SMALL, Shape::ROUND): print("bs()"); break;
        case flattenEnums(Color::BLUE, Size::MEDIUM, Shape::ROUND): print("bm()"); break;
        case flattenEnums(Color::BLUE, Size::LARGE, Shape::ROUND): print("bl()"); break;
    }
    return 0;
}
```
