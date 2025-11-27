// ===========================================================================
// YellowLight.h
// ===========================================================================

namespace TrafficLight02
{
    class YellowLight : public ITrafficLightState
    {
    public:
        void changeState(TrafficLight& light) override;
        void reportState() const override;
    };
}

// ===========================================================================
// End-of-File
// ===========================================================================
