#include <iostream>
#include <string>
#include <memory>

#include "ITrafficLight.h"
#include "TrafficLight.h"

#include "GreenLight.h"
#include "YellowLight.h"

namespace StatePattern
{
    void TrafficLight::setState(ITrafficLight* state)
    {
        m_state = state; 
    }

    ITrafficLight* TrafficLight::getState()
    {
        return m_state; 
    } // WIE SOLL DAS FUNKTIONIEREN ???

    void TrafficLight::Change()
    {
        m_state->Change(this);
    }

    void TrafficLight::ReportState()
    {
        m_state->ReportState();
    }
}
