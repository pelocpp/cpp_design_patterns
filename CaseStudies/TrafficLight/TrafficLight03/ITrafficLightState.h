// ===========================================================================
// ITrafficLightState.h
// ===========================================================================

namespace TrafficLight03
{
    class TrafficLight;

    class ITrafficLightState
    {
    public:
        virtual void changeState(TrafficLight& light) = 0;
        virtual void reportState() const = 0;
    };
}

// ===========================================================================
// End-of-File
// ===========================================================================
