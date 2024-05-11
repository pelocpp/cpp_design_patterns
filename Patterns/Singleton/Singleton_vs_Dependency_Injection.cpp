// ===========================================================================
// Singleton_vs_Dependency_Injection.cpp
// ===========================================================================

#include <iostream>
#include <memory>
#include <string_view>

namespace SingletonLogger {

    class Logger final
    {
    public:
        static Logger& getInstance()
        {
            static Logger theLogger{};
            return theLogger;
        }

        void writeInfoEntry(std::string_view entry) {
            std::cout << "[INFO] " << entry << std::endl;
        }

        void writeWarnEntry(std::string_view entry) {
            std::cout << "[WARNING] " << entry << std::endl;
        }

        void writeErrorEntry(std::string_view entry) {
            std::cout << "[ERROR] " << entry << std::endl;
        }
    };

    class Customer {};

    class Identifier {};

    class CustomerRepository {
    public:
        Customer findCustomerById(const Identifier& customerId)
        {
            Logger::getInstance().writeInfoEntry ("findCustomerById called ... ");
            // ...
            return {};
        }
        // ...
    };

    static void test_singleton_logger()
    {
        CustomerRepository customerRepository{ };

        Identifier id{};

        customerRepository.findCustomerById(id);
    }
}

// ===========================================================================

namespace DependencyInjectionLogger {

    class LoggingFacility
    {
    public:
        virtual ~LoggingFacility() = default;

        virtual void writeInfoEntry(std::string_view entry) = 0;
        virtual void writeWarnEntry(std::string_view entry) = 0;
        virtual void writeErrorEntry(std::string_view entry) = 0;
    };

    // ============================================================

    class StandardOutputLogger : public LoggingFacility
    {
    public:
        void writeInfoEntry(std::string_view entry) override {
            std::cout << "[INFO] " << entry << std::endl;
        }

        void writeWarnEntry(std::string_view entry) override {
            std::cout << "[WARNING] " << entry << std::endl;
        }

        void writeErrorEntry(std::string_view entry) override {
            std::cout << "[ERROR] " << entry << std::endl;
        }
    };

    // ============================================================

    class Customer {};

    class Identifier {};

    class CustomerRepository
    {
    public:
        CustomerRepository() = delete;

        explicit CustomerRepository(const std::shared_ptr<LoggingFacility>& logger)
            : m_logger{ logger }
        { }
        
        Customer findCustomerById(const Identifier& customerId)
        {
            m_logger->writeInfoEntry("findCustomerById called ... ");
            // ...
            return {};
        }

    private:
        std::shared_ptr<LoggingFacility> m_logger;
    };

    static void test_di_logger()
    {
        std::shared_ptr<LoggingFacility> logger = std::make_shared<StandardOutputLogger>();

        CustomerRepository customerRepository{ logger };

        Identifier id{};

        customerRepository.findCustomerById(id);
    }

    // ============================================================

    class MockLogger : public LoggingFacility
    {
    public:
        void writeInfoEntry(std::string_view entry) override {}
        void writeWarnEntry(std::string_view entry) override {}
        void writeErrorEntry(std::string_view entry) override {}
    };

    static void test_di_mock_logger()
    {
        std::shared_ptr<LoggingFacility> logger = std::make_shared<MockLogger>();

        CustomerRepository customerRepository{ logger };

        Identifier id{};

        customerRepository.findCustomerById(id);
    }
}


// ============================================================

void test_singleton_vs_di()
{
    SingletonLogger::test_singleton_logger();
    DependencyInjectionLogger::test_di_logger();
    DependencyInjectionLogger::test_di_mock_logger();
}

// ===========================================================================
// End-of-File
// ===========================================================================
