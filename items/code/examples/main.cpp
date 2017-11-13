#include <iostream>
#include "MirrorMap.hpp"
#include "EnumFlattener.hpp"
#include "Shadow.hpp"


void testMirrorMap()
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;

    enum class Color
    {
        RED,
        GREEN,
        BLUE
    };

    auto map = makeMirrorMap<Color, std::string>({
                                                     { Color::RED, "color_red" },
                                                     { Color::GREEN, "color_green" },
                                                     { Color::BLUE, "color_blue" },
                                                 });

    std::cout << static_cast<int>(map("color_blue", Color::GREEN)) << std::endl;
}

void testEnumFlattener()
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;

    enum class Color { RED, GREEN, BLUE, ENUM_END };
    enum class Size { SMALL, MEDIUM, LARGE, ENUM_END };
    enum class Shape { RECT, ROUND, ENUM_END };

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
}

void testShadow() {

    std::cout << __PRETTY_FUNCTION__ << std::endl;

    struct Currency { int i; };

    Shadow<std::string, int, Currency> price;

    price = "10";
    price = 11;
    price = Currency{12};

    std::cout << static_cast<std::string>(price) << std::endl;
    std::cout << static_cast<int>(price) << std::endl;
    std::cout << static_cast<Currency>(price).i << std::endl;
}

int main() {
    enum class Color { RED, GREEN, BLUE, ENUM_END };

    auto print = [](const std::string& data) {
        std::cout << data << std::endl;
    };

    FlattenEnums<Color, bool> flattenEnums;

    auto input = flattenEnums(Color::GREEN, true);
    switch (input) {
    case flattenEnums(Color::RED, true): print("red true"); break;
    case flattenEnums(Color::RED, false): print("red false"); break;
    case flattenEnums(Color::GREEN, true): print("green true"); break;
    case flattenEnums(Color::GREEN, false): print("green false"); break;
    case flattenEnums(Color::BLUE, true): print("blue true"); break;
    case flattenEnums(Color::BLUE, false): print("blue false"); break;
    }

    return 0;
}
