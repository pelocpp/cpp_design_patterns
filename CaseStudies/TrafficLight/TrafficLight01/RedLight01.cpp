// ===========================================================================
// RedLight.cpp
// ===========================================================================

#include <iostream>
#include <string>

#include "ITrafficLightState.h"
#include "TrafficLight.h"

#include "GreenLight.h"
#include "RedLight.h"

namespace TrafficLight01
{
    void RedLight::changeState(TrafficLight* light)
    {
        light->setState(new GreenLight());
    }

    void RedLight::reportState() const 
    {
        std::cout << "Red Light" << std::endl;
    }
}

// ===========================================================================
// End-of-File
// ===========================================================================
