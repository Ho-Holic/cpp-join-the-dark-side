#ifndef PREVIOUSVALUE_HPP
#define PREVIOUSVALUE_HPP

template <typename T>
class PreviousValue
{
public:
    PreviousValue(const T& fresh)
        : m_old(fresh)
        , m_fresh(fresh) {}

    // previous_value()
    // : m_old()
    // , m_fresh() {}

    PreviousValue& operator=(const T& fresh) {
        m_old = m_fresh;
        m_fresh = fresh;
        return *this;
    }
    operator T() {
        return m_fresh;
    }

    T* operator->() {
        return &m_fresh;
    }

    T& previous() {
        return m_old;
    }
    T m_old;
    T m_fresh;
};

#endif // PREVIOUSVALUE_HPP
