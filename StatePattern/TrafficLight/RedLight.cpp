#include <iostream>
#include <string>
#include <memory>

#include "ITrafficLight.h"
#include "TrafficLight.h"

#include "GreenLight.h"
#include "RedLight.h"
#include "YellowLight.h"

namespace StatePattern
{
    void RedLight::Change(TrafficLight* light)
    {
        light->setState(new GreenLight());
    }

    void RedLight::ReportState()
    {
        std::cout << "Red Light" << std::endl;
    }
}
