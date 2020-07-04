#include <iostream>
#include <string>

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
    void GreenLight::Change(TrafficLight* light)
    {
        light->setState(new YellowLight());
    }

    void GreenLight::ReportState()
    {
        std::cout << "Green Light" << std::endl;
    }
}
