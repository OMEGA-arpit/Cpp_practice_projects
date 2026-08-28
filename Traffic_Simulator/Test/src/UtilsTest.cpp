#include <gtest/gtest.h>
#include "Utils.h"
#include "Constants.h"

// Determine MoveType : UTurn

TEST(GivenUtils, WhenNorthToNorth_ThenReturnsUTurn) {
    EXPECT_EQ(Utils::determineMoveType(Constants::Direction::NORTH, Constants::Direction::NORTH), Constants::MoveType::UTURN);
}

TEST(GivenUtils, WhenEastToEast_ThenReturnsUTurn) {
    EXPECT_EQ(Utils::determineMoveType(Constants::Direction::EAST, Constants::Direction::EAST), Constants::MoveType::UTURN);
}

TEST(GivenUtils, WhenSouthToSouth_ThenReturnsUTurn) {
    EXPECT_EQ(Utils::determineMoveType(Constants::Direction::SOUTH, Constants::Direction::SOUTH), Constants::MoveType::UTURN);
}

TEST(GivenUtils, WhenWestToWest_ThenReturnsUTurn) {
    EXPECT_EQ(Utils::determineMoveType(Constants::Direction::WEST, Constants::Direction::WEST), Constants::MoveType::UTURN);
}

// Determine MoveType : Straight

TEST(GivenUtils, WhenNorthToSouth_ThenReturnsStraight) {
    EXPECT_EQ(Utils::determineMoveType(Constants::Direction::NORTH, Constants::Direction::SOUTH), Constants::MoveType::STRAIGHT);
}

TEST(GivenUtils, WhenSouthToNorth_ThenReturnsStraight) {
    EXPECT_EQ(Utils::determineMoveType(Constants::Direction::SOUTH, Constants::Direction::NORTH), Constants::MoveType::STRAIGHT);
}

TEST(GivenUtils, WhenEastToWest_ThenReturnsStraight) {
    EXPECT_EQ(Utils::determineMoveType(Constants::Direction::EAST, Constants::Direction::WEST), Constants::MoveType::STRAIGHT);
}

TEST(GivenUtils, WhenWestToEast_ThenReturnsStraight) {
    EXPECT_EQ(Utils::determineMoveType(Constants::Direction::WEST, Constants::Direction::EAST), Constants::MoveType::STRAIGHT);
}

// Determine MoveType : Left

TEST(GivenUtils, WhenNorthToEast_ThenReturnsLeft) {
    EXPECT_EQ(Utils::determineMoveType(Constants::Direction::NORTH, Constants::Direction::EAST), Constants::MoveType::LEFT);
}

TEST(GivenUtils, WhenEastToSouth_ThenReturnsLeft) {
    EXPECT_EQ(Utils::determineMoveType(Constants::Direction::EAST, Constants::Direction::SOUTH), Constants::MoveType::LEFT);
}

TEST(GivenUtils, WhenSouthToWest_ThenReturnsLeft) {
    EXPECT_EQ(Utils::determineMoveType(Constants::Direction::SOUTH, Constants::Direction::WEST), Constants::MoveType::LEFT);
}

TEST(GivenUtils, WhenWestToNorth_ThenReturnsLeft) {
    EXPECT_EQ(Utils::determineMoveType(Constants::Direction::WEST, Constants::Direction::NORTH), Constants::MoveType::LEFT);
}

// Determine MoveType : Right

TEST(GivenUtils, WhenNorthToWest_ThenReturnsRight) {
    EXPECT_EQ(Utils::determineMoveType(Constants::Direction::NORTH, Constants::Direction::WEST), Constants::MoveType::RIGHT);
}

TEST(GivenUtils, WhenEastToNorth_ThenReturnsRight) {
    EXPECT_EQ(Utils::determineMoveType(Constants::Direction::EAST, Constants::Direction::NORTH), Constants::MoveType::RIGHT);
}

TEST(GivenUtils, WhenSouthToEast_ThenReturnsRight) {
    EXPECT_EQ(Utils::determineMoveType(Constants::Direction::SOUTH, Constants::Direction::EAST), Constants::MoveType::RIGHT);
}

TEST(GivenUtils, WhenWestToSouth_ThenReturnsRight) {
    EXPECT_EQ(Utils::determineMoveType(Constants::Direction::WEST, Constants::Direction::SOUTH), Constants::MoveType::RIGHT);
}

// String To Direction

TEST(GivenUtils, WhenShortInputN_ThenReturnsNorth) {
    Constants::Direction direction;
    EXPECT_TRUE(Utils::stringToDirection(Constants::DIRECTION_NORTH_CHAR, direction));
    EXPECT_EQ(direction, Constants::Direction::NORTH);
}

