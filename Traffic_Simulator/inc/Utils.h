#ifndef UTILS_H
#define UTILS_H

#include "Constants.h"
#include <string>
#include <string_view>

/**
 * @brief Stateless utility functions for direction and move-type conversions.
 */
class Utils {
public:
    /**
     * @brief Converts a MoveType to its display string.
     * @param moveType The move type to convert.
     * @return Human-readable label (e.g. "U-Turn", "Left Turn").
     */
    [[nodiscard]] static std::string moveTypeToString(Constants::MoveType moveType);

    /**
     * @brief Converts a Direction to its display string.
     * @param direction The direction to convert.
     * @return Uppercase direction name (e.g. "NORTH").
     */
    [[nodiscard]] static std::string directionToString(Constants::Direction direction);

    /**
     * @brief Parses a direction string into a Direction enum value.
     *
     * Accepts both single-character ("N") and full-word ("NORTH") forms.
     * Input is case-sensitive — lowercase is rejected.
     *
     * @param input        The string to parse.
     * @param[out] outDirection  Set to the parsed direction on success; unchanged on failure.
     * @return true if input was recognised, false otherwise.
     */
    [[nodiscard]] static bool stringToDirection(std::string_view input, Constants::Direction& outDirection);

    /**
     * @brief Determines the move type for a given origin/destination pair.
     *
     * Uses a precomputed 4x4 lookup table indexed by Direction enum ordinals.
     * Ordinal order must be: NORTH=0, EAST=1, SOUTH=2, WEST=3 (clockwise).
     *
     * @param fromLane The lane the driver departs from.
     * @param toLane   The lane the driver wants to reach.
     * @return UTURN, LEFT, RIGHT, or STRAIGHT.
     */
    [[nodiscard]] static Constants::MoveType determineMoveType(Constants::Direction fromLane, Constants::Direction toLane);
};

#endif
