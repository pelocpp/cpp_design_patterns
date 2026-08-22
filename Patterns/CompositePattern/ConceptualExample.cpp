// ===========================================================================
// ConceptualExample.cpp // Composite Pattern
// ===========================================================================

#include <cstddef>
#include <format>
#include <memory>
#include <print>
#include <string>
#include <string_view>
#include <vector>

namespace ConceptualExample_Composite_Pattern {

    /**
     * The base Component class declares common operations for both
     * simple and complex objects of a composition.
     */

    class Component : public std::enable_shared_from_this<Component>
    {
    protected:
        // a child does not own its parents => weak_ptr prevents cycles.
        std::weak_ptr<Component> m_parent;

    public:
        Component() = default;

        Component(const Component&) = delete;
        Component& operator=(const Component&) = delete;
        Component(Component&&) = delete;
        Component& operator=(Component&&) = delete;

        virtual ~Component() = default;

        /**
         * Optionally, the 'Component' class can declare an interface for setting and
         * accessing a parent of the component in a tree structure.
         * It can also provide some default implementation for these methods.
         *
         * Note: passing a `shared_ptr` because we are registering (weak) ownership!
         */

        void setParent(std::shared_ptr<Component> parent) noexcept {
            m_parent = std::move(parent);
        }

        [[nodiscard]]
        std::shared_ptr<Component> getParent() const noexcept { return m_parent.lock(); }

        /**
         * In some cases, it would be beneficial to define the child-management
         * operations right in the base Component class. This way, you won't need to
         * expose any concrete component classes to the client code, even during the
         * object tree assembly. The downside is that these methods will be empty for
         * the leaf-level components.
         */
        virtual void add(std::shared_ptr<Component> /*component*/) {}
        virtual void remove(std::shared_ptr<Component> /*component*/) {}

        /**
         * You can provide a method that lets the client code figure out
         * whether a component can bear children.
         */
        [[nodiscard]]
        virtual bool isComposite() const noexcept { return false; }

        /**
         * The base Component may implement some default behavior or leave it to
         * concrete classes (by declaring the method containing
         * the behavior as "abstract").
         */
        [[nodiscard]]
        virtual std::string operation() const = 0;
    };

    /**
     * The Leaf class represents the end objects of a composition.
     * A leaf can't have any children.
     *
     * Usually, it's the Leaf objects that do the actual work,
     * whereas Composite objects only delegate to their sub-components.
     */

    class Leaf final : public Component
    {
    private:
        std::string m_description;

    public:
        explicit Leaf(std::string_view description) : m_description{ description } {}

        [[nodiscard]]
        std::string operation() const override {
            return m_description;
        }
    };

    /**
     * The Composite class represents the complex components that may have children.
     * Usually, the Composite objects delegate the actual work to their children and
     * then "sum-up" the result.
     */

    class Composite final : public Component
    {
    private:
        // children are owned via shared_ptr so that they can safely expose
        // their parent through a weak_ptr. The weak parent reference prevents
        // a reference cycle between parent and child.
        std::vector<std::shared_ptr<Component>> m_children;

    public:
        /**
         * A composite object can add or remove other components (both simple or
         * complex) to or from its child list.
         */
        void add(std::shared_ptr<Component> component) override {

            if (!component) return;
    
            // this `shared_from_this()` is being stored as a weak_ptr in the Component
            component->setParent(shared_from_this()); 
            m_children.push_back(std::move(component));
        }

        void remove(std::shared_ptr<Component> component) override {
            std::erase(m_children, component);   // C++ 20: std::erase for std::vector
            if (component) {
                component->setParent(nullptr);   // Remove parent reference
            }
        }

        [[nodiscard]]
        bool isComposite() const noexcept override {
            return true;
        }

        /**
         * The Composite executes its primary logic in a particular way. It traverses
         * recursively through all its children, collecting and summing their results.
         * Since the composite's children pass these calls to their children and so
         * forth, the whole object tree is traversed as a result.
         */

        [[nodiscard]]
        std::string operation() const override {

            if (m_children.empty()) {
                return "Branch [ ]";
            }

            std::string result;
            for (std::size_t i = 0; const auto& child : m_children) {
                result += child->operation();
                if (i < m_children.size() - 1) {
                    result += " + ";
                }
                ++i;
            }

            return std::format("Branch [ {} ]", result);
        }
    };

    /**
     * The client code works with all of the components via the base interface.
     */
    static void clientCode(const Component& component) {
        std::println("Result: {}", component.operation());
    }

    /**
     * Due to the fact that the child-management operations are declared in the
     * base Component class, the client code can work with any component, simple or
     * complex, without depending on their concrete classes.
     */
    static void clientCode2(Component& component1, const std::shared_ptr<Component>& component2) {

        if (component1.isComposite()) {
            component1.add(component2);
        }

        std::println("Result: {}", component1.operation());
    }
}

void test_conceptual_example_01() {

    using namespace ConceptualExample_Composite_Pattern;

    // Components participating in the tree must be owned by shared_ptr,
    // because parent links are established via shared_from_this().

    auto simple = std::make_shared<Leaf>("Simple");
    std::println("Client: I've got a simple component:");
    clientCode(*simple);
    std::println();

    // creating a tree structure
    auto tree = std::make_shared<Composite>();
    auto branch1 = std::make_shared<Composite>();

    branch1->add(std::make_shared<Leaf>("Leaf_1"));
    branch1->add(std::make_shared<Leaf>("Leaf_2"));
    tree->add(branch1);

    auto branch2 = std::make_shared<Composite>();
    branch2->add(std::make_shared<Leaf>("Leaf_3"));
    tree->add(branch2);

    std::println("Client: Now I've got a composite tree:");
    clientCode(*tree);
    std::println();

    std::println("Client: I don't need to know the concrete component classes::");
    clientCode2(*tree, simple);
    std::println();
}

// ===========================================================================
// End-of-File
// ===========================================================================
