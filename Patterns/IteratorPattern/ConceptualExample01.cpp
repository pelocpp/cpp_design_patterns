// ===========================================================================
// ConceptualExample01.cpp // Iterator Pattern // Standard Variant
// ===========================================================================

#include <iostream>
#include <string>
#include <vector>

namespace IteratorPatternStandard {

    template <typename T>
    class IteratorBase
    {
    public:
        virtual ~IteratorBase() = default;
        virtual void reset() = 0;
        virtual const T& getCurrent() const = 0;
        virtual bool hasNext() = 0;
    };

    // =======================================================================

    template <typename T>
    class AggregateBase
    {
    public:
        virtual ~AggregateBase() = default;
        virtual IteratorBase<T>* createForwardIterator() = 0;
        virtual IteratorBase<T>* createBackwardIterator() = 0;
    };

    // =======================================================================

    template <typename T>
    class ConcreteAggregate : public AggregateBase<T>
    {
    private:
        std::vector<T> m_vector;

    public:
        IteratorBase<T>* createForwardIterator() {
            return new class ForwardIterator<T>(this);
        }

        IteratorBase<T>* createBackwardIterator() {
            return new class BackwardIterator<T>(this);
        }

        void add(const T& content)
        {
            m_vector.push_back(content);
        }   

        int size() const
        {
            return static_cast<int> (m_vector.size());
        }

        T& get(int index)
        {
            return m_vector[index];
        }

        const T& get(int index) const
        {
            return m_vector[index];
        }
    };

    // =======================================================================

    template <typename T>
    class ForwardIterator : public IteratorBase<T>
    {
    private:
        const ConcreteAggregate<T>* m_aggregate;
        int m_pos;

    public:
        ForwardIterator(const ConcreteAggregate<T>* agg) 
            : m_aggregate{ agg }, m_pos{ -1 } {}

        void reset() override
        {
            m_pos = -1;
        }

        const T& getCurrent() const override
        {
            return m_aggregate->get(m_pos);
        }

        bool hasNext() override
        {
            bool erg = false;
            if (m_pos < m_aggregate->size() - 1)
            {
                m_pos++;
                erg = true;
            }
            return erg;
        }
    };

    template <typename T>
    class BackwardIterator : public IteratorBase<T>
    {
    private:
        const ConcreteAggregate<T>* m_aggregate;
        int m_pos;

    public:
        BackwardIterator(const ConcreteAggregate<T>* agg) 
            : m_aggregate{ agg }, m_pos{ agg->size() } {}

        void reset() override
        {
            m_pos = m_aggregate->size();
        }

        const T& getCurrent() const override
        {
            return m_aggregate->get(m_pos);
        }

        bool hasNext() override
        {
            bool erg = false;
            if (m_pos > 0)
            {
                m_pos--;
                erg = true;
            }
            return erg;
        }
    };

    // =======================================================================
}

void test_conceptual_example_01() {

    using namespace IteratorPatternStandard;

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

void test_conceptual_example_02() {

    using namespace IteratorPatternStandard;

    ConcreteAggregate<int> intContainer;

    for (int i = 0; i < 10; i++) {
        intContainer.add(i);
    }

    IteratorBase<int>* intIter1 = intContainer.createForwardIterator();
    IteratorBase<int>* intIter2 = intContainer.createForwardIterator();

    // using first iterator three times
    if (intIter1->hasNext()) {
        std::cout << "First Iterator:  " << intIter1->getCurrent() << std::endl;
    }
    if (intIter1->hasNext()) {
        std::cout << "First Iterator:  " << intIter1->getCurrent() << std::endl;
    }
    if (intIter1->hasNext()) {
        std::cout << "First Iterator:  " << intIter1->getCurrent() << std::endl;
    }
    std::cout << std::endl;

    // now using second iterator three times
    if (intIter2->hasNext()) {
        std::cout << "Second Iterator: " << intIter2->getCurrent() << std::endl;
    }
    if (intIter2->hasNext()) {
        std::cout << "Second Iterator: " << intIter2->getCurrent() << std::endl;
    }
    if (intIter2->hasNext()) {
        std::cout << "Second Iterator: " << intIter2->getCurrent() << std::endl;
    }

    delete intIter1;
    delete intIter2;
    std::cout << std::endl;
}

// ===========================================================================
// End-of-File
// ===========================================================================
