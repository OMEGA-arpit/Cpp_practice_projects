#ifndef I_MOCK_LOGGER_H
#define I_MOCK_LOGGER_H

#include <gmock/gmock.h>
#include "ILogger.h"

class IMockLogger : public ILogger {
public:
    MOCK_METHOD(void, printMessage, (const std::string& message), (override));
    MOCK_METHOD(void, printNewLine, (), (override));
};

#endif
