#include <iostream>
#include <iomanip>

#include "MirrorMap.hpp"

template <typename T >
bool compareEqual(const T& t1, const T& t2) {
    return t1 == t2;
}

template <typename C>
bool compareCollections(const C& c1arg, const C& c2arg) {

    C c1 { c1arg };
    C c2 { c2arg };

    bool isEqual = true;
    while (!c1.empty() && !c2.empty() && isEqual) {
         auto it1 = c1.begin();
         auto it2 = c2.begin();
         isEqual = (*it1 == *it2);
         c1.erase(it1);
         c2.erase(it2);
    }

    if (isEqual) { // if one container is bigger the other
        isEqual = (c1.empty() && c2.empty());
    }

    return isEqual;
}

void printTest(const std::string& name, bool success) {
    std::cout << "| " << std::setw(40) << name << " | " << (success ? "pass" : "fail") << std::endl;
}

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
}

int main() {
    testMirrorMap();
    return 0;
}
