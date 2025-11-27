// ===========================================================================
// DependencyInversionPrinciple.cpp
// ===========================================================================

#include <iostream>
#include <string>
#include <vector>
#include <variant>
#include <memory>

namespace Dependency_Inversion_Principle_Violating {

    class FrontEndDeveloper
    {
    public:
        void developFrontEnd() {
            std::cout << "implementing front end ..." << std::endl;
        }
    };

    class BackEndDeveloper
    {
    public:
        void developBackEnd() {
            std::cout << "implementing back end ..." << std::endl;
        }
    };

    class Project
    {
    private:
        FrontEndDeveloper m_fed;
        BackEndDeveloper m_bed;

    public:
        void develop() {
            m_fed.developFrontEnd();
            m_bed.developBackEnd();
        }
    };

    void test_01() {

        Project project{};
        project.develop();
    }
}

namespace Dependency_Inversion_Principle_Respecting_01 {

    // solution uses inheritance / polymorphism

    class Developer {
    public:
        virtual ~Developer() = default;
        virtual void develop() = 0;
    };

    using Developers = std::vector<std::unique_ptr<Developer>>;

    class FrontEndDeveloper : public Developer
    {
    public:
        virtual void develop() override {
            developFrontEnd();
        }

    private:
        void developFrontEnd() {
            std::cout << "implementing front end ..." << std::endl;
        }
    };

    class BackEndDeveloper : public Developer
    {
    public:
        virtual void develop() override {
            developBackEnd();
        }

    private:
        void developBackEnd() {
            std::cout << "implementing back end ..." << std::endl;
        }
    };

    class Project
    {
    public:
        explicit Project(Developers& developers)
            : m_developers{ std::move(developers) } {}

        void develop() {
            for (const auto& developer : m_developers) {
                developer->develop();
            }
        }

    private:
        Developers m_developers;
    };

    void test_02() {

        Developers developers;
        developers.push_back(std::make_unique<FrontEndDeveloper>());
        developers.push_back(std::make_unique<BackEndDeveloper>());

        Project project{ developers };
        project.develop();
    }
}

namespace Dependency_Inversion_Principle_Respecting_02 {

    // solution uses template techniques / no inheritance / no polymorphism

    class FrontEndDeveloper
    {
    public:
        void develop() {
            developFrontEnd();
        }

    private:
        void developFrontEnd() {
            std::cout << "implementing front end ..." << std::endl;
        }
    };

    class BackEndDeveloper
    {
    public:
        void develop() {
            developBackEnd();
        }

    private:
        void developBackEnd() {
            std::cout << "implementing back end ..." << std::endl;
        }
    };

    template <typename... TDevelopers>
    class Project
    {
        using Developers = std::vector<std::variant<TDevelopers ...>>;

    public:
        explicit Project(Developers developers)
            : m_developers{ std::move(developers) } {}

        void develop() {
            for (auto& developer : m_developers) {
                std::visit([](auto& dev) { dev.develop(); }, developer);
            }
        }

    private:
        Developers m_developers;
    };

    void test_03() {

        using MyProject = Project<FrontEndDeveloper, BackEndDeveloper>;

        FrontEndDeveloper susan = FrontEndDeveloper{};
        BackEndDeveloper bob = BackEndDeveloper{};

        MyProject project = MyProject{ { susan, bob } };
        project.develop();
    }
}

namespace Dependency_Inversion_Principle_Respecting_03 {

    // same as last solution / several using declarations used

    class FrontEndDeveloper
    {
    public:
        void develop() {
            developFrontEnd();
        }

    private:
        void developFrontEnd() {
            std::cout << "implementing front end ..." << std::endl;
        }
    };

    class BackEndDeveloper
    {
    public:
        void develop() {
            developBackEnd();
        }

    private:
        void developBackEnd() {
            std::cout << "implementing back end ..." << std::endl;
        }
    };

    template <typename... TDevelopers>
    using Developers = std::vector<std::variant<TDevelopers ...>>;

    template <typename... TDevelopers>
    class Project
    {
    public:
        explicit Project(Developers<TDevelopers ...> developers)
            : m_developers{ std::move(developers) } {}

        void develop() {
            for (auto& developer : m_developers) {
                std::visit([](auto& dev) { dev.develop(); }, developer);
            }
        }

    private:
        Developers<TDevelopers ...> m_developers;
    };

    void test_04() {

        using MyProject = Project<FrontEndDeveloper, BackEndDeveloper>;

        FrontEndDeveloper susan = FrontEndDeveloper{};
        BackEndDeveloper bob = BackEndDeveloper{};

        MyProject project = MyProject{ { susan, bob } };
        project.develop();
    }
}

void testDependencyInversionPrinciple()
{
    using namespace Dependency_Inversion_Principle_Violating;
    test_01();

    using namespace Dependency_Inversion_Principle_Respecting_01;
    test_02();

    using namespace Dependency_Inversion_Principle_Respecting_02;
    test_03();

    using namespace Dependency_Inversion_Principle_Respecting_03;
    test_04();
}

// ===========================================================================
// End-of-File
// ===========================================================================
