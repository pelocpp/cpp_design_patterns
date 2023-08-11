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
    struct Relationships
    {
        std::vector<std::tuple<Person, Relationship, Person>> m_relations;

        void addParentAndChild(const Person& parent, const Person& child)
        {
            m_relations.push_back({ parent, Relationship::Parent, child });
            m_relations.push_back({ child, Relationship::Child, parent });
        }
    };

    // high-level <<<<<<<<< -------------------
    struct FamilyTree
    {
        FamilyTree(const Relationships& relationships)
        {
            // using structured binding (C++ 17) and range-based for loop (C++ 11)
            for (const auto& [first, relation, second] : relationships.m_relations)
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
    struct RelationshipBrowser
    {
        virtual std::vector<Person> findAllChildrenOf(const std::string& name) const = 0;
    };

    // low-level <<<<<<<<< -------------------
    struct Relationships : public RelationshipBrowser
    {
        std::vector<std::tuple<Person, Relationship, Person>> m_relations;

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
    struct FamilyTree
    {
        FamilyTree(const RelationshipBrowser& browser) {

            for (const auto& child : browser.findAllChildrenOf("John")) {
                std::cout << "John has a child called " << child.m_name << std::endl;
            }
        }
    };
}

void test_anti_conceptual_example_dip()
{
    using namespace DependencyInversionPrinciple01;

    Person parent{ "John" };
    Person child1{ "Carina" };
    Person child2{ "Mary" };

    Relationships relationships;

    relationships.addParentAndChild(parent, child1);
    relationships.addParentAndChild(parent, child2);

    FamilyTree tree{ relationships };
}

void test_conceptual_example_dip()
{
    using namespace DependencyInversionPrinciple02;

    Person parent{ "John" };
    Person child1{ "Carina" };
    Person child2{ "Mary" };

    Relationships relationships;

    relationships.addParentAndChild(parent, child1);
    relationships.addParentAndChild(parent, child2);

    FamilyTree tree{ relationships };
}

void test_dip()
{
    test_anti_conceptual_example_dip();
    test_conceptual_example_dip();
}

// ===========================================================================
// End-of-File
// ===========================================================================