TEST(GivenUtils, WhenShortInputE_ThenReturnsEast) {
    Constants::Direction direction;
    EXPECT_TRUE(Utils::stringToDirection(Constants::DIRECTION_EAST_CHAR, direction));
    EXPECT_EQ(direction, Constants::Direction::EAST);
}

TEST(GivenUtils, WhenShortInputS_ThenReturnsSouth) {
    Constants::Direction direction;
    EXPECT_TRUE(Utils::stringToDirection(Constants::DIRECTION_SOUTH_CHAR, direction));
    EXPECT_EQ(direction, Constants::Direction::SOUTH);
}

TEST(GivenUtils, WhenShortInputW_ThenReturnsWest) {
    Constants::Direction direction;
    EXPECT_TRUE(Utils::stringToDirection(Constants::DIRECTION_WEST_CHAR, direction));
    EXPECT_EQ(direction, Constants::Direction::WEST);
}

TEST(GivenUtils, WhenFullInputNORTH_ThenReturnsNorth) {
    Constants::Direction direction;
    EXPECT_TRUE(Utils::stringToDirection(Constants::DIRECTION_NORTH, direction));
    EXPECT_EQ(direction, Constants::Direction::NORTH);
}

TEST(GivenUtils, WhenFullInputEAST_ThenReturnsEast) {
    Constants::Direction direction;
    EXPECT_TRUE(Utils::stringToDirection(Constants::DIRECTION_EAST, direction));
    EXPECT_EQ(direction, Constants::Direction::EAST);
}

TEST(GivenUtils, WhenFullInputSOUTH_ThenReturnsSouth) {
    Constants::Direction direction;
    EXPECT_TRUE(Utils::stringToDirection(Constants::DIRECTION_SOUTH, direction));
    EXPECT_EQ(direction, Constants::Direction::SOUTH);
}

TEST(GivenUtils, WhenFullInputWEST_ThenReturnsWest) {
    Constants::Direction direction;
    EXPECT_TRUE(Utils::stringToDirection(Constants::DIRECTION_WEST, direction));
    EXPECT_EQ(direction, Constants::Direction::WEST);
}

TEST(GivenUtils, WhenInvalidInputX_ThenReturnsFalse) {
    Constants::Direction direction;
    EXPECT_FALSE(Utils::stringToDirection("X", direction));
}

TEST(GivenUtils, WhenEmptyInput_ThenReturnsFalse) {
    Constants::Direction direction;
    EXPECT_FALSE(Utils::stringToDirection(Constants::EMPTY_STRING, direction));
}

TEST(GivenUtils, WhenLowercaseInput_ThenReturnsFalse) {
    Constants::Direction direction;
    EXPECT_FALSE(Utils::stringToDirection("north", direction));
}

TEST(GivenUtils, WhenNumericInput_ThenReturnsFalse) {
    Constants::Direction direction;
    EXPECT_FALSE(Utils::stringToDirection("123", direction));
}

// Direction To String

TEST(GivenUtils, WhenDirectionNorth_ThenReturnsNORTH) {
    EXPECT_EQ(Utils::directionToString(Constants::Direction::NORTH), Constants::DIRECTION_NORTH);
}

TEST(GivenUtils, WhenDirectionEast_ThenReturnsEAST) {
    EXPECT_EQ(Utils::directionToString(Constants::Direction::EAST), Constants::DIRECTION_EAST);
}

TEST(GivenUtils, WhenDirectionSouth_ThenReturnsSOUTH) {
    EXPECT_EQ(Utils::directionToString(Constants::Direction::SOUTH), Constants::DIRECTION_SOUTH);
}

TEST(GivenUtils, WhenDirectionWest_ThenReturnsWEST) {
    EXPECT_EQ(Utils::directionToString(Constants::Direction::WEST), Constants::DIRECTION_WEST);
}

// MoveType To String

TEST(GivenUtils, WhenMoveTypeUTurn_ThenReturnsUTurnString) {
    EXPECT_EQ(Utils::moveTypeToString(Constants::MoveType::UTURN), Constants::MOVE_UTURN);
}

TEST(GivenUtils, WhenMoveTypeLeft_ThenReturnsLeftTurnString) {
    EXPECT_EQ(Utils::moveTypeToString(Constants::MoveType::LEFT), Constants::MOVE_LEFT);
}

TEST(GivenUtils, WhenMoveTypeRight_ThenReturnsRightTurnString) {
    EXPECT_EQ(Utils::moveTypeToString(Constants::MoveType::RIGHT), Constants::MOVE_RIGHT);
}

TEST(GivenUtils, WhenMoveTypeStraight_ThenReturnsStraightString) {
    EXPECT_EQ(Utils::moveTypeToString(Constants::MoveType::STRAIGHT), Constants::MOVE_STRAIGHT);
}
