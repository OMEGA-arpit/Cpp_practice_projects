#ifndef UTILS_H
#define UTILS_H

#include "Constants.h"
#include <string>

class Utils {
public:
    static std::string moveTypeToString(Constants::MoveType moveType);
    static std::string directionToString(Constants::Direction direction);
    static bool stringToDirection(const std::string& input, Constants::Direction& outDirection);
    static Constants::MoveType determineMoveType(Constants::Direction fromLane, Constants::Direction toLane);
};

#endif
