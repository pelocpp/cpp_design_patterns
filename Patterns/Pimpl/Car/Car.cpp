// ===========================================================================
// Car.cpp
// ===========================================================================

#include <iostream>
#include <memory>

#include "Engine.h"
#include "Car.h"

class Car::EngineImpl
{
public:
    void coolDown()
    {
        /* ... */
        std::cout << "EngineImpl -> cooling down" << std::endl;
    }

private:
    Engine m_engine;
};

Car::Car() 
    : m_engineRaw{ new EngineImpl() },
      m_engineUnique(std::make_unique<EngineImpl>())
{}

Car::~Car()
{ 
    delete m_engineRaw;
}

void Car::coolDown()
{
    m_engineRaw->coolDown();
    // oder
    m_engineUnique->coolDown();
}

// ===========================================================================
// End-of-File
// ===========================================================================
