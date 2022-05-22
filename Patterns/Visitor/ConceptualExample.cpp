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
        // using "raw" pointers
        virtual void visit(const class ConcreteComponentA* element) const = 0;
        virtual void visit(const class ConcreteComponentB* element) const = 0;

        // using shared pointers
        virtual void visit2(const std::shared_ptr<const class ConcreteComponentA> element) const = 0;
        virtual void visit2(const std::shared_ptr<const class ConcreteComponentB> element) const = 0;
        virtual void visit2(const std::shared_ptr<const class ConcreteComponentC> element) const = 0;

        // other names (e.g. no method overloading) is also possible
        // virtual void visitConcreteComponentA(const class ConcreteComponentA* element) const = 0;
        // virtual void visitConcreteComponentB(const class ConcreteComponentB* element) const = 0;

        // other names (e.g. no method overloading) is also possible
        // virtual void visitConcreteComponentA(std::shared_ptr<const class ConcreteComponentA> element) = 0;
        // virtual void visitConcreteComponentB(std::shared_ptr<const class ConcreteComponentB> element) = 0;
        // virtual void visitConcreteComponentC(std::shared_ptr<const class ConcreteComponentC> element) = 0;
    };

    /**
     * The ElementBase interface declares an `accept` method that should take
     * the base visitor interface as an argument.
     */
    class ElementBase {
    public:
        virtual ~ElementBase() {}
        virtual void accept(std::shared_ptr<VisitorBase> visitor) const = 0;
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
        virtual void accept(std::shared_ptr<VisitorBase> visitor) const override {
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
        virtual void accept(std::shared_ptr<VisitorBase> visitor) const override {
            visitor->visit(this);
        }

        std::string SpecialMethodOfConcreteComponentB() const { return "B"; }
    };

    // demonstrating use of 'enable_shared_from_this' and 'shared_from_this'
    class ConcreteComponentC : public ElementBase, public std::enable_shared_from_this<ConcreteComponentC> {
    public:
        virtual void accept(std::shared_ptr<VisitorBase> visitor) const override {
            const std::shared_ptr<const ConcreteComponentC> me = shared_from_this();
            visitor->visit2(me);
        }
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

        virtual void visit2(const std::shared_ptr<const class ConcreteComponentA> element) const override {
            std::cout
                << element->ExclusiveMethodOfConcreteComponentA()
                << " + ConcreteVisitor1"
                << std::endl;
        }

        virtual void visit2(const std::shared_ptr<const class ConcreteComponentB> element) const override {
            std::cout
                << element->SpecialMethodOfConcreteComponentB()
                << " + ConcreteVisitor1"
                << std::endl;
        }

        virtual void visit2(const std::shared_ptr<const class ConcreteComponentC> element)  const override {
            std::cout
                << "C + ConcreteVisitor1"
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

        virtual void visit2(const std::shared_ptr<const class ConcreteComponentA> element) const override {
            std::cout
                << element->ExclusiveMethodOfConcreteComponentA()
                << " + ConcreteVisitor2"
                << std::endl;
        }

        virtual void visit2(const std::shared_ptr<const class ConcreteComponentB> element) const override {
            std::cout
                << element->SpecialMethodOfConcreteComponentB()
                << " + ConcreteVisitor2"
                << std::endl;
        }

        virtual void visit2(const std::shared_ptr<const class ConcreteComponentC> element)  const override {
            std::cout
                << "C + ConcreteVisitor2"
                << std::endl;
        }
    };

    /**
     * The client code can run visitor operations over any set of elements without
     * figuring out their concrete classes. The accept operation directs a call to
     * the appropriate operation in the visitor object.
     */
    void clientCode(
        std::array<std::shared_ptr<ElementBase>, 3> components,
        std::shared_ptr<VisitorBase> visitor) 
    {
        for (std::shared_ptr<ElementBase> comp : components) {
            comp->accept(visitor);
        }
    }
}

void test_conceptual_example() {

    using namespace ConceptualExample;

    std::array<std::shared_ptr<ElementBase>, 3> components = {
        std::make_shared<ConcreteComponentA>(), 
        std::make_shared<ConcreteComponentB>(),
        std::make_shared<ConcreteComponentC>()
    };

    std::cout << "The client code works with all visitors via the base Visitor interface:\n";
    std::shared_ptr<VisitorBase> visitor1 = std::make_shared<ConcreteVisitor1>();
    clientCode(components, visitor1);
    std::cout << std::endl;

    std::cout << "It allows the same client code to work with different types of visitors:\n";
    std::shared_ptr<VisitorBase> visitor2 = std::make_shared<ConcreteVisitor2>();
    clientCode(components, visitor2);
}

// ===========================================================================
// End-of-File
// ===========================================================================
