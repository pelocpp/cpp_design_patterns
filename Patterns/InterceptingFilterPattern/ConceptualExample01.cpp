// ===========================================================================
// ConceptualExample01.cpp // Intercepting Filter Pattern
// ===========================================================================

#include <algorithm>
#include <memory>
#include <print>
#include <string>
#include <string_view>
#include <vector>

namespace ConceptualExample_Intercepting_Filter {

    class IFilter
    {
    public:
        virtual ~IFilter() = default;

        [[nodiscard]]
        virtual bool execute(std::string_view request) = 0;
    };

    class DebugFilter final : public IFilter
    {
    public:
        [[nodiscard]]
        bool execute(std::string_view request) override {
            std::println("[Log Request: {}]", request);
            return true;
        }
    };

    class AuthenticationFilter final : public IFilter
    {
    public:
        [[nodiscard]]
        bool execute(std::string_view request) override {
            std::println("[Authenticating Request: {}]", request);
            return true;
        }
    };

    // ---------------------------------------------------------------------------

    class Target
    {
    public:
        void operation(std::string_view request) {
            std::println("Executing Request: {}", request);
        }
    };

    // ---------------------------------------------------------------------------

    class FilterChain final
    {
    private:
        std::vector<std::unique_ptr<IFilter>> m_filters;
        Target&                               m_target;

    public:
        explicit FilterChain(Target& target)
            : m_target{ target }
        {}

        IFilter* addFilter(std::unique_ptr<IFilter> filter)
        {
            m_filters.push_back(std::move(filter));
            return m_filters.back().get();
        }

        void removeFilter(const IFilter* filter)
        {
            std::erase_if(m_filters, [filter](const auto& f) {
                return f.get() == filter;
                }
            );
        }
        
        bool executeRequest(std::string_view request)
        {
            bool allPassed = std::all_of(
                m_filters.begin(), 
                m_filters.end(),
                [&](const auto& filter) {
                    return filter->execute(request);
                }
            );

            if (allPassed) {
                m_target.operation(request);
            }

            return allPassed;
        }
    };

    class FilterManager final
    {
    private:
        FilterChain& m_chain;

    public:
        explicit FilterManager(FilterChain& chain) : m_chain{chain} {}

        void request(std::string_view request)
        {
            bool passed = m_chain.executeRequest(request);
            std::println("Request {} passed: {}", request, passed);
        }
    };

    class Client final
    {
    private:
        FilterManager& m_filterManager;

    public:
        explicit Client(FilterManager& filterManager)
            : m_filterManager{ filterManager }  
        {}

        void sendRequest(const std::string& request)
        {
            m_filterManager.request(request);
        }
    };
}

// ---------------------------------------------------------------------------

void test_conceptual_example_01()
{
    using namespace ConceptualExample_Intercepting_Filter;

    Target target;

    FilterChain chain{ target };

    chain.addFilter(std::make_unique<DebugFilter>());
    chain.addFilter(std::make_unique<AuthenticationFilter>());

    FilterManager filterManager{ chain };

    Client client{ filterManager };

    client.sendRequest("Starting Downloads");
}

void test_conceptual_example_02()
{
    using namespace ConceptualExample_Intercepting_Filter;

    Target target;

    FilterChain chain{ target };

    auto filter1 = std::make_unique<DebugFilter>();
    auto filter2 = std::make_unique<AuthenticationFilter>();

    auto filterPrt1 = chain.addFilter(std::move(filter1));
    auto filterPrt2 = chain.addFilter(std::move(filter2));

    FilterManager filterManager{ chain };

    Client client{ filterManager };

    client.sendRequest("Starting Downloads");
    std::println();

    chain.removeFilter(filterPrt1);
    client.sendRequest("Starting Downloads again");
    std::println();

    chain.removeFilter(filterPrt2);
    client.sendRequest("Starting Downloads once again");
    std::println();
}

// ===========================================================================
// End-of-File
// ===========================================================================
