// ===========================================================================
// TrafficLight.cpp
// ===========================================================================

#include <iostream>
#include <string>
#include <memory>

#include "ITrafficLightState.h"
#include "TrafficLight.h"

namespace TrafficLight03
{
    void TrafficLight::setState(std::shared_ptr<ITrafficLightState> state)
    {
        m_state = state; 
    }

    std::shared_ptr<ITrafficLightState> TrafficLight::getState()
    {
        return m_state; 
    }

    void TrafficLight::change()
    {
        m_state->changeState(*this);
    }

    void TrafficLight::show()
    {
        m_state->reportState();
    }
}

// ===========================================================================
// End-of-File
// ===========================================================================
