// ===========================================================================
// ConceptualExample.cpp // Intercepting Filter Pattern
// ===========================================================================

#include <iostream>
#include <string>
#include <list>
#include <memory>

class IFilter
{
public:
    virtual void execute(const std::string& request) = 0;
};

class DebugFilter : public IFilter
{
public:
    virtual void execute(const std::string& request) override {
        std::cout << "Log Request: " << request << std::endl;
    }
};

class AuthenticationFilter : public IFilter
{
public:
    virtual void execute(const std::string& request) override {
        std::cout << "Authenticating Request: " << request << std::endl;
    }
};

class Target
{
public:
    void execute(const std::string& request) {
        std::cout << "Executing Request: " << request << std::endl;
    }
};

class FilterChain
{
private:
    std::list<std::shared_ptr<IFilter>> m_filters;
    std::shared_ptr<Target> m_target;

public:
    FilterChain()
    {
        m_target = nullptr;
    }

    void addFilter(const std::shared_ptr<IFilter>& filter)
    {
        m_filters.push_back(filter);
    }

    void removeFilter(const std::shared_ptr<IFilter>& filter)
    {
        m_filters.remove(filter);
    }

    void setTarget(const std::shared_ptr<Target>& target)
    {
        m_target = target;
    }

    void execute(std::string request)
    {
        for (const std::shared_ptr<IFilter>& filter : m_filters) {
            filter->execute(request);
        }

        m_target->execute(request);
    }
};

class FilterManager
{
private:
    FilterChain m_filterChain;

public:
    FilterManager() = default;

    FilterManager(const std::shared_ptr<Target>& target)
    {
        m_filterChain.setTarget(target);
    }

    void setFilter(const std::shared_ptr<IFilter>& filter)
    {
        m_filterChain.addFilter(filter);
    }

    void filterRequest(std::string request)
    {
        m_filterChain.execute(request);
    }
};

class Client
{
private:
    FilterManager m_filterManager;

public:
    Client() = default;

    void setFilterManager(const FilterManager& filterManager)
    {
        m_filterManager = filterManager;
    }

    void sendRequest(const std::string& request)
    {
        m_filterManager.filterRequest(request);
    }
};

void test_conceptual_example() {

    std::shared_ptr<Target> target = std::make_shared<Target>();
    FilterManager filterManager(target);

    std::shared_ptr<IFilter> filter1 = std::make_shared<DebugFilter>();
    filterManager.setFilter(filter1);

    std::shared_ptr<IFilter> filter2 = std::make_shared<AuthenticationFilter>();
    filterManager.setFilter(filter2);

    Client* client = new Client();
    client->setFilterManager(filterManager);
    client->sendRequest("Starting Downloads");
}

// ===========================================================================
// End-of-File
// ===========================================================================
