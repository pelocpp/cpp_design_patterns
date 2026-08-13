// ===========================================================================
// ConceptualExample:CRTP.cpp // Template Method
// ===========================================================================

#include <memory>
#include <print>

namespace ConceptualExample_Template_Method_Pattern_CRTP {

    template <typename Derived>
    class AbstractClassCRTP {
    public:
        void TemplateMethod() const {
            self().BaseOperation1();
            self().RequiredOperation1();
            if (self().ShouldExecuteBranch()) {
                self().BaseOperation2();
                self().Hook1();
            }
            else {
                self().RequiredOperation2();
                self().BaseOperation3();
                self().Hook2();
            }
        }

        void BaseOperation1() const { std::println("Default BaseOperation1"); }
        void BaseOperation2() const { std::println("Default BaseOperation2"); }
        void BaseOperation3() const { std::println("Default BaseOperation3"); }
        void Hook1() const {}
        void Hook2() const {}

    private:
        const Derived& self() const { return static_cast<const Derived&>(*this); }
    };

    class ConcreteClass1 : public AbstractClassCRTP<ConcreteClass1> {
    public:
        bool ShouldExecuteBranch() const { return true; }
        void RequiredOperation1() const { std::println("ConcreteClass1: Required1"); }
        void RequiredOperation2() const { std::println("ConcreteClass1: Required2"); }
    };

    static void clientCode(const AbstractClassCRTP<ConcreteClass1>& obj) {
        // ...
        obj.TemplateMethod();
        // ...
    }
}

void test_conceptual_example_crtp() {

    using namespace ConceptualExample_Template_Method_Pattern_CRTP;

    std::println("Same client code can work with different subclasses (1):");
    ConcreteClass1 concreteObject1;
    clientCode(concreteObject1);
    std::println();
}

// ===========================================================================
// End-of-File
// ===========================================================================
