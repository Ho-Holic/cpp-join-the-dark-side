#ifndef CYCLEVALUE_HPP
#define CYCLEVALUE_HPP

#include <cstddef>

//
// Will be a template class later
//

// void cycleUpNoWrap(); // Add no wrap mode
// void cycleDownNoWrap(); // Add no wrap mode
// CycleValue<int, NoWrap>
// 
// auto newIndex = clamp((i - 1), 0, limit); 
//

template <typename T>
class CycleValue {
public:
    explicit CycleValue(size_t limit);
    void up();
    void down();
    void cycleUp(const T& offset);
    void cycleDown(const T& offset);    
    T value() const;
public:
    operator T() const;
private:
    T m_value;
    size_t m_limit;
};

// implementation

template <typename T>
CycleValue<T>::CycleValue(size_t limit)
:   m_value()
,   m_limit(limit)
{
    //
}

template <typename T>
void CycleValue<T>::cycleUp(const T& offset)
{
    m_value = (m_value + offset) % m_limit;
}

template <typename T>
void CycleValue<T>::cycleDown(const T& offset)
{
    m_value = (m_limit + m_value - offset) % m_limit;
}

template <typename T>
void CycleValue<T>::up()
{
    m_value = (m_value + 1) % m_limit;
}

template <typename T>
void CycleValue<T>::down()
{
    //
    // 'm_limit + m_value' consider overflow here
    // regarding fact that this class is used for small amount of 'limits'
    //
    m_value = (m_limit + m_value - 1) % m_limit;
}

template <typename T>
T CycleValue<T>::value() const
{
    return m_value;
}

template <typename T>
CycleValue<T>::operator T() const
{
    return m_value;
}

#endif // CYCLEVALUE_HPP
