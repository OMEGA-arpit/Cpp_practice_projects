#ifndef TRAFFIC_STATE_H
#define TRAFFIC_STATE_H

#include "Constants.h"
#include <mutex>

struct TrafficState {
    Constants::Direction activeLane;
    int timeRemaining;
    std::mutex stateMutex;

    TrafficState() : activeLane(Constants::Direction::NORTH)
    , timeRemaining(Constants::GREEN_DURATION_SECONDS) {}
};

#endif
