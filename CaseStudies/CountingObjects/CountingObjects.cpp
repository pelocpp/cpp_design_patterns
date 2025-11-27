// ===========================================================================
// CountingObjects.cpp
// ===========================================================================

#include <iostream>
#include <list>

// Note: implicit forward declarations of classes Composite, Leaf1 and Leaf2

class Visitor {
public:
    virtual ~Visitor();
    virtual void visit(class Composite&) = 0;
    virtual void visit(class Leaf1&) = 0;
    virtual void visit(class Leaf2&) = 0;
    virtual void leave(class Composite&) = 0;  // extended variant
};

Visitor::~Visitor() {}

// ===========================================================================

class Component {
public:
    virtual ~Component();
    virtual void accept(Visitor&) = 0;
};

Component::~Component() {}

// ===========================================================================

class Composite : public Component {
public:
    ~Composite();
    void add(Component*);
    void remove(Component*);

    void accept(Visitor&);

private:
    std::list<Component*> m_container;
};

Composite::~Composite() {
    std::list<Component*>::iterator it;
    for (it = m_container.begin(); it != m_container.end(); ++it) {
        delete* it;
    }
}

void Composite::add(Component* c) {
    m_container.push_back(c);
}

void Composite::remove(Component* c) {
    m_container.remove(c);
}

void Composite::accept(Visitor& v) {
    v.visit(*this);

    std::list<Component*>::iterator it;
    for (it = m_container.begin(); it != m_container.end(); ++it) {
        (*it)->accept(v);
    }

    v.leave(*this);
}

// ===========================================================================

class Leaf1 : public Component {
public:
    void accept(Visitor&);
};

void Leaf1::accept(Visitor& v) {
    v.visit(*this);
}

// ===========================================================================

class Leaf2 : public Component {
public:
    void accept(Visitor&);
};

void Leaf2::accept(Visitor& v) {
    v.visit(*this);
}

// ===========================================================================

class SimpleCounter : public Visitor {
private:
    size_t m_n; 

public:
    SimpleCounter() : m_n{ 0 } {}

    void visit(Composite&) { m_n++; }
    void visit(Leaf1&) { m_n++; }
    void visit(Leaf2&) { m_n++; }

    void leave(class Composite&) {}  // extended variant (empty implementation)

    size_t count () const
    {
        return m_n;
    }
};

// ===========================================================================

class DetailedCounter : public Visitor
{
private:
    size_t m_nc;
    size_t m_n1;
    size_t m_n2;
    size_t m_currentDepth;
    size_t m_maxDepth;

public:
    DetailedCounter() : m_nc{ 0 }, m_n1{ 0 }, m_n2{ 0 }, m_currentDepth{ 0 }, m_maxDepth{0 } {}

    void visit(Composite&) { 
        m_nc++;
        m_currentDepth++;
        if (m_currentDepth > m_maxDepth) {
            m_maxDepth = m_currentDepth;
        }
    }

    void visit(Leaf1&) { m_n1++; }
    void visit(Leaf2&) { m_n2++; }

    void leave(class Composite&) { m_currentDepth--; }  // extended variant

    size_t countObjects() const { return m_nc + m_n1 + m_n2; }
    size_t countComposite() const { return m_nc; }
    size_t countLeaf1() const { return m_n1; }
    size_t countLeaf2() const { return m_n2; }
    size_t countDepth() const { return m_maxDepth; }
};

// ===========================================================================

void test_CountingObjects_01()
{
    Composite root;
    root.add(new Leaf1());
    root.add(new Leaf1());
    root.add(new Leaf2());

    Composite* p = new Composite();
    p->add(new Leaf2());
    p->add(new Leaf1());
    root.add(p);

    SimpleCounter counter;
    root.accept(counter);

    std::cout << counter.count() << std::endl;
}

void test_CountingObjects_02()
{
    Composite root;
    root.add(new Leaf1());
    root.add(new Leaf1());
    root.add(new Leaf2());

    Composite* p = new Composite();
    p->add(new Leaf2());
    p->add(new Leaf1());
    root.add(p);

    DetailedCounter counter;
    root.accept(counter);

    std::cout << "Objects:   " << counter.countObjects() << std::endl;
    std::cout << "Composite: " << counter.countComposite() << std::endl;
    std::cout << "Leaf1:     " << counter.countLeaf1() << std::endl;
    std::cout << "Leaf2:     " << counter.countLeaf2() << std::endl;
    std::cout << "Depth:     " << counter.countDepth() << std::endl;
}

void test_CountingObjects_03()
{
    Composite root;
    Composite* p1 = new Composite();
    root.add(p1);
    Composite* p2 = new Composite();
    p1->add(p2);
    Composite* p3 = new Composite();
    p2->add(p3);

    DetailedCounter counter;
    root.accept(counter);

    std::cout << "Depth:     " << counter.countDepth() << std::endl;
}

// ===========================================================================
// End-of-File
// ===========================================================================
