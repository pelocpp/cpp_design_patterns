// ===========================================================================
// ConceptualExample_Factory.cpp // Composite Pattern
// Solving `enable_shared_from_this`-Problem
// ===========================================================================

#include <cstddef>
#include <format>
#include <memory>
#include <print>
#include <string>
#include <string_view>
#include <vector>

namespace ConceptualExample_Composite_Pattern_Factory   {

    class Component : public std::enable_shared_from_this<Component>
    {
    protected:
        std::weak_ptr<Component> m_parent;

        // protected: only derived classes may construct directly,
        // and only through their own factory functions.
        Component() = default;

    public:
        Component(const Component&) = delete;
        Component& operator=(const Component&) = delete;
        Component(Component&&) = delete;
        Component& operator=(Component&&) = delete;
        virtual ~Component() = default;

        void setParent(std::shared_ptr<Component> parent) noexcept {
            m_parent = std::move(parent);
        }

        [[nodiscard]]
        std::shared_ptr<Component> getParent() const noexcept { return m_parent.lock(); }

        virtual void add(std::shared_ptr<Component> /*component*/) {}
        virtual void remove(std::shared_ptr<Component> /*component*/) {}

        [[nodiscard]]
        virtual bool isComposite() const noexcept { return false; }

        [[nodiscard]]
        virtual std::string operation() const = 0;
    };

    class Leaf : public Component
    {
    private:
        std::string m_description;

        // protected/private constructor - forces use of create()
        explicit Leaf(std::string_view description) : m_description{ description } {}

    public:
        [[nodiscard]]
        static std::shared_ptr<Leaf> create(std::string_view description) {

            // std::make_shared can't call a private/protected ctor directly;
            // this local-struct trick grants it temporary access.
            struct EnableMakeShared : Leaf {
                explicit EnableMakeShared(std::string_view desc) : Leaf(desc) {}
            };

            return std::make_shared<EnableMakeShared>(description);
        }

        [[nodiscard]]
        std::string operation() const override {
            return m_description;
        }
    };

    class Composite : public Component
    {
    private:
        std::vector<std::shared_ptr<Component>> m_children;

        Composite() = default;   // forces use of create()

    public:
        [[nodiscard]]
        static std::shared_ptr<Composite> create() {

            struct EnableMakeShared : Composite {
                EnableMakeShared() = default;
            };
            
            return std::make_shared<EnableMakeShared>();
        }

        void add(std::shared_ptr<Component> component) override {
            if (!component) return;

            component->setParent(shared_from_this());   // now always safe
            m_children.push_back(std::move(component));
        }

        void remove(std::shared_ptr<Component> component) override {
            std::erase(m_children, component);
            if (component) {
                component->setParent(nullptr);
            }
        }

        [[nodiscard]]
        bool isComposite() const noexcept override {
            return true;
        }

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

    static void clientCode(const Component& component) {
        std::println("Result: {}", component.operation());
    }
}

void test_conceptual_example_02() {

    using namespace ConceptualExample_Composite_Pattern_Factory;

    auto simple = Leaf::create("Simple");
    std::println("Client: I've got a simple component:");
    clientCode(*simple);
    std::println();

    // creating a tree structure
    auto tree = Composite::create();
    auto branch1 = Composite::create();

    branch1->add(Leaf::create("Leaf_1"));
    branch1->add(Leaf::create("Leaf_2"));
    tree->add(branch1);

    auto branch2 = Composite::create();
    branch2->add(Leaf::create("Leaf_3"));
    tree->add(branch2);

    std::println("Client: Now I've got a composite tree:");
    clientCode(*tree);
    std::println();
}

// ===========================================================================
// End-of-File
// ===========================================================================
