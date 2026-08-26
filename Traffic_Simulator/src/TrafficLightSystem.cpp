#include "TrafficLightSystem.h"
#include "Constants.h"

TrafficLightSystem::TrafficLightSystem(ITrafficController* trafficController,
    IUserController* userController, ILogger* logger)
    : trafficController(trafficController), userController(userController), 
    logger(logger) {}

void TrafficLightSystem::initiateTrafficSystem() {
    logger->printMessage(Constants::MSG_WELCOME);
    logger->printMessage(Constants::MSG_ROAD);

    controllerThread = std::thread(&ITrafficController::startTrafficCycle, trafficController);

    inputThread = std::thread(&IUserController::handleUserQueries, userController);

    inputThread.join();

    shutdownTrafficSystem();
}

void TrafficLightSystem::shutdownTrafficSystem() {
    trafficController->stopTrafficCycle();
    if (controllerThread.joinable()) 
    {
        controllerThread.join();
    }
}
