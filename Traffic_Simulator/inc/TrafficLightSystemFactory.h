#ifndef TRAFFIC_LIGHT_SYSTEM_FACTORY_H
#define TRAFFIC_LIGHT_SYSTEM_FACTORY_H

#include "TrafficLightSystem.h"
#include "ITrafficController.h"
#include "IUserController.h"
#include "IInputHandler.h"
#include "ILogger.h"
#include "TrafficState.h"
#include <memory>

class TrafficLightSystemFactory {
    std::unique_ptr<ILogger> logger;
    std::unique_ptr<IInputHandler> inputHandler;
    std::unique_ptr<TrafficState> trafficState;
    std::unique_ptr<ITrafficController> trafficController;
    std::unique_ptr<IUserController> userController;

public:
    std::unique_ptr<TrafficLightSystem> createTrafficLightSystem();
};

#endif
