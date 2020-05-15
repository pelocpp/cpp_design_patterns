#include <iostream>
#include <string>
#include <list>

class Vehicle
{
private:
    std::string m_model;
    std::string m_engine;
    std::string m_transmission;
    std::string m_body;
    int m_doors;
    std::list<std::string> m_accessories;

public:
    // c'tors
    Vehicle() = default;

    // getter / setter

    //std::string Model
    //std::string Engine
    //std::string Transmission
    //std::string Body
    //int Doors

    // public interface


    virtual void showInfo() = 0;
};

class IVehicleFactory
{
    virtual Vehicle createEconomyCar() = 0;
    virtual Vehicle createRacingCar() = 0;
    virtual Vehicle createSUV() = 0;
};

class FordFactory : public IVehicleFactory
{
public:
    public Vehicle createEconomyCar()
    {
        return new FordFocus();
    }

    //public Vehicle createRacingCar()
    //{
    //    return new FordGT1();
    //}

    //public Vehicle createSUV()
    //{
    //    return new FordExplorer();
    //}
}