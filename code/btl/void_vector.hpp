emplate <typename T>
struct zero_allocator
{
    T data[0];
};

template <typename T>
struct void_iterator
{
    void_iterator& operator++() { return *this; }
    void_iterator operator++(int) { return *this; }
    
    bool operator==(void_iterator) const { return true; }
    bool operator!=(void_iterator) const { return false; }
    T& operator*() const { return *(T*)this; }            
};

template <
    typename T = void, 
    typename Allocator = zero_allocator<T>
> class void_vector
{
public:
    using value_type = T;
    using reference = void;
    using const_reference = void;
    
    using iterator = void_iterator<T>;
    using const_iterator = void_iterator<T>;
    
    template <typename U>
    void push_back(const U&) {}
    
    template <typename U>
    void push_back(U&&) {}
    
    iterator begin() { return iterator(); };
    iterator end() { return iterator(); };
};
