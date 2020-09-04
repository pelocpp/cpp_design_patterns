// ===========================================================================
// ConceptualExample.cpp // Visitor Pattern
// ===========================================================================

#include <iostream>
#include <string>
#include <array>
#include <memory>

namespace ConceptualExample {

    /**
     * The Visitor Interface declares a set of visiting methods that correspond to
     * component classes. The signature of a visiting method allows the visitor to
     * identify the exact class of the component that it's dealing with.
     */

    // forward declaration - see short variant below
    // class ConcreteComponentA;
    // class ConcreteComponentB;

    class VisitorBase {
    public:
        virtual void visit(const class ConcreteComponentA* element) const = 0;
        virtual void visit(const class ConcreteComponentB* element) const = 0;
    };

    /**
     * The ElementBase interface declares an `accept` method that should take the base
     * visitor interface as an argument.
     */

    class ElementBase {
    public:
        virtual ~ElementBase() {}
        virtual void accept(VisitorBase* visitor) const = 0;
    };

    /**
     * Each Concrete Component must implement the `accept` method in such a way that
     * it calls the visitor's method corresponding to the component's class.
     */
    class ConcreteComponentA : public ElementBase {
    public:
        /**
         * Note that we're calling `visit (ConcreteComponentA)`, which matches the
         * current class name. This way we let the visitor know the class of the
         * component it works with.
         */
        virtual void accept(VisitorBase* visitor) const override {
            visitor->visit(this);
        }

        /**
         * Concrete Components may have special methods that don't exist in their base
         * class or interface. The Visitor is still able to use these methods since
         * it's aware of the component's concrete class.
         */
        std::string ExclusiveMethodOfConcreteComponentA() const { return "A"; }
    };

    class ConcreteComponentB : public ElementBase {
    public:
        /**
         * Same here: visitConcreteComponentB => ConcreteComponentB
         */
        virtual void accept(VisitorBase* visitor) const override {
            visitor->visit(this);
        }

        std::string SpecialMethodOfConcreteComponentB() const { return "B"; }
    };

    /**
     * Concrete Visitors implement several versions of the same algorithm,
     * which can work with all concrete component classes.
     *
     * You can experience the biggest benefit of the Visitor pattern when using it
     * with a complex object structure, such as a Composite tree. In this case, it
     * might be helpful to store some intermediate state of the algorithm while
     * executing visitor's methods over various objects of the structure.
     */
    class ConcreteVisitor1 : public VisitorBase {
    public:
        virtual void visit(const ConcreteComponentA* element) const override {
            std::cout
                << element->ExclusiveMethodOfConcreteComponentA()
                << " + ConcreteVisitor1"
                << std::endl;
        }

        virtual void visit(const ConcreteComponentB* element) const override {
            std::cout 
                << element->SpecialMethodOfConcreteComponentB()
                << " + ConcreteVisitor1"
                << std::endl;
        }
    };

    class ConcreteVisitor2 : public VisitorBase {
    public:
        virtual void visit(const ConcreteComponentA* element) const override {
            std::cout 
                << element->ExclusiveMethodOfConcreteComponentA() 
                << " + ConcreteVisitor2"
                << std::endl;
        }

        virtual void visit(const ConcreteComponentB* element) const override {
            std::cout
                << element->SpecialMethodOfConcreteComponentB() 
                << " + ConcreteVisitor2"
                << std::endl;
        }
    };

    /**
     * The client code can run visitor operations over any set of elements without
     * figuring out their concrete classes. The accept operation directs a call to
     * the appropriate operation in the visitor object.
     */
    void ClientCode(std::array<const ElementBase*, 2> components, VisitorBase* visitor) {

        for (const ElementBase* comp : components) {
            comp->accept(visitor);
        }
    }
}

void test_conceptual_example() {

    using namespace ConceptualExample;

    std::array<const ElementBase*, 2> components = { new ConcreteComponentA, new ConcreteComponentB };
    std::cout << "The client code works with all visitors via the base Visitor interface:\n";
    ConcreteVisitor1* visitor1 = new ConcreteVisitor1;
    ClientCode(components, visitor1);
    std::cout << std::endl;
    std::cout << "It allows the same client code to work with different types of visitors:\n";
    ConcreteVisitor2* visitor2 = new ConcreteVisitor2;
    ClientCode(components, visitor2);

    for (const ElementBase* comp : components) {
        delete comp;
    }
    delete visitor1;
    delete visitor2;
}

// ===========================================================================
// End-of-File
// ===========================================================================
