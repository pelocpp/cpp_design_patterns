// ===========================================================================
// ConceptualExample02.cpp // Iterator Pattern // C++ Variant
// ===========================================================================

#include <iostream>
#include <string>
#include <vector>

namespace IteratorPatternCpp {

    template <typename T>
    class IteratorBase
    {
    public:
        virtual ~IteratorBase() {};

        virtual void reset() = 0;
        virtual const T& getCurrent() const = 0;
        virtual bool hasNext() = 0;
    };

    // =======================================================================

    template <typename T>
    class AggregateBase
    {
    public:
        virtual ~AggregateBase() {};

        virtual IteratorBase<T>* createForwardIterator() = 0;
        virtual IteratorBase<T>* createBackwardIterator() = 0;
    };

    // =======================================================================

    /**
     * C++ has its own implementation of iterator that works with
     * different generics containers defined by the standard library.
     */

    template <typename TElement, typename TContainer>
    class Iterator : public IteratorBase<TElement> {

        using TIterator = typename std::vector<TElement>::iterator;

    private:
        TContainer* m_container;
        TIterator m_iterator;
        bool m_reverse;
        bool m_notFirstAccess;

    public:
        Iterator(TContainer* p_data, bool reverse)
            : m_container{ p_data }, m_reverse{ reverse }, m_notFirstAccess{ false }
        {
            m_iterator = (m_reverse)
                ? std::prev(m_container->m_vector.end())
                : m_container->m_vector.begin();
        }

        // interface 'IteratorBase'
        void reset() override {
            m_iterator = (m_reverse)
                ? std::prev(m_container->m_vector.end())
                : m_container->m_vector.begin();

            m_notFirstAccess = false;
        };

        const TElement& getCurrent() const override {
            return *m_iterator;
        };

        bool hasNext()  override {
            bool result;
            if (m_reverse) {
                if (m_iterator == m_container->m_vector.begin()) {
                    result = false;
                }
                else {
                    result = true;
                    if (m_notFirstAccess) {
                        m_iterator--;
                    }
                    m_notFirstAccess = true;
                }
            }
            else {
                if (m_iterator == std::prev(m_container->m_vector.end())) {
                    result = false;
                }
                else {
                    result = true;
                    if (m_notFirstAccess) {
                        m_iterator++;
                    }
                    m_notFirstAccess = true;
                }
            }
            return result;
        };
    };

    // =======================================================================

    template <class TElement>
    class ConcreteAggregate : public AggregateBase<TElement> {

        friend class Iterator<TElement, ConcreteAggregate>;

    private:
        std::vector<TElement> m_vector;

    public:
        void add(TElement a) {
            m_vector.push_back(a);
        }

        int size() const
        {
            return static_cast<int> (m_vector.size());
        }

        TElement& get(int index)
        {
            return m_vector[index];
        }

        const TElement& get(int index) const
        {
            return m_vector[index];
        }

        IteratorBase<TElement>* createForwardIterator() {
            return new Iterator<TElement, ConcreteAggregate>(this, false);
        }

        IteratorBase<TElement>* createBackwardIterator() {
            return new Iterator<TElement, ConcreteAggregate>(this, true);
        }
    };
}

void test_conceptual_example_03() {

    using namespace IteratorPatternCpp;

    ConcreteAggregate<int> intContainer;

    for (int i = 0; i < 3; i++) {
        intContainer.add(i);
    }

    IteratorBase<int>* intIter = intContainer.createForwardIterator();
    while (intIter->hasNext())
    {
        std::cout << intIter->getCurrent() << std::endl;
    }
    delete intIter;
    std::cout << std::endl;

    ConcreteAggregate<std::string> stringContainer;
    stringContainer.add("123");
    stringContainer.add("456");
    stringContainer.add("789");
    std::cout << "Size: " << stringContainer.size() << std::endl;
    std::cout << "[1]:  " << stringContainer.get(1) << std::endl;

    IteratorBase<std::string>* it = stringContainer.createForwardIterator();
    while (it->hasNext())
    {
        std::cout << it->getCurrent() << std::endl;
    }
    delete it;
    std::cout << std::endl;

    it = stringContainer.createBackwardIterator();
    while (it->hasNext())
    {
        std::cout << it->getCurrent() << std::endl;
    }
    std::cout << std::endl;

    it->reset();
    while (it->hasNext())
    {
        std::cout << it->getCurrent() << std::endl;
    }
    delete it;
}

// ===========================================================================
// End-of-File
// ===========================================================================
