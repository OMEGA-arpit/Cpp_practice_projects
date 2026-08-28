#ifndef LOGGER_H
#define LOGGER_H

#include "ILogger.h"
#include "Constants.h"
#include <string>

class Logger : public ILogger {
public:
    void printMessage(const std::string& message) override;
    void printNewLine() override;
};

#endif
