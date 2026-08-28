#ifndef ITRAFFIC_CONTROLLER_H
#define ITRAFFIC_CONTROLLER_H

#include "Constants.h"

/**
 * @brief Manages the traffic-light phase cycle on a background thread.
 *
 * The cycle loops through the configured lane sequence, writing each
 * active lane and its countdown into the shared TrafficState.
 * startTrafficCycle() blocks until stopTrafficCycle() is called from
 * another thread.
 */
class ITrafficController {
public:
    /**
     * @brief Starts the phase loop. Blocks until stopTrafficCycle() is called.
     */
    virtual void startTrafficCycle() = 0;

    /**
     * @brief Signals the cycle to stop and unblocks any in-progress wait.
     */
    virtual void stopTrafficCycle() = 0;

    virtual ~ITrafficController() = default;
};

#endif
