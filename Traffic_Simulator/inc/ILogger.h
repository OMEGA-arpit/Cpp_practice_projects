#ifndef I_LOGGER_H
#define I_LOGGER_H

#include "Constants.h"
#include <string>

class ILogger {
public:
    virtual void printMessage(const std::string& message) = 0;

    virtual ~ILogger() = default;
};

#endif
