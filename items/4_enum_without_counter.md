
```cpp
#include <iostream>

template <typename T>
int enum_size();

#define CONCAT_(x,y) x##y
#define CONCAT(x,y) CONCAT_(x,y)

#define LAST(X) }; \
template<> int enum_size<decltype(X)>() { return static_cast<int>(X) + 1; } struct CONCAT(enum_size_unique_, __COUNTER__) {

enum class Test{
    One, 
    Two,
    LAST(Test::Two)
};

enum class Dummy {
    Cat, 
    Dog,
    Bird,
    LAST(Dummy::Bird)
};

int main(){

    std::cout << enum_size<Test>() << "\n";
    std::cout << enum_size<Dummy>() << "\n";
    
    return 0;
}
```
