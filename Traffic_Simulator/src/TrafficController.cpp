#include "TrafficController.h"
#include "Constants.h"

TrafficController::TrafficController(TrafficState* trafficState)
    : trafficState(trafficState), activeLaneIndex(-1), isCyclingActive(false)
{
    initializeLanes();
}

void TrafficController::initializeLanes() {
    orderedLaneCycle.push_back(Lane(Constants::Direction::NORTH, Constants::DIRECTION_NORTH, Constants::GREEN_DURATION_SECONDS));
    orderedLaneCycle.push_back(Lane(Constants::Direction::SOUTH, Constants::DIRECTION_SOUTH, Constants::GREEN_DURATION_SECONDS));
    orderedLaneCycle.push_back(Lane(Constants::Direction::EAST,  Constants::DIRECTION_EAST,  Constants::GREEN_DURATION_SECONDS));
    orderedLaneCycle.push_back(Lane(Constants::Direction::WEST,  Constants::DIRECTION_WEST,  Constants::GREEN_DURATION_SECONDS));
}

void TrafficController::activateNextPhase() {
    activeLaneIndex = (activeLaneIndex + 1) % orderedLaneCycle.size();

    std::lock_guard<std::mutex> lock(trafficState->stateMutex);
    trafficState->activeLane = orderedLaneCycle[activeLaneIndex].direction;
    trafficState->timeRemaining = orderedLaneCycle[activeLaneIndex].greenLightDuration;
}

void TrafficController::countDownCurrentPhase() {
    for (int index = 0; index < Constants::GREEN_DURATION_SECONDS; index++)
    {
        std::unique_lock<std::mutex> lock(shutdownMutex);
        bool shutdownRequested = shutdownSignal.wait_for(lock, std::chrono::seconds(1), [this] { return !isCyclingActive.load(); });

        if (shutdownRequested)
        {
            return;
        }

        std::lock_guard<std::mutex> stateLock(trafficState->stateMutex);
        trafficState->timeRemaining--;
    }
}

void TrafficController::startTrafficCycle() {
    isCyclingActive = true;

    while (isCyclingActive)
    {
        activateNextPhase();
        countDownCurrentPhase();
    }
}

void TrafficController::stopTrafficCycle() {
    isCyclingActive = false;
    shutdownSignal.notify_one();
}
