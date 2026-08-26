#ifndef USER_CONTROLLER_H
#define USER_CONTROLLER_H

#include "IUserController.h"
#include "IInputHandler.h"
#include "ILogger.h"
#include "TrafficState.h"
#include "MoveResult.h"
#include "Lane.h"
#include <vector>
#include <string>

class UserController : public IUserController {
    IInputHandler* inputHandler;
    ILogger* logger;
    TrafficState* trafficState;
    const std::vector<Lane>& orderedLaneCycle;

    Constants::Direction getLane(const std::string& prompt);
    int calculateWaitTimeInSeconds(Constants::Direction fromLane, const TrafficState& snapshot);
    MoveResult buildMoveResult(Constants::Direction fromLane, 
    Constants::Direction toLane, const TrafficState& snapshot);
    void displayMoveResult(const MoveResult& result);
    void processQuery(Constants::Direction fromLane, Constants::Direction toLane);
    bool askUserToContinue();

public:
    UserController(IInputHandler* inputHandler, ILogger* logger,
        TrafficState* trafficState, const std::vector<Lane>& orderedLaneCycle);

    void handleUserQueries() override;
};

#endif
