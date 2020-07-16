class Car
{
public:
    Car();
    ~Car();

public:
    void coolDown();

private:
    class EngineImpl;
    EngineImpl* m_engineRaw;
    std::unique_ptr<EngineImpl> m_engineUnique;
};
