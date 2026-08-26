#include "TrafficLightSystemFactory.h"
#include "TrafficController.h"
#include "UserController.h"
#include "InputHandler.h"
#include "Logger.h"

TrafficLightSystemFactory::TrafficLightSystemFactory()
    : logger(nullptr), inputHandler(nullptr), trafficState(nullptr)
    , trafficController(nullptr), userController(nullptr) {}

TrafficLightSystem* TrafficLightSystemFactory::createTrafficLightSystem() {
    logger = new Logger();
    inputHandler = new InputHandler(logger);
    trafficState = new TrafficState();

    TrafficController* controller = new TrafficController(trafficState);
    trafficController = controller;

    userController = new UserController(inputHandler, logger, trafficState, 
        controller->getOrderedLaneCycle());

    return new TrafficLightSystem(trafficController, userController, logger);
}

TrafficLightSystemFactory::~TrafficLightSystemFactory() {
    delete userController;
    delete trafficController;
    delete trafficState;
    delete inputHandler;
    delete logger;
}
