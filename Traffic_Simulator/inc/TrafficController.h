#ifndef TRAFFIC_CONTROLLER_H
#define TRAFFIC_CONTROLLER_H

#include "ITrafficController.h"
#include "TrafficState.h"
#include "Lane.h"
#include <vector>
#include <atomic>
#include <mutex>
#include <condition_variable>

/**
 * @brief Drives the traffic-light phase cycle on a dedicated background thread.
 *
 * Cycles through orderedLaneCycle in sequence, writing the active lane and
 * countdown into the shared TrafficState each second. A condition_variable
 * allows stopTrafficCycle() to unblock the 1-second countdown wait immediately
 * rather than waiting for the current sleep to expire.
 */
class TrafficController : public ITrafficController {

    TrafficState* trafficState;
    std::vector<Lane> orderedLaneCycle;
    int activeLaneIndex;

    std::mutex shutdownMutex;
    std::condition_variable shutdownSignal;
    std::atomic<bool> isCyclingActive;

    void initializeLanes();
    void activateNextPhase();
    void countDownCurrentPhase();

public:
    /**
     * @brief Constructs the controller, populates the lane cycle, and sets the
     *        start index so the first activateNextPhase() call lands on NORTH.
     * @param trafficState Shared state to update during the cycle (non-owning).
     */
    TrafficController(TrafficState* trafficState);

    /**
     * @brief Returns the ordered lane sequence used by the cycle.
     *
     * The reference is stable for the lifetime of this TrafficController.
     * Used by UserController to calculate wait times.
     */
    const std::vector<Lane>& getOrderedLaneCycle() {
        return orderedLaneCycle;
    }

    void startTrafficCycle() override;
    void stopTrafficCycle() override;
};

#endif
