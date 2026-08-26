#include "TrafficLightSystemFactory.h"
#include "TrafficLightSystem.h"

int main()
{
    TrafficLightSystemFactory factory;
    TrafficLightSystem* system = factory.createTrafficLightSystem();
    system->initiateTrafficSystem();
    delete system;
    return 0;
}
