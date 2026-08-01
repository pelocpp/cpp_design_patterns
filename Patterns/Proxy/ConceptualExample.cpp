// ===========================================================================
// ConceptualExample.cpp // Proxy Pattern
// ===========================================================================

#include <memory>
#include <print>

/**
 * The SubjectBase interface declares common operations for both 'RealSubject'
 *    and the 'Proxy'. As long as the client works with 'RealSubject'
 *    using this interface, you'll be able to pass it a proxy
 *    instead of a real subject.
 */
class SubjectBase 
{
public:
    virtual ~SubjectBase() = default;
    virtual void request() const = 0;
};

/**
 * The RealSubject contains some core business logic. Usually, RealSubjects are
 * capable of doing some useful work which may also be very slow or sensitive -
 * e.g. correcting input data. A Proxy can solve these issues without any
 * changes to the RealSubject's code.
 */
class RealSubject final : public SubjectBase
{
public:
    void request() const override {
        std::println("RealSubject: Handling request.");
    }
};

/**
 * The Proxy has an interface identical to the RealSubject.
 */
class Proxy final : public SubjectBase
{
private:
    mutable std::unique_ptr<SubjectBase> m_realSubject;

    bool checkAccess() const {
        // some real checks should go here.
        std::println("Proxy: Checking access prior to executing a real request."); 
        return true;
    }

    void logAccess() const {
        std::println("Proxy: Logging the time of request.");
    }

public:
    /**
     * The Proxy maintains a reference to an object of the RealSubject class. It
     * can be either lazy-loaded or passed to the Proxy by the client.
     */

    // Option 1: The object is passed in from the outside (kind of dependency injection).
    // Flexible Variant: Accepts any SubjectBase, not just RealSubject

    explicit Proxy(std::unique_ptr<SubjectBase> subject)
        : m_realSubject{ std::move(subject) }
    {}

    // Option 2: Lazy-loading constructor
    // The actual object does not exist initially, this is saving resources.

    Proxy() : m_realSubject{ nullptr } {}

    void request() const override {

        if (checkAccess()) {

            /**
             * True lazy-loading implementation:
             * We create the heavy RealSubject object only when request() is called:
             */
            if (!m_realSubject) {
                std::println("Proxy: RealSubject is null. Creating it now (Lazy Loading) ...");
                m_realSubject = std::make_unique<RealSubject>();
            }

            /**
             * The most common applications of the Proxy pattern are lazy loading,
             * caching, controlling the access, logging, etc. A Proxy can perform one of
             * these things and then, depending on the result, pass the execution to the
             * same method in a linked RealSubject object.
             */
            m_realSubject->request();
            logAccess();
        }
    }
};

/**
 * The client code is supposed to work with all objects (both subjects and
 * proxies) via the SubjectBase interface in order to support both real subjects and proxies. 
 * In real life, however, clients mostly work with their real subjects
 * directly. In this case, to implement the pattern more easily, you can extend
 * your proxy from the real subject's class.
 */
static void clientCode(const SubjectBase& subject) {

    subject.request();
}

void test_conceptual_example()
{
    std::println("Client: Executing the client code with a real subject:");    
    // no std::move, no forced heap allocation in the test code
    RealSubject realSubject;
    clientCode(realSubject);
    std::println();

    std::println("Client: Executing with a proxy (Injected Subject):");
    auto dynamicRealSubject = std::make_unique<RealSubject>();
    Proxy proxyWithInjection{ std::move(dynamicRealSubject) };
    clientCode(proxyWithInjection);
    std::println();

    std::println("Client: Executing with a lazy proxy (No initial subject):");
    Proxy lazyProxy;         // RealSubject is not yet created!
    clientCode(lazyProxy);   // Only here is the RealSubject created in the background.
}

// ===========================================================================
// End-of-File
// ===========================================================================
