```
#include <iostream>
using namespace std;

struct EmptyExtra
{
    template <typename... Args>
    static void invoke(Args&&... args)
    {
        std::cout << "release\n";
    }

};

template <typename... Ts>
struct ExtraCompose
{
	//
};

template <typename T, typename... Ts>
struct ExtraCompose<T, Ts...> : public T, public ExtraCompose<Ts...>
{
	using Base = ExtraCompose<Ts...>;
	using T::invoke;
	using Base::invoke;
};

template <typename... Ts>
struct ExtraCompose<void, Ts...> : public ExtraCompose<Ts...>
{
	using Base = ExtraCompose<Ts...>;
	using Base::invoke;
};

template <typename T>
struct ExtraCompose<T> : public T, public EmptyExtra
{
	using T::invoke;
	using EmptyExtra::invoke;
};

template <>
struct ExtraCompose<void> : public EmptyExtra
{
	using EmptyExtra::invoke;
};

#define TDEBUG
#define TCHEAT

#ifdef TDEBUG
struct DebugExtra
{
	static void invoke(int i) {
		std::cout << "debug_" << i << "\n";
	}
};
#else
using DebugExtra = void;
#endif

#ifdef TCHEAT
struct CheatExtra
{
	static void invoke(std::string s) {
		std::cout << "cheat_" << s << "\n";
	}
};
#else
using CheatExtra = void;
#endif

using Extra = ExtraCompose<DebugExtra, CheatExtra>;

int main() {
	
	Extra::invoke(std::string("cat"));
	Extra::invoke(42);
	
	return 0;
}
```
