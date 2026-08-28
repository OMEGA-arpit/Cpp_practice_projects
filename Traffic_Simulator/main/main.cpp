#include "TrafficLightSystemFactory.h"
#include "TrafficLightSystem.h"

int main()
{
    TrafficLightSystemFactory factory;
    auto system = factory.createTrafficLightSystem();
    system->initiateTrafficSystem();
    return 0;
}
