// ===========================================================================
// GreenLight.h
// ===========================================================================

namespace TrafficLight01
{
    class GreenLight : public ITrafficLightState
    {
    public:
        void changeState(TrafficLight* light) override;
        void reportState() const override;
    };
}

// ===========================================================================
// End-of-File
// ===========================================================================
