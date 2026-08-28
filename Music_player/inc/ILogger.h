#ifndef I_LOGGER_H
#define I_LOGGER_H

#include "Constants.h"
#include <string>

/**
 * @brief Abstracts all console output operations.
 *
 * Centralising output through this interface keeps business logic free of
 * direct stdout calls and makes testing straightforward via mocking.
 */
class ILogger {
public:
    /**
     * @brief Writes @p message to the output stream without a trailing newline.
     * @param message The text to display.
     */
    virtual void printMessage(const std::string& message) = 0;

    /// Writes a single newline character to the output stream.
    virtual void printNewLine() = 0;

    virtual ~ILogger() {}
};

#endif
