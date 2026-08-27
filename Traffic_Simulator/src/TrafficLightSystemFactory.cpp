#include "TrafficLightSystemFactory.h"
#include "TrafficController.h"
#include "UserController.h"
#include "InputHandler.h"
#include "Logger.h"

std::unique_ptr<TrafficLightSystem> TrafficLightSystemFactory::createTrafficLightSystem() {
    logger       = std::make_unique<Logger>();
    inputHandler = std::make_unique<InputHandler>(logger.get());
    trafficState = std::make_unique<TrafficState>();

    auto controller = std::make_unique<TrafficController>(trafficState.get());
    userController  = std::make_unique<UserController>(
        inputHandler.get(), logger.get(), trafficState.get(),
        controller->getOrderedLaneCycle());
    trafficController = std::move(controller);

    return std::make_unique<TrafficLightSystem>(
        trafficController.get(), userController.get(), logger.get());
}
