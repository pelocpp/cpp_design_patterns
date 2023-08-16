// ===========================================================================
// PolicyBasedDesign.cpp
// ===========================================================================


// https://github.com/PacktPublishing/Hands-On-Design-Patterns-with-CPP



// Literatur:

// https://www4.cs.fau.de/Lehre/SS07/V_OSE/Skript/12-PolicyBased-2x2.pdf

// https://www.modernescpp.com/index.php/policy-and-traits/

// https://wiki.scc.kit.edu/gridkaschool/upload/8/87/5MorePatterns.pdf




#include <iostream>
#include <memory>
#include <fstream>
#include <string>

namespace PolicyBasedDesign_01 {

    template <typename T>
    class SmartPtr
    {
    private:
        T* m_ptr;

    public:
        // c'tor / d'tor
        explicit SmartPtr (T* ptr = nullptr) : m_ptr{ ptr } {}

        ~SmartPtr() {
            delete m_ptr;
        }

        // operators
        T* operator-> () { return m_ptr; }
        const T* operator-> () const { return m_ptr; }

        T& operator* () { return *m_ptr; }
        const T& operator* () const { return *m_ptr; }

    private:
        // prevent copy semantics
        SmartPtr(const SmartPtr&) = delete;
        SmartPtr& operator=(const SmartPtr&) = delete;
    };

    class Class {};

    void test_01() {
        SmartPtr<Class> ptr{ new Class{} };
    }

    void test_02() {
        SmartPtr<int> ptr1{ new int{123} };

        SmartPtr<int> ptr2{new int[5] { 1, 2, 3, 4, 5 }};

        int ip = *ptr2;


        //std::cout << *ip << std::endl;
        //std::cout << *(ip+1) << std::endl;
        //std::cout << *(ip + 2) << std::endl;
        //std::cout << *(ip + 3) << std::endl;
        //std::cout << *(ip + 4) << std::endl;
    }
}


void test_conceptual_example_01() {

    using namespace PolicyBasedDesign_01;

    test_01();
    test_02();
}

// ===========================================================================
// End-of-File
// ===========================================================================











// must reside in global namespace - due to operator new overload
class Heap {
public:
    void* allocate(size_t size) {

        return 0;
    };

    void deallocate(void* ptr) {
    };
};

void* operator new(size_t size, Heap* heap) {
    return heap->allocate(size);
}


namespace PolicyBasedDesign {

    namespace PolicyBasedDesign_01 {

        template <typename T>
        class SmartPtr
        {
        private:
            T* m_ptr;

        public:
            explicit SmartPtr(T* ptr = nullptr) : m_ptr{ ptr } {}

            ~SmartPtr() {
                delete m_ptr;
            }

            T* operator-> () { return m_ptr; }
            const T* operator-> () const { return m_ptr; }

            T& operator* () { return *m_ptr; }
            const T& operator* () const { return *m_ptr; }

        private:
            // prevent copy semantics
            SmartPtr(const SmartPtr&) = delete;
            SmartPtr& operator=(const SmartPtr&) = delete;
        };

        class Class {};

        void test() {
            SmartPtr<Class> ptr(new Class{});
        }
    }

    namespace PolicyBasedDesign_02 {

        template <typename T, typename DeletionPolicy>
        class SmartPtr
        {
        private:
            T* m_ptr;

        public:
            explicit SmartPtr(T* ptr = nullptr, const DeletionPolicy& deletion_policy = DeletionPolicy{})
                : m_ptr{ ptr }, m_deletionPolicy{ deletion_policy } {}

            ~SmartPtr() {
                m_deletionPolicy(m_ptr);
            }

            T* operator->() { return m_ptr; }
            const T* operator->() const { return m_ptr; }

            T& operator*() { return *m_ptr; }
            const T& operator*() const { return *m_ptr; }

        private:
            DeletionPolicy m_deletionPolicy;

            // prevent copy semantics
            SmartPtr(const SmartPtr&) = delete;
            SmartPtr& operator=(const SmartPtr&) = delete;
        };

        class Class {};

        template <typename T>
        struct DeleteByOperatorScalar {
            void operator()(T* ptr) const {
                delete ptr;
            }
        };

        template <typename T>
        struct DeleteByOperatorNonScalar {
            void operator()(T* ptr) const {
                delete[] ptr;
            }
        };

