#include "Logger.h"
#include "Constants.h"
#include <iostream>
#include <iomanip>

void Logger::printMessage(const std::string& message) {
    std::cout << message;
}

void Logger::printNewLine() {
    std::cout << "\n";
}
