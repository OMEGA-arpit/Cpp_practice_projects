#include "Utils.h"
#include "Constants.h"

std::string Utils::moveTypeToString(Constants::MoveType moveType) {
    std::string result;

    switch (moveType)
    {
        case Constants::MoveType::UTURN:    
        { 
            result = Constants::MOVE_UTURN;     
            break; 
        }
        case Constants::MoveType::LEFT:     
        { 
            result = Constants::MOVE_LEFT;  
            break; 
        }
        case Constants::MoveType::RIGHT:    
        { 
            result = Constants::MOVE_RIGHT; 
            break; 
        }
        case Constants::MoveType::STRAIGHT: 
        { 
            result = Constants::MOVE_STRAIGHT;   
            break; 
        }
    }

    return result;
}

std::string Utils::directionToString(Constants::Direction direction) {
    std::string result;

    switch (direction)
    {
        case Constants::Direction::NORTH:
        { 
            result = Constants::DIRECTION_NORTH; 
            break; 
        }
        case Constants::Direction::SOUTH: 
        { 
            result = Constants::DIRECTION_SOUTH; 
            break; 
        }
        case Constants::Direction::EAST:  
        { 
            result = Constants::DIRECTION_EAST;  
            break; 
        }
        case Constants::Direction::WEST:  
        { 
            result = Constants::DIRECTION_WEST;  
            break; 
        }
    }

    return result;
}

bool Utils::stringToDirection(const std::string& input, Constants::Direction& outDirection) {
    bool isValid = true;

    if (input == Constants::DIRECTION_NORTH_CHAR || input == Constants::DIRECTION_NORTH)       
    { 
        outDirection = Constants::Direction::NORTH; 
    }
    else if (input == Constants::DIRECTION_SOUTH_CHAR || input == Constants::DIRECTION_SOUTH)  
    { 
        outDirection = Constants::Direction::SOUTH; 
    }
    else if (input == Constants::DIRECTION_EAST_CHAR || input == Constants::DIRECTION_EAST)   
    { 
        outDirection = Constants::Direction::EAST;  
    }
    else if (input == Constants::DIRECTION_WEST_CHAR || input == Constants::DIRECTION_WEST)   
    { 
        outDirection = Constants::Direction::WEST;  
    }
    else                                        
    { 
        isValid = false; 
    }

    return isValid;
}

Constants::MoveType Utils::determineMoveType(Constants::Direction fromLane, Constants::Direction toLane) {
    using Move = Constants::MoveType;

    static const Move moveTable[4][4] = {
        { Move::UTURN,    Move::LEFT,      Move::STRAIGHT,  Move::RIGHT    },
        { Move::RIGHT,     Move::UTURN,     Move::LEFT,     Move::STRAIGHT },
        { Move::STRAIGHT, Move::RIGHT,     Move::UTURN,     Move::LEFT     },
        { Move::LEFT,    Move::STRAIGHT,  Move::RIGHT,      Move::UTURN    } 
    };
    
    return moveTable[(int)fromLane][(int)toLane];
}
