
#include <iostream>
#include "DimensionMap.hpp"

struct Point {
    Point() : x(0), y(0) {}
    Point(int x, int y) : x(x), y(y) {}
    int x;
    int y;
};

// bool operator< (const Point& left, const Point& right) {
//     if (left.x == right.x) {
//         return left.y < right.y;
//     }
//     return left.x < right.x;
// }




void testDimensionMap() {

    auto data = makeDimensionMap<std::string, int, Point>({
      {"cat", 42, {42, 12}},
      {"dog", 12, {1, 1}},
      {"parrot", 13, {8, 16}},
    });

   //{
   //    auto g = data(Point(42, 12));
   //    std::string s = g;
   //    int i = g;
   //    Point p = g;

   //    std::cout << ">Cat" << std::endl;
   //    std::cout << "String: " <<  s << std::endl;
   //    std::cout << "Integer: " <<  i << std::endl;
   //    std::cout << "Point: " <<  p.x << "," << p.y << std::endl;
   //}

    {
        auto g = data(12);
        std::string s = g;
        int i = g;
        Point p = g;

        std::cout << ">Dog" << std::endl;
        std::cout << "String: " <<  s << std::endl;
        std::cout << "Integer: " <<  i << std::endl;
        std::cout << "Point: " <<  p.x << "," << p.y << std::endl;
        std::cout << "Bad search: " <<  data(14, std::string("ball")) << std::endl;
    }

    {
        auto g = data("parrot");
        std::string s = g;
        int i = g;
        Point p = g;

        std::cout << ">Parrot" << std::endl;
        std::cout << "String: " <<  s << std::endl;
        std::cout << "Integer: " <<  i << std::endl;
        std::cout << "Point: " <<  p.x << "," << p.y << std::endl;
    }

}
