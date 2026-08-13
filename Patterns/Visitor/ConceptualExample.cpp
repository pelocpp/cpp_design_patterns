// ===========================================================================
// ConceptualExample.cpp // Visitor Pattern
// ===========================================================================

#include <memory>
#include <print>
#include <span>
#include <string>
#include <string_view>
#include <vector>

namespace ConceptualExample_Visitor_Pattern {

    /**
     * The Visitor Interface declares a set of visiting methods
     * that correspond to component classes.
     * The signature of a visiting method allows the visitor to
     * identify the exact class of the component that it's dealing with.
     */

    // forward declaration - see short variant below
    class ConcreteComponentA;
    class ConcreteComponentB;
    class ConcreteComponentC;

    class VisitorBase {
    public:
        virtual ~VisitorBase() = default;

        virtual void visit(const ConcreteComponentA&) = 0;
        virtual void visit(const ConcreteComponentB&) = 0;
        virtual void visit(const ConcreteComponentC&) = 0;
    };

    /**
     * The ElementBase interface declares an `accept` method that should take
     * the base visitor interface as an argument.
     */
    class ElementBase
    {
    public:
        virtual ~ElementBase() = default;

        virtual void accept(VisitorBase& visitor) const = 0;
    };

    /**
     * Each Concrete Component must implement the `accept` method in such a way that
     * it calls the visitor's method corresponding to the component's class.
     */
    class ConcreteComponentA final : public ElementBase
    {
    public:
        /**
         * Note that we're calling `visit (ConcreteComponentA)`, which matches the
         * current class name. This way we let the visitor know the class of the
         * component it works with.
         */
        void accept(VisitorBase& visitor) const override {
            visitor.visit(*this);
        }

        /**
         * Concrete Components may have special methods that don't exist in their base
         * class or interface. The Visitor is still able to use these methods since
         * it's aware of the component's concrete class.
         */
        [[nodiscard]]
        std::string_view exclusiveMethodOfConcreteComponentA() const { return "A"; }
    };

    class ConcreteComponentB final : public ElementBase
    {
    public:
        /**
         * Same here: visit => ConcreteComponentB
         */
        void accept(VisitorBase& visitor) const override {
            visitor.visit(*this);
        }

        [[nodiscard]]
        std::string_view specialMethodOfConcreteComponentB() const { return "B"; }
    };

    class ConcreteComponentC final : public ElementBase
    {
    public:
        void accept(VisitorBase& visitor) const override {
            visitor.visit(*this);
        }

        [[nodiscard]]
        std::string_view anotherMethodOfConcreteComponentC() const { return "C"; }
    };

    // =======================================================================
    // DATEN ... loose Kopplung ... Prinzip
    // -----------------------------------------------------------------------
    // OPERATIONEN ... greifen auf die Daten zu
    // =======================================================================

    /**
     * Concrete Visitors implement several versions of the same algorithm,
     * which can work with all concrete component classes.
     *
     * You can experience the biggest benefit of the Visitor pattern when using it
     * with a complex object structure, such as a Composite tree. In this case, it
     * might be helpful to store some intermediate state of the algorithm while
     * executing visitor's methods over various objects of the structure.
     */
    class ConcreteVisitor1 : public VisitorBase
    {
    public:
        void visit(const ConcreteComponentA& element) override {
            std::println("{} + ConcreteVisitor1", element.exclusiveMethodOfConcreteComponentA());
        }

        void visit(const ConcreteComponentB& element) override {
            std::println("{} + ConcreteVisitor1", element.specialMethodOfConcreteComponentB());
        }

        void visit(const ConcreteComponentC& element)  override {
            std::println("{} + ConcreteVisitor1", element.anotherMethodOfConcreteComponentC());
        }
    };

    class ConcreteVisitor2 : public VisitorBase
    {
    public:
        void visit(const ConcreteComponentA& element) override {
            std::println("{} + ConcreteVisitor2", element.exclusiveMethodOfConcreteComponentA());
        }

        void visit(const ConcreteComponentB& element) override {
            std::println("{} + ConcreteVisitor2", element.specialMethodOfConcreteComponentB());
        }

        void visit(const ConcreteComponentC& element) override {  
            std::println("{} + ConcreteVisitor2", element.anotherMethodOfConcreteComponentC());
        }
    };

    /**
     * The client code can run visitor operations over any set of elements without
     * figuring out their concrete classes. The accept operation directs a call to
     * the appropriate operation in the visitor object.
     */
    static void clientCode(
        std::span<const std::unique_ptr<ElementBase>> components,
        VisitorBase& visitor)
    {
        for (/*const*/ auto& comp : components) {
            comp->accept(visitor);
        }
    }
}

void test_conceptual_example_01() {

    using namespace ConceptualExample_Visitor_Pattern;

    std::vector<std::unique_ptr<ElementBase>> components;

    components.push_back(std::make_unique<ConcreteComponentA>());
    components.push_back(std::make_unique<ConcreteComponentB>());
    components.push_back(std::make_unique<ConcreteComponentC>());

    std::println("The client code works with all visitors via the base Visitor interface:");
    ConcreteVisitor1 visitor1;
    clientCode(components, visitor1);
    std::println();

    std::println("It allows the same client code to work with different types of visitors");
    ConcreteVisitor2 visitor2;
    clientCode(components, visitor2);
    std::println();
}

// ===========================================================================
// End-of-File
// ===========================================================================
