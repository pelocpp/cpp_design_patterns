#include <memory>

#include "Engine.h"
#include "Car.h"

class Car::EngineImpl
{
public:
    void coolDown()
    {
        /* ... */
    }

private:
    Engine m_engine;
};

Car::Car() : m_engine{ new EngineImpl() }, m_engine2(new EngineImpl()) {}

// Car::~Car() { delete m_engine; }

Car::~Car() = default;

void Car::coolDown()
{
    m_engine->coolDown();
}