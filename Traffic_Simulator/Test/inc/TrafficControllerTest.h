#ifndef TRAFFIC_CONTROLLER_TEST_H
#define TRAFFIC_CONTROLLER_TEST_H

#include <gtest/gtest.h>
#include "TrafficController.h"
#include "TrafficState.h"
#include "Constants.h"

class GivenTrafficControllerTest : public ::testing::Test {
protected:
    TrafficState trafficState;
    TrafficController* trafficController;

    void SetUp() override;
    void TearDown() override;
};

#endif
