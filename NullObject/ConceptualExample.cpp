// ===========================================================================
// ConceptualExample.cpp // Null Object Pattern
// ===========================================================================

#include <iostream>
#include <string>

/**
 * The base Component class declares common operations
 * for both real and null objects.
 */
class AbstractObject
{
public:
    virtual std::string  operation() const = 0;
};

/**
 * Implementation of a real object.
 */
class RealObject : public AbstractObject
{
public:
    virtual std::string  operation() const override
    {
     //   std::cout << "do something" << std::endl;
        return std::string("computed something!");
    }
};

/**
 * Implementation of a null object.
 */
class NullObject : public AbstractObject
{
public:
    virtual std::string operation() const override { return std::string(""); }
};

/**
 * The client code works with all of the objects via the base interface.
 * The function which requires an AbstractObject instance, and will not accept null
 */
void clientCode(const AbstractObject& obj) {
    // obj may never be null here
    std::string result = obj.operation();
    std::cout << "RESULT: " << result << std::endl;
}

void test_conceptual_example() {
    RealObject realObject;
    clientCode(realObject);
    NullObject nullObject;
    clientCode(nullObject);
}

// ===========================================================================
// End-of-File
// ===========================================================================
