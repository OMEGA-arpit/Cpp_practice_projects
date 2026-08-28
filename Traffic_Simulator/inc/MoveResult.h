#ifndef MOVE_RESULT_H
#define MOVE_RESULT_H

#include "Constants.h"

/**
 * @brief Aggregates the full result of evaluating a driver's movement query.
 *
 * Built by UserController::buildMoveResult and consumed directly by
 * UserController::displayMoveResult. All fields have safe in-class defaults.
 */
struct MoveResult {
    Constants::MoveType moveType         = Constants::MoveType::STRAIGHT;
    Constants::MovePermission permission = Constants::MovePermission::NEEDS_GREEN;
    bool canGoNow                        = false;   ///< true when fromLane is currently green
    int waitSeconds                      = 0;       ///< seconds until fromLane turns green (0 if already green)
    Constants::Direction fromLane        = Constants::Direction::NORTH;
    Constants::Direction toLane          = Constants::Direction::SOUTH;
    Constants::Direction currentGreenLane = Constants::Direction::NORTH;
    int timeRemaining                    = 0;       ///< seconds left on the current green phase
};

#endif
