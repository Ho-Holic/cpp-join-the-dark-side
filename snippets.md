# Is Comparable (Not working really)

```cpp
#include <iostream>
#include <type_traits>
#include <vector>

template <class...>
using void_t = void;

template <typename L, typename R, typename = int>
struct is_comparable : std::false_type
{
};

template <typename L, typename R>
struct is_comparable<L, R, decltype(std::declval<L>() == std::declval<R>(), 1)> : std::true_type
{
};

struct Cat{};

int main() 
{	
    std::cout << is_comparable<std::vector<int>, std::vector<int>>::value << "\n";
    std::cout << is_comparable<Cat, Cat>::value << "\n";
    std::cout << is_comparable<std::vector<Cat>, std::vector<Cat>>::value << "\n";
	
    std::vector<Cat> v1, v2;
	
    //v1 == v2; // compile error
    return 0;
}
```

# Has member variable

```cpp
template <typename T, typename = void>
struct has_fx_start_scene : std::false_type
{
};

template <typename T>
struct has_fx_start_scene<T, decltype((void)T::animation::start, void())> : std::true_type
{
};
```
