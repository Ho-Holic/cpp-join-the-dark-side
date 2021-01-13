#include "Protest.hpp"
#include "CycleValue.hpp"


void testCycleValue()
{
    { // up
        CycleValue<int> layer { 3 };
        printTest("Test Initialized", compareEqual(layer.value(), 0));

        layer.up();
        printTest("Test Inc 1", compareEqual(layer.value(), 1));

        layer.up();
        printTest("Test Inc 2", compareEqual(layer.value(), 2));

        layer.up();
        printTest("Test Inc 3 (transition)", compareEqual(layer.value(), 0));

        layer.up();
        printTest("Test Inc 4", compareEqual(layer.value(), 1));

        layer.up();
        printTest("Test Inc 5", compareEqual(layer.value(), 2));
    }

    { // down
        CycleValue<int> layer { 4 };
        printTest("Test Initialized", compareEqual(layer.value(), 0));

        layer.down();
        printTest("Test Dec 1 (transition)", compareEqual(layer.value(), 3));

        layer.down();
        printTest("Test Dec 2", compareEqual(layer.value(), 2));

        layer.down();
        printTest("Test Dec 3 ", compareEqual(layer.value(), 1));

        layer.down();
        printTest("Test Dec 4", compareEqual(layer.value(), 0));

        layer.down();
        printTest("Test Dec 5 (transition)", compareEqual(layer.value(), 3));
    }
}
