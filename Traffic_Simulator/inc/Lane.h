#ifndef LANE_H
#define LANE_H

#include "Constants.h"
#include <string>

struct Lane {
    Constants::Direction direction;
    std::string name;
    int greenLightDuration;

    Lane(Constants::Direction direction, const std::string& name, int greenLightDuration)
        : direction(direction), name(name), greenLightDuration(greenLightDuration) {}

    bool operator==(const Lane& other) {
        return direction == other.direction;
    }
};

#endif
