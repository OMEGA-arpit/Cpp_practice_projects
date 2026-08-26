#include "UserControllerTest.h"

using ::testing::SetArgReferee;
using ::testing::AtLeast;

void GivenUserControllerTest::SetUp() {
    lanes.push_back(Lane(Constants::Direction::NORTH, Constants::DIRECTION_NORTH, Constants::GREEN_DURATION_SECONDS));
    lanes.push_back(Lane(Constants::Direction::EAST,  Constants::DIRECTION_EAST,  Constants::GREEN_DURATION_SECONDS));
    lanes.push_back(Lane(Constants::Direction::SOUTH, Constants::DIRECTION_SOUTH, Constants::GREEN_DURATION_SECONDS));
    lanes.push_back(Lane(Constants::Direction::WEST,  Constants::DIRECTION_WEST,  Constants::GREEN_DURATION_SECONDS));

    trafficState.activeLane    = Constants::Direction::NORTH;
    trafficState.timeRemaining = Constants::GREEN_DURATION_SECONDS;

    userController = new UserController(&inputHandler, &logger, &trafficState, lanes);

    EXPECT_CALL(logger, printMessage(_)).Times(AnyNumber());
    EXPECT_CALL(logger, printNewLine()).Times(AnyNumber());
}

void GivenUserControllerTest::TearDown() {
    delete userController;
}

// getLane 

TEST_F(GivenUserControllerTest, WhenLaneInputIsInvalid_ThenShowsInvalidInputMessage) {
    EXPECT_CALL(inputHandler, inputString(_))
        .WillOnce(SetArgReferee<0>("X"))
        .WillOnce(SetArgReferee<0>(Constants::DIRECTION_NORTH_CHAR))
        .WillOnce(SetArgReferee<0>(Constants::DIRECTION_NORTH_CHAR))
        .WillOnce(SetArgReferee<0>("N"));

    EXPECT_CALL(logger, printMessage(Constants::MSG_INVALID_INPUT)).Times(AtLeast(1));

    userController->handleUserQueries();
}

TEST_F(GivenUserControllerTest, WhenDestinationInputIsInvalid_ThenShowsInvalidInputMessage) {
    EXPECT_CALL(inputHandler, inputString(_))
        .WillOnce(SetArgReferee<0>(Constants::DIRECTION_NORTH_CHAR))
        .WillOnce(SetArgReferee<0>("Z"))
        .WillOnce(SetArgReferee<0>(Constants::DIRECTION_NORTH_CHAR))
        .WillOnce(SetArgReferee<0>("N"));

    EXPECT_CALL(logger, printMessage(Constants::MSG_INVALID_INPUT)).Times(AtLeast(1));

    userController->handleUserQueries();
}

// askUserToContinue

TEST_F(GivenUserControllerTest, WhenContinueInputIsInvalid_ThenShowsInvalidContinueMessage) {
    EXPECT_CALL(inputHandler, inputString(_))
        .WillOnce(SetArgReferee<0>(Constants::DIRECTION_NORTH_CHAR))
        .WillOnce(SetArgReferee<0>(Constants::DIRECTION_NORTH_CHAR))
        .WillOnce(SetArgReferee<0>("x"))
        .WillOnce(SetArgReferee<0>("N"));

    EXPECT_CALL(logger, printMessage(Constants::MSG_INVALID_CONTINUE_INPUT)).Times(AtLeast(1));

    userController->handleUserQueries();
}

TEST_F(GivenUserControllerTest, WhenContinueInputIsN_ThenShowsGoodbye) {
    EXPECT_CALL(inputHandler, inputString(_))
        .WillOnce(SetArgReferee<0>(Constants::DIRECTION_NORTH_CHAR))
        .WillOnce(SetArgReferee<0>(Constants::DIRECTION_NORTH_CHAR))
        .WillOnce(SetArgReferee<0>("N"));

    EXPECT_CALL(logger, printMessage(Constants::MSG_GOODBYE)).Times(1);

    userController->handleUserQueries();
}

TEST_F(GivenUserControllerTest, WhenContinueInputIsY_ThenLoopsAndShowsTrafficStatusTwice) {
    EXPECT_CALL(inputHandler, inputString(_))
        .WillOnce(SetArgReferee<0>(Constants::DIRECTION_NORTH_CHAR))
        .WillOnce(SetArgReferee<0>(Constants::DIRECTION_NORTH_CHAR))
        .WillOnce(SetArgReferee<0>("Y"))
        .WillOnce(SetArgReferee<0>(Constants::DIRECTION_EAST_CHAR))
        .WillOnce(SetArgReferee<0>(Constants::DIRECTION_EAST_CHAR))
        .WillOnce(SetArgReferee<0>("N"));

    EXPECT_CALL(logger, printMessage(Constants::MSG_TRAFFIC_STATUS)).Times(2);

    userController->handleUserQueries();
}

// processQuery 

TEST_F(GivenUserControllerTest, WhenUTurn_ThenShowsFreeMoveMessage) {
    EXPECT_CALL(inputHandler, inputString(_))
        .WillOnce(SetArgReferee<0>(Constants::DIRECTION_NORTH_CHAR))
        .WillOnce(SetArgReferee<0>(Constants::DIRECTION_NORTH_CHAR))
        .WillOnce(SetArgReferee<0>("N"));

    EXPECT_CALL(logger, printMessage(Constants::MSG_GREEN_FREE)).Times(1);

    userController->handleUserQueries();
}

