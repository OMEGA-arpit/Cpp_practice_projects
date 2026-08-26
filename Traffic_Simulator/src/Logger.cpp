#include "Logger.h"
#include "Constants.h"
#include <iostream>

void Logger::printMessage(const std::string& message) {
    std::cout << message;
}

void Logger::printNewLine() {
    std::cout << Constants::NEW_LINE;
}
