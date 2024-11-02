// ===========================================================================
// ConceptualExample01.cpp // Intercepting Filter Pattern
// ===========================================================================

#include <iostream>
#include <string>
#include <list>
#include <memory>

namespace ConceptualExample01 {

    class IFilter
    {
    public:
        virtual void execute(const std::string& request) = 0;
    };

    class DebugFilter : public IFilter
    {
    public:
        virtual void execute(const std::string& request) override {
            std::cout << "[Log Request: " << request << "]" << std::endl;
        }
    };

    class AuthenticationFilter : public IFilter
    {
    public:
        virtual void execute(const std::string& request) override {
            std::cout << "[Authenticating Request: " << request << "]" << std::endl;
        }
    };

    // ---------------------------------------------------------------------------

    class Target
    {
    public:
        void operation(const std::string& request) {
            std::cout << "Executing Request: " << request << std::endl;
        }
    };

    // ---------------------------------------------------------------------------

    class FilterChain
    {
    private:
        std::list<std::weak_ptr<IFilter>> m_filters;
        std::weak_ptr<Target>             m_target;

    public:
        FilterChain() = default;

        void addFilter(const std::shared_ptr<IFilter>& filter)
        {
            m_filters.push_back(filter);
        }

        void removeFilter(const std::shared_ptr<IFilter>& filter)
        {
            // https://stackoverflow.com/questions/10120623/removing-item-from-list-of-weak-ptrs

            m_filters.remove_if([&](std::weak_ptr<IFilter> wp) {
                return !filter.owner_before(wp) && !wp.owner_before(filter);
                }
            );
        }

        void setTarget(const std::shared_ptr<Target>& target)
        {
            m_target = target;
        }

        void executeRequest(std::string request)
        {
            std::shared_ptr<Target> target{ m_target.lock() };
            if (target == nullptr) {
                std::cout << "Target Object doesn't exist anymore!" << std::endl;
                return;
            }

            for (const std::weak_ptr<IFilter>& filter : m_filters) {
                std::shared_ptr<IFilter> tmp{ filter.lock() };
                if (tmp != nullptr) {
                    tmp->execute(request);
                }
            }

            target->operation(request);
        }
    };

    class FilterManager
    {
    private:
        std::weak_ptr<FilterChain> m_chain;

    public:
        FilterManager() {}

        void setFilterChain(std::shared_ptr<FilterChain>& chain)
        {
            m_chain = chain;
        }

        void request(std::string request)
        {
            std::shared_ptr<FilterChain> chain{ m_chain.lock() };
            if (chain != nullptr) {
                chain->executeRequest(request);
            }
        }
    };

    class Client
    {
    private:
        FilterManager m_filterManager;

    public:
        Client() {};

        void setFilterManager(const FilterManager& filterManager)
        {
            m_filterManager = filterManager;
        }

        void sendRequest(const std::string& request)
        {
            m_filterManager.request(request);
        }
    };
}

// ---------------------------------------------------------------------------

void test_conceptual_example_01()
{
    using namespace ConceptualExample01;

    std::shared_ptr<Target> target{ std::make_shared<Target>() };
    std::shared_ptr<FilterChain> chain{ std::make_shared<FilterChain>() };
    chain->setTarget(target);

    std::shared_ptr<IFilter> filter1{ std::make_shared<DebugFilter>() };
    std::shared_ptr<IFilter> filter2{ std::make_shared<AuthenticationFilter>() };
    chain->addFilter(filter1);
    chain->addFilter(filter2);

    FilterManager filterManager{};
    filterManager.setFilterChain(chain);

    Client client{};
    client.setFilterManager(filterManager);
    client.sendRequest("Starting Downloads");
}

void test_conceptual_example_02()
{

    using namespace ConceptualExample01;

    std::shared_ptr<Target> target{ std::make_shared<Target>() };
    std::shared_ptr<FilterChain> chain{ std::make_shared<FilterChain>() };
    chain->setTarget(target);

    std::shared_ptr<IFilter> filter1{ std::make_shared<DebugFilter>() };
    std::shared_ptr<IFilter> filter2{ std::make_shared<AuthenticationFilter>() };
    chain->addFilter(filter1);
    chain->addFilter(filter2);

    FilterManager filterManager{};
    filterManager.setFilterChain(chain);

    Client client{};
    client.setFilterManager(filterManager);
    client.sendRequest("Starting Downloads");

    chain->removeFilter(filter1);
    client.sendRequest("Starting Downloads again");

    chain->removeFilter(filter2);
    client.sendRequest("Starting Downloads once again");
}

// ===========================================================================
// End-of-File
// ===========================================================================
