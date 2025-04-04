// ===========================================================================
// Abstract Factory // Example 'Vehicles'
// ===========================================================================

#include <map>
#include <memory>
#include <print>
#include <string>

// ===========================================================================
// abstract product

enum class VehicleType : int
{
    Bike,
    Car,
    Truck
};

class Vehicle
{
private:
    int  m_numGears;
    bool m_reverseGear;
    int  m_numTires;

public:
    Vehicle(int numGears, bool reverseGear, int numTires) :
        m_numGears{ numGears }, m_reverseGear{ reverseGear }, m_numTires{ numTires }
    {}

    virtual void moveForward() = 0;
    virtual bool moveBackward() = 0;
    virtual void turnLeft() = 0;
    virtual void turnRight() = 0;
};

// ===========================================================================
// concrete products

class Bike : public Vehicle
{
public:
    Bike(int numGears) : Vehicle{ numGears, false, 2 } {}

    void moveForward() override {
        std::println("accelerate using handle");
    }

    bool moveBackward() override {
        std::println("moving slowly backwards using the first gear");
        return false;
    }

    void turnLeft() override {
        std::println("move handle to 45 degrees clockwise");
    }

    void turnRight() override {
        std::println("move handle to 45 degrees anti-clockwise");
    }
};

class Car : public Vehicle
{
public:
    Car(int numGears) : Vehicle{ numGears, true, 4 } {}

    void moveForward() override {
        std::println("accelerate using paddle");
    }

    bool moveBackward() override {
        std::println("switch to reverse gear and accelerate");
        return true;
    }

    void turnLeft() override {
        std::println("move steering wheel to 45 degrees clockwise");
    }

    void turnRight() override {
        std::println("move steering wheel to 45 degrees anti-clockwise");
    }
};

class Truck : public Vehicle
{
public:
    Truck(int numGears) : Vehicle{ numGears, true, 6 } {}

    void moveForward() override {
        std::println("accelerate using paddle");
    }

    bool moveBackward() override {
        std::println("switch to reverse gear and accelerate");
        return true;
    }

    void turnLeft() override {
        std::println("move steering wheel to 45 degrees clockwise");
    }

    void turnRight() override {
        std::println("move steering wheel to 45 degrees anti-clockwise");
    }
};

// ===========================================================================
// abstract factory interface

class IVehicleFactory
{
public:
    virtual ~IVehicleFactory() {}

    virtual std::unique_ptr<Vehicle> create(int numGears) const = 0;
};

// ===========================================================================
// concrete factories

class BikeFactory : public IVehicleFactory {
public:
    std::unique_ptr<Vehicle> create(int numGears) const override
    {
        return std::make_unique<Bike>(numGears);
    }
};

class CarFactory : public IVehicleFactory {
public:
    std::unique_ptr<Vehicle> create(int numGears) const override
    {
        return std::make_unique<Car>(numGears);
    }
};

class TruckFactory : public IVehicleFactory {
public:
    std::unique_ptr<Vehicle> create(int numGears) const override
    {
        return std::make_unique<Truck>(numGears);
    }
};

// ===========================================================================

class VehicleCreator
{
private:
    std::map<VehicleType, std::unique_ptr<IVehicleFactory>> factories;

public:
    VehicleCreator()
    {
        factories[VehicleType::Bike] = std::make_unique<BikeFactory>();
        factories[VehicleType::Car] = std::make_unique<CarFactory>();
        factories[VehicleType::Truck] = std::make_unique<TruckFactory>();
    }

    std::unique_ptr<Vehicle> create(VehicleType type, int numGears) {
        return factories[type]->create(numGears);
    }
};

// ===========================================================================

void test_vehicles()
{
    auto vehicleCreator{ std::make_unique<VehicleCreator>() };

    std::unique_ptr<Vehicle> vehicle{ 
        vehicleCreator->create(VehicleType::Bike, 5) 
    };
    
    vehicle->moveForward();
    vehicle->moveBackward();
    vehicle->turnLeft();
    vehicle->turnRight();
}

// ===========================================================================
// End-of-File
// ===========================================================================
