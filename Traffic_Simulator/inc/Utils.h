#ifndef UTILS_H
#define UTILS_H

#include "Constants.h"
#include <string>
#include <string_view>

class Utils {
public:
    [[nodiscard]] static std::string moveTypeToString(Constants::MoveType moveType);
    [[nodiscard]] static std::string directionToString(Constants::Direction direction);
    [[nodiscard]] static bool stringToDirection(std::string_view input, Constants::Direction& outDirection);
    [[nodiscard]] static Constants::MoveType determineMoveType(Constants::Direction fromLane, Constants::Direction toLane);
};

#endif
