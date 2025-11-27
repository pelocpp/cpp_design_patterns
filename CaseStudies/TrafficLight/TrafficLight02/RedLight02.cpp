// ===========================================================================
// RedLight.cpp
// ===========================================================================

#include <iostream>
#include <string>

#include "ITrafficLightState.h"
#include "TrafficLight.h"

#include "GreenLight.h"
#include "RedLight.h"

namespace TrafficLight02
{
    void RedLight::changeState(TrafficLight& light)
    {
        light.setState(std::make_shared<GreenLight>());
    }

    void RedLight::reportState() const
    {
        std::cout << "Red Light" << std::endl;
    }
}

// ===========================================================================
// End-of-File
// ===========================================================================
