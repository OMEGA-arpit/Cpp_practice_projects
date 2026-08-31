#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

/**
 * @file InputHandler.h
 * @brief Stateless console input utilities with built-in validation loop.
 */

#include "Validator.h"
#include <string>

/**
 * @brief Provides static helper methods for reading and validating all console input.
 *
 * Each method loops until the user supplies acceptable input, printing
 * relevant error messages via Display on each rejected attempt.  This
 * ensures that callers always receive a validated value — never raw,
 * potentially malformed user input.
 *
 * All methods are static — the class is a utility namespace.
 */
class InputHandler {
public:
    /**
     * @brief Reads a @c double from stdin, retrying until a valid number is entered.
     * @param[out] value Reference to store the validated result.
     */
    static void inputValue(double& value);

    /**
     * @brief Reads an @c int from stdin, retrying until a valid integer is entered.
     * @param[out] value Reference to store the validated result.
     */
    static void inputValue(int& value);

    /**
     * @brief Strips leading and trailing whitespace characters in-place.
     *
     * Characters considered whitespace are defined in Constants::WHITESPACE_CHARS
     * (space, tab, newline, carriage-return).  If @p input consists entirely of
     * whitespace, it is set to an empty string.
     *
     * @param[in,out] input String to trim.
     */
    static void removeLeadingAndTrailingWhitespaces(std::string& input);

    /**
     * @brief Reads a string from stdin, trims whitespace, and validates it against
     *        the rules for @p type, retrying until input is accepted.
     *
     * Validation is delegated to Validator::isValidInput().  If validation fails,
     * the error message from the ValidationResult is printed and the user is
     * prompted to try again.
     *
     * @param[out] input Reference to store the validated string.
     * @param      type  The expected input type (NAME, EMAIL, PIN, etc.).
     */
    static void inputString(std::string& input, Constants::InputType type);
};

#endif
