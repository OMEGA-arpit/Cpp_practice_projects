#ifndef TRAFFIC_LIGHT_SYSTEM_FACTORY_H
#define TRAFFIC_LIGHT_SYSTEM_FACTORY_H

#include "TrafficLightSystem.h"
#include "ITrafficController.h"
#include "IUserController.h"
#include "IInputHandler.h"
#include "ILogger.h"
#include "TrafficState.h"

class TrafficLightSystemFactory {
    ILogger* logger;
    IInputHandler* inputHandler;
    TrafficState* trafficState;
    ITrafficController* trafficController;
    IUserController* userController;

public:
    TrafficLightSystemFactory();
    TrafficLightSystem* createTrafficLightSystem();
    ~TrafficLightSystemFactory();
};

#endif
