#ifndef I_MOCK_TRAFFIC_CONTROLLER_H
#define I_MOCK_TRAFFIC_CONTROLLER_H

#include <gmock/gmock.h>
#include "ITrafficController.h"

class IMockTrafficController : public ITrafficController {
public:
    MOCK_METHOD(void, startTrafficCycle, (), (override));
    MOCK_METHOD(void, stopTrafficCycle, (), (override));
};

#endif
