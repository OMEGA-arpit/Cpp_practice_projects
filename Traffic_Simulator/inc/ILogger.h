#ifndef I_LOGGER_H
#define I_LOGGER_H

#include "Constants.h"
#include <string>

/**
 * @brief Abstracts writing text output to any sink.
 *
 * Decouples display logic from stdout so output can be silenced or
 * redirected (e.g. captured in mock expectations during tests).
 */
class ILogger {
public:
    /**
     * @brief Writes a message to the output sink.
     *
     * @param message The text to display. May include embedded newlines.
     */
    virtual void printMessage(const std::string& message) = 0;

    virtual ~ILogger() = default;
};

#endif