        void test() {
            SmartPtr<Class, DeleteByOperatorScalar<Class>> ptr(new Class{});

            SmartPtr<int, DeleteByOperatorScalar<int>> singleInt(new int{});

            SmartPtr<int, DeleteByOperatorNonScalar<int>> arrayOfInts(new int[10]);
        }
    }

    namespace PolicyBasedDesign_03 {

        // siehe auch Seite 103 // 331

        template <typename T>
        class DeleteUsingMyHeap
        {
        private:
            Heap& m_heap;

        public:
            explicit DeleteUsingMyHeap(Heap& heap) : m_heap{ heap } {}

            void operator() (T* p) const {
                p->~T();
                m_heap.deallocate(p);
            }
        };

        class Class {};

        void test_00() {

            Heap heap;
            std::unique_ptr<int> p(new(&heap) int(0));

            // WAS TUT DAS HIER
        }

        void test() {

            Heap heap{};

            // https://en.cppreference.com/w/cpp/memory/new/operator_new

            // custom placement new

            PolicyBasedDesign::PolicyBasedDesign_02::SmartPtr<int, DeleteUsingMyHeap<int>> ptr{ new(&heap) int{ 123 }, DeleteUsingMyHeap<int>{ heap } };

            std::cout << *ptr << std::endl;

            // PolicyBasedDesign::PolicyBasedDesign_02::SmartPtr<Class, DeleteUsingMyHeap<Class>> ptr(new Class{});

      //      void* ptr = heap.allocate(sizeof (Class));


           // SmartPtr<Class, DeleteByOperatorScalar<Class>> ptr(new Class{});

        }
    }

    // weiter: Seite 331

    namespace PolicyBasedDesign_10 {

        class LogToConsole {
        public:
            void write(const std::string& message) const {
                std::cout << message << std::endl;
            }
        };

        class LogToFile {
        public:
            void write(const std::string& message) const {
                std::ofstream file;
                file.open("trace.txt");
                file << message << std::endl;
                file.close();
            }
        };

        template <typename OutputPolicy>
        class Logger {
        public:
            void log(const std::string& message) const {
                m_policy.write(message);
            }

        private:
            OutputPolicy m_policy;
        };

        void test() {

            Logger<LogToConsole> consoleLogger{};
            consoleLogger.log("Important information");

            Logger<LogToFile> fileLogger{};
            fileLogger.log("Important information");
        }

        void test_02() {

            std::cout << sizeof(LogToConsole) << std::endl;
            std::cout << sizeof(LogToFile) << std::endl;
            std::cout << sizeof(Logger<LogToConsole>) << std::endl;
            std::cout << sizeof(Logger<LogToFile>) << std::endl;
        }
    }


    namespace PolicyBasedDesign_11 {

        class LogToConsole {
        protected:
            void write(const std::string& message) const {
                std::cout << message << '\n';
            }
        };

        class LogToFile {
        protected:
            void write(const std::string& message) const {
                std::ofstream myFile;
                myFile.open("policyInheritance.txt");
                myFile << message << '\n';
            }
        };

        template <typename OutputPolicy>
        class Logger : private OutputPolicy {
        public:
            void log(const std::string& mess) const {
                write(mess);
            }
        private:
            using OutputPolicy::write;
        };

        void test() {

            Logger<LogToConsole> consoleLogger{};
            consoleLogger.log("Important information");

            Logger<LogToFile> fileLogger{};
            fileLogger.log("Important information");
        }

        void test_02() {

            std::cout << sizeof(LogToConsole) << std::endl;
            std::cout << sizeof(LogToFile) << std::endl;
            std::cout << sizeof(Logger<LogToConsole>) << std::endl;
            std::cout << sizeof(Logger<LogToFile>) << std::endl;
        }
    }


}

void test_policies()
{
    //PolicyBasedDesign::PolicyBasedDesign_01::test();
    //PolicyBasedDesign::PolicyBasedDesign_02::test();
    //PolicyBasedDesign::PolicyBasedDesign_03::test();

    // PolicyBasedDesign::PolicyBasedDesign_10::test();
    PolicyBasedDesign::PolicyBasedDesign_10::test_02();
    //PolicyBasedDesign::PolicyBasedDesign_11::test();
    PolicyBasedDesign::PolicyBasedDesign_11::test_02();
}