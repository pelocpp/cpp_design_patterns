// ===========================================================================
// GreenLight.cpp
// ===========================================================================

#include <iostream>
#include <string>

#include "ITrafficLightState.h"
#include "TrafficLight.h"

#include "GreenLight.h"
#include "YellowLight.h"

namespace TrafficLight03
{
    std::shared_ptr<GreenLight> GreenLight::m_instance{ nullptr };

    std::shared_ptr<GreenLight> GreenLight::getInstance() {
        if (m_instance == nullptr) {
            m_instance = std::shared_ptr<GreenLight>(new GreenLight{ });
        }

        return m_instance;
    }

    void GreenLight::changeState(TrafficLight& light)
    {
        light.setState(YellowLight::getInstance());
    }

    void GreenLight::reportState() const
    {
        std::cout << "Green Light" << std::endl;
    }
}

// ===========================================================================
// End-of-File
// ===========================================================================
