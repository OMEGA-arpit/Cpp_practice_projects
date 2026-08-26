#include "MoveResult.h"

MoveResult::MoveResult()
    : moveType(Constants::MoveType::STRAIGHT)
    , permission(Constants::MovePermission::NEEDS_GREEN)
    , canGoNow(false)
    , waitSeconds(0)
    , fromLane(Constants::Direction::NORTH)
    , toLane(Constants::Direction::SOUTH)
    , currentGreenLane(Constants::Direction::NORTH)
    , timeRemaining(0)
{}
