#include <iostream>
#include <string>
#include <memory>

#include "ITrafficLight.h"
#include "TrafficLight.h"

#include "GreenLight.h"
#include "RedLight.h"
#include "YellowLight.h"

// https://www.frag-den-fahrlehrer.de/2016/02/20/die-vier-ampelphasen/#:~:text=Die%20vier%20Phasen%20sind%20gr%C3%BCn,in%20die%20Kreuzung%20quetschen%20darf!


// https://www.c-sharpcorner.com/blogs/traffic-light-system-design-pattern

// http://www.cplusplus.com/articles/zAqpX9L8/

void test_trafficlight()
{
    using namespace StatePattern;

    TrafficLight trafficLight;
    trafficLight.setState (new RedLight());
    trafficLight.ReportState();

    while (true)
    {
        trafficLight.Change();
        trafficLight.ReportState();
        std::cout << "<enter key>";

        char ch;
        std::cin >> ch;
    }
}
