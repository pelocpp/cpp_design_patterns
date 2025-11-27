// ===========================================================================
// YellowLight.cpp
// ===========================================================================

#include <iostream>
#include <string>

#include "ITrafficLightState.h"
#include "TrafficLight.h"

#include "RedLight.h"
#include "YellowLight.h"

namespace TrafficLight01
{
    void YellowLight::changeState(TrafficLight* light)
    {
        light->setState(new RedLight());
    }

    void YellowLight::reportState() const
    {
        std::cout << "Yellow Light" << std::endl;
    }
}

// ===========================================================================
// End-of-File
// ===========================================================================
