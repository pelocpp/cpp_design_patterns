// ===========================================================================
// Abstract Factory // Example 'Vehicles'
// ===========================================================================

#include <iostream>
#include <sstream>
#include <string>
#include <list>
#include <memory>

// ===========================================================================
// abstract product

class Vehicle
{
protected:
    std::string m_model;
    std::string m_engine;
    std::string m_transmission;
    std::string m_body;
    int m_doors;
    std::list<std::string> m_accessories;

private:
    // c'tors
    Vehicle() = delete; // class shoud be abstract

public:
    Vehicle(
        std::string model, std::string engine, std::string transmission,
        std::string body,int doors) : 
        m_model{ model }, m_engine{ engine }, m_transmission{ transmission },
        m_body{ body }, m_doors{ doors }
    {}

    // public interface
    void showInfo()
    {
        std::cout << (*this)() << std::endl;
    }

    std::string operator ()() {
        std::ostringstream oss;

        oss << "Model: " << m_model << '\n';
        oss << "  Engine: " << m_engine << '\n';
        oss << "  Body: " << m_body << '\n';
        oss << "  Doors: " << m_doors << '\n';
        oss << "  Transmission: " << m_transmission << '\n';
        oss << "  Accessories: " << '\n';
        for (std::string accessory : m_accessories) {
            oss << "    " << accessory << '\n';
        }

        return oss.str();
    }
};

// ===========================================================================
// abstract factory

class IVehicleFactory
{
public:
    virtual ~IVehicleFactory() {}

    virtual std::shared_ptr<Vehicle> createEconomyCar() = 0;
    virtual std::shared_ptr<Vehicle> createRacingCar() = 0;
    virtual std::shared_ptr<Vehicle> createSUV() = 0;
};

// ===========================================================================
// concrete products

class FordExplorer : public Vehicle
{
public:
    FordExplorer() 
        : Vehicle(
            "Ford Explorer",
            "4.0 L Cologne V6",
            "5-speed M50D-R1 manual",
            "SUV",
            5)
    {
        m_accessories.push_back("Car Cover");
        m_accessories.push_back("Sun Shade");
    }
};

class FordFocus : public Vehicle
{
public:
    FordFocus()
        : Vehicle(
            "Ford Focus",
            "1.0 L EcoBoost I3", 
            "6-speed PowerShift automatic", 
            "5-door hatchback", 
            5)
    {
        m_accessories.push_back("Car Cover");
    }
};

class FordGT1 : public Vehicle
{
public:
    FordGT1()
        : Vehicle(
            "Ford GT1", 
            "5.4 L Supercharged Modular V8",
            "6-speed manual",
            "Roadster", 
            2) {}
};

class MitsubishiPajero : public Vehicle
{
public:
    MitsubishiPajero()
        : Vehicle(
            "Mitsubishi Pajero Super Exceed",
            "6G75 3.8 V6",
            "5-speed manual", 
            "SUV", 
            5) {}
};

class MitsubishiI : public Vehicle
{
public:
    MitsubishiI()
        : Vehicle(
            "Mitsubishi I",
            "659 cc DOHC MIVEC",
            "6-speed automatic",
            "Kei car", 
            5) {}
};

class MitsubishiLancerEvoIX : public Vehicle
{
public:
    MitsubishiLancerEvoIX()
        : Vehicle(
            "Mitsubishi Lancer Evo IX",
            "4B10 1.8 L DOHC I4",
            "6-speed twin-clutch transmission", 
            "4-door sedar", 
            4) {}
};

// ===========================================================================
// concrete factories

class FordFactory : public IVehicleFactory
{
public:
    std::shared_ptr<Vehicle> createEconomyCar()
    {
        return std::make_shared<FordFocus>();
    }

    std::shared_ptr<Vehicle>  createRacingCar()
    {
        return std::make_shared<FordGT1>();
    }

    std::shared_ptr<Vehicle>  createSUV()
    {
        return std::make_shared<FordExplorer>();
    }
};

class MitsubishiFactory : public IVehicleFactory
{
public:
    std::shared_ptr<Vehicle> createEconomyCar()
    {
        return std::make_shared<MitsubishiI>();
    }

    std::shared_ptr<Vehicle>  createRacingCar()
    {
        return std::make_shared<MitsubishiLancerEvoIX>();
    }

    std::shared_ptr<Vehicle>  createSUV()
    {
        return std::make_shared<MitsubishiPajero>();
    }
};

// ===========================================================================

void test_vehicles() {

    std::list<std::shared_ptr<IVehicleFactory>> factories {
        std::make_shared<FordFactory>(),
        std::make_shared<MitsubishiFactory>() 
    };

    for (std::shared_ptr<IVehicleFactory> factory : factories) {

        std::shared_ptr<Vehicle> vehicle;

        vehicle = factory->createEconomyCar();
        vehicle->showInfo();   

        vehicle = factory->createRacingCar();
        vehicle->showInfo();

        vehicle = factory->createSUV();
        vehicle->showInfo();
    }
}

// ===========================================================================
// End-of-File
// ===========================================================================
