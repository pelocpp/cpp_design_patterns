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
        virtual IteratorBase<T>* createIterator() = 0;
    };

    // =======================================================================

    /**
     * C++ has its own implementation of iterator that works with a different
     * generics containers defined by the standard library.
     */

    template <typename T, typename U>
    class Iterator : public IteratorBase<T>   {
    public:
        typedef typename std::vector<T>::iterator iter_type;

        Iterator(U* p_data, bool reverse = false) : m_p_data_(p_data) {
            m_it_ = m_p_data_->m_data_.begin();
        }

        void First() {
            m_it_ = m_p_data_->m_data_.begin();
        }

        void Next() {
            m_it_++;
        }

        bool IsDone() {
            return (m_it_ == m_p_data_->m_data_.end());
        }

        iter_type Current() {
            return m_it_;
        }

        // new interface
        void reset() override {
            m_it_ = m_p_data_->m_data_.begin();
        };

        const T& getCurrent() const  override {
            return *m_it_;
        };

        bool hasNext()  override {

            if (m_it_ == m_p_data_->m_data_.end()) {
                return false;
            }
            else {
                m_it_++;
                return true;
            }
        };

    private:
        U* m_p_data_;
        iter_type m_it_;
    };

    // =======================================================================

    template <class T>
    class Container : public AggregateBase<T> {
        friend class Iterator<T, Container>;

    public:
        void Add(T a) {
            m_data_.push_back(a);
        }

        Iterator<T, Container>* CreateIterator() {
            return new Iterator<T, Container>(this);
        }

        IteratorBase<T>* Container<T>::createIterator() {
            return new Iterator<T, Container>(this);
        }


    private:
        std::vector<T> m_data_;
    };

    // =======================================================================

    //template <typename T>
    //IteratorBase<T>* Container<T>::createIterator()
    //{
    //    return new Iterator<T>(this);
    //}

    //template <typename T>
    //IteratorBase<T>* ConcreteAggregate<T>::createForwardIterator()
    //{
    //    return new ForwardIterator<T>(this);
    //}

    //template <typename T>
    //IteratorBase<T>* ConcreteAggregate<T>::createBackwardIterator()
    //{
    //    return new BackwardIterator<T>(this);
    //}

    // =======================================================================
}

void test_conceptual_example_02() {

    using namespace IteratorPatternCpp;

    Container<int> cont;

    for (int i = 0; i < 3; i++) {
        cont.Add(i);
    }

    //Iterator<int, Container<int>>* it = cont.CreateIterator();
    //for (it->First(); !it->IsDone(); it->Next()) {
    //    std::cout << *it->Current() << std::endl;
    //}

    IteratorBase<int>* it2 = cont.createIterator();
    while (it2->hasNext())
    {
        std::cout << it2->getCurrent() << std::endl;
    }
    delete it2;
    std::cout << std::endl;

    //Container<std::string> container;
    //container.add("123");
    //container.add("456");
    //container.add("789");
    //std::cout << "Size: " << container.size() << std::endl;
    //std::cout << "[2]:  " << container.get(1) << std::endl;

    //IteratorBase<std::string>* it = container.createIterator();
    //while (it->hasNext())
    //{
    //    std::cout << it->getCurrent() << std::endl;
    //}
    //delete it;
    //std::cout << std::endl;

    //it = container.createBackwardIterator();
    //while (it->hasNext())
    //{
    //    std::cout << it->getCurrent() << std::endl;
    //}
    //std::cout << std::endl;

    //it->reset();
    //while (it->hasNext())
    //{
    //    std::cout << it->getCurrent() << std::endl;
    //}
    //delete it;
}

// ===========================================================================
// End-of-File
// ===========================================================================
