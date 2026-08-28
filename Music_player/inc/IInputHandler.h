#ifndef I_INPUT_HANDLER_H
#define I_INPUT_HANDLER_H

#include <string>

/**
 * @brief Abstracts all user input operations.
 *
 * Wraps stdin reads with validation so the rest of the application
 * is shielded from raw I/O and stream-error handling.
 */
class IInputHandler {
public:
    /**
     * @brief Reads a validated integer from stdin.
     *
     * Loops until the user enters a value that can be parsed as an integer,
     * printing an error prompt on each invalid attempt.
     *
     * @return The integer entered by the user.
     */
    virtual int inputValue() = 0;

    /**
     * @brief Reads a single character from stdin.
     * @return The first non-whitespace character entered by the user.
     */
    virtual char inputCharacter() = 0;

    /**
     * @brief Reads a trimmed string from stdin.
     *
     * Leading and trailing whitespace is removed before the string is returned
     * via the output parameter.
     *
     * @param[out] input Populated with the trimmed line entered by the user.
     */
    virtual void inputString(std::string& input) = 0;

    virtual ~IInputHandler() {}
};

#endif
