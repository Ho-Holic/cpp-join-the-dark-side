#include "Protest.hpp"
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

    printTest("String To Color: Red", compareEqual(map("color_red", Color::RED), Color::RED));
    printTest("String To Color: Green", compareEqual(map("color_green", Color::RED), Color::GREEN));
    printTest("String To Color: Blue", compareEqual(map("color_blue", Color::RED), Color::BLUE));

    printTest("String To Color no default: Red", compareEqual(map("color_red"), Color::RED));
    printTest("String To Color no default: Green", compareEqual(map("color_green"), Color::GREEN));
    printTest("String To Color no default: Blue", compareEqual(map("color_blue"), Color::BLUE));

    printTest("Bad search: Red", compareEqual(map("color_reed", Color::RED), Color::RED));
    printTest("Bad search: empty string", compareEqual(map("", Color::RED), Color::RED));
    printTest("Bad search: one symbol", compareEqual(map("c", Color::RED), Color::RED));

    printTest("Extract keys: Enum", compareCollections<std::vector<Color>>(map.keysAs<Color>(), { Color::RED, Color::GREEN, Color::BLUE }));
    printTest("Extract keys: String", compareCollections<std::vector<std::string>>(map.keysAs<std::string>(), { "color_red", "color_green", "color_blue" }));


    auto map2 = makeMirrorMap<Color, NotComparable<int>>({
        { Color::RED, NotComparable<int>{42} },
        { Color::GREEN, NotComparable<int>{300} },
        { Color::BLUE, NotComparable<int>{123} },
    });

    printTest("Not comparable: 42", compareEqual(map2(Color::RED).data, 42));
    printTest("Not comparable: 300", compareEqual(map2(Color::GREEN).data, 300));
    printTest("Not comparable: 123", compareEqual(map2(Color::BLUE).data, 123));
}
