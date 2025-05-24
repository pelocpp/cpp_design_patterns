// ===========================================================================
// ConceptualExample01.cpp // Iterator Pattern // Standard C++ 
// ===========================================================================

#include <iostream>
#include <vector>
#include <print>

class MyContainer
{
public:
    using value_type        = int;
    using difference_type   = std::ptrdiff_t;
    using iterator_category = std::vector<int>::iterator;
    using pointer           = const value_type*;
    using reference         = const value_type&;

    using iterator          = std::vector<int>::iterator;
    using const_iterator    = std::vector<int>::const_iterator;

private:
    std::vector<int> m_data;

public:
    MyContainer(const std::initializer_list<int>& values) : m_data(values) {}

    // nested iterator class
    class Iterator {
    private:
        std::vector<int>::iterator m_iter;

    public:
        // c'tor
        Iterator(std::vector<int>::iterator it) : m_iter{ it } {}

        // dereference operator
        int& operator*() { return *m_iter; }

        // pre-increment operator
        Iterator& operator++() {
            ++m_iter;
            return *this;
        }

        // post-increment operator
        Iterator operator++(int) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        // equality comparison
        bool operator==(const Iterator& other) const {
            return m_iter == other.m_iter;
        }

        // inequality comparison
        bool operator!=(const Iterator& other) const {
            return !(*this == other);
        }
    };

public:
    // begin iterator
    Iterator begin() { return Iterator{ m_data.begin() }; }

    // end iterator
    Iterator end() { return Iterator{ m_data.end() }; }
};

void test_conceptual_example_01()
{
    MyContainer container { 1, 2, 3, 4, 5 };

    for (MyContainer::Iterator it = container.begin(); it != container.end(); ++it) {
        std::print("{} ", *it);
    }
    std::println();

    for (auto elem : container) {
        std::print("{} ", elem);
    }
}

// ===========================================================================
// End-of-File
// ===========================================================================