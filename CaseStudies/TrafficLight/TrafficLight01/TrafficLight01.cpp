// ===========================================================================
// TrafficLight.cpp
// ===========================================================================

#include <iostream>
#include <string>

#include "ITrafficLightState.h"
#include "TrafficLight.h"

namespace TrafficLight01
{
    void TrafficLight::setState(ITrafficLightState* state)
    {
        m_state = state; 
    }

    ITrafficLightState* TrafficLight::getState()
    {
        return m_state; 
    }

    void TrafficLight::change()
    {
        m_state->changeState(this);
    }

    void TrafficLight::show() const
    {
        m_state->reportState();
    }
}

// ===========================================================================
// End-of-File
// ===========================================================================
