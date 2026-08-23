// ===========================================================================
// Shapes.cpp // Composite Pattern
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

    [[nodiscard]]
    virtual void draw(std::size_t indent) const = 0;

    [[nodiscard]]
    virtual bool isComposite() const noexcept = 0;
};

class Circle final : public IShape
{
private:
    std::string m_name;

public:
    explicit Circle(std::string_view name) : m_name{ name } {}

    [[nodiscard]]
    void draw(std::size_t indent) const override {
        std::println("{}Circle: {}", std::string(indent, ' '), m_name);
    }

    [[nodiscard]]
    virtual bool isComposite() const noexcept { return false; }
};

class Group final : public IShape
{
private:
    std::string m_name;

    std::vector<std::unique_ptr<IShape>> m_objects;

public:
    static constexpr std::size_t s_indentStep = 2;

    explicit Group(std::string_view name) : m_name{ name } {}

    [[nodiscard]]
    void draw(std::size_t indent) const override {
       
        std::println("{}Group: {}", std::string(indent, ' '), m_name);

        for (const auto& shape : m_objects) {
            shape->draw(indent + s_indentStep);
        }
    }

    void add(std::unique_ptr<IShape> shape) {
        if (!shape) return;
        m_objects.push_back(std::move(shape));
    }

    // Since `std::unique_ptr` is not copyable, you cannot compare by value here as you would
    // with `std::shared_ptr` — hence the comparison using the raw pointer(`get()`).
    // This is the standard approach for `unique_ptr` std::composites.
    void remove(const IShape* shape) {
        std::erase_if(
            m_objects,
            [shape](const auto& ptr) { return ptr.get() == shape; }
        );
    }

    [[nodiscard]]
    const std::vector<std::unique_ptr<IShape>>& getComponents() const noexcept {
        return m_objects;
    }

    [[nodiscard]]
    virtual bool isComposite() const noexcept { return true; }
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
