#ifndef TRAFFIC_STATE_H
#define TRAFFIC_STATE_H

#include "Constants.h"
#include <mutex>

/**
 * @brief Lightweight, mutex-free snapshot of TrafficState.
 *
 * Captured under stateMutex in UserController::processQuery so the mutex
 * is held only for the brief field copy, not during computation or display.
 * Adding a new field here requires a matching copy in processQuery.
 */
struct TrafficStateSnapshot {
    Constants::Direction activeLane  = Constants::Direction::NORTH;
    int timeRemaining                = Constants::GREEN_DURATION_SECONDS;
};

/**
 * @brief Shared mutable state written by TrafficController and read by UserController.
 *
 * All accesses to activeLane and timeRemaining must be guarded by stateMutex
 * to prevent data races across the controller and input threads.
 */
struct TrafficState {
    Constants::Direction activeLane;
    int timeRemaining;
    std::mutex stateMutex;

    TrafficState() : activeLane(Constants::Direction::NORTH)
    , timeRemaining(Constants::GREEN_DURATION_SECONDS) {}
};

#endif
