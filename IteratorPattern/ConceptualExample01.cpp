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
        std::vector<T> m_list;

    public:
        IteratorBase<T>* createForwardIterator();
        IteratorBase<T>* createBackwardIterator();

        void add(const T& content)
        {
            m_list.push_back(content);
        }   

        int size() const
        {
            return static_cast<int> (m_list.size());
        }

        T& get(int index)
        {
            return m_list[index];
        }

        const T& get(int index) const
        {
            return m_list[index];
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
            : m_aggregate(agg), m_pos(-1) { }

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
            : m_aggregate(agg), m_pos(agg->size()) { }

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

    template <typename T>
    IteratorBase<T>* ConcreteAggregate<T>::createForwardIterator()
    {
        return new ForwardIterator<T>(this);
    }

    template <typename T>
    IteratorBase<T>* ConcreteAggregate<T>::createBackwardIterator()
    {
        return new BackwardIterator<T>(this);
    }

    // =======================================================================
}

void test_conceptual_example01() {

    using namespace IteratorPatternStandard;

    ConcreteAggregate<std::string> container;
    container.add("123");
    container.add("456");
    container.add("789");
    std::cout << "Size: " << container.size() << std::endl;
    std::cout << "[2]:  " << container.get(1) << std::endl;

    IteratorBase<std::string>* it = container.createForwardIterator();
    while (it->hasNext())
    {
        std::cout << it->getCurrent() << std::endl;
    }
    delete it;
    std::cout << std::endl;

    it = container.createBackwardIterator();
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
