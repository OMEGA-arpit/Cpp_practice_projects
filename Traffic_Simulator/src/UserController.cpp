#include "UserController.h"
#include "Utils.h"

UserController::UserController(
    IInputHandler* inputHandler,
    ILogger* logger,
    TrafficState* trafficState,
    const std::vector<Lane>& orderedLaneCycle)
    : inputHandler(inputHandler)
    , logger(logger)
    , trafficState(trafficState)
    , orderedLaneCycle(orderedLaneCycle)
{}

Constants::Direction UserController::getLane(const std::string& prompt) {
    std::string laneInput;
    Constants::Direction currentLane = Constants::Direction::NORTH;

    while (true)
    {
        logger->printMessage(prompt);
        inputHandler->inputString(laneInput);

        if (!Utils::stringToDirection(laneInput, currentLane))
        {
            logger->printMessage(Constants::MSG_INVALID_INPUT);
        }
        else
        {
            break;
        }
    }

    return currentLane;
}

int UserController::calculateWaitTimeInSeconds(Constants::Direction fromLane, const TrafficState& snapshot) {
    int waitSeconds = 0;

    int activeIndex = 0;
    for (int index = 0; index < (int)orderedLaneCycle.size(); index++)
    {
        if (orderedLaneCycle[index].direction == snapshot.activeLane)
        {
            activeIndex = index;
            break;
        }
    }

    if (orderedLaneCycle[activeIndex].direction == fromLane)
    {
        waitSeconds = 0;
    }
    else
    {
        waitSeconds = snapshot.timeRemaining;
        int totalLanes = (int)orderedLaneCycle.size();
        int current = (activeIndex + 1) % totalLanes;

        while (orderedLaneCycle[current].direction != fromLane)
        {
            waitSeconds += orderedLaneCycle[current].greenLightDuration;
            current = (current + 1) % totalLanes;
        }
    }

    return waitSeconds;
}

MoveResult UserController::buildMoveResult(Constants::Direction fromLane, 
    Constants::Direction toLane, const TrafficState& snapshot) {
    MoveResult result;
    result.fromLane = fromLane;
    result.toLane = toLane;
    result.currentGreenLane = snapshot.activeLane;
    result.timeRemaining = snapshot.timeRemaining;
    result.moveType = Utils::determineMoveType(fromLane, toLane);

    if (result.moveType == Constants::MoveType::UTURN || 
        result.moveType == Constants::MoveType::LEFT)
    {
        result.permission = Constants::MovePermission::FREE;
        result.canGoNow = true;
        result.waitSeconds = 0;
    }
    else
    {
        result.permission = Constants::MovePermission::NEEDS_GREEN;
        result.waitSeconds = calculateWaitTimeInSeconds(fromLane, snapshot);
        result.canGoNow = (result.waitSeconds == 0);
    }

    return result;
}

void UserController::displayMoveResult(const MoveResult& result) {
    logger->printMessage(Constants::MSG_TRAFFIC_STATUS);

    logger->printMessage(Constants::MSG_FROM + Utils::directionToString(result.fromLane) + Constants::NEW_LINE);
    logger->printMessage(Constants::MSG_TO   + Utils::directionToString(result.toLane)   + Constants::NEW_LINE);
    logger->printMessage(Constants::MSG_MOVE + Utils::moveTypeToString(result.moveType)  + Constants::NEW_LINE);
    logger->printNewLine();

    if (result.permission == Constants::MovePermission::FREE)
    {
        logger->printMessage(Constants::MSG_GREEN_FREE);
    }
    else if (result.canGoNow)
    {
        logger->printMessage(Constants::MSG_GREEN_GO);
        logger->printMessage(Constants::MSG_TIME_REMAINING + std::to_string(result.timeRemaining) + Constants::MSG_SECONDS + Constants::NEW_LINE);
    }
    else
    {
        logger->printMessage(Constants::MSG_RED_WAIT);
        logger->printMessage(Constants::MSG_CURRENT_GREEN + Utils::directionToString(result.currentGreenLane) 
        + Constants::MSG_CAN_MOVE + Constants::PARENTHESIS + std::to_string(result.timeRemaining) 
        + Constants::MSG_SEC_REMAINING + Constants::NEW_LINE);
        logger->printMessage(Constants::MSG_LANE_GREEN_IN + std::to_string(result.waitSeconds) + Constants::MSG_SECONDS + Constants::NEW_LINE);
    }

    logger->printMessage(Constants::MSG_DIVIDER);
}

void UserController::processQuery(Constants::Direction fromLane, Constants::Direction toLane) {
    TrafficState snapshot;
    {
        std::lock_guard<std::mutex> lock(trafficState->stateMutex);
        snapshot.activeLane    = trafficState->activeLane;
        snapshot.timeRemaining = trafficState->timeRemaining;
    }

    MoveResult result = buildMoveResult(fromLane, toLane, snapshot);
    displayMoveResult(result);
}

bool UserController::askUserToContinue() {
    bool shouldContinue = false;

    while (true)
    {
        logger->printMessage(Constants::MSG_ASK_ANOTHER_QUERY);
        std::string continueInput;
        inputHandler->inputString(continueInput);

        if (continueInput == Constants::CHOICE_YES)
        {
            shouldContinue = true;
            break;
        }
        else if (continueInput == Constants::CHOICE_NO)
        {
            shouldContinue = false;
            break;
        }
        else
        {
            logger->printMessage(Constants::MSG_INVALID_CONTINUE_INPUT);
        }
    }

    return shouldContinue;
}

void UserController::handleUserQueries()
{
    while (true)
    {
        Constants::Direction fromLane = getLane(Constants::MSG_ENTER_LANE);
        Constants::Direction toLane   = getLane(Constants::MSG_ENTER_DESTINATION);

        processQuery(fromLane, toLane);

        if (!askUserToContinue())
        {
            break;
        }
    }

    logger->printMessage(Constants::MSG_GOODBYE);
}
