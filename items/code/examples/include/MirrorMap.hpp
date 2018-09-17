#ifndef MIRRORMAP_HPP
#define MIRRORMAP_HPP

#include <initializer_list>
#include <utility>
#include <map>
#include <vector>
#include <cassert>

#include "Traits.hpp"

#define Z_ASSERT(x) assert(x)

// main template
template <bool B, typename Left, typename Right, size_t N>
struct MirrorMap  {
    //
};

// with less operator
template <typename Left, typename Right, size_t N>
class MirrorMap<true, Left, Right, N>
{
public:
    MirrorMap(const std::pair<Left, Right> (&items)[N])
        : m_directAccess()
        , m_reverseAccess()
    {
        for (const std::pair<Left, Right>& pair : items) {
            m_directAccess.insert(pair);
            m_reverseAccess.insert({ pair.second, pair.first });
        }
        Z_ASSERT(m_directAccess.size() == m_reverseAccess.size());
        Z_ASSERT(m_directAccess.size() == N);
        Z_ASSERT(m_reverseAccess.size() == N);
    }

    // strict
    const Left& operator()(const Right& key)
    {
        Z_ASSERT(m_reverseAccess.find(key) != m_reverseAccess.end());
        return m_reverseAccess[key];
    }

    const Right& operator()(const Left& key)
    {
        Z_ASSERT(m_directAccess.find(key) != m_directAccess.end());
        return m_directAccess[key];
    }

    // with fallback
    Left operator()(const Right& key, const Left& fallback)
    {
        return m_reverseAccess.find(key) != m_reverseAccess.end() ? m_reverseAccess[key] : fallback;
    }

    Right operator()(const Left& key, const Right& fallback)
    {
        return m_directAccess.find(key) != m_directAccess.end() ? m_directAccess[key] : fallback;
    }

    template <typename T, typename C = std::vector<T>>
    C keysAs(typename std::enable_if<std::is_same<T, Left>::value, Left>::type* = nullptr)
    {
        C result;
        for (auto& item : m_directAccess) {
            result.insert(result.end(), item.first);
        }
        Z_ASSERT(result.size() == N);
        return result;
    }

    template <typename T, typename C = std::vector<T>>
    C keysAs(typename std::enable_if<std::is_same<T, Right>::value, Right>::type* = nullptr)
    {
        C result;
        // don't change for 'm_reverseAccess' and 'item.first'
        // we need to preserve the order
        for (auto& item : m_directAccess) {
            result.insert(result.end(), item.second);
        }
        Z_ASSERT(result.size() == N);
        return result;
    }

private:
    std::map<Left, Right> m_directAccess;
    std::map<Right, Left> m_reverseAccess;
};

template <typename Left, typename Right, size_t N>
class MirrorMap<false, Left, Right, N>
{
public:
    MirrorMap(const std::pair<Left, Right> (&items)[N])
        : m_directAccess()
    {
        for (const std::pair<Left, Right>& pair : items) {
            m_directAccess.insert(pair);
        }
        Z_ASSERT(m_directAccess.size() == N);
    }

    // strict

    const Right& operator()(const Left& key)
    {
        Z_ASSERT(m_directAccess.find(key) != m_directAccess.end());
        return m_directAccess[key];
    }

    // with fallback
    Right operator()(const Left& key, const Right& fallback)
    {
        return m_directAccess.find(key) != m_directAccess.end() ? m_directAccess[key] : fallback;
    }

    template <typename T, typename C = std::vector<T>>
    C keysAs(typename std::enable_if<std::is_same<T, Left>::value, Left>::type* = nullptr)
    {
        C result;
        for (auto& item : m_directAccess) {
            result.insert(result.end(), item.first);
        }
        Z_ASSERT(result.size() == N);
        return result;
    }

    template <typename T, typename C = std::vector<T>>
    C keysAs(typename std::enable_if<std::is_same<T, Right>::value, Right>::type* = nullptr)
    {
        C result;
        // don't change for 'm_reverseAccess' and 'item.first'
        // we need to preserve the order
        for (auto& item : m_directAccess) {
            result.insert(result.end(), item.second);
        }
        Z_ASSERT(result.size() == N);
        return result;
    }

private:
    std::map<Left, Right> m_directAccess;
};

template <typename Left, typename Right, size_t N>
auto makeMirrorMap(const std::pair<Left, Right> (&items)[N])
    -> MirrorMap<has_operator_less<Right>::value, Left, Right, N>
{
    return MirrorMap<has_operator_less<Right>::value, Left, Right, N>(items);
}

#endif // MIRRORMAP_HPP
