
#include "Protest.hpp"
#include "Random.hpp"

void testRandom()
{
    std::vector<int> data = {
        Random::uniform(100),
        Random::uniform(50),
    };

    for (auto value : data) {
        std::cout << value << std::endl;
    }

//    Random::uniformCall({
//        []() ->void { std::cout << "first: " << std::endl; },
//        []() ->void { std::cout << "second: " << std::endl; },
//    });
}
