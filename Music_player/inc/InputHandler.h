#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include "IInputHandler.h"
#include "ILogger.h"
#include <string>

class InputHandler : public IInputHandler {
    ILogger* logger;

    void removeLeadingAndTrailingWhitespaces(std::string& input);
public:
    InputHandler(ILogger* logger) : logger(logger) {}
    int inputValue() override; 
    char inputCharacter() override;     
    void inputString(std::string& input) override;  
};

#endif
