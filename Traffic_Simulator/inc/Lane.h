#ifndef LANE_H
#define LANE_H

#include "Constants.h"
#include <string>

/**
 * @brief Represents a single lane at the intersection.
 *
 * Stores the lane's direction enum value, its display name, and the
 * duration (in seconds) for which it holds a green light each phase.
 */
struct Lane {
    Constants::Direction direction;
    std::string name;
    int greenLightDuration;

    Lane(Constants::Direction direction, const std::string& name, int greenLightDuration)
        : direction(direction), name(name), greenLightDuration(greenLightDuration) {}

    bool operator==(const Lane& other) const {
        return direction == other.direction;
    }
};

#endif
