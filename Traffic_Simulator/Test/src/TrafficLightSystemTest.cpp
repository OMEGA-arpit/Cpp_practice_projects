#include "TrafficLightSystemTest.h"

using ::testing::Return;
using ::testing::AtLeast;

void GivenTrafficLightSystemTest::SetUp() {
    trafficLightSystem = new TrafficLightSystem(&trafficController, &userController, &logger);

    EXPECT_CALL(logger, printMessage(_)).Times(AnyNumber());
    EXPECT_CALL(logger, printNewLine()).Times(AnyNumber());
    EXPECT_CALL(trafficController, startTrafficCycle()).Times(AnyNumber()).WillRepeatedly(Return());
    EXPECT_CALL(trafficController, stopTrafficCycle()).Times(AnyNumber()).WillRepeatedly(Return());
    EXPECT_CALL(userController, handleUserQueries()).Times(AnyNumber()).WillRepeatedly(Return());
}

void GivenTrafficLightSystemTest::TearDown() {
    delete trafficLightSystem;
}

// initiateTrafficSystem

TEST_F(GivenTrafficLightSystemTest, WhenSystemInitiated_ThenShowsWelcomeMessage) {
    EXPECT_CALL(logger, printMessage(Constants::MSG_WELCOME)).Times(1);

    trafficLightSystem->initiateTrafficSystem();
}

TEST_F(GivenTrafficLightSystemTest, WhenSystemInitiated_ThenShowsRoadStructure) {
    EXPECT_CALL(logger, printMessage(Constants::MSG_ROAD)).Times(1);

    trafficLightSystem->initiateTrafficSystem();
}

TEST_F(GivenTrafficLightSystemTest, WhenSystemInitiated_ThenStartsTrafficCycle) {
    EXPECT_CALL(trafficController, startTrafficCycle()).Times(AtLeast(1)).WillRepeatedly(Return());

    trafficLightSystem->initiateTrafficSystem();
}

TEST_F(GivenTrafficLightSystemTest, WhenSystemInitiated_ThenHandlesUserQueries) {
    EXPECT_CALL(userController, handleUserQueries()).Times(1).WillOnce(Return());

    trafficLightSystem->initiateTrafficSystem();
}

TEST_F(GivenTrafficLightSystemTest, WhenSystemInitiated_ThenStopsTrafficCycleExactlyOnce) {
    EXPECT_CALL(trafficController, stopTrafficCycle()).Times(1).WillOnce(Return());

    trafficLightSystem->initiateTrafficSystem();
}
