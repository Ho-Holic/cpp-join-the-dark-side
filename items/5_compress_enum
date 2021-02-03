```cpp
namespace compression
{
template <typename CompressedValue, typename EnumType>
CompressedValue compressEnumSet(std::set<EnumType> data)
{
    CompressedValue result = 0;

    for (auto element : data) {
        Z_ASSERT(static_cast<CompressedValue>(element) < sizeof(CompressedValue) * 8);
        auto value = (1 << static_cast<CompressedValue>(element));
        result |= value;
    }

    return result;
}

template <typename CompressedValue, typename EnumType>
std::set<EnumType> decompressEnumSet(CompressedValue value)
{
    std::set<EnumType> result;

    for (CompressedValue i = 0; i < sizeof(CompressedValue) * 8; ++i) {
        if (value & 1) {
            result.insert(static_cast<EnumType>(i));
        }

        value = value >> 1;
    }

    return result;
}

}

```
