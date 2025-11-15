// ===========================================================================
// GreenLight.h
// ===========================================================================

namespace TrafficLight03
{
    class GreenLight : public ITrafficLightState
    {
    private:
        GreenLight() noexcept {};

        static std::shared_ptr<GreenLight> m_instance;

    public:
        static std::shared_ptr<GreenLight> getInstance();

        void changeState(TrafficLight& light) override;
        void reportState() const override;
    };
}

// ===========================================================================
// End-of-File
// ===========================================================================
