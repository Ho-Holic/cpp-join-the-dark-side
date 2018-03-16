#include <iostream>

template <typename T>
struct TreeGen
{
    //
};

template <typename T>
struct TreeGenItem
{
    TreeGenItem() : index(0) {}

    TreeGenItem& operator-()
    {
        index += 1;
        return *this;
    }

    size_t index;
};

template <typename T>
TreeGenItem<T> operator-(const T& value)
{
    TreeGenItem<T> item(value);
    return item;
}

// client

int main() {
    TreeGen<std::string> root;

//    root +=
//    - "defensive behaviour",
//    - - "x",
//    - - "y",
//    - "attacking behaviour",
//    - - "x",
//    - - "y";
}
