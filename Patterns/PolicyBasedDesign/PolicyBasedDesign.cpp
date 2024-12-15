// ===========================================================================
// PolicyBasedDesign.cpp
// ===========================================================================

#include <fstream>
#include <iostream>
#include <string>

namespace PolicyBasedDesign_01 {

    // erroneous implementation

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

    static void test_01() {
        SmartPtr<Class> ptr{ new Class{} };
    }

    static void test_02() {

        SmartPtr<int> sp1{ new int{ 123 } };
        SmartPtr<int> sp2{ new int[5] { 1, 2, 3, 4, 5 } };

        // which delete is called?
        // Scalar Deleting Destructor or Vector Deleting Destructor?
    }

    static void test()
    {
        test_01();
        test_02();
    }
}

namespace PolicyBasedDesign_02 {

    // correct implementation

    template <typename T, typename DeletionPolicy>
    class SmartPtr
    {
    private:
        T* m_ptr;
        DeletionPolicy m_deletionPolicy;

    public:
        // c'tor / d'tor
        explicit SmartPtr(T* ptr = nullptr, const DeletionPolicy& policy = DeletionPolicy{})
            : m_ptr{ ptr }, m_deletionPolicy{ policy } {}

        ~SmartPtr() {
            m_deletionPolicy(m_ptr);
        }

        // operators
        T* operator->() { return m_ptr; }
        const T* operator->() const { return m_ptr; }

        T& operator*() { return *m_ptr; }
        const T& operator*() const { return *m_ptr; }

    private:
        // prevent copy semantics
        SmartPtr(const SmartPtr&) = delete;
        SmartPtr& operator=(const SmartPtr&) = delete;
    };

    class Class {};

    template <typename T>
    struct ScalarDeletePolicy {
        void operator()(T* ptr) const {
            delete ptr;
        }
    };

    template <typename T>
    struct VectorDeletePolicy {
        void operator()(T* ptr) const {
            delete[] ptr;
        }
    };

    static void test()
    {
        SmartPtr<Class, ScalarDeletePolicy<Class>> ptr(new Class{});

        SmartPtr<int, ScalarDeletePolicy<int>> sp1{ new int{ 123 } };
        SmartPtr<int, VectorDeletePolicy<int>> sp2{ new int[5] { 1, 2, 3, 4, 5 } };
    }
}

namespace PolicyBasedDesign_10 {

    class LogToConsole {
    public:
        static void write(const std::string& message) {
            std::cout << message << std::endl;
        }
    };

    class LogToFile {
    public:
        static void write(const std::string& message) {
            std::ofstream file;
            file.open("trace.txt");
            file << message << std::endl;
            file.close();
        }
    };

    template <typename TOutputPolicy>
    class Logger {
    public:
        void log(const std::string& message) const {
            TOutputPolicy::write(message);
        }
    };

    static void test_01() {

        Logger<LogToConsole> consoleLogger{};
        consoleLogger.log("Important information");

        Logger<LogToFile> fileLogger{};
        fileLogger.log("Important information");
    }

    static void test_02() {

        std::cout << sizeof(LogToConsole) << std::endl;
        std::cout << sizeof(LogToFile) << std::endl;
        std::cout << sizeof(Logger<LogToConsole>) << std::endl;
        std::cout << sizeof(Logger<LogToFile>) << std::endl;
    }
}

namespace PolicyBasedDesign_11 {

    class LogToConsole {
    protected:
        static void write(const std::string& message) {
            std::cout << message << '\n';
        }
    };

    class LogToFile {
    protected:
        static void write(const std::string& message) {
            std::ofstream myFile;
            myFile.open("policyInheritance.txt");
            myFile << message << '\n';
        }
    };

    template <typename TOutputPolicy>
    class Logger : private TOutputPolicy {
    public:
        void log(const std::string& mess) const {
            write(mess);
        }
    private:
        using TOutputPolicy::write;
    };

    static void test_01() {

        Logger<LogToConsole> consoleLogger{};
        consoleLogger.log("Important information");

        Logger<LogToFile> fileLogger{};
        fileLogger.log("Important information");
    }

    static void test_02() {
        std::cout << sizeof(LogToConsole) << std::endl;
        std::cout << sizeof(LogToFile) << std::endl;
        std::cout << sizeof(Logger<LogToConsole>) << std::endl;
        std::cout << sizeof(Logger<LogToFile>) << std::endl;
    }
}

void test_conceptual_example_01() {

    using namespace PolicyBasedDesign_01;
    test_01();
    test_02();
}

void test_conceptual_example_02() {

    using namespace PolicyBasedDesign_02;
    test();
}

void test_conceptual_example_10() {

    using namespace PolicyBasedDesign_10;
    test_01();
    test_02();
}

void test_conceptual_example_11() {

    using namespace PolicyBasedDesign_11;
    test_01();
    test_02();
}

// ===========================================================================
// End-of-File
// ===========================================================================
