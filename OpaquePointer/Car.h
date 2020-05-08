class Car
{
public:
    Car();
    ~Car();

public:
    void coolDown();
private:
    class EngineImpl;
    EngineImpl* m_engine;
    std::unique_ptr<EngineImpl> m_engine2;
};
