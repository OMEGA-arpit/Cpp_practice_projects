#ifndef USER_CONTROLLER_TEST_H
#define USER_CONTROLLER_TEST_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "IMockLogger.h"
#include "IMockInputHandler.h"
#include "UserController.h"
#include "TrafficState.h"
#include "Constants.h"
#include <vector>

using ::testing::_;
using ::testing::AnyNumber;

class GivenUserControllerTest : public ::testing::Test {
protected:
    IMockLogger logger;
    IMockInputHandler inputHandler;
    TrafficState trafficState;
    std::vector<Lane> lanes;
    UserController* userController;

    void SetUp() override;
    void TearDown() override;
};

#endif
