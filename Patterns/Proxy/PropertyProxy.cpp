// ===========================================================================
// PropertyProxy.cpp // Proxy Pattern
// ===========================================================================

#include <iostream>

template<typename T>
class Property
{
private:
    T m_value;

public:
    Property(const T initialValue) { *this = initialValue; }
    operator T() { return m_value; }
    T operator= (T newValue) { return m_value = newValue; }
};

struct Rectangle
{
    Property<size_t> m_top{ 10 };
    Property<size_t> m_left{ 5 };
    Property<size_t> m_width{ 20 };
    Property<size_t> m_height{ 30 };
};

void test_property_proxy()
{
    Rectangle rect;
    rect.m_width = 20;

    std::cout << rect.m_top << std::endl;
    std::cout << rect.m_left << std::endl;
    std::cout << rect.m_width << std::endl;
    std::cout << rect.m_height << std::endl;

    size_t top = rect.m_top;
}

// ===========================================================================
// End-of-File
// ===========================================================================
