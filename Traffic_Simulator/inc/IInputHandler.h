#ifndef I_INPUT_HANDLER_H
#define I_INPUT_HANDLER_H

#include <string>

/**
 * @brief Abstracts reading string input from any source.
 *
 * Decouples input acquisition from business logic so the real stdin
 * implementation can be swapped for a mock in tests.
 */
class IInputHandler {
public:
    /**
     * @brief Reads one non-empty, trimmed string from the input source.
     *
     * Implementations must loop until a non-empty string is available,
     * prompting the user again on blank input.
     *
     * @param[out] input Populated with the trimmed, non-empty result.
     */
    virtual void inputString(std::string& input) = 0;

    virtual ~IInputHandler() = default;
};

#endif
