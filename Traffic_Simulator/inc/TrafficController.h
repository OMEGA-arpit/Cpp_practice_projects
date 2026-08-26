#ifndef TRAFFIC_CONTROLLER_H
#define TRAFFIC_CONTROLLER_H

#include "ITrafficController.h"
#include "TrafficState.h"
#include "Lane.h"
#include <vector>
#include <atomic>
#include <mutex>
#include <condition_variable>

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
    TrafficController(TrafficState* trafficState);

    const std::vector<Lane>& getOrderedLaneCycle() {
        return orderedLaneCycle;
    }

    void startTrafficCycle() override;
    void stopTrafficCycle() override;
};

#endif
