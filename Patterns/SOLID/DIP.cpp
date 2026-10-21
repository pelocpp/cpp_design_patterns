// ===========================================================================
// DIP.cpp // Dependency Inversion Principle
// ===========================================================================

#include <print>
#include <string>
#include <vector>

enum class Relationship { Parent, Child, Sibling };

struct Person
{
    std::string name;
};

namespace DependencyInversionPrinciple01
{
    // low-level <<<<<<<<< -------------------
    class Relationships
    {
    public:
        struct Relation
        {
            std::shared_ptr<const Person> parent;
            Relationship                  relation;
            std::shared_ptr<const Person> child;
        };

        std::vector<Relation> m_relations;

        void addParentAndChild(
            std::shared_ptr<const Person> parent,
            std::shared_ptr<const Person> child)
        {
            m_relations.push_back({ std::move(parent), Relationship::Parent, std::move(child) });
        }
    };

    // high-level <<<<<<<<< -------------------
    class FamilyTree
    {
    private:
        const Relationships& m_relationships;

    public:
        FamilyTree(const Relationships& relationships)
            : m_relationships{ relationships }
        {}

        void showChildrenOfJohn()
        {
            // using structured binding (C++ 17) and range-based for loop (C++ 11)
            for (const auto& [parent, relation, child] : m_relationships.m_relations)
            {
                if (parent->name == "John" && relation == Relationship::Parent) {
                    std::println("John has a child called {}", child->name);
                }
            }
        }
    };
}

namespace DependencyInversionPrinciple02
{
    // abstraction
    struct IRelationshipBrowser
    {
        virtual ~IRelationshipBrowser() = default;
        virtual std::vector<Person> findAllChildrenOf(const std::string& name) const = 0;
    };

    // low-level <<<<<<<<< -------------------
    class Relationships : public IRelationshipBrowser
    {
    private:
        struct Relation
        {
            std::shared_ptr<const Person> parent;
            Relationship                  relation;
            std::shared_ptr<const Person> child;
        };

        std::vector<Relation> m_relations;

    public:
        void addParentAndChild(
            std::shared_ptr<const Person> parent,
            std::shared_ptr<const Person> child)
        {
            m_relations.push_back({ std::move(parent), Relationship::Parent, std::move(child) });
        }

        std::vector<Person> findAllChildrenOf(const std::string& name) const override {

            std::vector<Person> result;
            for (const auto& [parent, relation, child] : m_relations) {
                if (parent->name == name && relation == Relationship::Parent)
                    result.push_back(*child);
            }
            return result;
        }
    };

    // high-level <<<<<<<<< -------------------
    class FamilyTree
    {
    private:
        const IRelationshipBrowser& m_browser;

    public:
        FamilyTree(const IRelationshipBrowser& browser)
            : m_browser{ browser }
        {}

        void showChildrenOfJohn() const {

            std::vector<Person> children{ m_browser.findAllChildrenOf("John") };

            for (const auto& child : children) {
                std::println("John has a child called {}", child.name);
            }
        }
    };
}

static void test_anti_conceptual_example_dip()
{
    using namespace DependencyInversionPrinciple01;

    auto parent = std::make_shared<Person>("John");
    auto child1 = std::make_shared<Person>("Carina");
    auto child2 = std::make_shared<Person>("Mary");

    Relationships relationships{};

    relationships.addParentAndChild(parent, child1);
    relationships.addParentAndChild(parent, child2);

    FamilyTree tree{ relationships };

    tree.showChildrenOfJohn();
}

static void test_conceptual_example_dip()
{
    using namespace DependencyInversionPrinciple02;

    auto parent = std::make_shared<Person>("John");
    auto child1 = std::make_shared<Person>("Carina");
    auto child2 = std::make_shared<Person>("Mary");

    Relationships relationships{};

    relationships.addParentAndChild(parent, child1);
    relationships.addParentAndChild(parent, child2);

    const IRelationshipBrowser& browser = relationships;

    FamilyTree tree{ browser };

    tree.showChildrenOfJohn();
}

void test_dip()
{
    test_anti_conceptual_example_dip();
    test_conceptual_example_dip();
}

// ===========================================================================
// End-of-File
// ===========================================================================
