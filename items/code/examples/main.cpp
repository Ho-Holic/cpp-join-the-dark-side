#include <iostream>
#include <functional>
#include <map>
#include <vector>

namespace SA
{
    template <typename T>
    class Cache
    {
    public:
        using cache_type = std::vector<T>;
        using callback = std::function<void(cache_type&)>;

    public:
        Cache();
        const cache_type& getOrFill(callback&& writeTo);
        void invalidate();

    private:
        bool m_isCached;
        cache_type m_cachedValues;
    };

    template <typename K, typename V>
    class CacheMap
    {
    public:
        using cache_type = std::map<K, V>;
        using callback = std::function<void(cache_type&)>;

    public:
        CacheMap();
        const cache_type& getOrFill(callback&& writeTo);
        void invalidate();

    private:
        bool m_isCached;
        cache_type m_cachedValues;
    };

    template <typename T>
    Cache<T>::Cache()
        : m_isCached(false)
    {
    }

    template <typename K, typename V>
    CacheMap<K, V>::CacheMap()
        : m_isCached(false)
    {
    }

    template <typename T>
    const typename Cache<T>::cache_type& Cache<T>::getOrFill(callback&& writeTo)
    {
        if (!m_isCached) {
            writeTo(m_cachedValues);
            m_isCached = true;
        }
        return m_cachedValues;
    }

    template <typename K, typename V>
    const typename CacheMap<K, V>::cache_type& CacheMap<K, V>::getOrFill(callback&& writeTo)
    {
        if (!m_isCached) {
            writeTo(m_cachedValues);
            m_isCached = true;
        }
        return m_cachedValues;
    }

    template <typename T>
    void Cache<T>::invalidate()
    {
        m_isCached = false;
        m_cachedValues.clear();
    }

    template <typename K, typename V>
    void CacheMap<K, V>::invalidate()
    {
        m_isCached = false;
        m_cachedValues.clear();
    }
}

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
//  root +=
//      - node1,
//      - - subnode1,
//      - - subnode2,
//      - node2,
//      - node3,
//      - node4;

// root += node1, --subnode1, --subnode2, -node2, -node3, -node4;

int main() {

    std::cout << "Main Darkside:" << std::endl;

    TreeGen<std::string> root;

//    root +=
//    - "defensive behaviour",
//    - - "x",
//    - - "y",
//    - "attacking behaviour",
//    - - "x",
//    - - "y";
}
