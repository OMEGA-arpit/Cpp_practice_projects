#ifndef TRAFFIC_LIGHT_SYSTEM_TEST_H
#define TRAFFIC_LIGHT_SYSTEM_TEST_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "IMockTrafficController.h"
#include "IMockUserController.h"
#include "IMockLogger.h"
#include "TrafficLightSystem.h"
#include "Constants.h"

using ::testing::_;
using ::testing::AnyNumber;

class GivenTrafficLightSystemTest : public ::testing::Test {
protected:
    IMockTrafficController trafficController;
    IMockUserController userController;
    IMockLogger logger;
    TrafficLightSystem* trafficLightSystem;

    void SetUp() override;
    void TearDown() override;
};

#endif
