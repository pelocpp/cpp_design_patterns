// ===========================================================================
// ConceptualExample.cpp // Proxy Pattern
// ===========================================================================

#include <memory>
#include <print>
#include <utility>

namespace ConceptualExample_Proxy_Pattern {

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
     *
     * Note: currently coupled specifically to RealSubject (not SubjectBase),
     * since it needs to be able to construct it lazily. If you want the proxy
     * to wrap arbitrary SubjectBase implementations, lazy-loading must be
     * dropped (or a factory/std::function<std::unique_ptr<SubjectBase>()>
     * injected instead). But normally a Proxy class is designed for a
     * specific target class.
     */
    class Proxy final : public SubjectBase
    {
    private:
        // the proxy typically represents exactly one concrete type
        mutable std::unique_ptr<RealSubject> m_realSubject;
        // mutable because lazy initialization happens in a logically const operation

    public:
        /**
         * The Proxy maintains a reference to an object of the RealSubject class.
         * It can either be injected by the client, or left empty for lazy-loading
         * (created on first request()).
         */

        explicit Proxy(std::unique_ptr<RealSubject> subject = nullptr)
            : m_realSubject{ std::move(subject) }
        {}

        void request() const override {

            if (!checkAccess()) {
                return;
            }

            /**
            * True lazy-loading implementation:
            * We create the heavy RealSubject object only when request() is called:
            */
            if (!m_realSubject) {
                std::println("Proxy: RealSubject is null - creating it now (Lazy Loading) ...");
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

    private:
        [[nodiscard]]
        bool checkAccess() const noexcept {
            // some real checks should go here.
            std::println("Proxy: Checking access prior to executing a real request.");
            return true;
        }

        void logAccess() const noexcept {
            std::println("Proxy: Logging the time of request.");
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
}

void test_conceptual_example()
{
    using namespace ConceptualExample_Proxy_Pattern;

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
    clientCode(lazyProxy);   // only here is the RealSubject created in the background.
}

// ===========================================================================
// End-of-File
// ===========================================================================
