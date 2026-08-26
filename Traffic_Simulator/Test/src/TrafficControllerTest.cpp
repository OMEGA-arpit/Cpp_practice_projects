#include "TrafficControllerTest.h"
#include <thread>
#include <chrono>

void GivenTrafficControllerTest::SetUp() {
    trafficController = new TrafficController(&trafficState);
}

void GivenTrafficControllerTest::TearDown() {
    delete trafficController;
}

// initializeLanes

TEST_F(GivenTrafficControllerTest, WhenConstructed_ThenLaneCycleHasFourLanes) {
    EXPECT_EQ(trafficController->getOrderedLaneCycle().size(), 4);
}

TEST_F(GivenTrafficControllerTest, WhenConstructed_ThenFirstLaneIsNorth) {
    EXPECT_EQ(trafficController->getOrderedLaneCycle()[0].direction, Constants::Direction::NORTH);
}

TEST_F(GivenTrafficControllerTest, WhenConstructed_ThenSecondLaneIsSouth) {
    EXPECT_EQ(trafficController->getOrderedLaneCycle()[1].direction, Constants::Direction::SOUTH);
}

TEST_F(GivenTrafficControllerTest, WhenConstructed_ThenThirdLaneIsEast) {
    EXPECT_EQ(trafficController->getOrderedLaneCycle()[2].direction, Constants::Direction::EAST);
}

TEST_F(GivenTrafficControllerTest, WhenConstructed_ThenFourthLaneIsWest) {
    EXPECT_EQ(trafficController->getOrderedLaneCycle()[3].direction, Constants::Direction::WEST);
}

TEST_F(GivenTrafficControllerTest, WhenConstructed_ThenEachLaneHasCorrectGreenDuration) {
    for (const auto& lane : trafficController->getOrderedLaneCycle()) 
    {
        EXPECT_EQ(lane.greenLightDuration, Constants::GREEN_DURATION_SECONDS);
    }
}

TEST_F(GivenTrafficControllerTest, WhenConstructed_ThenTrafficStateInitialisedToNorth) {
    EXPECT_EQ(trafficState.activeLane, Constants::Direction::NORTH);
}

TEST_F(GivenTrafficControllerTest, WhenConstructed_ThenTrafficStateTimeRemainingIsGreenDuration) {
    EXPECT_EQ(trafficState.timeRemaining, Constants::GREEN_DURATION_SECONDS);
}

// stopTrafficCycle

TEST_F(GivenTrafficControllerTest, WhenStopCycleCalled_ThenThreadJoinsCleanly) {
    std::thread cycleThread(&TrafficController::startTrafficCycle, trafficController);
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    trafficController->stopTrafficCycle();
    cycleThread.join();

    SUCCEED();
}

// TrafficState after cycle runs

TEST_F(GivenTrafficControllerTest, WhenCycleRuns_ThenActiveLaneIsAlwaysAValidDirection) {
    std::thread cycleThread(&TrafficController::startTrafficCycle, trafficController);
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    trafficController->stopTrafficCycle();
    cycleThread.join();

    Constants::Direction lane = trafficState.activeLane;
    bool isValid = (lane == Constants::Direction::NORTH || lane == Constants::Direction::SOUTH ||
                    lane == Constants::Direction::EAST || lane == Constants::Direction::WEST);
    EXPECT_TRUE(isValid);
}

TEST_F(GivenTrafficControllerTest, WhenCycleRuns_ThenTimeRemainingIsWithinValidRange) {
    std::thread cycleThread(&TrafficController::startTrafficCycle, trafficController);
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    trafficController->stopTrafficCycle();
    cycleThread.join();

    EXPECT_GE(trafficState.timeRemaining, 0);
    EXPECT_LE(trafficState.timeRemaining, Constants::GREEN_DURATION_SECONDS);
}
