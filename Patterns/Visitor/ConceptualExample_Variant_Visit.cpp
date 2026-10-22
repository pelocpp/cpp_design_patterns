// ===========================================================================
// ConceptualExample_Variant_Visit.cpp // Visitor Pattern - Mopdern C++
// ===========================================================================

#include <print>
#include <span>
#include <string_view>
#include <variant>
#include <vector>

namespace ConceptualExample_Visitor_Pattern_Modern {

    // =======================================================================
    // Components: plain value types, no common base class, no virtuals needed.
    // =======================================================================

    class ConcreteComponentA final
    {
    public:
        std::string_view exclusiveMethodOfConcreteComponentA() const { return "A"; }
    };

    class ConcreteComponentB final
    {
    public:
        std::string_view specialMethodOfConcreteComponentB() const { return "B"; }
    };

    class ConcreteComponentC final
    {
    public:
        std::string_view anotherMethodOfConcreteComponentC() const { return "C"; }
    };

    // =======================================================================
    // "Visitors" are now just callable overload sets - no base class,
    // no accept()/visit() plumbing. Each free function below plays the role
    // of one former ConcreteVisitor.
    // =======================================================================

    class ConcreteVisitor1
    {
    public:
        void operator() (const ConcreteComponentA& element) const {
            std::println("{} + ConcreteVisitor1", element.exclusiveMethodOfConcreteComponentA());
        }

        void operator() (const ConcreteComponentB& element) const {
            std::println("{} + ConcreteVisitor1", element.specialMethodOfConcreteComponentB());
        }

        void operator() (const ConcreteComponentC& element) const {
            std::println("{} + ConcreteVisitor1", element.anotherMethodOfConcreteComponentC());
        }
    };

    class ConcreteVisitor2
    {
    public:
        void operator() (const ConcreteComponentA& element) const {
            std::println("{} + ConcreteVisitor2", element.exclusiveMethodOfConcreteComponentA());
        }

        void operator() (const ConcreteComponentB& element) const {
            std::println("{} + ConcreteVisitor2", element.specialMethodOfConcreteComponentB());
        }

        void operator() (const ConcreteComponentC& element) const {
            std::println("{} + ConcreteVisitor2", element.anotherMethodOfConcreteComponentC());
        };
    };

    // =======================================================================
    // The variant replaces the ElementBase hierarchy: it's a closed set
    // of the exact types that can appear. Adding a new component type means
    // adding it here AND updating every visitor's overload set below —
    // the compiler enforces that for you (see "Overloaded" usage).
    // =======================================================================

    using Component = std::variant<ConcreteComponentA, ConcreteComponentB, ConcreteComponentC>;

    // =======================================================================
    // The client code can run any visitor over any set of components without
    // knowing their concrete types. std::visit dispatches to the matching
    // lambda based on the variant's active alternative - this replaces the
    // accept()/visit() double dispatch entirely.
    // =======================================================================

    template <typename TVisitor>
    static void clientCode(const std::vector<Component>& components, const TVisitor& visitor)
    {
        for (const auto& comp : components) {
            std::visit(visitor, comp);
        }
    }
}

void test_conceptual_example_03() {

    using namespace ConceptualExample_Visitor_Pattern_Modern;

    std::vector<Component> components;

    components.emplace_back(ConcreteComponentA{});
    components.emplace_back(ConcreteComponentB{});
    components.emplace_back(ConcreteComponentC{});

    std::println("The client code works with all visitors via std::visit:");
    ConcreteVisitor1 visitor1;
    clientCode<ConcreteVisitor1>(components, visitor1);
    std::println();

    std::println("It allows the same client code to work with different types of visitors");
    ConcreteVisitor2 visitor2;
    clientCode<ConcreteVisitor2>(components, visitor2);
}

// ===========================================================================
// End-of-File
// ===========================================================================
