// ===========================================================================
// ConceptualExample01.cpp // Composite Pattern
// ===========================================================================

#include <iostream>
#include <list>
#include <string>
#include <memory>

namespace CompositePatternRawPointer {

    /**
     * The base Component class declares common operations for both
     * simple and complex objects of a composition.
     */
    class Component {

    protected:
        Component* m_parent;

    public:
        Component() : m_parent(nullptr) {}
        virtual ~Component() {}

        /**
         * Optionally, the 'Component' class can declare an interface for setting and
         * accessing a parent of the component in a tree structure.
         * It can also provide some default implementation for these methods.
         */
        void setParent(Component* parent) { m_parent = parent; }
        Component* getParent() const { return m_parent; }

        /**
         * In some cases, it would be beneficial to define the child-management
         * operations right in the base Component class. This way, you won't need to
         * expose any concrete component classes to the client code, even during the
         * object tree assembly. The downside is that these methods will be empty for
         * the leaf-level components.
         */
        virtual void add(Component* component) {}
        virtual void remove(Component* component) {}

        /**
         * You can provide a method that lets the client code figure out whether
         * a component can bear children.
         */
        virtual bool isComposite() const { return false; }

        /**
         * The base Component may implement some default behavior or leave it to
         * concrete classes (by declaring the method containing
         * the behavior as "abstract").
         */
        virtual std::string operation() const = 0;
    };

    /**
     * The Leaf class represents the end objects of a composition.
     * A leaf can't have any children.
     *
     * Usually, it's the Leaf objects that do the actual work, whereas Composite
     * objects only delegate to their sub-components.
     */
    class Leaf : public Component {
    private:
        std::string m_description;
    public:
        Leaf() = delete;
        Leaf (std::string description) : m_description{ description } {}
        std::string operation() const override {
            return m_description;
        }
    };

    /**
     * The Composite class represents the complex components that may have children.
     * Usually, the Composite objects delegate the actual work to their children and
     * then "sums-up" the result.
     */
    class Composite : public Component {

    protected:
        std::list<Component*> m_children;

    public:
        /**
         * A composite object can add or remove other components
         * (both simple or complex) to or from its child list.
         */
        void add(Component* component) {
            m_children.push_back(component);
            component->setParent(this);
        }

        /**
         * Have in mind that this method removes the pointer to the list but doesn't
         * free the memory, you should do it manually or better use smart pointers.
         */
        void remove(Component* component) {
            m_children.remove(component);
            component->setParent(nullptr);
        }

        bool isComposite() const override {
            return true;
        }

        /**
         * The Composite executes its primary logic in a particular way. It traverses
         * recursively through all its children, collecting and summing their results.
         * Since the composite's children pass these calls to their children and so
         * forth, the whole object tree is traversed as a result.
         */
        std::string operation() const override {
            std::string result{};
            for (const Component* comp : m_children) {
                if (comp == m_children.back()) {
                    result += comp->operation();
                }
                else {
                    result += comp->operation() + " + ";
                }
            }
            return "Branch [ " + result + " ]";
        }
    };

    /**
     * The client code works with all of the components via the base interface.
     */
    static void clientCode(Component* component) {
        std::cout << "Result: " << component->operation();
    }

    /**
     * Due to the fact that the child-management operations are declared in the
     * base Component class, the client code can work with any component, simple or
     * complex, without depending on their concrete classes.
     */
    static void clientCode2(Component* component1, Component* component2) {
        if (component1->isComposite()) {
            component1->add(component2);
        }
        std::cout << "Result: " << component1->operation();
    }
}


void test_conceptual_example_01() {

    using namespace CompositePatternRawPointer;

    Component* simple = new Leaf{"Simple"};
    std::cout << "Client: I've got a simple component:\n";
    clientCode(simple);
    std::cout << std::endl << std::endl;

    /**
     * ...as well as the complex composites.
     */
    Component* tree = new Composite;
    Component* branch1 = new Composite;
    Component* leaf_1 = new Leaf{"Leaf_1"};
    Component* leaf_2 = new Leaf{"Leaf_2"};
    branch1->add(leaf_1);
    branch1->add(leaf_2);
    tree->add(branch1);
    Component* branch2 = new Composite;
    Component* leaf_3 = new Leaf{ "Leaf_3" };
    branch2->add(leaf_3);
    tree->add(branch2);

    std::cout << "Client: Now I've got a composite tree:" << std::endl;
    clientCode(tree);
    std::cout << std::endl << std::endl;

    std::cout 
        << "Client: I don't need to check the components " 
        << "classes even when managing the tree:" << std::endl;
    clientCode2(tree, simple);
    std::cout << std::endl;

    delete simple;
    delete tree;
    delete branch1;
    delete branch2;
    delete leaf_1;
    delete leaf_2;
    delete leaf_3;
}

// ===========================================================================
// End-of-File
// ===========================================================================
