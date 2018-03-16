#ifndef MIRRORMAP_HPP
#define MIRRORMAP_HPP

#include <initializer_list>
#include <utility>
#include <map>
#include <vector>
#include <cassert>

#define Z_ASSERT(x) assert(x)

//#error "add support for synonims"
// NORMAL:
//
//    makeMirrorMap(
//        { Color::RED, "Red" }
//    );
//
// SYNONIM:
//
//    makeMirrorMap(
//        { Synonim(Color::RED, HSLColor::Red), Synonim("Red", "red", "r", "R") }
//    );

template <typename Left, typename Right, size_t N>
class MirrorMap
{
public:
    MirrorMap(const std::pair<Left, Right>(&items)[N])
        :   m_directAccess()
        ,   m_reverseAccess()
    {
        for (const std::pair<Left, Right>& pair : items) {
            m_directAccess.insert(pair);
            m_reverseAccess.insert({pair.second, pair.first});
        }
    }

    // strict
    const Left& operator()(const Right& key) {
        Z_ASSERT(m_reverseAccess.find(key) != m_reverseAccess.end());
        return m_reverseAccess[key];
    }

    const Right& operator()(const Left& key) {
        Z_ASSERT(m_directAccess.find(key) != m_directAccess.end());
        return m_directAccess[key];
    }

    // with fallback
    Left operator()(const Right& key, const Left& fallback) {
        return m_reverseAccess.find(key) != m_reverseAccess.end() ? m_reverseAccess[key] : fallback;
    }

    Right operator()(const Left& key,const Right& fallback) {
        return m_directAccess.find(key) != m_directAccess.end() ? m_directAccess[key] : fallback;
    }

    //
    // static allSkillTypes = cache.keysAs<SkillType, std::vector<SkillType>>();
    //

    template <typename T, typename C = std::vector<T>>
    C keysAs(typename std::enable_if<std::is_same<T, Left>::value, Left>::type* ptr = nullptr) {
        C result;
        for (auto& item : m_directAccess) {
            result.insert(result.end(), item.first);
        }
        return result;
    }

    template <typename T, typename C = std::vector<T>>
    C keysAs(typename std::enable_if<std::is_same<T, Right>::value, Right>::type* ptr = nullptr) {
        C result;
        // don't change for 'm_reverseAccess' and 'item.first'
        // we need to preserve the order
        for (auto& item : m_directAccess) {
            result.insert(result.end(), item.second);
        }
        return result;
    }

private:
    std::map<Left, Right> m_directAccess;
    std::map<Right, Left> m_reverseAccess;
};

template <typename Left, typename Right, size_t N>
auto makeMirrorMap(const std::pair<Left, Right>(&items)[N]) -> MirrorMap<Left, Right, N>
{
    return MirrorMap<Left, Right, N>(items);
}

#endif // MIRRORMAP_HPP
