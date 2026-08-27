#ifndef TRAFFIC_STATE_H
#define TRAFFIC_STATE_H

#include "Constants.h"
#include <mutex>

// Lightweight, copyable snapshot of TrafficState captured under a lock.
struct TrafficStateSnapshot {
    Constants::Direction activeLane  = Constants::Direction::NORTH;
    int timeRemaining                = Constants::GREEN_DURATION_SECONDS;
};

struct TrafficState {
    Constants::Direction activeLane;
    int timeRemaining;
    std::mutex stateMutex;

    TrafficState() : activeLane(Constants::Direction::NORTH)
    , timeRemaining(Constants::GREEN_DURATION_SECONDS) {}
};

#endif
