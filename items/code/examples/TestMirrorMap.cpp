#include <iostream>

#include "MirrorMap.hpp"

void testMirrorMap()
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;

    enum Color
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

    std::cout << map("color_blue", Color::GREEN) << std::endl;

    for (auto i : map.keysAs<std::string>()) {
        std::cout << i << ", ";
    }
    std::cout << std::endl;
}

int main() {
    testMirrorMap();
    return 0;
}
