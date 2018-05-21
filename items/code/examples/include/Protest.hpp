#ifndef PROTEST_HPP
#define PROTEST_HPP

#include <iostream>
#include <iomanip>

template <typename T >
inline bool compareEqual(const T& t1, const T& t2) {
    return t1 == t2;
}

template <typename C>
inline bool compareCollections(const C& c1arg, const C& c2arg) {

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

inline void printTest(const std::string& name, bool success) {
    std::cout << "| " << std::setw(40) << name << " | " << (success ? "pass" : "fail") << std::endl;
}

#endif // PROTEST_HPP
