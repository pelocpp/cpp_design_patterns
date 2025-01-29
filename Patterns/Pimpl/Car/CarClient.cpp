// ===========================================================================
// CarClient.cpp
// ===========================================================================


#include "Car.h"

//
//#include <iostream>
//#include <memory>
//
//#include "Engine.h"
//#include "Car.h"
//
//class Car::EngineImpl
//{
//public:
//    void coolDown()
//    {
//        /* ... */
//        std::cout << "EngineImpl -> cooling down" << std::endl;
//    }
//
//private:
//    Engine m_engine;
//};
//
//Car::Car() 
//    : m_engineRaw{ new EngineImpl() }, m_engineUnique(std::make_unique<EngineImpl>())
//{}
//
//Car::~Car()
//{ 
//    delete m_engineRaw;
//}
//
//// Car::~Car() {}
//
//void Car::coolDown()
//{
//    m_engineRaw->coolDown();
//    m_engineUnique->coolDown();
//}

void test_car()
{
    Car vw;
    vw.coolDown();
}

// ===========================================================================
// End-of-File
// ===========================================================================
