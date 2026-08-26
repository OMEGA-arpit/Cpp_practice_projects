#ifndef MOVE_RESULT_H
#define MOVE_RESULT_H

#include "Constants.h"

struct MoveResult {
    Constants::MoveType moveType;
    Constants::MovePermission permission;

    bool canGoNow;
    int waitSeconds;

    Constants::Direction fromLane;
    Constants::Direction toLane;
    Constants::Direction currentGreenLane;
    int timeRemaining;

    MoveResult();
};

#endif
