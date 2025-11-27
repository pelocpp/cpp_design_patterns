// ===========================================================================
// ApprovalSystem.cpp
// ===========================================================================

#include <iostream>
#include <string>
#include <memory>
#include <limits>

class Role
{
public:
    virtual ~Role() {}
    virtual double getApprovalLimit() const = 0;
};

class EmployeeRole : public Role
{
public:
    virtual double getApprovalLimit() const override
    {
        return 1000;
    }
};

class TeamManagerRole : public Role
{
public:
    virtual double getApprovalLimit() const override
    {
        return 10000;
    }
};

class DepartmentManagerRole : public Role
{
public:
    virtual double getApprovalLimit() const override
    {
        return 100000;
    }
};

class CEORole : public Role
{
public:
    virtual double getApprovalLimit() const override
    {
        return std::numeric_limits<double>::max();
    }
};

class Expense
{
private:
    double m_amount;
    std::string m_description;

public:
    Expense(double const amount, std::string description)
        : m_amount{ amount }, m_description{ description } {}

    double getAmount() const noexcept { return m_amount; }
    std::string getDescription() const noexcept { return m_description; }
};

class Employee
{
private:
    std::string m_name;
    std::unique_ptr<Role> m_ownRole;
    std::weak_ptr<Employee> m_directManager;

public:
    explicit Employee(std::string name, std::unique_ptr<Role> ownrole)
        : m_name{ name }, m_ownRole{ std::move(ownrole) } {}

    void setDirectManager(std::shared_ptr<Employee> manager)
    {
        m_directManager = manager;
    }

    void approve(const Expense& e)
    {
        if (e.getAmount() <= m_ownRole->getApprovalLimit()) {
            std::cout
                << m_name << " approved expense '" << e.getDescription()
                << "', cost=" << e.getAmount() << std::endl;
        }
        else if (std::shared_ptr<Employee> manager; (manager = m_directManager.lock()) != nullptr) {
            manager->approve(e);
        }
    }
};

void approval_system() 
{
    std::unique_ptr<Role> role1 = std::make_unique<EmployeeRole>();
    std::shared_ptr<Employee> cliff = 
        std::make_shared<Employee>("Cliff Booth", std::move(role1));

    std::unique_ptr<Role> role2 = std::make_unique<TeamManagerRole>();
    std::shared_ptr<Employee> rick = 
        std::make_shared<Employee>("Rick Dalton", std::move(role2));

    std::unique_ptr<Role> role3 = std::make_unique<DepartmentManagerRole>();
    std::shared_ptr<Employee> randy =
        std::make_shared<Employee>("Randy Miller", std::move(role3));

    std::unique_ptr<Role> role4 = std::make_unique<CEORole>();
    std::shared_ptr<Employee> marvin = 
        std::make_shared<Employee>("Marvin Swartz", std::move(role4));

    cliff->setDirectManager(rick);
    rick->setDirectManager(randy);
    randy->setDirectManager(marvin);

    // employee 'cliff' gets all bills
    cliff->approve(Expense{ 500, "Magazins" });
    cliff->approve(Expense{ 5000, "Hotel Accomodation" });
    cliff->approve(Expense{ 50000, "Conference costs" });
    cliff->approve(Expense{ 200000, "New Truck" });
}

// ===========================================================================
// End-of-File
// ===========================================================================
