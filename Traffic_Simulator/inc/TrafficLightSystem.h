#ifndef TRAFFIC_LIGHT_SYSTEM_H
#define TRAFFIC_LIGHT_SYSTEM_H

#include "ITrafficController.h"
#include "IUserController.h"
#include "ILogger.h"
#include <thread>

class TrafficLightSystem {
    ITrafficController* trafficController;
    IUserController* userController;
    ILogger* logger;

    std::thread controllerThread;
    std::thread inputThread;
    
    void shutdownTrafficSystem();

public:
    TrafficLightSystem(ITrafficController* trafficController,
    IUserController* userController, ILogger* logger);

    void initiateTrafficSystem();
};

#endif
