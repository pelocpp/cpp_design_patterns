// ===========================================================================
// ConceptualExample02.cpp // Intercepting Filter Pattern // added second queue
// ===========================================================================

#include <iostream>
#include <string>
#include <list>
#include <memory>

namespace ConceptualExample02 {

    enum class FilterType
    {
        PreFilter,
        PostFilter
    };

    class IFilter
    {
    public:
        virtual void execute(const std::string& request) = 0;
    };

    class PreDebugFilter : public IFilter
    {
    public:
        virtual void execute(const std::string& request) override {
            std::cout << ">>>: " << request << std::endl;
        }
    };

    class PostDebugFilter : public IFilter
    {
    public:
        virtual void execute(const std::string& request) override {
            std::cout << "<<<: " << request << std::endl;
        }
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

    class Target
    {
    public:
        void operation(const std::string& request) {
            std::cout << "Executing Request: " << request << std::endl;
        }
    };

    class FilterChain
    {
    private:
        std::list<std::shared_ptr<IFilter>> m_prefilters;
        std::list<std::shared_ptr<IFilter>> m_postFilters;
        std::shared_ptr<Target> m_target;

    public:
        FilterChain()
        {
            m_target = nullptr;
        }

        void addFilter(FilterType type, const std::shared_ptr<IFilter>& filter)
        {
            if (type == FilterType::PreFilter)
                m_prefilters.push_back(filter);
            else
                m_postFilters.push_back(filter);
        }

        void removeFilter(FilterType type, const std::shared_ptr<IFilter>& filter)
        {
            if (type == FilterType::PreFilter)
                m_prefilters.remove(filter);
            else
                m_postFilters.remove(filter);
        }

        void setTarget(const std::shared_ptr<Target>& target)
        {
            m_target = target;
        }

        void executeRequest(std::string request)
        {
            for (const std::shared_ptr<IFilter>& filter : m_prefilters) {
                filter->execute(request);
            }

            m_target->operation(request);

            for (const std::shared_ptr<IFilter>& filter : m_postFilters) {
                filter->execute(request);
            }
        }
    };

    class FilterManager
    {
    private:
        std::shared_ptr<FilterChain> m_filterChain;

    public:
        FilterManager() {};

        void setFilterChain(std::shared_ptr<FilterChain>& chain)
        {
            m_filterChain = chain;
        }

        void request(std::string request)
        {
            m_filterChain->executeRequest(request);
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

void test_conceptual_example_03()
{
    using namespace ConceptualExample02;

    std::shared_ptr<Target> target = std::make_shared<Target>();
    std::shared_ptr<FilterChain> chain = std::make_shared<FilterChain>();

    chain->setTarget(target);
    std::shared_ptr<IFilter> filter1 = std::make_shared<PreDebugFilter>();
    std::shared_ptr<IFilter> filter2 = std::make_shared<PostDebugFilter>();
    chain->addFilter(FilterType::PreFilter, filter1);
    chain->addFilter(FilterType::PostFilter, filter2);

    FilterManager filterManager;
    filterManager.setFilterChain(chain);

    Client client;
    client.setFilterManager(filterManager);
    client.sendRequest("Starting Downloads");
}

// ===========================================================================
// End-of-File
// ===========================================================================
