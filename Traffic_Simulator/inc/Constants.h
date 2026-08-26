#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

namespace Constants {
    enum class Direction {
        NORTH,
        EAST,
        SOUTH,
        WEST
    };

    enum class MoveType {
        UTURN,
        LEFT,
        RIGHT,
        STRAIGHT
    };

    enum class MovePermission {
        FREE,           
        NEEDS_GREEN     
    };
    
    
    const int GREEN_DURATION_SECONDS = 10;

    inline constexpr char NEW_LINE = '\n';

    inline const std::string PARENTHESIS = " (";
    inline const std::string CHOICE_NO = "N";
    inline const std::string CHOICE_YES = "Y";

    // Utils
    inline const std::string MOVE_UTURN = "U-Turn";
    inline const std::string MOVE_LEFT = "Left Turn";
    inline const std::string MOVE_RIGHT = "Right Turn";
    inline const std::string MOVE_STRAIGHT = "Straight";

    inline const std::string DIRECTION_NORTH = "NORTH";
    inline const std::string DIRECTION_EAST = "EAST";
    inline const std::string DIRECTION_SOUTH = "SOUTH";
    inline const std::string DIRECTION_WEST = "WEST";

    inline const std::string DIRECTION_NORTH_CHAR = "N";
    inline const std::string DIRECTION_EAST_CHAR = "E";
    inline const std::string DIRECTION_SOUTH_CHAR = "S";
    inline const std::string DIRECTION_WEST_CHAR = "W";


    inline const std::string MSG_WELCOME =
        "\n========================================\n"
        "       TRAFFIC LIGHT SIMULATION         \n"
        "========================================\n";

    inline const std::string MSG_ROAD =
        "\n          |  N  |\n"
        "          |  ↓  |\n"
        "          |     |\n"
        "----------+     +----------\n"
        "  W →                ← E   \n"
        "----------+     +----------\n"
        "          |     |\n"
        "          |  ↑  |\n"
        "          |  S  |\n";
    
    inline const std::string MSG_ENTER_LANE = "\nWhich lane are you in? (N/S/E/W): ";
    inline const std::string MSG_ENTER_DESTINATION = "Where do you want to go?  (N/S/E/W): ";
    inline const std::string MSG_ASK_ANOTHER_QUERY = "\nAnother query? (Y/N): ";
    inline const std::string MSG_GOODBYE = "\nThank you for using Traffic Light Simulation. Goodbye.\n";

    inline const std::string WHITESPACE_CHARS = " \t\r\n";
    inline const std::string EMPTY_STRING = "";

    inline const std::string MSG_DIVIDER = "\n========================================\n";

    inline const std::string MSG_TRAFFIC_STATUS = 
        "\n========================================\n"
        "            TRAFFIC STATUS\n"
        "========================================\n";

    inline const std::string MSG_INVALID_INPUT = "Invalid input. Please enter N, S, E or W.\n";
    inline const std::string MSG_INVALID_CONTINUE_INPUT = "Invalid input. Please enter Y or N.\n";
    inline const std::string MSG_EMPTY_INPUT = "Input cannot be empty. Please enter again: ";

    inline const std::string MSG_GREEN_FREE = "\U0001F7E2  Free move — No signal needed. You may proceed.\n";
    inline const std::string MSG_GREEN_GO = "\U0001F7E2  Your lane is GREEN — You may proceed.\n";
    inline const std::string MSG_RED_WAIT = "\U0001F534  Your lane is RED — Please wait.\n";

    // Display Message
    inline const std::string MSG_FROM = "  From : ";
    inline const std::string MSG_TO = "  To   : ";
    inline const std::string MSG_MOVE = "  Move : ";
    inline const std::string MSG_CURRENT_GREEN = "  Current green  : Vehicles from ";
    inline const std::string MSG_CAN_MOVE = " can move";
    inline const std::string MSG_SEC_REMAINING = " sec remaining)";
    inline const std::string MSG_TIME_REMAINING = "  Time remaining : ";
    inline const std::string MSG_LANE_GREEN_IN = "  Your lane turns green in : ";
    inline const std::string MSG_SECONDS = " seconds";
}

#endif
