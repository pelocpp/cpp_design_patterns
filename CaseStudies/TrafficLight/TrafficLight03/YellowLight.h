// ===========================================================================
// YellowLight.h
// ===========================================================================

namespace TrafficLight03
{
    class YellowLight : public ITrafficLightState
    {
    private:
        YellowLight() noexcept {};

        static std::shared_ptr<YellowLight> m_instance;

    public:
        static std::shared_ptr<YellowLight> getInstance();

    public:
        void changeState(TrafficLight& light) override;
        void reportState() const override;
    };
}

// ===========================================================================
// End-of-File
// ===========================================================================
