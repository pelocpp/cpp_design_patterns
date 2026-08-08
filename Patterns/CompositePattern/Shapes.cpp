// ===========================================================================
// Shapes.cpp
// ===========================================================================

#include <cstddef>
#include <memory>
#include <print>
#include <string>
#include <string_view>
#include <vector>

struct IShape
{
    virtual ~IShape() = default;

    virtual void draw(std::size_t indent) const = 0;
};

class Circle final : public IShape
{
private:
    std::string m_name;

public:
    explicit Circle(std::string_view name) : m_name{ name } {}

    void draw(std::size_t indent) const override {
        std::println("{}Circle: {}", std::string(indent, ' '), m_name);
    }
};

class Group final : public IShape
{
private:
    std::string m_name;

    std::vector<std::unique_ptr<IShape>> m_objects;

public:
    explicit Group(std::string_view name) : m_name{ name } {}

    void draw(std::size_t indent) const override {
       
        std::println("{}Group: {}", std::string(indent, ' '), m_name);

        for (const auto& shape : m_objects) {
            shape->draw(indent + 2);
        }
    }

    void add(std::unique_ptr<IShape> shape) {
        m_objects.push_back(std::move(shape));
    }
};

void test_shapes()
{
    // create a top-level group - on the stack
    Group root{ "Root" };

    // add a shape to the group
    root.add(std::make_unique<Circle>("Top Level Circle"));

    // create a subgroup
    auto subgroup = std::make_unique<Group>("Subgroup");

    subgroup->add(
        std::make_unique<Circle>("First Second Level Circle")
    );
    
    subgroup->add(
        std::make_unique<Circle>("Another Second Level Circle")
    );

    // transfer ownership of the subgroup to root
    root.add(std::move(subgroup));

    // start drawing
    root.draw(0);
}

// ===========================================================================
// End-of-File
// ===========================================================================
