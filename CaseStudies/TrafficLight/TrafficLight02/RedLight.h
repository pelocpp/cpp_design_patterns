// ===========================================================================
// RedLight.h
// ===========================================================================

namespace TrafficLight02
{
    class RedLight : public ITrafficLightState
    {
    public:
        void changeState(TrafficLight& light) override;
        void reportState() const override;
    };
}

// ===========================================================================
// End-of-File
// ===========================================================================
