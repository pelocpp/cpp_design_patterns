// ===========================================================================
// DIP.cpp // Dependency Inversion Principle
// ===========================================================================

#include <iostream>
#include <string>
#include <vector>
#include <tuple>

enum class Relationship { Parent, Child, Sibling };

struct Person
{
    std::string m_name;
};

namespace DependencyInversionPrinciple01
{
    // low-level <<<<<<<<< -------------------
    class Relationships
    {
    public:
        std::vector<std::tuple<Person, Relationship, Person>> m_relations;

        void addParentAndChild(const Person& parent, const Person& child)
        {
            m_relations.push_back({ parent, Relationship::Parent, child });
            m_relations.push_back({ child, Relationship::Child, parent });
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
            for (const auto& [first, relation, second] : m_relationships.m_relations)
            {
                if (first.m_name == "John" && relation == Relationship::Parent) {
                    std::cout << "John has a child called " << second.m_name << std::endl;
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
        virtual std::vector<Person> findAllChildrenOf(const std::string& name) const = 0;
    };

    // low-level <<<<<<<<< -------------------
    class Relationships : public IRelationshipBrowser
    {
    private:
        std::vector<std::tuple<Person, Relationship, Person>> m_relations;

    public:
        void addParentAndChild(const Person& parent, const Person& child) {
            m_relations.push_back({ parent, Relationship::Parent, child });
            m_relations.push_back({ child, Relationship::Child, parent });
        }

        std::vector<Person> findAllChildrenOf(const std::string& name) const override {

            std::vector<Person> result;
            for (const auto& [first, rel, second] : m_relations) {
                if (first.m_name == name && rel == Relationship::Parent) {
                    result.push_back(second);
                }
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
            : m_browser { browser } 
        {}

        void showChildrenOfJohn() {

            std::vector<Person> children{ m_browser.findAllChildrenOf("John") };

            for (const auto& child : children) {
                std::cout << "John has a child called " << child.m_name << std::endl;
            }
        }
    };
}

static void test_anti_conceptual_example_dip()
{
    using namespace DependencyInversionPrinciple01;

    Person parent{ "John" };
    Person child1{ "Carina" };
    Person child2{ "Mary" };

    Relationships relationships{};

    relationships.addParentAndChild(parent, child1);
    relationships.addParentAndChild(parent, child2);

    FamilyTree tree{ relationships };

    tree.showChildrenOfJohn();
}

static void test_conceptual_example_dip()
{
    using namespace DependencyInversionPrinciple02;

    Person parent{ "John" };
    Person child1{ "Carina" };
    Person child2{ "Mary" };

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
