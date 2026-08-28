#ifndef TRAFFIC_LIGHT_SYSTEM_H
#define TRAFFIC_LIGHT_SYSTEM_H

#include "ITrafficController.h"
#include "IUserController.h"
#include "ILogger.h"
#include <thread>

/**
 * @brief Top-level orchestrator that wires subsystems and manages the two threads.
 *
 * On initiateTrafficSystem():
 *  - Spawns a controller thread running ITrafficController::startTrafficCycle.
 *  - Spawns an input thread running IUserController::handleUserQueries.
 *  - Blocks until the input thread completes (user exits), then stops the cycle.
 *
 * All pointers are non-owning; lifetime is managed by TrafficLightSystemFactory.
 */
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

    /**
     * @brief Displays the welcome screen and enters the two-thread run loop.
     *
     * Returns only after the user exits the query loop and the controller
     * thread has been joined cleanly.
     */
    void initiateTrafficSystem();
};

#endif
