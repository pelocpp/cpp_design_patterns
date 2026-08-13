// ===========================================================================
// ConceptualExample.cpp // Template Method
// ===========================================================================

#include <memory>
#include <print>

namespace ConceptualExample_Template_Method_Pattern {

    /**
     * The Abstract Class defines a template method that contains a skeleton of some
     * algorithm, composed of calls to (usually) abstract primitive operations.
     *
     * Concrete subclasses should implement these operations, but leave the template
     * method itself intact.
     */
    class AbstractClass {

    public:
        AbstractClass() = default; // Base class should not be directly instantiable

        virtual ~AbstractClass() = default;

        AbstractClass(const AbstractClass&) = delete;
        AbstractClass& operator=(const AbstractClass&) = delete;
        AbstractClass(AbstractClass&&) = delete;
        AbstractClass& operator=(AbstractClass&&) = delete;

        /**
         * The template method defines the skeleton of an algorithm:
         * Non-virtual: Subclasses must not redefine the algorithm.
         */

        void TemplateMethod() const
        {
            BaseOperation1();             // overriden, but it's not mandatory

            RequiredOperation1();         // MUST be overriden

            if (ShouldExecuteBranch()) {  // MUST be overriden

                BaseOperation2();         // overriden, but it's not mandatory
                Hook1();                  // overriden, but it's not mandatory
            }
            else
            {
                RequiredOperation2();     // MUST be overriden
                BaseOperation3();         // overriden, but it's not mandatory
                Hook2();                  // overriden, but it's not mandatory
            }
        }

        /**
         * These operations already have implementations.
         */
    protected:
        virtual void BaseOperation1() const {
            std::println("AbstractClass says: I am doing the bulk of the work");
        }

        virtual void BaseOperation2() const {
            std::println("AbstractClass says: But I let subclasses override some operations");
        }

        virtual void BaseOperation3() const {
            std::println("AbstractClass says: But I am doing the bulk of the work anyway");
        }

        /**
         * These operations have to be implemented in subclasses.
         */
        virtual bool ShouldExecuteBranch() const = 0;
        virtual void RequiredOperation1() const = 0;
        virtual void RequiredOperation2() const = 0;

        /**
         * These are "hooks." Subclasses may override them, but it's not mandatory
         * since the hooks already have default (but empty) implementation.
         * Hooks provide additional extension points in some crucial places of the
         * algorithm.
         */
        virtual void Hook1() const {}  // default: do nothing
        virtual void Hook2() const {}  // default: do nothing
    };

    /**
     * Concrete classes have to implement all abstract operations of the base class.
     * They can also override some operations with a default implementation.
     */
    class ConcreteClass1 final : public AbstractClass {
    protected:
        bool ShouldExecuteBranch() const override {
            std::println("ConcreteClass1 says: Implemented ShouldExecuteBranch decision");
            return true;
        }

        void RequiredOperation1() const override {
            std::println("ConcreteClass1 says: Implemented required Operation1");
        }

        void RequiredOperation2() const override {
            std::println("ConcreteClass1 says: Implemented required Operation2");
        }
    };

    /**
     * Usually, concrete classes override only a fraction of base class' operations.
     */
    class ConcreteClass2 final : public AbstractClass {
    protected:
        bool ShouldExecuteBranch() const override {
            std::println("ConcreteClass2 says: Implemented ShouldExecuteBranch decision");
            return false;
        }

        void RequiredOperation1() const override {
            std::println("ConcreteClass2 says: Implemented required Operation1");
        }

        void RequiredOperation2() const override {
            std::println("ConcreteClass2 says: Implemented required Operation2");
        }

        void BaseOperation1() const override {
            std::println("ConcreteClass2 says: Overridden BaseOperation1");
        }

        void Hook1() const override {
            std::println("ConcreteClass2 says: Overridden Hook1");
        }
    };

    /**
     * The client code calls the template method to execute the algorithm. Client
     * code does not have to know the concrete class of an object it works with, as
     * long as it works with objects through the interface of their base class.
     */
    static void clientCode(const AbstractClass& obj) {
        // ...
        obj.TemplateMethod();
        // ...
    }
}

void test_conceptual_example() {

    using namespace ConceptualExample_Template_Method_Pattern;

    std::println("Same client code can work with different subclasses (1):");
    ConcreteClass1 concreteObject1;
    clientCode(concreteObject1);
    std::println();

    std::println("Same client code can work with different subclasses (2):");
    ConcreteClass2 concreteObject2;
    clientCode(concreteObject2);
    std::println();
}

// ===========================================================================
// End-of-File
// ===========================================================================
