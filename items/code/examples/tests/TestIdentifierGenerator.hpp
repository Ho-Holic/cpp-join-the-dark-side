#ifndef TESTIDENTIFIERGENERATOR_HPP
#define TESTIDENTIFIERGENERATOR_HPP

#include <vector>
#include <iostream>
#include "IdentifierGenerator.hpp"
#include "Protest.hpp"

void testIdentifierGenerator()
{
    std::vector<int> data = {
            generateId<>(),
            generateId<>(),
            generateId<>(),
            generateId<>(),
            generateId<>(),
    };

    for (auto value : data) {
            std::cout << value << ", ";
    }
}

#endif // TESTIDENTIFIERGENERATOR_HPP