TEST_F(GivenUserControllerTest, WhenLeftTurn_ThenShowsFreeMoveMessage) {
    EXPECT_CALL(inputHandler, inputString(_))
        .WillOnce(SetArgReferee<0>(Constants::DIRECTION_NORTH_CHAR))
        .WillOnce(SetArgReferee<0>(Constants::DIRECTION_EAST_CHAR))
        .WillOnce(SetArgReferee<0>("N"));

    EXPECT_CALL(logger, printMessage(Constants::MSG_GREEN_FREE)).Times(1);

    userController->handleUserQueries();
}


TEST_F(GivenUserControllerTest, WhenStraightAndLaneIsGreen_ThenShowsGoMessage) {
    trafficState.activeLane = Constants::Direction::NORTH;
    trafficState.timeRemaining = 7;

    EXPECT_CALL(inputHandler, inputString(_))
        .WillOnce(SetArgReferee<0>(Constants::DIRECTION_NORTH_CHAR))
        .WillOnce(SetArgReferee<0>(Constants::DIRECTION_SOUTH_CHAR))
        .WillOnce(SetArgReferee<0>("N"));

    EXPECT_CALL(logger, printMessage(Constants::MSG_GREEN_GO)).Times(1);

    userController->handleUserQueries();
}

TEST_F(GivenUserControllerTest, WhenRightTurnAndLaneIsGreen_ThenShowsGoMessage) {
    trafficState.activeLane = Constants::Direction::NORTH;
    trafficState.timeRemaining = 7;

    EXPECT_CALL(inputHandler, inputString(_))
        .WillOnce(SetArgReferee<0>(Constants::DIRECTION_NORTH_CHAR))
        .WillOnce(SetArgReferee<0>(Constants::DIRECTION_WEST_CHAR))
        .WillOnce(SetArgReferee<0>("N"));

    EXPECT_CALL(logger, printMessage(Constants::MSG_GREEN_GO)).Times(1);

    userController->handleUserQueries();
}


TEST_F(GivenUserControllerTest, WhenStraightAndLaneIsRed_ThenShowsWaitMessage) {
    trafficState.activeLane = Constants::Direction::EAST;
    trafficState.timeRemaining = 5;

    EXPECT_CALL(inputHandler, inputString(_))
        .WillOnce(SetArgReferee<0>(Constants::DIRECTION_NORTH_CHAR))
        .WillOnce(SetArgReferee<0>(Constants::DIRECTION_SOUTH_CHAR))
        .WillOnce(SetArgReferee<0>("N"));

    EXPECT_CALL(logger, printMessage(Constants::MSG_RED_WAIT)).Times(1);

    userController->handleUserQueries();
}

TEST_F(GivenUserControllerTest, WhenRightAndLaneIsRed_ThenShowsWaitMessage) {
    trafficState.activeLane = Constants::Direction::EAST;
    trafficState.timeRemaining = 5;

    EXPECT_CALL(inputHandler, inputString(_))
        .WillOnce(SetArgReferee<0>(Constants::DIRECTION_NORTH_CHAR))
        .WillOnce(SetArgReferee<0>(Constants::DIRECTION_WEST_CHAR))
        .WillOnce(SetArgReferee<0>("N"));

    EXPECT_CALL(logger, printMessage(Constants::MSG_RED_WAIT)).Times(1);

    userController->handleUserQueries();
}

// calculateWaitTimeInSeconds

TEST_F(GivenUserControllerTest, WhenMyLaneIsNextInCycle_ThenWaitIsTimeRemaining) {
    trafficState.activeLane = Constants::Direction::NORTH;
    trafficState.timeRemaining = 6;

    EXPECT_CALL(inputHandler, inputString(_))
        .WillOnce(SetArgReferee<0>(Constants::DIRECTION_EAST_CHAR))
        .WillOnce(SetArgReferee<0>(Constants::DIRECTION_WEST_CHAR))
        .WillOnce(SetArgReferee<0>("N"));

    EXPECT_CALL(logger, printMessage(Constants::MSG_LANE_GREEN_IN + "6" + Constants::MSG_SECONDS + Constants::NEW_LINE)).Times(1);

    userController->handleUserQueries();
}

TEST_F(GivenUserControllerTest, WhenMyLaneIsTwoPhasesAway_ThenWaitAccumulatesCorrectly) {
    trafficState.activeLane = Constants::Direction::NORTH;
    trafficState.timeRemaining = 4;

    EXPECT_CALL(inputHandler, inputString(_))
        .WillOnce(SetArgReferee<0>(Constants::DIRECTION_SOUTH_CHAR))
        .WillOnce(SetArgReferee<0>(Constants::DIRECTION_NORTH_CHAR))
        .WillOnce(SetArgReferee<0>("N"));

    EXPECT_CALL(logger, printMessage(Constants::MSG_LANE_GREEN_IN + "14" + Constants::MSG_SECONDS + Constants::NEW_LINE)).Times(1);

    userController->handleUserQueries();
}

TEST_F(GivenUserControllerTest, WhenMyLaneIsThreePhasesAway_ThenWaitAccumulatesCorrectly) {
    trafficState.activeLane = Constants::Direction::NORTH;
    trafficState.timeRemaining = 3;

    EXPECT_CALL(inputHandler, inputString(_))
        .WillOnce(SetArgReferee<0>(Constants::DIRECTION_WEST_CHAR))
        .WillOnce(SetArgReferee<0>(Constants::DIRECTION_EAST_CHAR))
        .WillOnce(SetArgReferee<0>("N"));

    EXPECT_CALL(logger, printMessage(Constants::MSG_LANE_GREEN_IN + "23" + Constants::MSG_SECONDS + Constants::NEW_LINE)).Times(1);

    userController->handleUserQueries();
}
