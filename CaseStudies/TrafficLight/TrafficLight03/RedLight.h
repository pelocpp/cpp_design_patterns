// ===========================================================================
// RedLight.h
// ===========================================================================

namespace TrafficLight03
{
    class RedLight : public ITrafficLightState
    {
    private:
        RedLight() noexcept {};

        static std::shared_ptr<RedLight> m_instance;

    public:
        static std::shared_ptr<RedLight> getInstance();

    public:
        void changeState(TrafficLight& light) override;
        void reportState() const override;
    };
}

// ===========================================================================
// End-of-File
// ===========================================================================
