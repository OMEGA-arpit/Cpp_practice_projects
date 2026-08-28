#ifndef TRAFFIC_LIGHT_SYSTEM_FACTORY_H
#define TRAFFIC_LIGHT_SYSTEM_FACTORY_H

#include "TrafficLightSystem.h"
#include "ITrafficController.h"
#include "IUserController.h"
#include "IInputHandler.h"
#include "ILogger.h"
#include "TrafficState.h"
#include <memory>

/**
 * @brief Constructs and owns the full component graph for one simulation run.
 *
 * Build order: Logger → InputHandler → TrafficState → TrafficController
 *           → UserController → TrafficLightSystem.
 *
 * Ownership is expressed via unique_ptr members; the compiler-generated
 * destructor releases them in reverse-declaration order, which is the
 * correct dependency teardown sequence.
 *
 * @note The factory must outlive the TrafficLightSystem it creates, because
 *       the system holds raw (non-owning) pointers into factory-managed objects.
 */
class TrafficLightSystemFactory {
    std::unique_ptr<ILogger> logger;
    std::unique_ptr<IInputHandler> inputHandler;
    std::unique_ptr<TrafficState> trafficState;
    std::unique_ptr<ITrafficController> trafficController;
    std::unique_ptr<IUserController> userController;

public:
    /**
     * @brief Allocates and wires all subsystem components.
     * @return A unique_ptr to the fully initialised TrafficLightSystem.
     */
    std::unique_ptr<TrafficLightSystem> createTrafficLightSystem();
};

#endif
