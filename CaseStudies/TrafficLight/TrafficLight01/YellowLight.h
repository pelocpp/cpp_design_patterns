// ===========================================================================
// YellowLight.h
// ===========================================================================

namespace TrafficLight01
{
    class YellowLight : public ITrafficLightState
    {
    public:
        void changeState(TrafficLight* light) override;
        void reportState() const override;
    };
}

// ===========================================================================
// End-of-File
// ===========================================================================
