// ===========================================================================
// TrafficLight.h
// ===========================================================================

namespace TrafficLight03
{
    class TrafficLight
    {
    private:
        std::shared_ptr<ITrafficLightState> m_state;

    public:
        void setState(std::shared_ptr<ITrafficLightState> state);
        std::shared_ptr<ITrafficLightState> getState();

        void change();
        void show();
    };
}

// ===========================================================================
// End-of-File
// ===========================================================================
