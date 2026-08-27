#ifndef MOVE_RESULT_H
#define MOVE_RESULT_H

#include "Constants.h"

struct MoveResult {
    Constants::MoveType moveType         = Constants::MoveType::STRAIGHT;
    Constants::MovePermission permission = Constants::MovePermission::NEEDS_GREEN;
    bool canGoNow                        = false;
    int waitSeconds                      = 0;
    Constants::Direction fromLane        = Constants::Direction::NORTH;
    Constants::Direction toLane          = Constants::Direction::SOUTH;
    Constants::Direction currentGreenLane = Constants::Direction::NORTH;
    int timeRemaining                    = 0;
};

#endif
