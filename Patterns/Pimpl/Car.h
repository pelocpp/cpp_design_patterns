// ===========================================================================
// Car.cpp
// ===========================================================================

class Car
{
public:
    Car();
    ~Car();

public:
    void coolDown();

private:
    class EngineImpl;           // forward declaration

    EngineImpl*                 m_engineRaw;      // raw pointer
    // or
    std::unique_ptr<EngineImpl> m_engineUnique;   // smart pointer
};

// ===========================================================================
// End-of-File
// ===========================================================================

