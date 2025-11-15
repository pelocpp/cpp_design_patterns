// ===========================================================================
// TrafficLight.h
// ===========================================================================

namespace TrafficLight01
{
    class TrafficLight
    {
    private:
        ITrafficLightState* m_state;

    public:
        void setState(ITrafficLightState* state);
        ITrafficLightState* getState();

        void change();
        void show() const;
    };
}

// ===========================================================================
// End-of-File
// ===========================================================================
